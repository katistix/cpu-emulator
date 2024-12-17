# CPU Emulator 🖥️

A simple CPU emulator written in C++ that simulates basic instructions. Let's bring your assembly code to life! 💻✨

---

## Instruction Set 📝

The CPU emulator supports the following instructions:

| **Instruction**        | **Description**                                                        |
|------------------------|------------------------------------------------------------------------|
| `MOV <reg> <val>`       | Move a value into a register 🏷️                                          |
| `MOVR <reg1> <reg2>`    | Move the value of one register into another 🔄                           |
| `ADD <reg1> <reg2>`     | Add the value of one register to another ➕                             |
| `SUB <reg1> <reg2>`     | Subtract the value of one register from another ➖                      |
| `PRINT <reg>`           | Print the value of a register 🖨️                                        |
| `INCR <reg>`            | Increment the value of a register 🔼                                    |
| `DECR <reg>`            | Decrement the value of a register 🔽                                    |
| `BEQ <reg1> <reg2> <label>` | Branch to a label if two registers are equal 🚦                    |
| `BNE <reg1> <reg2> <label>` | Branch to a label if two registers are not equal ✖️               |
| `BLT <reg1> <reg2> <label>` | Branch to a label if the first register is less than the second ⬇️ |
| `JMP <label>`           | Jump to a label 🔁                                                      |
| `HALT`                  | Halt the program ⏹️                                                     |

---

## Example Assembly Code 🧑‍💻

This example demonstrates a Fibonacci Sequence Generator that calculates and prints the first N Fibonacci numbers.

```assembly
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
```


## Future Improvements 🚀
- [ ] Add support for binary and hexadecimal numbers (e.g., `MOV R0 0b1010`, `MOV R1 0x0A`)
- [ ] Add support for bitwise operations (e.g., `AND`, `OR`, `XOR`, `NOT`, `LSHIFT`, `RSHIFT`)
- [ ] Add support for memory operations (e.g., `LOAD`, `STORE`)
- [ ] Add support for function calls and stack operations (e.g., `CALL`, `RET`, `PUSH`, `POP`)


---

## Contributing 🤝

We would love to have your contributions! Here's how you can help improve this project:

1. Fork this repository 🍴
2. Create a new branch (`git checkout -b feature-branch`) 🌿
3. Make your changes and commit them (`git commit -m 'Add a new feature'`) 💡
4. Push to the branch (`git push origin feature-branch`) 🚀
5. Open a pull request 📩

Let's build something awesome together! 🙌

---

## License 📜

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Support ☕️

If you like this project and want to support its development, you can buy me a coffee:

<a href="https://www.buymeacoffee.com/katistix" target="_blank"><img src="https://www.buymeacoffee.com/assets/img/custom_images/yellow_img.png" alt="Buy Me A Coffee"></a>

Thank you for your support! 😊