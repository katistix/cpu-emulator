#ifndef CPU_H
#define CPU_H

#include <array>
#include <iostream>
#include <cstdint>
#include <string>

class CPU
{
public:
    static const int NUM_REGISTERS = 4;
    static const int MEMORY_SIZE = 1024;

    enum class Instruction
    {
        MOV_IMM_TO_REG = 0,
        MOV_REG_TO_REG,
        ADD,
        SUB,
        INCR,
        DECR,
        JMP,
        BEQ,
        BNE,
        BLT,
        PRINT,
        PRINTC,
        HALT = 255
    };

    CPU();

    void execute();
    void handle_instruction(uint32_t instruction);
    void load_program(const std::array<uint32_t, MEMORY_SIZE> &program);
    void print_state() const;

    bool is_halted() const { return halted; }

private:
    std::array<uint32_t, NUM_REGISTERS> registers;
    std::array<uint32_t, MEMORY_SIZE> memory;
    uint32_t program_counter;
    bool halted;
};

#endif // CPU_H
