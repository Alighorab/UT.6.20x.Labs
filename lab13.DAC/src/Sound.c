/* Sound.c */
/* Runs on LM4F120 or TM4C123,  */
/* edX lab 13  */
/* Use the SysTick timer to request interrupts at a particular period. */
/* Daniel Valvano, Jonathan Valvano */
/* December 29, 2014 */
/* This routine calls the 4-bit DAC */

#include "Sound.h"
#include "DAC.h"
#include "tm4c123gh6pm.h"


static unsigned long last_period = 0;
const unsigned char SineWave[32] = 
                            {8, 9, 10, 11, 12, 13, 14, 15, 15, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 2, 3, 4, 5, 6, 7};
unsigned int Index = 0;

/* **************Sound_Init********************* */
/* Initialize Systick periodic interrupts */
/* Also calls DAC_Init() to initialize DAC */
/* Input: none */
/* Output: none */
void
Sound_Init(void)
{
    DAC_Init();
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 0;
    NVIC_ST_CURRENT_R = 0;
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000;
    NVIC_ST_CTRL_R = 0x0007;
}

/* **************Sound_Tone********************* */
/* Change Systick periodic interrupts to start sound output */
/* Input: interrupt period */
/*           Units of period are 12.5ns */
/*           Maximum is 2^24-1 */
/*           Minimum is determined by length of ISR */
/* Output: none */
void
Sound_Tone(unsigned long period)
{
    if (period != last_period) {
        NVIC_ST_RELOAD_R = period-1;
        last_period = period;
    }
}


/* **************Sound_Off********************* */
/* stop outputing to DAC */
/* Output: none */
void
Sound_Off(void)
{
    DAC_Out(0);
    NVIC_ST_RELOAD_R = 0;
    last_period = 0;
}


/* Interrupt service routine */
/* Executed every 12.5ns*(period) */
void
SysTick_Handler(void)
{
    DAC_Out(SineWave[Index]);
    Index = (Index + 1) & 0x1F;
}
