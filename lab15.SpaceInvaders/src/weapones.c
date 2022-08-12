#include "weapones.h"

static void
PortE_Init(void)
{
    SYSCTL_RCGC2_R |= 0x00000010;
    GPIO_PORTE_DIR_R &= ~0x03;
    GPIO_PORTE_AFSEL_R &= ~0x03;
    GPIO_PORTE_DEN_R |= 0x03;
    GPIO_PORTE_AMSEL_R &= ~0x03;
    GPIO_PORTE_PCTL_R &= ~0x03;
}

void
Weapones_Init(void)
{
    PortE_Init();
}

unsigned long
Weapones_GetButtons(void)
{
    return GPIO_PORTE_DATA_R & 0x03;
}
