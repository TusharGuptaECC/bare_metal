# Microcontroller Driver Collection

## Purpose
This repository is an ongoing effort to build the **largest open-source collection of raw drivers** for various microcontrollers and peripherals. It currently includes driver code for:

- **ATmega328P** (portable to ATmega16 & ATmega2560 if the same pins and modules exist)
- **STM32 Nucleo F401RE**
- **TM4C123GH6PMT7**

The goal is to provide **reusable and well-structured low-level drivers** that help developers integrate hardware components efficiently across different platforms.

## Features
- **Cross-Compatible Code**: ATmega328P drivers can be adapted to ATmega16 and ATmega2560.
- **Modular Design**: Drivers are structured to be easily extended and modified.
- **Raw Peripheral Access**: Focuses on writing low-level, register-based drivers for maximum control.
- **Expanding Library**: More microcontrollers and drivers will be added over time.

## Scope for Improvement
- **Extend Compatibility**: Add support for more microcontrollers and make drivers more portable across families.
- **Add Documentation**: Improve comments and usage examples for easier adoption.
- **Support for New Peripherals**: Implement drivers for additional hardware like sensors, displays, and communication modules.
- **Middleware & HAL Integration**: Provide optional abstraction layers for ease of use.

## Contributing
Contributions are welcome! If you have driver implementations or improvements, feel free to open a pull request.  
Let's build a comprehensive driver library together.

---
