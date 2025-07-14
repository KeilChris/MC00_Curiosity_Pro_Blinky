/******************************************************************************
 * @file     vio_MC00_Curiosity_Pro.c
 * @brief    Virtual I/O implementation for board PIC32CM MC00 Curiosity Pro
 * @version  V2.0.0
 * @date     14. July 2025
 ******************************************************************************/
/*
 * Copyright (c) 2021-2025 Arm Limited (or its affiliates).
 * All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*! \page vio_PIC32CM MC00 Curiosity Pro Physical I/O Mapping

The table below lists the physical I/O mapping of this CMSIS-Driver VIO implementation.

Virtual Resource  | Variable       | Physical Resource on PIC32CM MC00 Curiosity Pro              |
:-----------------|:---------------|:------------------------------------------------|
vioBUTTON0        | vioSignalIn.0  | PA25: User Button (SW0)                         |
vioLED0           | vioSignalOut.0 | PA24: LED (LED0)                                |
*/

/* History:
 *  Version 2.0.0
 *    Updated to API 1.0.0
 */

#include <string.h>
#include "cmsis_vio.h"

#include "RTE_Components.h"                 // Component selection
#include CMSIS_device_header

#if !defined CMSIS_VOUT || !defined CMSIS_VIN
#endif

// VIO input, output definitions
#define VIO_VALUE_NUM           1U          // Number of values

// VIO input, output variables
__USED uint32_t vioSignalIn;                // Memory for incoming signal
__USED uint32_t vioSignalOut;               // Memory for outgoing signal
__USED int32_t  vioValue[VIO_VALUE_NUM];    // Memory for value used in vioGetValue/vioSetValue

// Helper functions for the LED0 on PA24
#define LED_Set()               (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 24U))
#define LED_Clear()             (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 24U))
#define LED_Toggle()            (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 24U))

// Helper functions for the SW0 on PA25
#define SW0_Get()               ((PORT_REGS->GROUP[0].PORT_IN & (1U << 25U)) ? 1U : 0U)
#define SW0_Pressed()           (SW0_Get() == 0U)
#define SW0_Released()          (SW0_Get() == 1U)

/*-----------------------------------------------------------------------------
  PORT_Initialize: Initialize PORT for LED and Button
 *----------------------------------------------------------------------------*/
static void PORT_Initialize(void)
{
   /************************** GROUP 0 Initialization *************************/
   PORT_REGS->GROUP[0].PORT_DIR = 0x1000000U;
   PORT_REGS->GROUP[0].PORT_OUT = 0x1000000U;
   PORT_REGS->GROUP[0].PORT_PINCFG[24] = 0x0U;

   // Set pin 25/USER_BUTTON as input (clear bit 25)
   PORT_REGS->GROUP[0].PORT_DIR &= ~(1U << 25U);
   // Optionally, enable input buffer and pull-up for pin 25
   PORT_REGS->GROUP[0].PORT_PINCFG[25] = 0x5U; // INEN=1, PULLEN=1
   PORT_REGS->GROUP[0].PORT_OUTSET = (1U << 25U); // Enable pull-up

   PORT_REGS->GROUP[0].PORT_PMUX[12] = 0x0U;
}

// Initialize test input, output.
void vioInit (void) {
#if !defined CMSIS_VOUT
// Add user variables here:

#endif
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  vioSignalIn  = 0U;
  vioSignalOut = 0U;

  memset(vioValue, 0, sizeof(vioValue));
  PORT_Initialize(); // Initialize PORT for LED and Button

}

// Set signal output.
void vioSetSignal (uint32_t mask, uint32_t signal) {
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  vioSignalOut &= ~mask;
  vioSignalOut |=  mask & signal;

#if !defined CMSIS_VOUT
  // Output signals to LEDs
  if ((mask & vioLED0) != 0U) {
    if ((signal & vioLED0) != 0U) {
      LED_Set();
    } else {
      LED_Clear();
    }
  }
#endif
}

// Get signal input.
uint32_t vioGetSignal (uint32_t mask) {
  uint32_t signal;
#if !defined CMSIS_VIN
// Add user variables here:

#endif

#if !defined CMSIS_VIN
  // Get input signals from buttons
  // User Button (SW0)
  if ((mask & vioBUTTON0) != 0U) {
    if (SW0_Get() == 0U) {
      vioSignalIn |=  vioBUTTON0;
    } else {
      vioSignalIn &= ~vioBUTTON0;
    }
  }
#endif

  signal = vioSignalIn & mask;

  return signal;
}

// Set value output.
void vioSetValue (uint32_t id, int32_t value) {
  uint32_t index = id;
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioValue[index] = value;

#if !defined CMSIS_VOUT
// Add user code here:

#endif
}

// Get value input.
int32_t vioGetValue (uint32_t id) {
  uint32_t index = id;
  int32_t  value = 0;
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return value;                       /* return default in case of out-of-range index */
  }

#if !defined CMSIS_VIN
// Add user code here:

//   vioValue[index] = ...;
#endif

  value = vioValue[index];

  return value;
}