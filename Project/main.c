#include <stdbool.h>
#include "RTE_Components.h"
#include CMSIS_device_header

#include "cmsis_os2.h"

// Helper functions for the LED0 on PA24
#define LED_Set()               (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 24U))
#define LED_Clear()             (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 24U))
#define LED_Toggle()            (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 24U))

// Helper functions for the SW0 on PA25
#define SW0_Get()               ((PORT_REGS->GROUP[0].PORT_IN & (1U << 25U)) ? 1U : 0U)
#define SW0_Pressed()           (SW0_Get() == 0U)
#define SW0_Released()          (SW0_Get() == 1U)

static osThreadId_t tid_thrLED;         // Thread id of thread: LED
static osThreadId_t tid_thrButton;      // Thread id of thread: Button

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

/*-----------------------------------------------------------------------------
  thrLED: blink LED
 *----------------------------------------------------------------------------*/
static __NO_RETURN void thrLED (void *argument) {
  uint32_t active_flag = 0U;

  (void)argument;

  for (;;) {
    if (osThreadFlagsWait(1U, osFlagsWaitAny, 0U) == 1U) {
      active_flag ^= 1U;
    }

    if (active_flag == 1U) {
      LED_Set();
      osDelay(100U);                            // Delay 100 ms
      LED_Clear();
      osDelay(100U);                            // Delay 100 ms
    }
    else {
      LED_Set();
      osDelay(500U);                            // Delay 500 ms
      LED_Clear();
      osDelay(500U);                            // Delay 500 ms
    }
  }
}

/*-----------------------------------------------------------------------------
  thrButton: check Button state
 *----------------------------------------------------------------------------*/
static __NO_RETURN void thrButton (void *argument) {
  uint32_t last = 1U;
  uint32_t state;

  (void)argument;

  for (;;) {
    state = SW0_Get();           // Get pressed Button state
    if (state != last) {
      if (state == 0U) {
        osThreadFlagsSet(tid_thrLED, 1U);         // Set flag to thrLED
      }
      last = state;
    }
    osDelay(100U);
  }
}


/*-----------------------------------------------------------------------------
  Application main thread
 *----------------------------------------------------------------------------*/
__NO_RETURN void app_main_thread (void *argument) {

  // printf("Blinky example\n");

  tid_thrLED = osThreadNew(thrLED, NULL, NULL);         // Create LED thread
  tid_thrButton = osThreadNew(thrButton, NULL, NULL);   // Create Button thread

  for (;;) {                            // Loop forever
  }
}

/*-----------------------------------------------------------------------------
  Application initialization
 *----------------------------------------------------------------------------*/
int app_main (void) {
  osKernelInitialize();                         /* Initialize CMSIS-RTOS2 */
  osThreadNew(app_main_thread, NULL, NULL);
  osKernelStart();                              /* Start thread execution */
  return 0;
}

/*-----------------------------------------------------------------------------
  main: Main function
  Initializes the system and starts the application.
  This function configures the system clock, initializes the PORT for LED,
  and starts the application main thread.
  It enters an infinite loop to keep the application running.
 *----------------------------------------------------------------------------*/
int main() {
    SystemCoreClockUpdate();           // Configure the system clock
    PORT_Initialize();                 // Initialize PORT for LED
    app_main();                        // Start the application

    while(true)
    {
        /* Never exit this loop */
    }
}
