/*---------------------------------------------------------------------------
 * Copyright (c) 2025 Arm Limited (or its affiliates). All rights reserved.
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
 *---------------------------------------------------------------------------*/
 
#include <stdbool.h>
#include "main.h"
#include "RTE_Components.h"
#include CMSIS_device_header

#include "cmsis_os2.h"
#include "cmsis_vio.h"

/*-----------------------------------------------------------------------------
  main: Main function
  Initializes the system and starts the application.
  This function configures the system clock, initializes the PORT for LED,
  and starts the application main thread.
  It enters an infinite loop to keep the application running.
 *----------------------------------------------------------------------------*/
int main() {
    SystemCoreClockUpdate();           // Configure the system clock
    vioInit();                         // Initialize VIO (Virtual Input/Output)
    app_main();                        // Start the application

    for (;;) {}
}
