#include "ADC.h"
#include "tm4c123gh6pm.h"

void
ADC0_Init(void) 
{
    SYSCTL_RCGCGPIO_R |= (1 << 4);
    SYSCTL_RCGCADC_R |= 0x1;

    GPIO_PORTE_AFSEL_R |= 0x04;
    GPIO_PORTE_DEN_R &= ~0x04;
    GPIO_PORTE_AMSEL_R |= 0x04;

    ADC0_ACTSS_R &= ~0x0008;
    ADC0_EMUX_R &= ~0xF000;
    ADC0_SSMUX3_R &= ~0x000F;
    ADC0_SSMUX3_R += 1;

    ADC0_PP_R = 0x1;
    ADC0_SSCTL3_R = 0x0006;
    ADC0_ACTSS_R |= 0x0008;
}

unsigned long
ADC0_In(void)  
{
    unsigned long result;
    ADC0_PSSI_R = 0x0008;
    while((ADC0_RIS_R&0x08)==0){};
    result = ADC0_SSFIFO3_R&0xFFF;
    ADC0_ISC_R = 0x0008;
    return result;
}
