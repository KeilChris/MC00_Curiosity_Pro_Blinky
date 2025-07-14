# Blinky Example for the Microchip PIC32CM MC00 Curiosity Pro

The **Blinky** project can be easily used to verify the basic tool setup:

- In the beginning, `vioLED0` blinks in 1 sec interval.
- Pressing `vioBUTTON0` changes the blink frequency of `vioLED0`.

It is compliant to the Cortex Microcontroller Software Interface Standard (CMSIS).

## Prerequisites

### Tools:

- [CMSIS-Toolbox v2.10.0](https://github.com/Open-CMSIS-Pack/cmsis-toolbox/releases) or newer
- [Microsoft Visual Studio Code](https://code.visualstudio.com/download) with Keil Studio Pack extension (optional, alternatively CLI can be used)
- [Arm Compiler 6](https://developer.arm.com/Tools%20and%20Software/Arm%20Compiler%20for%20Embedded) (automatically installed when using Visual Studio Code with vcpkg)

## Build Solution/Project

### Using Visual Studio Code with extensions

Required tools described in file 'vcpkg-configuration.json' should be automatically installed by vcpkg. You can see the
status of vcpkg in the status bar.

Required CMSIS packs need to be also installed. In case a required pack is missing, a notification window will pop-up
to install the missing pack.

Open the **CMSIS view** from the side bar, select desired 'Build Type' and press the 'Build' button.

### Using Command Line Interface (CLI)

Download required packs (not required when the packs are already available) by executing the following commands:

```sh
csolution list packs -s Blinky.csolution.yml -m >packs.txt
cpackget update-index
cpackget add -f packs.txt
```

Build the project by executing the following command:

```sh
cbuild Blinky.csolution.yml
```

## Run the application

> [!NOTE]
> The on-board [Atmel Embedded Debugger (EDBG)](http://ww1.microchip.com/downloads/en/devicedoc/atmel-42096-microcontrollers-embedded-debugger_user-guide.pdf)
> ("DEBUG USB") currently only works on Windows machines. If you are using macOS, attach an external debug probe to the
> **J203** header ("CORTEX DEBUG").

### Using Visual Studio Code with extensions

- Connect the board's "DEBUG USB" to the PC (provides also power).
- Open the **CMSIS view** from the activity bar, press the 'Load & Run' button, and wait until the image is programmed
  and starts running.

## Debug the application

Before starting to debug the application, make sure that you have gone through the steps as
described in the [run the application](#run-the-application) section.

Open the **CMSIS view** from the activity bar, press the 'Load & Debug' button, and wait until the image is programmed
and the debug session starts. It will run to `main` and stop there. Start debugging.

## Project Configuration

### RTOS: Keil RTX5 Real-Time Operating System

The real-time operating system [Keil RTX5](https://arm-software.github.io/CMSIS_5/RTOS2/html/rtx5_impl.html) implements
the resource management.

It is configured with the following settings:

- [Global Dynamic Memory size](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html#systemConfig):
  2048 bytes
- [Default Thread Stack size](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html#threadConfig):
  512 bytes

Refer to [Configure RTX v5](https://arm-software.github.io/CMSIS_5/RTOS2/html/config_rtx5.html) for a detailed
description of all configuration options.

### Board: Microchip PIC32CM MC00 Curiosity Pro

![Microchip PIC32CM MC00 Curiosity Pro development board](./images/3592-32cm-curiosity-4640.avif)

The tables below list the device configuration for this board.

The heap/stack setup and the CMSIS-Driver assignment is in configuration files of related software components.

#### System Configuration

| System Component        | Setting
|:------------------------|:-------------------------------------------------------------
| Device                  | PIC32CM1216MC00048
| Board                   | PIC32CM MC00 Curiosity Pro
| Heap                    | 3072 bytes (configured in regions_PIC32CM1216MC00048.h file)
| Stack.                  | 512  bytes (configured in regions_PIC32CM1216MC00048.h file)

#### GPIO Configuration and usage

| Pin  | Peripheral | Signal   | Identifier | Pin Settings | Usage
|:-----|:-----------|:---------|:-----------|:-------------|:-----------------------
| PA24 | GPIO0      | GPIO, 24 | LED0       | default      | User LED0 (PA24)
| PA25 | GPIO0      | GPIO, 25 | SW0        | default      | User Button SW0 (PA25)

#### CMSIS-Driver mapping

| CMSIS-Driver VIO  | Physical board hardware
|:------------------|:------------------------------
| vioBUTTON0        | User Button SW0
| vioLED0           | User LED0
