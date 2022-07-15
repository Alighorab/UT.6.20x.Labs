void DisableInterrupts(void);
void EnableInterrupts(void);
void WaitForInterrupt(void);
void StartCritical(void);
void EndCritical(void);

void
DisableInterrupts(void)
{
    __asm__ 
    (
        "CPSID  I"
    );
}

void
EnableInterrupts(void)
{
    __asm__ 
    (
        "CPSIE I"
    );
}

void
WaitForInterrupt(void)
{
    __asm__ 
    (
        "WFI"
    );
}

void
StartCritical(void)
{
    __asm__ 
    (
        "MRS R0, PRIMASK\n"
        "CPSID I"
    );
}

void
EndCritical(void)
{
    __asm__
    (
        "MSR    PRIMASK, R0"
    );
}
