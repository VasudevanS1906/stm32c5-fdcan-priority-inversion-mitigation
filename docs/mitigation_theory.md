# Technical Breakdown: FDCAN Tx FIFO Priority Inversion

## The Hardware Limitation (Errata ES0676)
On affected silicon revisions of the STM32C5, using the standard FDCAN hardware Tx FIFO can under specific high-load interleaving conditions cause message priority inversion. Lower-priority CAN frames queued into the FIFO can bypass or reorder ahead of higher-priority pending messages due to internal pointer race conditions in the Message RAM interface.

## The Software Workaround
To bypass the FIFO scheduling vulnerability:
1. **Bypass the FIFO:** Instead of pushing frames to `FDCAN_TX_FIFO`, transmissions are routed exclusively through **Dedicated Tx Buffers**.
2. **Ping-Pong Alternation:** The router alternates between two dedicated buffers (`buffer_a` and `buffer_b`) on consecutive message calls. 
3. **Deterministic Sequencing:** This guarantees that hardware arbitration handles the priority externally without relying on vulnerable internal FIFO pointer states.
