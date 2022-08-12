#include "DAC.h"

void
DAC_Init(void)
{
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1) == 0) {}
    GPIO_PORTB_DIR_R |= 0x3F;
    GPIO_PORTB_AFSEL_R &= ~0x3F;
    GPIO_PORTB_DEN_R |= 0x3F;
    GPIO_PORTB_PCTL_R = 0x00;
    GPIO_PORTB_AMSEL_R = 0x00;
    GPIO_PORTB_DATA_R = 0x00;
}

void
DAC_Out(unsigned long data)
{
    GPIO_PORTB_DATA_R = data;
}
