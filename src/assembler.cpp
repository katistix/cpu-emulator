#include "assembler.h"
#include <sstream>

Assembler::Assembler() : labels{} {}

bool Assembler::assemble(const std::vector<std::string> &lines, std::array<uint32_t, CPU::MEMORY_SIZE> &program)
{
    // Strip comments and empty lines
    std::vector<std::string> cleaned_lines;
    for (const std::string &line : lines)
    {
        std::string cleaned_line = line;
        size_t comment_pos = cleaned_line.find_first_of(';');
        if (comment_pos != std::string::npos)
        {
            cleaned_line = cleaned_line.substr(0, comment_pos);
        }

        if (!cleaned_line.empty())
        {
            cleaned_lines.push_back(cleaned_line);
        }
    }

    if (!first_pass(cleaned_lines))
    {
        return false;
    }

    if (!second_pass(cleaned_lines, program))
    {
        return false;
    }
    return true;
}

size_t Assembler::getInstructionSize(const std::string &line)
{
    std::istringstream iss(line);
    std::string token;
    size_t count = 0;

    // Count the number of tokens (words) in the line
    while (iss >> token)
    {
        count++;
    }

    return count; // The size is equal to the number of tokens
}

bool Assembler::first_pass(const std::vector<std::string> &lines)
{
    size_t current_address = 0;

    for (const std::string &line : lines)
    {
        // Check if the line is a label
        if (line.back() == ':')
        {
            std::string label = line.substr(0, line.size() - 1); // Remove the colon
            if (labels.find(label) != labels.end())
            {
                std::cerr << "Duplicate label: " << label << std::endl;
                return false;
            }
            labels[label] = current_address; // Store label address
        }
        else
        {
            current_address += getInstructionSize(line); // Increment address based on instruction size
        }
    }

    return true;
}

bool Assembler::second_pass(const std::vector<std::string> &lines, std::array<uint32_t, CPU::MEMORY_SIZE> &program)
{
    size_t current_address = 0;
    for (const std::string &line : lines)
    {
        if (line.back() == ':')
        {
            continue; // Skip label lines
        }

        std::istringstream iss(line);
        std::string instruction;
        iss >> instruction;

        if (instruction.empty())
        {
            continue; // Skip empty instructions
        }

        if (instruction == "MOV")
        {
            std::string arg1, arg2;
            iss >> arg1 >> arg2;
            if (arg1.empty() || arg2.empty())
            {
                std::cerr << "Invalid MOV instruction: " << line << std::endl;
                return false;
            }

            // Use the reg_map to translate register names to numbers
            if (reg_map.find(arg1) == reg_map.end())
            {
                std::cerr << "Invalid register in MOV instruction: " << arg1 << std::endl;
                return false;
            }

            program[current_address++] = static_cast<uint32_t>(CPU::Instruction::MOV_IMM_TO_REG);
            program[current_address++] = reg_map[arg1];   // Translate register using the map
            program[current_address++] = std::stoi(arg2); // Immediate value
        }
        else if (instruction == "MOVR")
        {
            std::string arg1, arg2;
            iss >> arg1 >> arg2;
            if (arg1.empty() || arg2.empty())
            {
                std::cerr << "Invalid MOVR instruction: " << line << std::endl;
                return false;
            }

            program[current_address++] = static_cast<uint32_t>(CPU::Instruction::MOV_REG_TO_REG);
            program[current_address++] = reg_map[arg1];
            program[current_address++] = reg_map[arg2];
        }
        else if (instruction == "ADD")
        {
            std::string arg1, arg2;
            iss >> arg1 >> arg2;
            if (arg1.empty() || arg2.empty())
            {
                std::cerr << "Invalid ADD instruction: " << line << std::endl;
                return false;
            }

            program[current_address++] = static_cast<uint32_t>(CPU::Instruction::ADD);
            program[current_address++] = reg_map[arg1];
            program[current_address++] = reg_map[arg2];
        }
        else if (instruction == "SUB")
        {
            std::string arg1, arg2;
            iss >> arg1 >> arg2;
            if (arg1.empty() || arg2.empty())
            {
                std::cerr << "Invalid SUB instruction: " << line << std::endl;
                return false;
            }

            program[current_address++] = static_cast<uint32_t>(CPU::Instruction::SUB);
            program[current_address++] = reg_map[arg1];
            program[current_address++] = reg_map[arg2];
        }
        else if (instruction == "INCR")
        {
            std::string arg;
            iss >> arg;
            if (arg.empty())
            {
                std::cerr << "Invalid INCR instruction: " << line << std::endl;
                return false;
            }

            program[current_address++] = static_cast<uint32_t>(CPU::Instruction::INCR);
            program[current_address++] = reg_map[arg];
        }
        else if (instruction == "DECR")
        {
            std::string arg;
            iss >> arg;
            if (arg.empty())
            {
                std::cerr << "Invalid DECR instruction: " << line << std::endl;
                return false;
            }

            program[current_address++] = static_cast<uint32_t>(CPU::Instruction::DECR);
            program[current_address++] = reg_map[arg];
        }
        else if (instruction == "PRINT")
        {
            std::string arg;
            iss >> arg;
            if (arg.empty())
            {
                std::cerr << "Invalid PRINT instruction: " << line << std::endl;
                return false;
            }

            program[current_address++] = static_cast<uint32_t>(CPU::Instruction::PRINT);
            program[current_address++] = reg_map[arg];
        }
        else if (instruction == "PRINTC")
        {
            std::string arg;
            iss >> arg;
            if (arg.empty())
            {
                std::cerr << "Invalid PRINTC instruction: " << line << std::endl;
                return false;
            }

            program[current_address++] = static_cast<uint32_t>(CPU::Instruction::PRINTC);
            program[current_address++] = reg_map[arg];
        }
        else if (instruction == "JMP")
        {
            std::string arg;
            iss >> arg;
            if (arg.empty())
            {
                std::cerr << "Invalid JMP instruction: " << line << std::endl;
                return false;
            }

            program[current_address++] = static_cast<uint32_t>(CPU::Instruction::JMP);
            program[current_address++] = labels[arg];
        }
        else if (instruction == "BEQ" || instruction == "BNE" || instruction == "BLT")
        {
            std::string arg1, arg2, arg3;
            iss >> arg1 >> arg2 >> arg3;
            if (arg1.empty() || arg2.empty() || arg3.empty())
            {
                std::cerr << "Invalid branch instruction: " << line << std::endl;
                return false;
            }

            CPU::Instruction branch_instruction;
            if (instruction == "BEQ")
            {
                branch_instruction = CPU::Instruction::BEQ;
            }
            else if (instruction == "BNE")
            {
                branch_instruction = CPU::Instruction::BNE;
            }
            else if (instruction == "BLT")
            {
                branch_instruction = CPU::Instruction::BLT;
            }
            else
            {
                std::cerr << "Unknown branch instruction: " << instruction << std::endl;
                return false;
            }

            program[current_address++] = static_cast<uint32_t>(branch_instruction);
            program[current_address++] = reg_map[arg1];
            program[current_address++] = reg_map[arg2];
            program[current_address++] = labels[arg3];
        }
        else if (instruction == "HALT")
        {
            program[current_address++] = static_cast<uint32_t>(CPU::Instruction::HALT);
        }
        else
        {
            std::cerr << "Unknown instruction: " << instruction << std::endl;
            return false;
        }
    }

    return true;
}
