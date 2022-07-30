.global  DisableInterrupts
.global  EnableInterrupts
.global  StartCritical
.global  EndCritical
.global  WaitForInterrupt

DisableInterrupts:
        CPSID  I
        BX     LR

EnableInterrupts:
        CPSIE  I
        BX     LR

StartCritical:
        MRS    R0, PRIMASK 
        CPSID  I
        BX     LR

EndCritical:
        MSR    PRIMASK, R0
        BX     LR

WaitForInterrupt:
        WFI
        BX     LR
