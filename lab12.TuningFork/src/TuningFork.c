#include "tm4c123gh6pm.h"

void DisableInterrupts(void);
void EnableInterrupts(void);
void WaitForInterrupt(void);
void Sound_Init(void);
void sys_tick_handler(void);

int
main(void)
{
    Sound_Init(); 
    EnableInterrupts();
    while (1) {
    }
}

/* input from PA3, output from PA2, SysTick interrupts */
void
Sound_Init(void)
{ 

}

/* called at 880 Hz */
void
sys_tick_handler(void)
{

}

