Multiple Channels
=================

This example demonstrates how to work with multiple channels and multiplex between them.

A topology of three devices - **FLP**, **EPN** and **SCHEDULER**. The Sampler sends data to the Sink via the PUSH-PULL pattern. The Broadcaster device sends a message to both Sampler and Sink containing a string "OK" every second. The Broadcaster sends the message via PUB pattern. Both Sampler and Sink, besides doing their PUSH-PULL job, listen via SUB to the Broadcaster.

The multiplexing between their data channels and the broadcast channels happens with `FairMQPoller`.
