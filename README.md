# Blinky Example for the Microchip PIC32CM MC00 Curiosity Pro

The **Blinky** project is a simple example that can be used to verify the basic tool setup.

It is compliant to the Cortex Microcontroller Software Interface Standard (CMSIS).

## Required tools

This CMSIS solution project requires the following VS Code extension:

- [Keil Studio Pack (MDK v6)](https://marketplace.visualstudio.com/items?itemName=Arm.keil-studio-pack)

Other tools will be downloaded automatically via the `vcpkg-configuration.json` file.

## Operation

Once stated, the application blinks "LED0" in 1 sec interval.

![Microchip PIC32CM MC00 Curiosity Pro development board](./images/3592-32cm-curiosity-4640.avif)

> [!NOTE]
> The on-board [Atmel Embedded Debugger (EDBG)](http://ww1.microchip.com/downloads/en/devicedoc/atmel-42096-microcontrollers-embedded-debugger_user-guide.pdf)
> ("DEBUG USB") currently only works on Windows machines. If you are using macOS, attach an external debug probe to the
> **J203** header ("CORTEX DEBUG").
