# STM32C5 FDCAN Errata Analysis

## Introduction

While reviewing the STM32C5 errata sheet, I noticed a reported issue
related to FDCAN transmission priority handling.

The issue is documented in Section 2.13.2 of the STM32C5 errata
documentation.

## Problem Description

According to the errata, specific combinations of dedicated
Tx Buffers and Tx FIFO usage can lead to unexpected transmission
ordering.

In systems where message priority is important, this behavior
may create timing issues.

## Why This Matters

CAN communication is widely used in:

- Industrial control systems
- Automotive electronics
- Robotics
- Distributed embedded systems

Developers generally expect higher priority frames
to be handled correctly.

## Initial Observation

The workaround proposed in this project avoids mixing
transmission paths.

Instead, frames are transmitted through dedicated
buffers under software control.

## Project Goal

The goal of this project is not to modify the silicon behavior.

The goal is to investigate the issue and implement
a simple software mitigation strategy.
