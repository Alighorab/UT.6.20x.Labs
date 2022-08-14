#include "ADC.h"
#include "tm4c123gh6pm.h"

void
ADC0_Init(void) 
{
#ifndef KEIL
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
#else
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= 0x00000010;   /* 1) activate clock for Port E */
    delay = SYSCTL_RCGC2_R;         /*    allow time for clock to stabilize */
    GPIO_PORTE_DIR_R &= ~0x04;      /* 2) make PE2 input */
    GPIO_PORTE_AFSEL_R |= 0x04;     /* 3) enable alternate function on PE2 */
    GPIO_PORTE_DEN_R &= ~0x04;      /* 4) disable digital I/O on PE2 */
    GPIO_PORTE_AMSEL_R |= 0x04;     /* 5) enable analog function on PE2 */
    SYSCTL_RCGC0_R |= 0x00010000;   /* 6) activate ADC0 */
    delay = SYSCTL_RCGC2_R;        
    SYSCTL_RCGC0_R &= ~0x00000300;  /* 7) configure for 125K */
    ADC0_SSPRI_R = 0x0123;          /* 8) Sequencer 3 is highest priority */
    ADC0_ACTSS_R &= ~0x0008;        /* 9) disable sample sequencer 3 */
    ADC0_EMUX_R &= ~0xF000;         /* 10) seq3 is software trigger */
    ADC0_SSMUX3_R &= ~0x000F;       /* 11) clear SS3 field */
    ADC0_SSMUX3_R += 1;             /*    set channel Ain1 (PE2) */
    ADC0_SSCTL3_R = 0x0006;         /* 12) no TS0 D0, yes IE0 END0 */
    ADC0_ACTSS_R |= 0x0008;         /* 13) enable sample sequencer 3 */
#endif
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
