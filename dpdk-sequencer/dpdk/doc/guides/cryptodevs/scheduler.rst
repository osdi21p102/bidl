..  BSD LICENSE
    Copyright(c) 2017 Intel Corporation. All rights reserved.
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

Cryptodev Scheduler Poll Mode Driver Library
============================================

Scheduler PMD is a software crypto PMD, which has the capabilities of
attaching hardware and/or software cryptodevs, and distributes ingress
crypto ops among them in a certain manner.

.. figure:: img/scheduler-overview.*

   Cryptodev Scheduler Overview


The Cryptodev Scheduler PMD library (**librte_pmd_crypto_scheduler**) acts as
a software crypto PMD and shares the same API provided by librte_cryptodev.
The PMD supports attaching multiple crypto PMDs, software or hardware, as
slaves, and distributes the crypto workload to them with certain behavior.
The behaviors are categorizes as different "modes". Basically, a scheduling
mode defines certain actions for scheduling crypto ops to its slaves.

The librte_pmd_crypto_scheduler library exports a C API which provides an API
for attaching/detaching slaves, set/get scheduling modes, and enable/disable
crypto ops reordering.

Limitations
-----------

* Sessionless crypto operation is not supported
* OOP crypto operation is not supported when the crypto op reordering feature
  is enabled.


Installation
------------

To build DPDK with CRYTPO_SCHEDULER_PMD the user is required to set
CONFIG_RTE_LIBRTE_PMD_CRYPTO_SCHEDULER=y in config/common_base, and
recompile DPDK


Initialization
--------------

To use the PMD in an application, user must:

* Call rte_vdev_init("crpyto_scheduler") within the application.

* Use --vdev="crpyto_scheduler" in the EAL options, which will call
  rte_vdev_init() internally.


The following parameters (all optional) can be provided in the previous
two calls:

* socket_id: Specify the socket where the memory for the device is going
  to be allocated (by default, socket_id will be the socket where the core
  that is creating the PMD is running on).

* max_nb_sessions: Specify the maximum number of sessions that can be
  created. This value may be overwritten internally if there are too
  many devices are attached.

* slave: If a cryptodev has been initialized with specific name, it can be
  attached to the scheduler using this parameter, simply filling the name
  here. Multiple cryptodevs can be attached initially by presenting this
  parameter multiple times.

* mode: Specify the scheduling mode of the PMD. The supported scheduling
  mode parameter values are specified in the "Cryptodev Scheduler Modes
  Overview" section.

* ordering: Specify the status of the crypto operations ordering feature.
  The value of this parameter can be "enable" or "disable". This feature
  is disabled by default.

Example:

.. code-block:: console

    ... --vdev "crypto_aesni_mb_pmd,name=aesni_mb_1" --vdev "crypto_aesni_mb_pmd,name=aesni_mb_2" --vdev "crypto_scheduler_pmd,slave=aesni_mb_1,slave=aesni_mb_2" ...

.. note::

    * The scheduler cryptodev cannot be started unless the scheduling mode
      is set and at least one slave is attached. Also, to configure the
      scheduler in the run-time, like attach/detach slave(s), change
      scheduling mode, or enable/disable crypto op ordering, one should stop
      the scheduler first, otherwise an error will be returned.

    * The crypto op reordering feature requires using the userdata field of
      every mbuf to be processed to store temporary data. By the end of
      processing, the field is set to pointing to NULL, any previously
      stored value of this field will be lost.


Cryptodev Scheduler Modes Overview
----------------------------------

Currently the Crypto Scheduler PMD library supports following modes of
operation:

*   **CDEV_SCHED_MODE_ROUNDROBIN:**

   *Initialization mode parameter*: **round-robin**

   Round-robin mode, which distributes the enqueued burst of crypto ops
   among its slaves in a round-robin manner. This mode may help to fill
   the throughput gap between the physical core and the existing cryptodevs
   to increase the overall performance.

*   **CDEV_SCHED_MODE_PKT_SIZE_DISTR:**

   *Initialization mode parameter*: **packet-size-distr**

   Packet-size based distribution mode, which works with 2 slaves, the primary
   slave and the secondary slave, and distributes the enqueued crypto
   operations to them based on their data lengths. A crypto operation will be
   distributed to the primary slave if its data length is equal to or bigger
   than the designated threshold, otherwise it will be handled by the secondary
   slave.

   A typical usecase in this mode is with the QAT cryptodev as the primary and
   a software cryptodev as the secondary slave. This may help applications to
   process additional crypto workload than what the QAT cryptodev can handle on
   its own, by making use of the available CPU cycles to deal with smaller
   crypto workloads.

   The threshold is set to 128 bytes by default. It can be updated by calling
   function **rte_cryptodev_scheduler_option_set**. The parameter of
   **option_type** must be **CDEV_SCHED_OPTION_THRESHOLD** and **option** should
   point to a rte_cryptodev_scheduler_threshold_option structure filled with
   appropriate threshold value. Please NOTE this threshold has be a power-of-2
   unsigned integer.

*   **CDEV_SCHED_MODE_FAILOVER:**

   *Initialization mode parameter*: **fail-over**

   Fail-over mode, which works with 2 slaves, the primary slave and the
   secondary slave. In this mode, the scheduler will enqueue the incoming
   crypto operation burst to the primary slave. When one or more crypto
   operations fail to be enqueued, then they will be enqueued to the secondary
   slave.
