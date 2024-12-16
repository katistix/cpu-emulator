#include "cpu.h"

CPU::CPU() : registers{}, memory{}, program_counter(0), halted(false) {}

void CPU::load_program(const std::array<uint32_t, MEMORY_SIZE> &program)
{
    program_counter = 0; // Start at the beginning of the program

    for (size_t i = 0; i < program.size(); ++i)
    {
        memory[i] = program[i];
    }
}

void CPU::execute()
{
    while (!halted)
    {
        uint32_t instruction = memory[program_counter++];
        handle_instruction(instruction);
    }
}

void CPU::handle_instruction(uint32_t instruction)
{
    switch (static_cast<Instruction>(instruction))
    {
    case Instruction::MOV_IMM_TO_REG:
    {
        uint32_t reg = memory[program_counter++];
        uint32_t value = memory[program_counter++];
        registers[reg] = value;
        break;
    }
    case Instruction::MOV_REG_TO_REG:
    {
        uint32_t reg1 = memory[program_counter++];
        uint32_t reg2 = memory[program_counter++];
        registers[reg1] = registers[reg2];
        break;
    }
    case Instruction::ADD:
    {
        uint32_t reg1 = memory[program_counter++];
        uint32_t reg2 = memory[program_counter++];
        registers[reg1] += registers[reg2];
        break;
    }
    case Instruction::SUB:
    {
        uint32_t reg1 = memory[program_counter++];
        uint32_t reg2 = memory[program_counter++];
        registers[reg1] -= registers[reg2];
        break;
    }
    case Instruction::INCR:
    {
        uint32_t reg = memory[program_counter++];
        registers[reg]++;
        break;
    }
    case Instruction::DECR:
    {
        uint32_t reg = memory[program_counter++];
        registers[reg]--;
        break;
    }
    case Instruction::JMP:
    {
        program_counter = memory[program_counter];
        break;
    }
    case Instruction::BEQ:
    {
        uint32_t reg1 = memory[program_counter++];
        uint32_t reg2 = memory[program_counter++];
        uint32_t target = memory[program_counter++];
        if (registers[reg1] == registers[reg2])
        {
            program_counter = target;
        }
        break;
    }
    case Instruction::BNE:
    {
        uint32_t reg1 = memory[program_counter++];
        uint32_t reg2 = memory[program_counter++];
        uint32_t target = memory[program_counter++];
        if (registers[reg1] != registers[reg2])
        {
            program_counter = target;
        }
        break;
    }
    case Instruction::BLT:
    {
        uint32_t reg1 = memory[program_counter++];
        uint32_t reg2 = memory[program_counter++];
        uint32_t target = memory[program_counter++];
        if (registers[reg1] < registers[reg2])
        {
            program_counter = target;
        }
        break;
    }
    case Instruction::PRINT:
    {
        uint32_t reg = memory[program_counter++];
        std::cout << registers[reg] << std::endl;
        break;
    }
    case Instruction::PRINTC:
    {
        uint32_t reg = memory[program_counter++];
        std::cout << static_cast<char>(registers[reg]);
        break;
    }
    case Instruction::HALT:
    {
        halted = true;
        break;
    }
    default:
        std::cerr << "Unknown instruction: " << instruction << std::endl;
        break;
    }
}

void CPU::print_state() const
{
    std::cout << "---\nRegisters:" << std::endl;
    for (size_t i = 0; i < NUM_REGISTERS; ++i)
    {
        std::cout << "R" << i << ": " << registers[i] << " ";
    }
    std::cout << std::endl;
}