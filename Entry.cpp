#include "Machine.hpp"
// #include <fmt/format.h>
#include <iostream>
#include <vector>

int main() {

    Machine machine;
    std::vector<Instruction> Program;
    Program.push_back({OP_MOV_IMM, REGISTER_1, 55});
    Program.push_back({OP_MOV_IMM, REGISTER_2, 7});
    Program.push_back({OP_ADD, REGISTER_1, REGISTER_2});
    Program.push_back({OP_ADD, REGISTER_1, REGISTER_2});
    Program.push_back({OP_ADD, REGISTER_1, REGISTER_2});
    Program.push_back({OP_SUB, REGISTER_1, REGISTER_2});
    Program.push_back({OP_ADD_IMM, REGISTER_1, 11});
    Program.push_back({OP_MOV, REGISTER_OUT, REGISTER_1});

    for (auto Inst : Program) {
        machine.DecodeInstruction(Inst);
    }
    std::cout << machine.Out(&machine.R1) << std::endl;

    return 0;
}
