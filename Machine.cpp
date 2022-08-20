#include "Machine.hpp"
#include <iostream>


void Machine::DecodeInstruction(Instruction & Inst) {
    int op_code = Inst.OPCODE;
    REGRef _r1 = nullptr;
    REGRef _r2 = nullptr;

    if(Inst.REG_1 == REGISTER_1) {
        _r1 = &R1;
    }

    if(Inst.REG_2 == REGISTER_2) {
        _r2 = &R2;
    }

    if(op_code == OP_MOV) {
        std::cout << "mov detected " << std::endl;
        Mov(_r1, _r2);
        return;
    }

    if(op_code == OP_ADD) {
        std::cout << "add detected " << std::endl;
        Add(_r1, _r2);
        return;
    }


    std::cout << "unknown op" << std::endl;
}

void Machine::Mov(REGRef a, REGRef b) {
    a = b;
    SP++;
}

void Machine::Mov(REGRef a, int b) {
    *a = b;
    SP++;
}

void Machine::Add(REGRef a, REGRef b) {
    *a = *a + *b;
    SP++;
}

void Machine::Sub(REGRef a, REGRef b) {
    *a = *a - *b;
    SP++;
}

REG Machine::Out(REGRef a) {
    OUT = *a;
    SP++;
    return OUT;
}