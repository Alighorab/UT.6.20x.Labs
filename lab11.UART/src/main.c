#include "tm4c123gh6pm.h"
#include "UART.h"

void PLL_init(void);

int
main(void)
{ 
    unsigned long n;
    PLL_init();
    UART_Init();
    UART_OutString((unsigned char*)"Running Lab 11");
    while (1) {
        UART_OutString((unsigned char*)"\n\rInput:");
        n = UART_InUDec();
        UART_OutString((unsigned char*)" UART_OutUDec = ");
        UART_OutUDec(n);
        UART_OutString((unsigned char*)",  UART_OutDistance ~ ");
        UART_OutDistance(n);
    }
}

void
PLL_init(void)
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
