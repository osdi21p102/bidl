/*
 * Copyright 2008-2010 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
 *
 * Copyright (c) 2014, Cisco Systems, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in
 * the documentation and/or other materials provided with the
 * distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _CQ_ENET_DESC_H_
#define _CQ_ENET_DESC_H_

#include "cq_desc.h"

/* Ethernet completion queue descriptor: 16B */
struct cq_enet_wq_desc {
	__le16 completed_index;
	__le16 q_number;
	u8 reserved[11];
	u8 type_color;
};

static inline void cq_enet_wq_desc_enc(struct cq_enet_wq_desc *desc,
	u8 type, u8 color, u16 q_number, u16 completed_index)
{
	cq_desc_enc((struct cq_desc *)desc, type,
		color, q_number, completed_index);
}

static inline void cq_enet_wq_desc_dec(struct cq_enet_wq_desc *desc,
	u8 *type, u8 *color, u16 *q_number, u16 *completed_index)
{
	cq_desc_dec((struct cq_desc *)desc, type,
		color, q_number, completed_index);
}

/* Completion queue descriptor: Ethernet receive queue, 16B */
struct cq_enet_rq_desc {
	__le16 completed_index_flags;
	__le16 q_number_rss_type_flags;
	__le32 rss_hash;
	__le16 bytes_written_flags;
	__le16 vlan;
	__le16 checksum_fcoe;
	u8 flags;
	u8 type_color;
};

#define CQ_ENET_RQ_DESC_FLAGS_INGRESS_PORT          (0x1 << 12)
#define CQ_ENET_RQ_DESC_FLAGS_FCOE                  (0x1 << 13)
#define CQ_ENET_RQ_DESC_FLAGS_EOP                   (0x1 << 14)
#define CQ_ENET_RQ_DESC_FLAGS_SOP                   (0x1 << 15)

#define CQ_ENET_RQ_DESC_RSS_TYPE_BITS               4
#define CQ_ENET_RQ_DESC_RSS_TYPE_MASK \
	((1 << CQ_ENET_RQ_DESC_RSS_TYPE_BITS) - 1)
#define CQ_ENET_RQ_DESC_RSS_TYPE_NONE               0
#define CQ_ENET_RQ_DESC_RSS_TYPE_IPv4               1
#define CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv4           2
#define CQ_ENET_RQ_DESC_RSS_TYPE_IPv6               3
#define CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv6           4
#define CQ_ENET_RQ_DESC_RSS_TYPE_IPv6_EX            5
#define CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv6_EX        6

#define CQ_ENET_RQ_DESC_FLAGS_CSUM_NOT_CALC         (0x1 << 14)

#define CQ_ENET_RQ_DESC_BYTES_WRITTEN_BITS          14
#define CQ_ENET_RQ_DESC_BYTES_WRITTEN_MASK \
	((1 << CQ_ENET_RQ_DESC_BYTES_WRITTEN_BITS) - 1)
#define CQ_ENET_RQ_DESC_FLAGS_TRUNCATED             (0x1 << 14)
#define CQ_ENET_RQ_DESC_FLAGS_VLAN_STRIPPED         (0x1 << 15)

#define CQ_ENET_RQ_DESC_VLAN_TCI_VLAN_BITS          12
#define CQ_ENET_RQ_DESC_VLAN_TCI_VLAN_MASK \
	((1 << CQ_ENET_RQ_DESC_VLAN_TCI_VLAN_BITS) - 1)
#define CQ_ENET_RQ_DESC_VLAN_TCI_CFI_MASK           (0x1 << 12)
#define CQ_ENET_RQ_DESC_VLAN_TCI_USER_PRIO_BITS     3
#define CQ_ENET_RQ_DESC_VLAN_TCI_USER_PRIO_MASK \
	((1 << CQ_ENET_RQ_DESC_VLAN_TCI_USER_PRIO_BITS) - 1)
#define CQ_ENET_RQ_DESC_VLAN_TCI_USER_PRIO_SHIFT    13

#define CQ_ENET_RQ_DESC_FCOE_SOF_BITS               8
#define CQ_ENET_RQ_DESC_FCOE_SOF_MASK \
	((1 << CQ_ENET_RQ_DESC_FCOE_SOF_BITS) - 1)
#define CQ_ENET_RQ_DESC_FCOE_EOF_BITS               8
#define CQ_ENET_RQ_DESC_FCOE_EOF_MASK \
	((1 << CQ_ENET_RQ_DESC_FCOE_EOF_BITS) - 1)
#define CQ_ENET_RQ_DESC_FCOE_EOF_SHIFT              8

#define CQ_ENET_RQ_DESC_FLAGS_TCP_UDP_CSUM_OK       (0x1 << 0)
#define CQ_ENET_RQ_DESC_FCOE_FC_CRC_OK              (0x1 << 0)
#define CQ_ENET_RQ_DESC_FLAGS_UDP                   (0x1 << 1)
#define CQ_ENET_RQ_DESC_FCOE_ENC_ERROR              (0x1 << 1)
#define CQ_ENET_RQ_DESC_FLAGS_TCP                   (0x1 << 2)
#define CQ_ENET_RQ_DESC_FLAGS_IPV4_CSUM_OK          (0x1 << 3)
#define CQ_ENET_RQ_DESC_FLAGS_IPV6                  (0x1 << 4)
#define CQ_ENET_RQ_DESC_FLAGS_IPV4                  (0x1 << 5)
#define CQ_ENET_RQ_DESC_FLAGS_IPV4_FRAGMENT         (0x1 << 6)
#define CQ_ENET_RQ_DESC_FLAGS_FCS_OK                (0x1 << 7)

static inline void cq_enet_rq_desc_enc(struct cq_enet_rq_desc *desc,
	u8 type, u8 color, u16 q_number, u16 completed_index,
	u8 ingress_port, u8 fcoe, u8 eop, u8 sop, u8 rss_type, u8 csum_not_calc,
	u32 rss_hash, u16 bytes_written, u8 packet_error, u8 vlan_stripped,
	u16 vlan, u16 checksum, u8 fcoe_sof, u8 fcoe_fc_crc_ok,
	u8 fcoe_enc_error, u8 fcoe_eof, u8 tcp_udp_csum_ok, u8 udp, u8 tcp,
	u8 ipv4_csum_ok, u8 ipv6, u8 ipv4, u8 ipv4_fragment, u8 fcs_ok)
{
	cq_desc_enc((struct cq_desc *)desc, type,
		color, q_number, completed_index);

	desc->completed_index_flags |= cpu_to_le16(
		(ingress_port ? CQ_ENET_RQ_DESC_FLAGS_INGRESS_PORT : 0) |
		(fcoe ? CQ_ENET_RQ_DESC_FLAGS_FCOE : 0) |
		(eop ? CQ_ENET_RQ_DESC_FLAGS_EOP : 0) |
		(sop ? CQ_ENET_RQ_DESC_FLAGS_SOP : 0));

	desc->q_number_rss_type_flags |= cpu_to_le16(
		((rss_type & CQ_ENET_RQ_DESC_RSS_TYPE_MASK) <<
		CQ_DESC_Q_NUM_BITS) |
		(csum_not_calc ? CQ_ENET_RQ_DESC_FLAGS_CSUM_NOT_CALC : 0));

	desc->rss_hash = cpu_to_le32(rss_hash);

	desc->bytes_written_flags = cpu_to_le16(
		(bytes_written & CQ_ENET_RQ_DESC_BYTES_WRITTEN_MASK) |
		(packet_error ? CQ_ENET_RQ_DESC_FLAGS_TRUNCATED : 0) |
		(vlan_stripped ? CQ_ENET_RQ_DESC_FLAGS_VLAN_STRIPPED : 0));

	desc->vlan = cpu_to_le16(vlan);

	if (fcoe) {
		desc->checksum_fcoe = cpu_to_le16(
			(fcoe_sof & CQ_ENET_RQ_DESC_FCOE_SOF_MASK) |
			((fcoe_eof & CQ_ENET_RQ_DESC_FCOE_EOF_MASK) <<
				CQ_ENET_RQ_DESC_FCOE_EOF_SHIFT));
	} else {
		desc->checksum_fcoe = cpu_to_le16(checksum);
	}

	desc->flags =
		(tcp_udp_csum_ok ? CQ_ENET_RQ_DESC_FLAGS_TCP_UDP_CSUM_OK : 0) |
		(udp ? CQ_ENET_RQ_DESC_FLAGS_UDP : 0) |
		(tcp ? CQ_ENET_RQ_DESC_FLAGS_TCP : 0) |
		(ipv4_csum_ok ? CQ_ENET_RQ_DESC_FLAGS_IPV4_CSUM_OK : 0) |
		(ipv6 ? CQ_ENET_RQ_DESC_FLAGS_IPV6 : 0) |
		(ipv4 ? CQ_ENET_RQ_DESC_FLAGS_IPV4 : 0) |
		(ipv4_fragment ? CQ_ENET_RQ_DESC_FLAGS_IPV4_FRAGMENT : 0) |
		(fcs_ok ? CQ_ENET_RQ_DESC_FLAGS_FCS_OK : 0) |
		(fcoe_fc_crc_ok ? CQ_ENET_RQ_DESC_FCOE_FC_CRC_OK : 0) |
		(fcoe_enc_error ? CQ_ENET_RQ_DESC_FCOE_ENC_ERROR : 0);
}

static inline void cq_enet_rq_desc_dec(struct cq_enet_rq_desc *desc,
	u8 *type, u8 *color, u16 *q_number, u16 *completed_index,
	u8 *ingress_port, u8 *fcoe, u8 *eop, u8 *sop, u8 *rss_type,
	u8 *csum_not_calc, u32 *rss_hash, u16 *bytes_written, u8 *packet_error,
	u8 *vlan_stripped, u16 *vlan_tci, u16 *checksum, u8 *fcoe_sof,
	u8 *fcoe_fc_crc_ok, u8 *fcoe_enc_error, u8 *fcoe_eof,
	u8 *tcp_udp_csum_ok, u8 *udp, u8 *tcp, u8 *ipv4_csum_ok,
	u8 *ipv6, u8 *ipv4, u8 *ipv4_fragment, u8 *fcs_ok)
{
	u16 completed_index_flags;
	u16 q_number_rss_type_flags;
	u16 bytes_written_flags;

	cq_desc_dec((struct cq_desc *)desc, type,
		color, q_number, completed_index);

	completed_index_flags = le16_to_cpu(desc->completed_index_flags);
	q_number_rss_type_flags =
		le16_to_cpu(desc->q_number_rss_type_flags);
	bytes_written_flags = le16_to_cpu(desc->bytes_written_flags);

	*ingress_port = (completed_index_flags &
		CQ_ENET_RQ_DESC_FLAGS_INGRESS_PORT) ? 1 : 0;
	*fcoe = (completed_index_flags & CQ_ENET_RQ_DESC_FLAGS_FCOE) ?
		1 : 0;
	*eop = (completed_index_flags & CQ_ENET_RQ_DESC_FLAGS_EOP) ?
		1 : 0;
	*sop = (completed_index_flags & CQ_ENET_RQ_DESC_FLAGS_SOP) ?
		1 : 0;

	*rss_type = (u8)((q_number_rss_type_flags >> CQ_DESC_Q_NUM_BITS) &
		CQ_ENET_RQ_DESC_RSS_TYPE_MASK);
	*csum_not_calc = (q_number_rss_type_flags &
		CQ_ENET_RQ_DESC_FLAGS_CSUM_NOT_CALC) ? 1 : 0;

	*rss_hash = le32_to_cpu(desc->rss_hash);

	*bytes_written = bytes_written_flags &
		CQ_ENET_RQ_DESC_BYTES_WRITTEN_MASK;
	*packet_error = (bytes_written_flags &
		CQ_ENET_RQ_DESC_FLAGS_TRUNCATED) ? 1 : 0;
	*vlan_stripped = (bytes_written_flags &
		CQ_ENET_RQ_DESC_FLAGS_VLAN_STRIPPED) ? 1 : 0;

	/*
	 * Tag Control Information(16) = user_priority(3) + cfi(1) + vlan(12)
	 */
	*vlan_tci = le16_to_cpu(desc->vlan);

	if (*fcoe) {
		*fcoe_sof = (u8)(le16_to_cpu(desc->checksum_fcoe) &
			CQ_ENET_RQ_DESC_FCOE_SOF_MASK);
		*fcoe_fc_crc_ok = (desc->flags &
			CQ_ENET_RQ_DESC_FCOE_FC_CRC_OK) ? 1 : 0;
		*fcoe_enc_error = (desc->flags &
			CQ_ENET_RQ_DESC_FCOE_ENC_ERROR) ? 1 : 0;
		*fcoe_eof = (u8)((le16_to_cpu(desc->checksum_fcoe) >>
			CQ_ENET_RQ_DESC_FCOE_EOF_SHIFT) &
			CQ_ENET_RQ_DESC_FCOE_EOF_MASK);
		*checksum = 0;
	} else {
		*fcoe_sof = 0;
		*fcoe_fc_crc_ok = 0;
		*fcoe_enc_error = 0;
		*fcoe_eof = 0;
		*checksum = le16_to_cpu(desc->checksum_fcoe);
	}

	*tcp_udp_csum_ok =
		(desc->flags & CQ_ENET_RQ_DESC_FLAGS_TCP_UDP_CSUM_OK) ? 1 : 0;
	*udp = (desc->flags & CQ_ENET_RQ_DESC_FLAGS_UDP) ? 1 : 0;
	*tcp = (desc->flags & CQ_ENET_RQ_DESC_FLAGS_TCP) ? 1 : 0;
	*ipv4_csum_ok =
		(desc->flags & CQ_ENET_RQ_DESC_FLAGS_IPV4_CSUM_OK) ? 1 : 0;
	*ipv6 = (desc->flags & CQ_ENET_RQ_DESC_FLAGS_IPV6) ? 1 : 0;
	*ipv4 = (desc->flags & CQ_ENET_RQ_DESC_FLAGS_IPV4) ? 1 : 0;
	*ipv4_fragment =
		(desc->flags & CQ_ENET_RQ_DESC_FLAGS_IPV4_FRAGMENT) ? 1 : 0;
	*fcs_ok = (desc->flags & CQ_ENET_RQ_DESC_FLAGS_FCS_OK) ? 1 : 0;
}

#endif /* _CQ_ENET_DESC_H_ */
