#include "Machine.hpp"
#include <iostream>
#include <vector>

void Machine::DecodeInstruction(Instruction & Inst) {

    int op_code = Inst.OPCODE;
    REGRef _r1 = DecodeRegisterOp(Inst.REG_1);
    REGRef _r2 = DecodeRegisterOp(Inst.REG_2);

    if(op_code == OP_MOV) {
        std::cout << "mov detected " << std::endl;
        Mov(_r1, _r2);
        return;
    }

    if(op_code == OP_MOV_IMM) {
        std::cout << "mov IMM detected " << std::endl;
        char imm = Inst.IMMVal;
        Mov(_r1, imm);
        return;
    }

    if(op_code == OP_ADD) {
        std::cout << "add detected " << std::endl;
        Add(_r1, _r2);
        return;
    }

    if(op_code == OP_ADD_IMM) {
        std::cout << "add IMM detected " << std::endl;
        char imm = Inst.IMMVal;
        Add(_r1, imm);
        return;
    }

    if(op_code == OP_SUB) {
        std::cout << "sub detected " << std::endl;
        Sub(_r1, _r2);
        return;
    }

    if(op_code == OP_CMP) {
        std::cout << "cmp detected " << std::endl;
        Cmp(_r1, _r2);
        return;
    }

    if(op_code == OP_JAE) {
        std::cout << "JAE detected " << std::endl;
        char jmp_offset = Inst.IMMVal;
        Jae(jmp_offset);
        return;
    }

    if (op_code == OP_JNE) {
        std::cout << "JNE detected " << std::endl;
        char jmp_offset = Inst.IMMVal;
        Jne(jmp_offset);
        return;
    }

    if(op_code == OP_RET) { 
        std::cout << "ret detected " << std::endl;
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
        case REGISTER_OUT:
            return &OUT;
    }
    return nullptr;
}

Instruction & Machine::GetNextInstruction() {
    return Memory[IP];
}

void Machine::LoadProgram(const std::vector<Instruction> & Program) {
    Memory = Program;
}

void Machine::Execute() {
    Instruction Next = {0, 0, 0};
    size_t MaxCount = 20;
    while (Next.OPCODE != OP_RET || IP > MaxCount) {
        Next = GetNextInstruction();
        DecodeInstruction(Next);
        std::cout << IP << std::endl;
    }
    std::cout << "Program Finished Executing." << std::endl;
}

void Machine::Reset() {
    IP = 0;
    Flags.CMP = 0;
    Flags.OF = 0;
    Flags.UF = 0;
    Memory.clear(); 

    std::cout << "Program Finished Executing." << std::endl;
}

void Machine::Mov(REGRef a, REGRef b) {
    a = b;
    IP++;
}

void Machine::Mov(REGRef a, char b) {
    *a = b;
    IP++;
}

void Machine::Add(REGRef a, REGRef b) {
    *a = *a + *b;
    IP++;
}

void Machine::Add(REGRef a, char b) {
    *a = *a + b;
    IP++;
}

void Machine::Sub(REGRef a, REGRef b) {
    *a = *a - *b;
    IP++;
}

void Machine::Cmp(REGRef a, REGRef b) {
    int cmp_result = *a - *b;
    if (cmp_result == 0) {
        Flags.CMP = 1;
    }
    IP++;
}
void Machine::Jae(char offset) {
    if (offset != 0 && Flags.CMP == 1) {
        IP += offset;
        std::cout << "The value of the Instruction Pointer post Jump is: " << IP << std::endl;
        Flags.CMP = 0;
        return;
    }
    IP++;
}

void Machine::Jne(char offset) {
    if (offset != 0 && Flags.CMP == 0) {
        IP += offset;
        std::cout << "The value of the Instruction Pointer post Jump is: " << IP << std::endl;
        Flags.CMP = 0;
        return;
    }
    IP++;
}

REG Machine::Out(REGRef a) {
    OUT = *a;
    IP++;
    return OUT;
}