#include "Machine.hpp"
#include <iostream>


void Machine::DecodeInstruction(Instruction & Inst) {

    int op_code = Inst.OPCODE;
    REGRef _r1 = DecodeRegisterOp(Inst.REG_1);
    REGRef _r2 = DecodeRegisterOp(Inst.REG_2);

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

    if(op_code == OP_SUB) {
        std::cout << "sub detected " << std::endl;
        Sub(_r1, _r2);
        return;
    }

    std::cout << "unknown op" << std::endl;
}

REGRef Machine::DecodeRegisterOp(REG _r) {
    switch(_r) {
        case REGISTER_1:
            return &R1;
        case REGISTER_2:
            return &R2;
        case REGISTER_3:
            return &R3;
    }
    return nullptr;
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