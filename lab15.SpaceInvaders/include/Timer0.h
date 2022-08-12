#ifndef TIMER0_h
#define TIMER0_h
    
#include "tm4c123gh6pm.h"

/* ***************** Timer0_Init **************** */
/* Activate Timer0 interrupts to run user task periodically */
/* Inputs:  task is a pointer to a user function */
/*          period in units (1/clockfreq) */
/* Outputs: none */
void Timer0_Init(void (*task)(void), unsigned long period);

/* ********** Timer0A_Enable_Interrupt ********** */
/* Activate Timer0 IRQ */
/* Inputs: none */
/* Outputs: none */
void Timer0A_Enable_IRQ(void);

/* ********** Timer0A_Disable_Interrupt ********** */
/* Deactivate Timer0 IRQ */
/* Inputs: none */
/* Outputs: none */
void Timer0A_Disable_IRQ(void);

/* *************** Timer0A_Enable *************** */
/* Activate Timer0 */
/* Inputs: none */
/* Outputs: none */
void Timer0A_Enable(void);

#endif
