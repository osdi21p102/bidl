package chaincode

import (
	"bytes"
	"math"

	pb "github.com/hyperledger/fabric/protos/peer"
	"github.com/golang/protobuf/proto"
	"github.com/hyperledger/fabric/protos/common"
	"github.com/hyperledger/fabric/protos/orderer"
	"github.com/hyperledger/fabric/protos/peer"
	putil "github.com/hyperledger/fabric/protos/utils"
	"github.com/pkg/errors"
)

func CreateProposal(signer *Crypto, channel, ccname, version string, args *pb.ChaincodeInput) *peer.Proposal {

	spec := &peer.ChaincodeSpec{
		Type:        peer.ChaincodeSpec_GOLANG,
		ChaincodeId: &peer.ChaincodeID{Name: ccname, Version: version},
		Input:       args,
	}

	invocation := &peer.ChaincodeInvocationSpec{ChaincodeSpec: spec}

	creator, err := signer.Serialize()
	if err != nil {
		panic(err)
	}

	prop, _, err := putil.CreateChaincodeProposal(common.HeaderType_ENDORSER_TRANSACTION, channel, invocation, creator)
	if err != nil {
		panic(err)
	}

	return prop
}

func SignProposal(prop *peer.Proposal, signer *Crypto) (*peer.SignedProposal, error) {
	propBytes, err := proto.Marshal(prop)
	if err != nil {
		return nil, err
	}

	// sig, err := signer.Sign(propBytes)
	// if err != nil {
	// 	return nil, err
	// }

	sig := []byte("")
	return &peer.SignedProposal{ProposalBytes: propBytes, Signature: sig}, nil
}

func CreateSignedTx(proposal *peer.Proposal, signer *Crypto, resps []*peer.ProposalResponse) (*common.Envelope, error) {
	if len(resps) == 0 {
		return nil, errors.New("at least one proposal response is required")
	}

	// the original header
	hdr, err := GetHeader(proposal.Header)
	if err != nil {
		return nil, err
	}

	// the original payload
	pPayl, err := GetChaincodeProposalPayload(proposal.Payload)
	if err != nil {
		return nil, err
	}

	// check that the signer is the same that is referenced in the header
	// TODO: maybe worth removing?
	signerBytes, err := signer.Serialize()
	if err != nil {
		return nil, err
	}

	shdr, err := GetSignatureHeader(hdr.SignatureHeader)
	if err != nil {
		return nil, err
	}

	if bytes.Compare(signerBytes, shdr.Creator) != 0 {
		return nil, errors.New("signer must be the same as the one referenced in the header")
	}

	// get header extensions so we have the visibility field
	_, err = GetChaincodeHeaderExtension(hdr)
	if err != nil {
		return nil, err
	}

	endorsements := make([]*peer.Endorsement, 0)

	// ensure that all actions are bitwise equal and that they are successful
	var a1 []byte
	for n, r := range resps {
		if n == 0 {
			a1 = r.Payload
			if r.Response.Status < 200 || r.Response.Status >= 400 {
				return nil, errors.Errorf("proposal response was not successful, error code %d, msg %s", r.Response.Status, r.Response.Message)
			}
		}
		if bytes.Compare(a1, r.Payload) != 0 {
			return nil, errors.New("ProposalResponsePayloads do not match")
		}
		endorsements = append(endorsements, r.Endorsement)
	}
	// create ChaincodeEndorsedAction
	cea := &peer.ChaincodeEndorsedAction{ProposalResponsePayload: a1, Endorsements: endorsements}

	// obtain the bytes of the proposal payload that will go to the transaction
	propPayloadBytes, err := putil.GetBytesProposalPayloadForTx(pPayl, nil)
	if err != nil {
		return nil, err
	}

	// serialize the chaincode action payload
	cap := &peer.ChaincodeActionPayload{ChaincodeProposalPayload: propPayloadBytes, Action: cea}
	capBytes, err := putil.GetBytesChaincodeActionPayload(cap)
	if err != nil {
		return nil, err
	}

	// create a transaction
	taa := &peer.TransactionAction{Header: hdr.SignatureHeader, Payload: capBytes}
	taas := make([]*peer.TransactionAction, 1)
	taas[0] = taa
	tx := &peer.Transaction{Actions: taas}
	// serialize the tx
	txBytes, err := putil.GetBytesTransaction(tx)
	if err != nil {
		return nil, err
	}

	// create the payload
	payl := &common.Payload{Header: hdr, Data: txBytes}
	paylBytes, err := putil.GetBytesPayload(payl)
	if err != nil {
		return nil, err
	}

	// // sign the payload
	// sig, err := signer.Sign(paylBytes)
	// if err != nil {
	// 	return nil, err
	// }
	// // here's the envelope
	sig := []byte("")


	return &common.Envelope{Payload: paylBytes, Signature: sig}, nil
}

func CreateSignedDeliverNewestEnv(ch string, signer *Crypto) (*common.Envelope, error) {
	start := &orderer.SeekPosition{
		Type: &orderer.SeekPosition_Newest{
			Newest: &orderer.SeekNewest{},
		},
	}

	stop := &orderer.SeekPosition{
		Type: &orderer.SeekPosition_Specified{
			Specified: &orderer.SeekSpecified{
				Number: math.MaxUint64,
			},
		},
	}

	seekInfo := &orderer.SeekInfo{
		Start:    start,
		Stop:     stop,
		Behavior: orderer.SeekInfo_BLOCK_UNTIL_READY,
	}

	return putil.CreateSignedEnvelope(
		common.HeaderType_DELIVER_SEEK_INFO,
		ch,
		signer,
		seekInfo,
		0,
		0,
	)
}

func GetHeader(bytes []byte) (*common.Header, error) {
	hdr := &common.Header{}
	err := proto.Unmarshal(bytes, hdr)
	return hdr, errors.Wrap(err, "error unmarshaling Header")
}

func GetChaincodeProposalPayload(bytes []byte) (*peer.ChaincodeProposalPayload, error) {
	cpp := &peer.ChaincodeProposalPayload{}
	err := proto.Unmarshal(bytes, cpp)
	return cpp, errors.Wrap(err, "error unmarshaling ChaincodeProposalPayload")
}

func GetSignatureHeader(bytes []byte) (*common.SignatureHeader, error) {
	return UnmarshalSignatureHeader(bytes)
}

func GetChaincodeHeaderExtension(hdr *common.Header) (*peer.ChaincodeHeaderExtension, error) {
	chdr, err := UnmarshalChannelHeader(hdr.ChannelHeader)
	if err != nil {
		return nil, err
	}

	chaincodeHdrExt := &peer.ChaincodeHeaderExtension{}
	err = proto.Unmarshal(chdr.Extension, chaincodeHdrExt)
	return chaincodeHdrExt, errors.Wrap(err, "error unmarshaling ChaincodeHeaderExtension")
}

// UnmarshalChannelHeader returns a ChannelHeader from bytes
func UnmarshalChannelHeader(bytes []byte) (*common.ChannelHeader, error) {
	chdr := &common.ChannelHeader{}
	err := proto.Unmarshal(bytes, chdr)
	return chdr, errors.Wrap(err, "error unmarshaling ChannelHeader")
}

func UnmarshalSignatureHeader(bytes []byte) (*common.SignatureHeader, error) {
	sh := &common.SignatureHeader{}
	if err := proto.Unmarshal(bytes, sh); err != nil {
		return nil, errors.Wrap(err, "error unmarshaling SignatureHeader")
	}
	return sh, nil
}
