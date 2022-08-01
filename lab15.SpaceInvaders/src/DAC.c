/* DAC.c */
/* Runs on LM4F120 or TM4C123,  */
/* edX lab 13  */
/* Implementation of the 4-bit digital to analog converter */
/* Daniel Valvano, Jonathan Valvano */
/* December 29, 2014 */
/* Port B bits 3-0 have the 4-bit DAC */

#include "DAC.h"
#include "tm4c123gh6pm.h"

/* **************DAC_Init********************* */
/* Initialize 4-bit DAC  */
/* Input: none */
/* Output: none */
void
DAC_Init(void)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    volatile unsigned long delay;
#pragma GCC diagnostic pop
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
    delay = SYSCTL_RCGC2_R;
    GPIO_PORTB_DIR_R |= 0x3F;    /* make PB3-0 output (DAC data bus) */
    GPIO_PORTB_AFSEL_R &= ~0x3F; /* disable alt funct on PB3-0 */
    GPIO_PORTB_DR8R_R |= 0x3F;
    GPIO_PORTB_DEN_R |= 0x3F;    /* enable digital I/O on PB3-0 */
    GPIO_PORTB_PCTL_R = 0x00;    /* configure PB3-0 as GPIO */
    GPIO_PORTB_AMSEL_R = 0x00;   /* disable analog functionality on PB3-0 */
    GPIO_PORTB_DATA_R = 0x00;    /* set PB3-0 to 0 */
}


/* **************DAC_Out********************* */
/* output to DAC */
/* Input: 4-bit data, 0 to 15  */
/* Output: none */
void
DAC_Out(unsigned long data)
{
    GPIO_PORTB_DATA_R = data;
}
