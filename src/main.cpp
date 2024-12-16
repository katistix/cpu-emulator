#include "cpu.h"
#include "assembler.h"
#include <array>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
    // Check for the correct number of command-line arguments
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <assembly_file.asm>" << std::endl;
        return 1;
    }

    // Open the assembly file specified in the command-line argument
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    // Read lines from the file into a vector
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line))
    {
        // Optionally trim whitespace and ignore empty lines
        if (!line.empty())
        {
            lines.push_back(line);
        }
    }

    inputFile.close(); // Close the file after reading

    Assembler assembler;
    CPU cpu;
    std::array<uint32_t, CPU::MEMORY_SIZE> program;

    // Assemble the read lines into the program
    if (!assembler.assemble(lines, program))
    {
        std::cerr << "Failed to assemble program" << std::endl;
        return 1;
    }

    // Print the assembled program
    for (size_t i = 0; i < program.size(); ++i)
    {
        std::cout << program[i] << " ";
    }
    std::cout << std::endl;

    cpu.load_program(program);
    cpu.execute();
    cpu.print_state();

    return 0;
}
