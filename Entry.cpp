#include "Machine.hpp"
// #include <fmt/format.h>
#include <iostream>
#include <vector>

int main() {

    int somevalue_1 = 5;
    int somevalue_2 = 10;
    int somevalue_3 = 54;

    Machine machine;
    std::vector<Instruction> Program;
    Program.push_back({OP_ADD, REGISTER_1, REGISTER_2});
    Program.push_back({OP_ADD, REGISTER_1, REGISTER_2});
    Program.push_back({OP_ADD, REGISTER_1, REGISTER_2});

    machine.Mov(&machine.R1, somevalue_1);
    machine.Mov(&machine.R2, somevalue_2);

    for (auto Inst : Program) {
        machine.DecodeInstruction(Inst);
    }
    std::cout << machine.Out(&machine.R1) << std::endl;

    

    machine.Mov(&machine.R1, somevalue_1);
    machine.Mov(&machine.R2, somevalue_2);
    machine.Add(&machine.R1, &machine.R2);
    machine.Mov(&machine.R2, somevalue_3);
    machine.Sub(&machine.R1, &machine.R2);
    std::cout << machine.Out(&machine.R1) << std::endl;

    Instruction instruction_1 = {OP_ADD, REGISTER_1, REGISTER_2};
    machine.DecodeInstruction(instruction_1);


    std::cout << machine.Out(&machine.R1) << std::endl;


    return 0;
}
