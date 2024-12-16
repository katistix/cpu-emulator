#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>
#include "cpu.h"

class Assembler
{
public:
    Assembler();
    bool assemble(const std::vector<std::string> &lines, std::array<uint32_t, CPU::MEMORY_SIZE> &program);

private:
    std::unordered_map<std::string, uint32_t> labels;

    bool first_pass(const std::vector<std::string> &lines);
    bool second_pass(const std::vector<std::string> &lines, std::array<uint32_t, CPU::MEMORY_SIZE> &program);
    size_t getInstructionSize(const std::string &line);

    std::unordered_map<std::string, uint8_t> reg_map = {
        {"R0", 0},
        {"R1", 1},
        {"R2", 2},
        {"R3", 3},
        {"R4", 4},
        {"R5", 5},
        {"R6", 6},
        {"R7", 7},

    };
};

#endif // ASSEMBLER_H