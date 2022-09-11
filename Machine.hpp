

#ifndef MACHINE_H
#define MACHINE_H

#include <vector>

using REG = unsigned int;
using FLAGReg = unsigned int;
using REGRef = REG *;

#define OP_RESERVED 0
#define OP_MOV 1
#define OP_ADD 2
#define OP_SUB 3
#define OP_MOV_IMM 4
#define OP_ADD_IMM 5
#define OP_SUB_IMM 6
#define OP_CMPEQ 7
#define OP_JAE 8
#define OP_JNE 9
#define OP_RET 15

#define REGISTER_1 1
#define REGISTER_2 2
#define REGISTER_3 3
#define REGISTER_OUT 4


struct EFlags {
    EFlags() : OF(0), UF(0), CMP(0) {}
    FLAGReg OF : 1;
    FLAGReg UF : 1;
    FLAGReg CMP : 1;
    FLAGReg : 1;
};

// 2-byte aligned instruction 
struct Instruction {
    uint8_t OPCODE : 4;
    uint8_t REG_1 : 4;
    // second part of the op maybe either src reg or im value
    union {
        int IMMVal : 8;
        uint8_t REG_2 : 4;
    };
};


/* A Small virtual machine with 3 registers, two param opcode syntax */
class Machine {


    public:

        Machine() : R1(0), R2(0), R3(0), OUT(0), IP(0) {};
        void DecodeInstruction(Instruction & Inst);
        void LoadProgram(const std::vector<Instruction> & Program);
        void Execute();
        void Reset();

        REG Out(REGRef);


        // visible registers
        REG R1;
        REG R2;
        REG R3;
        REG OUT;

    protected:

        REGRef DecodeRegisterOp(REG _r);
        Instruction & GetNextInstruction();

        void Mov(REGRef a, REGRef b);
        void Mov(REGRef a, char val);
        void Add(REGRef a, REGRef b);
        void Add(REGRef a, char b);
        void Sub(REGRef a, REGRef b);
        void CmpEQ(REGRef a, REGRef b);
        void Jae(char offset);
        void Jne(char offset);

        REG IP;
        EFlags Flags;

        std::vector<Instruction> Memory;
        std::vector<Instruction> arse;

    private:


};

#endif