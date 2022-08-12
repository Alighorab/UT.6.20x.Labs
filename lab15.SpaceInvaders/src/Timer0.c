#include "Timer0.h"

void Timer0A_Handler(void);
void (*PeriodicTask)(void);

void
Timer0_Init(void (*task)(void), unsigned long period) 
{
    SYSCTL_RCGC1_R |= 0x10000;
    PeriodicTask = task;
    TIMER0_CTL_R = 0x00000000;
    TIMER0_CFG_R = 0x00000000;
    TIMER0_TAMR_R = 0x00000002;
    TIMER0_TAILR_R = period - 1;
    TIMER0_TAPR_R = 0;
    TIMER0_ICR_R = 0x00000001;
    TIMER0_IMR_R = 0x00000001;
    NVIC_PRI4_R = (NVIC_PRI4_R & 0x00FFFFFF) | 0x80000000;
    NVIC_EN0_R = 1 << 19;
    TIMER0_CTL_R = 0x00000001;
}

void
Timer0A_Enable(void)
{
    TIMER0_CTL_R |= 0x00000001;
}

void
Timer0A_Enable_IRQ(void)
{
    NVIC_EN0_R = 1 << 19;
}

void
Timer0A_Disable_IRQ(void)
{
    NVIC_DIS0_R = 1 << 19;
}

void
Timer0A_Handler(void) 
{
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;
    (*PeriodicTask)();
}
