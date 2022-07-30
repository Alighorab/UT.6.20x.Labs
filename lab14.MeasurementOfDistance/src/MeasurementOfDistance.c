/* MeasurementOfDistance.c */
/* Runs on LM4F120/TM4C123 */
/* Use SysTick interrupts to periodically initiate a software- */
/* triggered ADC conversion, convert the sample to a fixed- */
/* point decimal distance, and store the result in a mailbox. */
/* The foreground thread takes the result from the mailbox, */
/* converts the result to a string, and prints it to the */
/* Nokia5110 LCD.  The display is optional. */
/* January 15, 2016 */

/* Slide pot pin 3 connected to +3.3V */
/* Slide pot pin 2 connected to PE2(Ain1) and PD3 */
/* Slide pot pin 1 connected to ground */


#include "tm4c123gh6pm.h"
#include "ADC.h"
#include "Nokia5110.h"

void PLL_Init(void);
void EnableInterrupts(void);
void WaitForInterrupt(void); 
void SysTick_Handler(void);
void SysTick_Init(unsigned long period);
unsigned long Convert(unsigned long sample);
void UART_ConvertDistance(unsigned long n);

unsigned char String[10]; /* null-terminated ASCII string */
unsigned long Distance;   /* units 0.001 cm */
unsigned long ADCdata;    /* 12-bit 0 to 4095 sample */
volatile unsigned long Flag;       /* 1 means valid Distance, 0 means Distance is empty */

/* once the ADC is operational, you can use main2 to debug the convert to distance */
int
main(void) 
{
    PLL_Init();
    ADC0_Init();
    SysTick_Init(2000000);
    Nokia5110_Init();
    Nokia5110_Clear();
    Nokia5110_SetCursor(0, 0);
    Nokia5110_OutString((unsigned char*)"D = ");
    EnableInterrupts();
    while (1) { 
        if (Flag == 1) {
            Distance = Convert(ADCdata); 
            UART_ConvertDistance(Distance);
            Nokia5110_SetCursor(4, 0);
            Nokia5110_OutString(String);
            Flag = 0;
        }
    }
}

/*********Convert**************** */
/* Convert a 12-bit binary ADC sample into a 32-bit unsigned */
/* fixed-point distance (resolution 0.001 cm).  Calibration */
/* data is gathered using known distances and reading the */
/* ADC value measured on PE1.   */
/* Overflow and dropout should be considered  */
/* Input: sample  12-bit ADC sample */
/* Output: 32-bit distance (resolution 0.001cm) */
unsigned long
Convert(unsigned long sample)
{
    unsigned long distance;
    float voltage, resolution = 3.3/4096;
    voltage = (float)sample * resolution;
    distance = (unsigned long)(voltage * (2000.0/3.3) + 0.5);
    return distance;
}

/* Initialize SysTick interrupts to trigger at 40 Hz, 25 ms */
void
SysTick_Init(unsigned long period)
{
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = period - 1;
    NVIC_ST_CURRENT_R = 0;
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) + 0x40000000;

    NVIC_ST_CTRL_R = 0x00000007;
}
/* executes every 25 ms, collects a sample, converts and stores in mailbox */
void
SysTick_Handler(void) 
{
    ADCdata = ADC0_In();
    Flag = 1;
}

static void
Strcpy(unsigned char *dest, unsigned char *src)
{
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

/*-----------------------UART_ConvertDistance----------------------- */
/* Converts a 32-bit distance into an ASCII string */
/* Input: 32-bit number to be converted (resolution 0.001cm) */
/* Output: store the conversion in global variable String[10] */
/* Fixed format 1 digit, point, 3 digits, space, units, null termination */
/* Examples */
/*    4 to "0.004 cm"   */
/*   31 to "0.031 cm"  */
/*  102 to "0.102 cm"  */
/* 2210 to "2.210 cm" */
/*10000 to "*.*** cm"  any value larger than 9999 converted to "*.*** cm" */
void
UART_ConvertDistance(unsigned long n)
{
    unsigned long d;
    if (n >= 10000) {
        Strcpy(String, (unsigned char*) "*.*** cm");
        return;
    } else {
        d = n / 1000;
        n = n % 1000;
        String[0] = d + '0';
        String[1] = '.';
        d = n / 100;
        n = n % 100;
        String[2] = d + '0';
        d = n / 10;
        n = n % 10;
        String[3] = d + '0';
        d = n;
        String[4] = d + '0';
        Strcpy(String + 5, (unsigned char*) " cm");
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
