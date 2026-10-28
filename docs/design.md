# Design Overview

## Workaround Idea

Instead of relying on the affected transmission flow,
the library alternates between two dedicated transmit
buffers.

This provides a predictable software-controlled path.

## Buffer Selection Logic

Current Buffer A
      ↓
Transmit Frame
      ↓
Wait For Completion
      ↓
Switch To Buffer B
      ↓
Transmit Frame
      ↓
Wait For Completion
      ↓
Switch To Buffer A

## Advantages

- Simple implementation
- Low memory overhead
- Easy to integrate into existing projects
- Compatible with STM32 HAL

## Limitations

- Adds small software overhead
- Requires two dedicated transmit buffers
- Has not been validated for safety-critical applications
