/*
 * Z80CPUOpcodesLoadTests.cpp
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

TEST(Z80CPUModule_Load, 01_LD_BC_nn) {
    const UINT8 opcodeNumber = 0x1;
    const UINT16 valueOfPCRegisterAfter = 0x3;

    const UINT16 someNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(someNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();
    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.BC = someNumber;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}

TEST(Z80CPUModule_Load, 06_LD_B_n) {
    const UINT8 opcodeNumber = 0x6;
    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(someNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.B = someNumber;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}

TEST(Z80CPUModule_Load, 08_EX_AF_secAF) {
    const UINT8 opcodeNumber = 0x8;

    const UINT16 valueOfAFRegisterBefore = 0xAA;
    const UINT16 valueOfsecAFRegisterBefore = 0x55;

    const UINT16 valueOfAFRegisterAfter = 0x55;
    const UINT16 valueOfsecAFRegisterAfter = 0xAA;

    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 someNumber = 0x12;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.AF = valueOfAFRegisterBefore;
    regToSet.secAF = valueOfsecAFRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.AF = valueOfAFRegisterAfter;
    regCompare.secAF = valueOfsecAFRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;
}


TEST(Z80CPUModule_Load, EB_EX_DE_HL) {
    const UINT8 opcodeNumber = 0xEB;

    const UINT16 valueOfDERegisterBefore = 0xAA;
    const UINT16 valueOfHLRegisterBefore = 0x55;

    const UINT16 valueOfDERegisterAfter = 0x55;
    const UINT16 valueOfHLRegisterAfter = 0xAA;

    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 someNumber = 0x12;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.DE = valueOfDERegisterBefore;
    regToSet.HL = valueOfHLRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.DE = valueOfDERegisterAfter;
    regCompare.HL = valueOfHLRegisterAfter;
    
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;
}


TEST(Z80CPUModule_Load, E3_EX_addr_SP_HL) {
    const UINT8 opcodeNumber = 0xE3;

    const UINT16 valueOfSPRegisterBefore = 0x11AA;
    const UINT16 valueOfHLRegisterBefore = 0x5500;

    const UINT16 valueOfSPRegisterAfter = 0x11AA;
    const UINT16 valueOfHLRegisterAfter = 0x1234;

    const UINT16 valueOfPCRegisterAfter = 0x1;

    UINT16 someNumber = 0x1234;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(valueOfSPRegisterBefore)).WillOnce(Return(&someNumber));
    
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.HL = valueOfHLRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterAfter;
    regCompare.HL = valueOfHLRegisterAfter;
    
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someNumber,valueOfHLRegisterBefore);
    
    delete oZ80CPU;
}



TEST(Z80CPUModule_Load, D9_EXX) {
    const UINT8 opcodeNumber = 0xD9;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    
    
    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    
    regToSet.BC = 0xFF00;
    regToSet.DE = 0xFF00;
    regToSet.HL = 0xFF00;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.BC = 0xffff;
    regCompare.DE = 0xffff;
    regCompare.HL = 0xffff;
    regCompare.secBC = 0xFF00;
    regCompare.secDE = 0xFF00;
    regCompare.secHL = 0xFF00;
    regCompare.PC = 1;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Load, 41_LD_B_C) {
    const UINT8 opcodeNumber = 0x41;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT8 valueOfCRegisterBefore =  0x12;
    const UINT8 valueOfCRegisterAfter =  0x12;
    const UINT8 valueOfBRegisterAfter =  0x12;

    const UINT8 someNumber = 0x12;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.C = valueOfCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.B = valueOfBRegisterAfter;
    regCompare.C = valueOfCRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_Load, 02_LD_addr_BC_A) {
    const UINT8 opcodeNumber = 0x02;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfBCRegisterBefore =  0x1234;
    const UINT8 valueOfARegisterBefore =  0x34;

    MockZ80Memory oMockZ80Memory;
    
    UINT8 somePlaceInMemory = 0;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfBCRegisterBefore)).WillOnce(Return(&somePlaceInMemory));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.BC = valueOfBCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterBefore;
    regCompare.BC = valueOfBCRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(somePlaceInMemory,valueOfARegisterBefore);

    delete oZ80CPU;
}



TEST(Z80CPUModule_Load, 12_LD_addr_DE_A) {
    const UINT8 opcodeNumber = 0x12;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfDERegisterBefore =  0x1234;
    const UINT8 valueOfARegisterBefore =  0x34;

    MockZ80Memory oMockZ80Memory;
    
    UINT8 somePlaceInMemory = 0;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfDERegisterBefore)).WillOnce(Return(&somePlaceInMemory));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.DE = valueOfDERegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterBefore;
    regCompare.DE = valueOfDERegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(somePlaceInMemory,valueOfARegisterBefore);

    delete oZ80CPU;
}



TEST(Z80CPUModule_Load, 0A_LD_A_addr_BC) {
    const UINT8 opcodeNumber = 0xA;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfARegisterBefore = 0x56;
    const UINT16 valueOfBCRegisterBefore = 0x3201;
    
    UINT8 someVal = 16;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfBCRegisterBefore)).WillOnce(Return(&someVal));
    
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();
    
    Z80Registers regToSet;
    regToSet.reset();    
    regToSet.BC = valueOfBCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);
    
    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.A = someVal;
    regCompare.BC = valueOfBCRegisterBefore;
    checkRegisters(regOut,regCompare);    
    delete oZ80CPU;
}


TEST(Z80CPUModule_Load, 1A_LD_A_addr_DE) {
    const UINT8 opcodeNumber = 0x1A;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfARegisterBefore = 0x56;
    const UINT16 valueOfDERegisterBefore = 0x3201;
    
    UINT8 someVal = 16;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfDERegisterBefore)).WillOnce(Return(&someVal));
    
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();
    
    Z80Registers regToSet;
    regToSet.reset();    
    regToSet.DE = valueOfDERegisterBefore;
    oZ80CPU->setRegisters(regToSet);
    
    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.A = someVal;
    regCompare.DE = valueOfDERegisterBefore;
    checkRegisters(regOut,regCompare);    
    delete oZ80CPU;
}



TEST(Z80CPUModule_Load, 22_LD_addr_nn_HL) {
    const UINT8 opcodeNumber = 0x22;
    const UINT16 valueOfPCRegisterAfter = 0x3;
    const UINT16 valueOfHLRegisterBefore = 0x1234;
    const UINT16 someNumber = 0xFF00;
    
    UINT16 someValue = 0;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(someNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(someNumber)).WillOnce(Return(&someValue));
     

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();
    
    Z80Registers regToSet;
    regToSet.reset();    
    regToSet.HL = valueOfHLRegisterBefore;
    oZ80CPU->setRegisters(regToSet);
    
    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.HL = valueOfHLRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValue,valueOfHLRegisterBefore);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Load, 32_LD_addr_nn_A) {
    const UINT8 opcodeNumber = 0x32;
    const UINT16 valueOfPCRegisterAfter = 0x3;
    const UINT8 valueOfARegisterBefore = 0x34;
    const UINT16 someNumber = 0xFF00;
    
    UINT8 someValue = 0;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(someNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(someNumber)).WillOnce(Return(&someValue));
     

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();
    
    Z80Registers regToSet;
    regToSet.reset();    
    regToSet.A = valueOfARegisterBefore;
    oZ80CPU->setRegisters(regToSet);
    
    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValue,regCompare.A );

    delete oZ80CPU;
}


TEST(Z80CPUModule_Load, 2A_LD_HL_addr_nn) {
    const UINT8 opcodeNumber = 0x2A;
    const UINT16 valueOfPCRegisterAfter = 0x3;
    const UINT16 valueOfHLRegisterAfter = 0x3;

    const UINT16 someNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;
    
    UINT16 someValue = 0xF0F0;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(someNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(someNumber)).WillOnce(Return(&someValue));
    
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();
    
    Z80Registers regToSet;
    regToSet.reset();    
    regToSet.HL = valueOfHLRegisterAfter;
    oZ80CPU->setRegisters(regToSet);
    
    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.HL = someValue;
    checkRegisters(regOut,regCompare);

    
    delete oZ80CPU;
}


TEST(Z80CPUModule_Load, 3A_LD_A_addr_nn) {
    const UINT8 opcodeNumber = 0x3A;
    const UINT16 valueOfPCRegisterAfter = 0x3;

    const UINT16 someNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;
    
    UINT8 someValue = 0x21;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));    
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(someNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(someNumber)).WillOnce(Return(&someValue));
            
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();
    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = someValue;
    regCompare.PC = valueOfPCRegisterAfter;    
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_Load, F9_LD_SP_HL) {
    const UINT8 opcodeNumber = 0xF9;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfSPRegisterBefore = 0x0;
    const UINT16 valueOfSPRegisterAfter = 0x12;
    const UINT16 valueOfHLRegisterBefore = 0x12;

    const UINT16 someNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();
    
    Z80Registers regToSet;
    regToSet.reset();    
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.HL = valueOfHLRegisterBefore;
    
    oZ80CPU->setRegisters(regToSet);
    
    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.SP = valueOfSPRegisterAfter;
    regCompare.HL = valueOfHLRegisterBefore;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Load, ED_43_LD_addr_nn_BC) {
    const UINT8 opcodeNumber1 = 0xED;
    const UINT8 opcodeNumber2 = 0x43;
    const UINT16 valueOfPCRegisterAfter = 0x4;
    const UINT16 valueOfBCRegisterBefore = 0x1234;

    const UINT16 someNumber = 0xFF00;
    UINT16 someValue = 0x3300;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    EXPECT_CALL(oMockZ80Memory, get16(2)).WillOnce(Return(someNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(someNumber)).WillOnce(Return(&someValue));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.BC = valueOfBCRegisterBefore;
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValue,valueOfBCRegisterBefore);
    delete oZ80CPU;
}



TEST(Z80CPUModule_Load, ED_4B_LD_BC_addr_nn) {
    const UINT8 opcodeNumber1 = 0xED;
    const UINT8 opcodeNumber2 = 0x43;
    const UINT16 valueOfPCRegisterAfter = 0x4;
    const UINT16 valueOfBCRegisterBefore = 0x1234;

    const UINT16 someNumber = 0xFF00;
    UINT16 someValue = 0x3300;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    EXPECT_CALL(oMockZ80Memory, get16(2)).WillOnce(Return(someNumber));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(someNumber)).WillOnce(Return(&someValue));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.BC = someValue;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;
}



TEST(Z80CPUModule_Load, ED_47_LD_I_A) {
	const UINT8 opcodeNumber1 = 0xED;
	const UINT8 opcodeNumber2 = 0x47;
    const UINT16 valueOfPCRegisterAfter = 0x2;
    const UINT16 valueOfARegister = 0x2E;

    const UINT16 someNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();


    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegister;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.A = valueOfARegister;
    regCompare.I = valueOfARegister;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}
