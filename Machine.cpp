#include "Machine.hpp"
#include <vector>

// planning to change all std::iostream to fmtlib
#define FMT_HEADER_ONLY
#include "fmt/include/fmt/core.h"

void Machine::DecodeInstruction(Instruction & Inst) {

    int op_code = Inst.OPCODE;
    REGRef _r1 = DecodeRegisterOp(Inst.REG_1);
    REGRef _r2 = DecodeRegisterOp(Inst.REG_2);

    if(op_code == OP_MOV) {
        fmt::print("mov detected\n");
        Mov(_r1, _r2);
        return;
    }

    if(op_code == OP_MOV_IMM) {
        fmt::print("mov IMM detected\n");
        char imm = Inst.IMMVal;
        Mov(_r1, imm);
        return;
    }

    if(op_code == OP_ADD) {
        fmt::print("add detected\n");
        Add(_r1, _r2);
        return;
    }

    if(op_code == OP_ADD_IMM) {
        fmt::print("add IMM detected\n");
        char imm = Inst.IMMVal;
        Add(_r1, imm);
        return;
    }

    if(op_code == OP_SUB) {
        fmt::print("sub detected\n");
        Sub(_r1, _r2);
        return;
    }

    if(op_code == OP_CMP) {
        fmt::print("cmp detected\n");
        Cmp(_r1, _r2);
        return;
    }

    if(op_code == OP_JAE) {
        fmt::print("JAE detected\n");
        char jmp_offset = Inst.IMMVal;
        Jae(jmp_offset);
        return;
    }

    if (op_code == OP_JNE) {
        fmt::print("JNE detected\n");
        char jmp_offset = Inst.IMMVal;
        Jne(jmp_offset);
        return;
    }

    if(op_code == OP_RET) { 
        fmt::print("ret detected\n");
        return;
    }

    fmt::print("unknown op\n");
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
        fmt::print("{}\n", IP);
    }
    fmt::print("Program finished executing.\n");
}

void Machine::Reset() {
    IP = 0;
    Flags.CMP = 0;
    Flags.OF = 0;
    Flags.UF = 0;
    Memory.clear(); 

    
    fmt::print("*** machine has been reset ***\n\n");
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
        fmt::print("The value of IP post jump is: {}\n", IP);
        Flags.CMP = 0;
        return;
    }
    IP++;
}

void Machine::Jne(char offset) {
    if (offset != 0 && Flags.CMP == 0) {
        IP += offset;
        fmt::print("The value of IP post jump is: {}\n", IP);
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