#include "cpu.h"
#include <array>
#include <iostream>

int main()
{

    CPU cpu;
    std::array<uint32_t, CPU::MEMORY_SIZE> program = {
        0, 0, 10, // MOV R1 10
        4, 0,     // INCR R0
        10, 0,    // PRINT R0
        255,      // HALT
    };

    cpu.load_program(program);
    cpu.execute();
    cpu.print_state();

    return 0;
}
