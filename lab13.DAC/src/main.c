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

enum Key {
    KEY_C = 1,
    KEY_D = 2,
    KEY_E = 4,
    KEY_G = 8,
};

void DisableInterrupts(void);
void EnableInterrupts(void);
void PLL_Init(void);

int
main(void)
{
    unsigned long Keys;
    PLL_Init();
    Sound_Init();
    Piano_Init();
    EnableInterrupts();
    while (1) {                
        Keys = Piano_In(); 
        switch (Keys) {
        case KEY_C:
            Sound_Tone(C);
            break;
        case KEY_D:
            Sound_Tone(D);
            break;
        case KEY_E:
            Sound_Tone(E);
            break;
        case KEY_G:
            Sound_Tone(G);
            break;
        default:
            Sound_Off();
            break;
        }
    }
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
