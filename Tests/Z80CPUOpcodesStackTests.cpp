/*
 * Z80CPUOpcodesStackTests.cpp
 *
 *  Created on: 13 kwi 2014
 *      Author: cod3r
 */




#include <stdexcept>
#include "Z80CPUModuleTest.hpp"
#include "Z80Registers.hpp"
#include "Z80Opcodes.hpp"
#include "Z80CPUModule.hpp"
#include "Helpers.hpp"

TEST(Z80CPUModule_Stack, C5_PUSH_BC) {
    const UINT8 opcodeNumber = 0xC5;
    const UINT16 valueOfBCRegisterBefore = 0x12;
    const UINT16 valueOfPCRegisterAfter = 1;
    const UINT16 stackAddr = 0x1000;
    UINT16 someVal = 0;
    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(stackAddr)).WillOnce(Return(&someVal));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBCRegisterBefore;
    regToSet.SP = stackAddr;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.BC = valueOfBCRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.SP = stackAddr - 2;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;
}



TEST(Z80CPUModule_Stack, C1_POP_BC) {
    const UINT8 opcodeNumber = 0xC1;
    const UINT16 valueOfBCRegisterAfter = 0x12;
    const UINT16 valueOfPCRegisterAfter = 1;
    const UINT16 stackAddr = 0x1000;
    UINT16 someVal = 0x12;
    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(stackAddr)).WillOnce(Return(someVal));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = stackAddr;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.BC = valueOfBCRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.SP = stackAddr + 2;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;
}

TEST(Z80CPUModule_Stack, F1_POP_AF) {
    const UINT8 opcodeNumber = 0xF1;
    const UINT16 valueOfAFRegisterAfter = 0x12;
    const UINT16 valueOfPCRegisterAfter = 1;
    const UINT16 stackAddr = 0x1000;
    UINT16 someVal = 0x12;
    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(stackAddr+2)).WillOnce(Return(someVal));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = stackAddr;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.AF = valueOfAFRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.SP = stackAddr + 2;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;
}

