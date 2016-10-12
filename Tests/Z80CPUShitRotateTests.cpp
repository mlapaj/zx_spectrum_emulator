/*
 * Z80CPUShitRotateTests.cpp
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

TEST(Z80CPUModule_ShiftRotate, 07_RLC_A) {
    const UINT8 opcodeNumber = 0x7;
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b00010011;
    const UINT16 valueOfARegisterAfter  = 0b00100110;

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
    regToSet.A = valueOfARegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    regCompare.A = valueOfARegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_ShiftRotate, 07_RLCA_CARRY_1) {
    const UINT8 opcodeNumber = 0x7;

    const UINT16 valueOfARegisterBefore = 0b10101010;
    const UINT16 valueOfARegisterAfter =  0b01010101;

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
    regToSet.A = valueOfARegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    regCompare.A = valueOfARegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    set_flag_c(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}





TEST(Z80CPUModule_ShiftRotate, 0F_RRCA) {
    const UINT8 opcodeNumber = 0xF;
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b00010010;
    const UINT16 valueOfARegisterAfter  = 0b00001001;

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
    regToSet.A = valueOfARegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    regCompare.A = valueOfARegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_ShiftRotate, 0F_RRCA_CARRY_1) {
    const UINT8 opcodeNumber = 0xF;
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b00010011;
    const UINT16 valueOfARegisterAfter  = 0b10001001;

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
    regToSet.A = valueOfARegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    regCompare.A = valueOfARegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    set_flag_c(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_ShiftRotate, 17_RLA) {
    const UINT8 opcodeNumber = 0x17;    
    // 0x13 =
    const UINT8 valueOfARegisterBefore = 0b10010010;
    const UINT8 valueOfARegisterAfter  = 0b00100101;

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
    regToSet.A = valueOfARegisterBefore;
    
    // set registers
    set_flag_h(regToSet);    
    set_flag_n(regToSet);
    set_flag_c(regToSet);
    
    
    oZ80CPU->setRegisters(regToSet);
    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    regCompare.A = valueOfARegisterAfter;
    set_flag_c(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_ShiftRotate, 1F_RRA) {
    const UINT8 opcodeNumber = 0x1F;    
    // 0x13 =
    const UINT8 valueOfARegisterBefore = 0b01001000;
    const UINT8 valueOfARegisterAfter  = 0b10100100;

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
    regToSet.A = valueOfARegisterBefore;
    
    // set registers
    set_flag_h(regToSet);    
    set_flag_n(regToSet);
    set_flag_c(regToSet);
    
    
    oZ80CPU->setRegisters(regToSet);
    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    regCompare.A = valueOfARegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_ShiftRotate, CB_07_RLC_A) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0x7;
    // 0x13 =s
    const UINT16 valueOfARegisterBefore = 0b00010011;
    const UINT16 valueOfARegisterAfter  = 0b00100110;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;
    
    // set registers
    set_flag_h(regToSet);
    set_flag_c(regToSet);
    set_flag_pv(regToSet);
    set_flag_n(regToSet);
    set_flag_c(regToSet);
    set_flag_s(regToSet);
    set_flag_z(regToSet);
    
    oZ80CPU->setRegisters(regToSet);
    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    regCompare.A = valueOfARegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_ShiftRotate, CB_0F_RRC_A) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0x0F;
    
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b00010010;
    const UINT16 valueOfARegisterAfter  = 0b00001001;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;
    // set registers
    set_flag_h(regToSet);
    set_flag_c(regToSet);
    set_flag_pv(regToSet);
    set_flag_n(regToSet);
    set_flag_c(regToSet);
    set_flag_s(regToSet);
    set_flag_z(regToSet);
    

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    regCompare.A = valueOfARegisterAfter;
    set_flag_pv(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}




TEST(Z80CPUModule_ShiftRotate, CB_17_RL_A) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0x17;
    
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b10001111;
    const UINT16 valueOfARegisterAfter  = 0b00011110;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;
    // set registers
    set_flag_h(regToSet);
    set_flag_pv(regToSet);
    set_flag_n(regToSet);
    set_flag_s(regToSet);
    set_flag_z(regToSet);
    

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    
    regCompare.A = valueOfARegisterAfter;
    
    set_flag_c(regCompare);
    set_flag_pv(regCompare);

    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_ShiftRotate, CB_0F_RR_A) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0x1F;
    
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b11011101;
    const UINT16 valueOfARegisterAfter  = 0b01101110;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;
    // set registers
    set_flag_h(regToSet);
    set_flag_pv(regToSet);
    set_flag_n(regToSet);
    set_flag_s(regToSet);
    set_flag_z(regToSet);
    

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    
    regCompare.A = valueOfARegisterAfter;
    
    set_flag_c(regCompare);

    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}




TEST(Z80CPUModule_ShiftRotate, CB_27_SLA_A) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0x27;
    
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b10110001;
    const UINT16 valueOfARegisterAfter  = 0b01100010;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;
    // set registers
    set_flag_h(regToSet);
    set_flag_pv(regToSet);
    set_flag_n(regToSet);
    set_flag_s(regToSet);
    set_flag_z(regToSet);
    

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    
    regCompare.A = valueOfARegisterAfter;
    
    set_flag_c(regCompare);

    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_ShiftRotate, CB_27_SRA_A) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0x2F;
    
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b10111001;
    const UINT16 valueOfARegisterAfter  = 0b11011100;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;
    // set registers
    set_flag_h(regToSet);
    set_flag_pv(regToSet);
    set_flag_n(regToSet);
    set_flag_s(regToSet);
    set_flag_z(regToSet);
    

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    
    regCompare.A = valueOfARegisterAfter;
    
    set_flag_c(regCompare);
    set_flag_s(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_ShiftRotate, CB_37_SLL_A) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0x37;
    
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b10110001;
    const UINT16 valueOfARegisterAfter  = 0b01100011;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;
    // set registers
    set_flag_h(regToSet);
    set_flag_pv(regToSet);
    set_flag_n(regToSet);
    set_flag_s(regToSet);
    set_flag_z(regToSet);
    

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    
    regCompare.A = valueOfARegisterAfter;
    
    set_flag_c(regCompare);
    set_flag_pv(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_ShiftRotate, CB_3F_SRL_A) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0x3F;
    
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b10111001;
    const UINT16 valueOfARegisterAfter  = 0b01011100;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;
    // set registers
    set_flag_h(regToSet);
    set_flag_pv(regToSet);
    set_flag_n(regToSet);
    set_flag_s(regToSet);
    set_flag_z(regToSet);
    

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    
    regCompare.A = valueOfARegisterAfter;
    
    set_flag_c(regCompare);
    set_flag_pv(regCompare);    
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_ShiftRotate, CB_4F_BIT_1_A_is_1) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0x4F;
    
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b10101010;
    const UINT16 valueOfARegisterAfter  = 0b10101010;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;
    // set registers
    set_flag_h(regToSet);
    set_flag_n(regToSet);    
    set_flag_z(regToSet);
    

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    
    regCompare.A = valueOfARegisterAfter;
    
    set_flag_z(regCompare);
    set_flag_h(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}

TEST(Z80CPUModule_ShiftRotate, CB_4F_BIT_1_A_is_0) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0x4F;
    
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b10101000;
    const UINT16 valueOfARegisterAfter  = 0b10101000;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;
    // set registers
    set_flag_h(regToSet);
    set_flag_n(regToSet);    
    set_flag_z(regToSet);
    

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    
    regCompare.A = valueOfARegisterAfter;
    
    set_flag_h(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_ShiftRotate, CB_8F_RES_1_A) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0x8F;
    
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b10101010;
    const UINT16 valueOfARegisterAfter  = 0b10101000;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    
    regCompare.A = valueOfARegisterAfter;
    
    
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_ShiftRotate, CB_CF_SET_1_A) {
    const UINT8 opcodeNumber1 = 0xCB;
    const UINT8 opcodeNumber2 = 0xCF;
    
    // 0x13 =
    const UINT16 valueOfARegisterBefore = 0b10101000;
    const UINT16 valueOfARegisterAfter  = 0b10101010;

    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT8 someNumber = 0x12;

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
    regToSet.A = valueOfARegisterBefore;

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();


    Z80Registers regCompare;
    regCompare.zero();
    
    regCompare.A = valueOfARegisterAfter;
    
    
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}
