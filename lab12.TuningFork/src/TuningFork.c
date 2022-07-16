#include "tm4c123gh6pm.h"

void DisableInterrupts(void);
void EnableInterrupts(void);
void WaitForInterrupt(void);
void Sound_Init(void);
void SysTick_Handler(void);
void PLL_Init(void);
void SysTick_Init(void);
void PortA_Init(void);
void DelayMS(unsigned long msec);

unsigned long Toggle = 0;

int
main(void)
{
    DisableInterrupts();
    Sound_Init(); 
    EnableInterrupts();
    while (1) {
        if (GPIO_PORTA_DATA_R & 0x08) {
            Toggle++;
            DelayMS(20);
            while (GPIO_PORTA_DATA_R & 0x08);
        }
    }
}

/* input from PA3, output from PA2, SysTick interrupts */
void
Sound_Init(void)
{
    PLL_Init();
    SysTick_Init();
    PortA_Init();
}

void
PLL_Init(void)
{
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
    SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
    SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;
    SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;
    SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) + (4<<22);
    while ((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS) == 0) {
        ;
    }
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}

void
SysTick_Init(void)
{
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 90908; /* 1.1363ms / 880Hz */
    NVIC_ST_CURRENT_R = 0;
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000;
    NVIC_ST_CTRL_R = 0x00000007;
}

void
PortA_Init(void)
{
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
    GPIO_PORTA_DIR_R &= ~0x08; /* make PA3 in */
    GPIO_PORTA_DIR_R |= 0x04; /* make PA2 out */
    GPIO_PORTA_AFSEL_R &= ~0x08; /* disable alt funct on PA3 */
    GPIO_PORTA_AFSEL_R &= ~0x04; /* disable alt funct on PA2 */
    GPIO_PORTA_DEN_R |= 0x08; /* enable digital I/O on PA3 */
    GPIO_PORTA_DEN_R |= 0x04; /* enable digital I/O on PA2 */
    GPIO_PORTA_PCTL_R &= 0xF000; /* configure PA3 as GPIO */
    GPIO_PORTA_PCTL_R &= 0xF00; /* configure PA2 as GPIO */
    GPIO_PORTA_AMSEL_R &= ~0x0C; /* disable analog functionality on PA3-PA2 */
}


/* called at 880 Hz */
void
SysTick_Handler(void)
{
    if (Toggle % 2 == 0) {
        GPIO_PORTA_DATA_R &= ~0x04;
    } else {
        GPIO_PORTA_DATA_R ^= 0x04;
    }
}

/* Subroutine to delay in units of milliseconds */
/* Inputs:  Number of milliseconds to delay */
/* Outputs: None */
/* Notes:   assumes 80 MHz clock */
void
DelayMS(unsigned long msec)
{
    while (msec > 0) {
        volatile unsigned long count = 4000;
        while (count > 0) {
            count--;
        }
        msec--;
    }
}
