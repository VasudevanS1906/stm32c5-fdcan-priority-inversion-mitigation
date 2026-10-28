# STM32C5 FDCAN Priority Inversion Mitigation

A reference implementation and software workaround for the FDCAN Tx FIFO priority inversion issue documented in **STM32C5 Errata ES0676 (Section 2.13.2)**.

---

## Overview

When utilizing standard Tx FIFO operations on affected silicon, certain edge cases can introduce message priority inversions. This project investigates the underlying hardware limitation and provides a lightweight, robust software routing layer utilizing dedicated Tx buffers to ensure strict message prioritization.

## Key Features

* **Deterministic Scheduling:** Bypasses standard Tx FIFO priority quirks by routing transmissions through controlled, dedicated Tx buffers.
* **STM32 HAL Compatible:** Integrates seamlessly with existing STM32Cube HAL initialization and FDCAN handle structures.
* **Built-in Diagnostics:** Tracks transmission success rates, timeout occurrences, and error counters for reliability monitoring.
* **Modular API:** Cleanly separated interface designed for easy integration into existing embedded firmware architectures.

## Repository Structure

```text
├── Inc/         # Header files (public API definitions)
├── Src/         # Source files (implementation logic)
├── examples/    # Usage examples and integration guides
└── docs/        # Additional technical notes and errata references
