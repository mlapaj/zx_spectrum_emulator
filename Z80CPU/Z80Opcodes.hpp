/*
 * File:   Z80Opcodes.hpp
 * Author: lapajmar
 *
 * Created on 18 marzec 2014, 16:45
 */

#ifndef Z80OPCODES_HPP
#define	Z80OPCODES_HPP


#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "Z80Memory.hpp"
#include "Z80Registers.hpp"
#include "../Tests/Z80CPUModuleTest.hpp"
#include "Z80OpcodesMacros.hpp"

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

struct opcodeInfo
{
	string mnemonic;
	int size;
};


enum condition
    {
       NZ = 0,
       Z = 1,
       NC = 2,
       C = 3,
       PO = 4,
       PE = 5,
       P = 6,
       M = 7,
    };

enum aluOperation
    {
       ADD_A = 0,
       ADC_A = 1,
       SUB = 2,
       SBC_A = 3,
       AND = 4,
       XOR = 5,
       OR = 6,
       CP = 7,
    };
enum rotOperation
    {
       RLC = 0,
       RRC = 1,
       RL = 2,
       RR = 3,
       SLA = 4,
       SRA = 5,
       SLL = 6,
       SRL = 7,
    };

enum interruptMode
    {
       MODE_0 = 0,
       MODE_0_1 = 1,
       MODE_1 = 2,
       MODE_2 = 3
    };

enum blockOperationType
{
    LDI,
    LDD,
    LDIR,
    LDDR,
    CPI,
    CPD,
    CPIR,
    CPDR,
    INI,
    IND,
    INIR,
    INDR,
    OUTI,
    OUTD,
    OUTIR,
    OUTDR
};




template<typename tZ80Memory>
class Z80Opcodes {
public:
	int debug;
    // typedef void (Z80Opcodes::*Z80Instruction)();
    Z80Opcodes(tZ80Memory &cZ80Memory,Z80Registers &cZ80Registers);
	void executeOpcode();
    virtual ~Z80Opcodes();
	int getCpuCurrentInstructionCycles(){ return currentInstructionCycles;}

    opcodeInfo debugOpcode(UINT8 opcode,UINT16 pc);
private:
	int counterInterrupt;
	int counterInstructionCycles;
	int currentInstructionCycles;
	int additionalTCycles;
	bool fdPrefixUsed;
	bool ddPrefixUsed;
	bool debugHLReplaced;
	bool debugRegReplaced;
    Z80Registers &reg;
    tZ80Memory &mem;
    LoggerPtr logger;
    void parseNormalOpcode(UINT8 opcode);

    opcodeInfo debugCBPrefixOpcode(UINT8 opcode,UINT16 pc);
	opcodeInfo debugFDCBorDDCBPrefixOpcode(UINT8 opcode,UINT16 pc);
    opcodeInfo debugEDPrefixOpcode(UINT16 pc);

	void parseCBPrefixOpcode();
    void parseEDPrefixOpcode();
    void parseFDCBorDDCBPrefixOpcode();

    inline string debugGet16BRegisterPair1(int p);
    inline UINT16 *parseGet16BRegisterPair1(int p);

    inline string debugGet16BRegisterPair2(int p);
    inline UINT16 *parseGet16BRegisterPair2(int p);

    inline string debugGet8BRegisterPair(int p, UINT16 pc);
    inline UINT8 *parseGet8BRegisterPair(int p);

    inline string debugCondition(int y);
    inline condition parseCondition(int y);

    inline string debugALUOperation(int y);
    inline aluOperation parseALUOperation(int y);

    inline rotOperation parseROTOperation(int y);
    inline string debugROTOperation(int y);

    inline interruptMode parseInterruptModes(int y);
    inline blockOperationType parseBlockOperation(int y,int z);
    inline string debugBlockOperation(int y,int z);
    void loadNormalInstructions();

    void NOP();

    void INC_r16(UINT16 *dst);
    void DEC_r16(UINT16 *dst);
    void INC_r8(UINT8 *dst);
    void DEC_r8(UINT8 *dst);
    void LD_r16_nn(UINT16 *dst);
    void LD_addr_r16_A(UINT16 *dst);
    void LD_r8_n(UINT8 *dst);
    void LD_A_addr_r16(UINT16 *dst);
    void LD_addr_nn_r16(UINT16 *dst);
    void LD_addr_nn_r8(UINT8 *dst);
    void LD_r16_addr_nn(UINT16 *dst);
    void LD_r8_addr_nn(UINT8 *dst);
    void LD_r8_r8(UINT8 *src,UINT8 *dst);
    void LD_r16_r16(UINT16 *src,UINT16 *dst);

    void RLCA();
    void RRCA();
    void RLA();
    void RRA();
    void DAA();
    void CPL();
    void SCF();
    void CCF();


    void EX_AF_sAF();
    void EX_addr_SP_IX();
    void EX_addr_SP_IY();
    void EX_addr_SP_HL();
    void EX_DE_HL();
    void EXX();


    void HALT();

    void IM(interruptMode mode);
    void DI();
    void EI();

    void ADD_HL_r16(UINT16 *dst);
    void ADD_IX_r16(UINT16 *dst);
    void ADD_IY_r16(UINT16 *dst);
    void SBC_HL_r16(UINT16 *dst);
    void ADC_HL_r16(UINT16 *dst);


    void DJNZ();
    void JR();
    void CALL_cond_nn(condition cond);
    void CALL_nn();
    void JR_cond_nn(condition cond);
    void JP_cond_nn(condition cond);
    void JP(UINT16 *dst);
    void JP(UINT16 dst); // to fix
    void JP_nn();
    void RET(condition cond);
    void RETN();
    void RETI();
    void RET();
    void RST(UINT16 val);

    void ALU(aluOperation operType,UINT8 *dst);
    void ALU_n(aluOperation operType);
    void BLI(blockOperationType operType);

    // stack
    void POP16(UINT16 *dst);
    void PUSH16(UINT16 *dst);


    // io
    void OUT_addr_n_A();
    void IN_A_addr_n();
    void IN_r8_addr_C(UINT8 *dst);
    void IN_addr_C();
    void OUT_addr_C_r8(UINT8 *dst);
    void OUT_addr_C();

    void ROT_r8(rotOperation rot,UINT8 *dst);

    void BIT(UINT8 y,UINT8 *dst);
    void SET(UINT8 y,UINT8 *dst);
    void RES(UINT8 y,UINT8 *dst);
    void NEG();

    void RRD();
    void RLD();


};


#endif	/* Z80OPCODES_HPP */

