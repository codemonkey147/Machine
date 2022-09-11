#include "Machine.hpp"
// #include <fmt/format.h>
#include <iostream>
#include <vector>

int main() {

    Machine Machine;
    std::vector<Instruction> Program;
    Program.push_back({OP_MOV_IMM, REGISTER_1, 55});
    Program.push_back({OP_MOV_IMM, REGISTER_2, 7});
    Program.push_back({OP_CMPEQ, REGISTER_1, REGISTER_2});
    Program.push_back({OP_MOV_IMM, REGISTER_2, 55});
    Program.push_back({OP_CMPEQ, REGISTER_1, REGISTER_2});
    Program.push_back({OP_JAE, 0, 5});
    Program.push_back({OP_ADD, REGISTER_1, REGISTER_2});
    Program.push_back({OP_ADD, REGISTER_1, REGISTER_2});
    Program.push_back({OP_ADD, REGISTER_1, REGISTER_2});
    Program.push_back({OP_SUB, REGISTER_1, REGISTER_2});
    Program.push_back({OP_ADD_IMM, REGISTER_1, 11});
    Program.push_back({OP_MOV, REGISTER_OUT, REGISTER_1});
    Program.push_back({OP_RET, 0, 0});

    Machine.LoadProgram(Program);
    Machine.Execute();

    std::cout << Machine.Out(&Machine.R1) << std::endl;
    Machine.Reset();
    

    // simple loop sum of digits 1 to 10.
    std::vector<Instruction> ProgramLoop;
    ProgramLoop.push_back({OP_MOV_IMM, REGISTER_1, 10});
    ProgramLoop.push_back({OP_MOV_IMM, REGISTER_2, 0});

    // loop
    ProgramLoop.push_back({OP_ADD_IMM, REGISTER_2, 1});
    ProgramLoop.push_back({OP_ADD, REGISTER_3, REGISTER_2});
    ProgramLoop.push_back({OP_CMPEQ, REGISTER_1, REGISTER_2});
    ProgramLoop.push_back({OP_JNE, 0, -3});

    ProgramLoop.push_back({OP_MOV, REGISTER_OUT, REGISTER_3});
    ProgramLoop.push_back({OP_RET, 0, 0});

    Machine.LoadProgram(ProgramLoop);
    Machine.Execute();

    std::cout << "The sum of the digits 1 to 10 is: ";
    std::cout << Machine.Out(&Machine.R3) << std::endl;
    Machine.Reset();

    return 0;
}
