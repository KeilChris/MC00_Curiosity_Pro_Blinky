#include <stdbool.h>
#include "RTE_Components.h"
#include CMSIS_device_header

#define LED_Set()               (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << 24U))
#define LED_Clear()             (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << 24U))
#define LED_Toggle()            (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << 24U))

static void PORT_Initialize(void)
{
   /************************** GROUP 0 Initialization *************************/
   PORT_REGS->GROUP[0].PORT_DIR = 0x1000000U;
   PORT_REGS->GROUP[0].PORT_OUT = 0x1000000U;
   PORT_REGS->GROUP[0].PORT_PINCFG[24] = 0x0U;

   PORT_REGS->GROUP[0].PORT_PMUX[12] = 0x0U;
}

static void SYSTICK_TimerInitialize ( void )
{
    SysTick->CTRL = 0U;
    SysTick->VAL = 0U;
    SysTick->LOAD = 0x1fffffU - 1U;
    SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;
}

static void SYSTICK_TimerStart ( void )
{
    SysTick->VAL = 0U;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

int main() {

    PORT_Initialize();
    SYSTICK_TimerInitialize();
    SYSTICK_TimerStart();

    while(true)
    {
        /* Never exit this loop */
    }
}

void __attribute__((used)) SysTick_Handler(void)
{
   /* Reading control register clears the count flag */
   (void)SysTick->CTRL;

   LED_Toggle();
}


