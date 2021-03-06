..  BSD LICENSE
    Copyright(c) 2016 Intel Corporation. All rights reserved.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in
    the documentation and/or other materials provided with the
    distribution.
    * Neither the name of Intel Corporation nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

.. _virtio_user_as_excpetional_path:

Virtio_user as Exceptional Path
===============================

The virtual device, virtio-user, was originally introduced with vhost-user
backend, as a high performance solution for IPC (Inter-Process Communication)
and user space container networking.

Virtio_user with vhost-kernel backend is a solution for exceptional path,
such as KNI which exchanges packets with kernel networking stack. This
solution is very promising in:

*   Maintenance

    All kernel modules needed by this solution, vhost and vhost-net (kernel),
    are upstreamed and extensively used kernel module.

*   Features

    vhost-net is born to be a networking solution, which has lots of networking
    related featuers, like multi queue, tso, multi-seg mbuf, etc.

*   Performance

    similar to KNI, this solution would use one or more kthreads to
    send/receive packets from user space DPDK applications, which has little
    impact on user space polling thread (except that it might enter into kernel
    space to wake up those kthreads if necessary).

The overview of an application using virtio-user as exceptional path is shown
in :numref:`figure_virtio_user_as_exceptional_path`.

.. _figure_virtio_user_as_exceptional_path:

.. figure:: img/virtio_user_as_exceptional_path.*

   Overview of a DPDK app using virtio-user as excpetional path


Sample Usage
------------

As a prerequisite, the vhost/vhost-net kernel CONFIG should be chosen before
compiling the kernel and those kernel modules should be inserted.

#.  Compile DPDK and bind a physical NIC to igb_uio/uio_pci_generic/vfio-pci.

    This physical NIC is for communicating with outside.

#.  Run testpmd.

    .. code-block:: console

        $(testpmd) -l 2-3 -n 4 \
		--vdev=virtio_user0,path=/dev/vhost-net,queue_size=1024 \
		-- -i --txqflags=0x0 --disable-hw-vlan --enable-lro \
		--enable-rx-cksum --rxd=1024 --txd=1024

    This command runs testpmd with two ports, one physical NIC to communicate
    with outside, and one virtio-user to communicate with kernel.

* ``--enable-lro``

    This is used to negotiate VIRTIO_NET_F_GUEST_TSO4 and
    VIRTIO_NET_F_GUEST_TSO6 feature so that large packets from kernel can be
    transmitted DPDK application and further TSOed by physical NIC.

* ``--enable-rx-cksum``

    This is used to negotiate VIRTIO_NET_F_GUEST_CSUM so that packets from
    kernel can be deemed as valid Rx checksumed.

* ``queue_size``

    256 by default. To avoid shortage of descriptors, we can increase it to 1024.

* ``queues``

    Number of multi-queues. Each qeueue will be served by a kthread. For example:

    .. code-block:: console

        $(testpmd) -l 2-3 -n 4 \
		--vdev=virtio_user0,path=/dev/vhost-net,queues=2,queue_size=1024 \
		-- -i --txqflags=0x0 --disable-hw-vlan --enable-lro \
		--enable-rx-cksum --txq=2 --rxq=2 --rxd=1024 \
		--txd=1024

#. Start testpmd:

    .. code-block:: console

        (testpmd) start

#.  Configure IP address and start tap:

    .. code-block:: console

        ifconfig tap0 1.1.1.1/24 up

.. note::

    The tap device will be named tap0, tap1, etc, by kernel.

Then, all traffic from physical NIC can be forwarded into kernel stack, and all
traffic on the tap0 can be sent out from physical NIC.

Limitations
-----------

This solution is only available on Linux systems.
