#include "SysTick.h"

void (*SysTicHandler)(void);

void
SysTick_Init(void (*handler)(void))
{
    SysTicHandler = handler;
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 2666666;
    NVIC_ST_CURRENT_R = 0;
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000;
    NVIC_ST_CTRL_R = 0x0007;
}

void
SysTick_Handler(void)
{
    if (SysTicHandler) {
        SysTicHandler();
    }
}
