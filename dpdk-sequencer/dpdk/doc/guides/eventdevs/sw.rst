..  BSD LICENSE
    Copyright(c) 2017 Intel Corporation. All rights reserved.

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

Software Eventdev Poll Mode Driver
==================================

The software eventdev is an implementation of the eventdev API, that provides a
wide range of the eventdev features. The eventdev relies on a CPU core to
perform event scheduling.


Features
--------

The software eventdev implements many features in the eventdev API;

Queues
 * Atomic
 * Ordered
 * Parallel
 * Single-Link

Ports
 * Load balanced (for Atomic, Ordered, Parallel queues)
 * Single Link (for single-link queues)

Event Priorities
 * Each event has a priority, which can be used to provide basic QoS


Configuration and Options
-------------------------

The software eventdev is a vdev device, and as such can be created from the
application code, or from the EAL command line:

* Call ``rte_vdev_init("event_sw0")`` from the application

* Use ``--vdev="event_sw0"`` in the EAL options, which will call
  rte_vdev_init() internally

Example:

.. code-block:: console

    ./your_eventdev_application --vdev="event_sw0"


Scheduling Quanta
~~~~~~~~~~~~~~~~~

The scheduling quanta sets the number of events that the device attempts to
schedule before returning to the application from the ``rte_event_schedule()``
function. Note that is a *hint* only, and that fewer or more events may be
scheduled in a given iteration.

The scheduling quanta can be set using a string argument to the vdev
create call:

.. code-block:: console

    --vdev="event_sw0,sched_quanta=64"


Credit Quanta
~~~~~~~~~~~~~

The credit quanta is the number of credits that a port will fetch at a time from
the instance's credit pool. Higher numbers will cause less overhead in the
atomic credit fetch code, however it also reduces the overall number of credits
in the system faster. A balanced number (eg 32) ensures that only small numbers
of credits are pre-allocated at a time, while also mitigating performance impact
of the atomics.

Experimentation with higher values may provide minor performance improvements,
at the cost of the whole system having less credits. On the other hand,
reducing the quanta may cause measurable performance impact but provide the
system with a higher number of credits at all times.

A value of 32 seems a good balance however your specific application may
benefit from a higher or reduced quanta size, experimentation is required to
verify possible gains.

.. code-block:: console

    --vdev="event_sw0,credit_quanta=64"


Limitations
-----------

The software eventdev implementation has a few limitations. The reason for
these limitations is usually that the performance impact of supporting the
feature would be significant.


"All Types" Queues
~~~~~~~~~~~~~~~~~~

The software eventdev does not support creating queues that handle all types of
traffic. An eventdev with this capability allows enqueueing Atomic, Ordered and
Parallel traffic to the same queue, but scheduling each of them appropriately.

The reason to not allow Atomic, Ordered and Parallel event types in the
same queue is that it causes excessive branching in the code to enqueue packets
to the queue, causing a significant performance impact.

The ``RTE_EVENT_DEV_CAP_QUEUE_ALL_TYPES`` flag is not set in the
``event_dev_cap`` field of the ``rte_event_dev_info`` struct for the software
eventdev.

Distributed Scheduler
~~~~~~~~~~~~~~~~~~~~~

The software eventdev is a centralized scheduler, requiring the
``rte_event_schedule()`` function to be called by a CPU core to perform the
required event distribution. This is not really a limitation but rather a
design decision.

The ``RTE_EVENT_DEV_CAP_DISTRIBUTED_SCHED`` flag is not set in the
``event_dev_cap`` field of the ``rte_event_dev_info`` struct for the software
eventdev.

Dequeue Timeout
~~~~~~~~~~~~~~~

The eventdev API supports a timeout when dequeuing packets using the
``rte_event_dequeue_burst`` function.
This allows a core to wait for an event to arrive, or until ``timeout`` number
of ticks have passed. Timeout ticks is not supported by the software eventdev
for performance reasons.
