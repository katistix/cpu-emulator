# cpu-emulator
A simple CPU emulator written in C++.


## Future work
- Write a simple assembler for the CPU that uses the following syntax
```assembly
MOV R0, 10 ; move immediate value 10 to register R0
MOVR R0, R1 ; move value from R1 to R0

ADD R_dest, R_src ; R_dest = R_dest + R_src
SUB R_dest, R_src ; R_dest = R_dest - R_src

INCR R0 ; R0 = R0 + 1
DECR R0 ; R0 = R0 - 1

; Control flow
JMP label ; jump to label
BEQ R0, R1, label ; jump to label if R0 == R1
BNE R0, R1, label ; jump to label if R0 != R1
BLT R0, R1, label ; jump to label if R0 < R1


; Output
PRINT R0 ; print value of R0
PRINTC R0 ; print character value of R0
```
> All those instructions should technically already be implemented in the CPU, but the assembler will make it easier to write programs for the CPU.