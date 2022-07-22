/* Runs on LM4F120 or TM4C123 */
/* Use SysTick interrupts to implement a 4-key digital piano */
/* edX Lab 13  */
/* Daniel Valvano, Jonathan Valvano */
/* December 29, 2014 */
/* Port B bits 3-0 have the 4-bit DAC */
/* Port E bits 3-0 have 4 piano keys */

#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"

void DisableInterrupts(void);
void EnableInterrupts(void);
void delay(unsigned long msec);

int
main(void)
{
    Sound_Init();
    Piano_Init();
    EnableInterrupts();
    while (1) {                

    }
}

void
delay(unsigned long msec) 
{
    unsigned long count;
    while(msec > 0 ) {
        count = 16000;
        while (count > 0) { 
            count--;
        }
        msec--;
    }
}
