.global  Random_Init
.global  Random
.global  Random32

Random_Init:
    LDR R2,=M
    STR R0,[R2]
    BX  LR

Random32: 
    LDR R2,=M
    LDR R0,[R2]
    LDR R1,=1664525
    MUL R0,R0,R1 
    LDR R1,=1013904223
    ADD R0,R1    
    STR R0,[R2]  
    BX  LR

Random:
    LDR R2,=M     
    LDR R0,[R2]   
    LDR R1,=1664525
    MUL R0,R0,R1  
    LDR R1,=1013904223
    ADD R0,R1     
    STR R0,[R2]   
    LSR R0,R0,#24 
    BX  LR
