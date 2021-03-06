package bftsmart.tom;

import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

import io.netty.buffer.ByteBuf;
import io.netty.channel.socket.DatagramPacket;
import io.netty.channel.socket.InternetProtocolFamily;
import io.netty.bootstrap.Bootstrap;
import io.netty.channel.*;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioDatagramChannel;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import bftsmart.reconfiguration.ServerViewController;
import bftsmart.tom.core.ExecutionManager;

public class BidlFrontend extends Thread {
    public static final ConcurrentMap<String, byte[]> txMap = new ConcurrentHashMap<>();
    public static int maxSeqNum = 0;

    private Logger logger = LoggerFactory.getLogger(this.getClass());
    private ServerViewController controller;
    private ExecutionManager execManager;

    BidlFrontend(ServerViewController controller, ExecutionManager executionManager) {
        super("BIDL frontend");
        this.controller = controller;
        this.execManager = executionManager;
    }

    @Override
    public void run() {
        InetSocketAddress groupAddress = new InetSocketAddress("230.0.0.0", 7777);
        logger.info("bidl: new BIDL frontend started, listening group address: {}", groupAddress);
        Bootstrap bootstrap = new Bootstrap();
        NioEventLoopGroup acceptGroup = new NioEventLoopGroup(4);
        try {
            NetworkInterface ni = NetworkInterface.getByName("enp5s0"); // used enp5s0 for hostwork
            // NetworkInterface ni = NetworkInterface.getByName("eth0"); // used en0 for
            // docker overlay network
            Enumeration<InetAddress> addresses = ni.getInetAddresses();
            InetAddress localAddress = null;
            while (addresses.hasMoreElements()) {
                InetAddress address = addresses.nextElement();
                if (address instanceof Inet4Address) {
                    localAddress = address;
                }
            }
            logger.info("Local address is {}", localAddress);

            bootstrap = new Bootstrap().group(acceptGroup).channelFactory(new ChannelFactory<NioDatagramChannel>() {
                @Override
                public NioDatagramChannel newChannel() {
                    return new NioDatagramChannel(InternetProtocolFamily.IPv4);
                }
            }).localAddress(localAddress, groupAddress.getPort()).option(ChannelOption.IP_MULTICAST_IF, ni)
                    .option(ChannelOption.SO_RCVBUF, 1024 * 1024 * 100)
                    .option(ChannelOption.RCVBUF_ALLOCATOR, new FixedRecvByteBufAllocator(1024 * 1024))
                    .option(ChannelOption.SO_REUSEADDR, true).handler(new ChannelInitializer<NioDatagramChannel>() {
                        @Override
                        public void initChannel(NioDatagramChannel ch) throws Exception {
                            ChannelPipeline pipeline = ch.pipeline();
                            pipeline.addLast(new SequencerDecodeHandler());
                        }
                    });
            ChannelFuture channelFuture = bootstrap.bind(new InetSocketAddress(groupAddress.getPort()));
            channelFuture.awaitUninterruptibly();
            NioDatagramChannel ch = (NioDatagramChannel) channelFuture.channel();
            ch.joinGroup(groupAddress, ni).sync();
            ch.closeFuture().await();
        } catch (InterruptedException | SocketException e) {
            e.printStackTrace();
        } finally {
            acceptGroup.shutdownGracefully();
        }
    }

    private class SequencerDecodeHandler extends ChannelInboundHandlerAdapter {
        private int num = 0;
        private int totalNum = 0;
        private MessageDigest digest = null;
        private ServiceProxy proxy = null;
        private byte[] signature = null;
        private ByteBuffer blockBuffer = null;
        private ByteBuffer payloadBuffer = null;
        private int blockSize = 500;

        SequencerDecodeHandler() {
            try {
                this.num = 0;
                this.totalNum = 0;
                this.digest = MessageDigest.getInstance("SHA-256");
                this.proxy = new ServiceProxy(1001, controller.getStaticConf().getProcessId());
                this.signature = new byte[0];
                this.blockBuffer = ByteBuffer.allocate(this.blockSize * 32 + Integer.BYTES * 2 + Integer.BYTES);
                this.payloadBuffer = ByteBuffer.allocate(this.blockSize * 32 + Integer.BYTES);
                logger.info("The default batch size is of BIDLFrontend is {}", this.blockSize);
            } catch (NoSuchAlgorithmException e) {
                e.printStackTrace();
            }
        }

        // retrieve int from the byte array
        int fromByteArray(byte[] bytes) {
            return bytes[0] << 24 | (bytes[1] & 0xFF) << 16 | (bytes[2] & 0xFF) << 8 | (bytes[3] & 0xFF);
        }

        @Override
        public void channelRead(ChannelHandlerContext ctx, Object msg) throws Exception {
            // Get input stream
            io.netty.channel.socket.DatagramPacket packet = (DatagramPacket) msg;
            ByteBuf bytebuf = packet.content();
            final int rcvPktLength = bytebuf.readableBytes();

            byte[] rcvPktBuf = new byte[rcvPktLength];
            bytebuf.readBytes(rcvPktBuf);

            // retrieve the sequence number of this transaction
            int seqNum = fromByteArray(rcvPktBuf);
            maxSeqNum = seqNum > maxSeqNum ? seqNum : maxSeqNum;
            logger.debug("bidl: sequence Number of current transaction is {}, maximum:{}", seqNum, maxSeqNum);

            // get sha256 of the transaction bytes
            byte[] hash = this.digest.digest(rcvPktBuf);

            this.num++;
            this.totalNum++;

            // add the tranasaction to the txmap
            txMap.put(new String(hash), rcvPktBuf);
            logger.debug("bidl: new transaction received, size: {}, totalNumber: {}, num: {}, txMap size: {} ",
                    rcvPktLength, this.totalNum, num, txMap.size());

            // add hashes to the next block
            this.payloadBuffer.put(hash);

            // int aLen = block.length;
            // int bLen = hash.length;
            // ByteBuffer blockBuf = ByteBuffer.allocate(aLen + bLen);
            // blockBuf.put(block);
            // blockBuf.put(hash);
            // this.block = blockBuf.array();
            // logger.trace("bidl: BidlFrontend, tx hash, length:" + bLen + " content: " +
            // Arrays.toString(hash)
            // + " Block after adding a hash " + " length: " + this.block.length + "
            // content: "
            // + Arrays.toString(this.block));

            // if I have collected enough transactions and I am the leader, submit txs
            if (this.num == this.blockSize) {
                logger.info("bidl: collected enough transactions. Num:{}, TotalNum:{}", this.num, this.totalNum);
                logger.debug("bidl: currentleader: {}, myID: {}", execManager.getCurrentLeader(),
                        controller.getStaticConf().getProcessId());
                payloadBuffer.putInt(maxSeqNum);
                if (execManager.getCurrentLeader() == controller.getStaticConf().getProcessId()) {
                    payloadBuffer.flip();
                    byte[] payload = new byte[payloadBuffer.remaining()];
                    payloadBuffer.get(payload);

                    blockBuffer.putInt(payload.length);
                    blockBuffer.put(payload);
                    blockBuffer.putInt(signature.length);
                    blockBuffer.put(signature);
                    blockBuffer.flip();
                    byte[] block = new byte[blockBuffer.remaining()];
                    blockBuffer.get(block);

                    logger.debug("bidl: BidlFrontend, block " + " length " + block.length + " content "
                            + Arrays.toString(block));

                    byte[] reply = proxy.invokeOrdered(block);
                    logger.info("bidl: I am the leader, new block submitted, totalNumber: " + this.totalNum
                            + " block length: " + block.length + " signature.length " + this.signature.length
                            + "maximum sequence number" + maxSeqNum);
                }
                this.num = 0;
                this.payloadBuffer.clear();
                this.blockBuffer.clear();
            }
            bytebuf.release();
        }
    }
}