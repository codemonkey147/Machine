#ifndef MACHINE_H
#define MACHINE_H

using REG = int;
using REGRef = REG *;

#define OP_MOV 0001
#define OP_ADD 0002
#define OP_SUB 0003
#define OP_MOV_IMM 0004
#define OP_ADD_IMM 0005

#define REGISTER_1 001
#define REGISTER_2 002
#define REGISTER_3 003
#define REGISTER_OUT 004


struct EFlags {
    int OF : 1;
    int UF : 1;
    int CMP : 1;
    int : 0;
};

// 2-byte aligned instruction 
struct Instruction {
    int OPCODE : 4;
    int REG_1 : 4;
    // second part of the op maybe either src reg or im value
    union {
        int IMMVal : 8;
        int REG_2 : 4;
    };
};

/* A Small virtual machine with 3 registers, two param opcode syntax */
class Machine {


    public:

        Machine() : R1(0), R2(0), R3(0), OUT(0), SP(0) {};
        void DecodeInstruction(Instruction & Inst);
        REGRef DecodeRegisterOp(REG _r);

        void Mov(REGRef a, REGRef b);
        void Mov(REGRef a, char val);
        void Add(REGRef a, REGRef b);
        void Add(REGRef a, char b);
        void Sub(REGRef a, REGRef b);
        REG Out(REGRef);


        // visible registers
        REG R1;
        REG R2;
        REG R3;
        REG OUT;

    protected:

        REG SP;

};

#endif