; Fibonacci Sequence Generator
; This program calculates and prints the first N Fibonacci numbers

; Initialize registers
MOV R0 0      ; R0 = 0 (first Fibonacci number)
MOV R1 1      ; R1 = 1 (second Fibonacci number)
MOV R2 10     ; R2 = 10 (number of Fibonacci numbers to print)
MOV R3 0      ; R3 = 0 (counter)

loop:
    PRINT R0   ; Print the current Fibonacci number (R0)
    INCR R3    ; Increment the counter

    ; Check if we have printed N numbers
    BEQ R3 R2 exit ; If counter (R3) equals N (R2), exit loop

    ; Calculate next Fibonacci number
    MOVR R4 R0   ; Move current Fibonacci number (R0) to R4
    ADD R0 R1   ; Update R0 to the next Fibonacci number (R0 + R1)
    MOVR R1 R4   ; Update R1 to the last printed Fibonacci number

    JMP loop    ; Repeat the loop

exit:
    HALT        ; End of program
