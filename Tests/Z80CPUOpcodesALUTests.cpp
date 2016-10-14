/*
 * Z80CPUOpcodesALUTests.cpp
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

TEST(Z80CPUModule_Alu, 03_INC_BC) {
    const UINT8 opcodeNumber = 0x03;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfBCRegisterBefore = 0x1100;
    const UINT16 valueOfBCRegisterAfter = 0x1101;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.BC = valueOfBCRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 04_INC_B) {
    const UINT8 opcodeNumber = 0x04;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfBRegisterBefore = 0x1100;
    const UINT16 valueOfBRegisterAfter = 0x1200;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.BC = valueOfBRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    clear_flag_h(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 04_INC_B_R_REGISTER_7F) {
    const UINT8 opcodeNumber = 0x04;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfBRegisterBefore = 0x1100;
    const UINT16 valueOfRRegisterBefore = 0x7F;
    const UINT16 valueOfBRegisterAfter = 0x1200;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.R = valueOfRRegisterBefore;
    regToSet.BC = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.BC = valueOfBRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    set_flag_pv(regCompare);
    regCompare.R = 0x7F;
    clear_flag_n(regCompare);
    //clear_flag_pv(regCompare);
    clear_flag_h(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 05_DEC_B) {
    const UINT8 opcodeNumber = 0x05;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfBRegisterBefore = 0x1100;
    const UINT16 valueOfBRegisterAfter = 0x1000;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.BC = valueOfBRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    clear_flag_h(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}

TEST(Z80CPUModule_Alu, 05_DEC_B_VALUE_1) {
    const UINT8 opcodeNumber = 0x05;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfBRegisterBefore = 0x0100;
    const UINT16 valueOfBRegisterAfter = 0x0000;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.BC = valueOfBRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    clear_flag_h(regCompare);
    set_flag_z(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 05_DEC_B_VALUE_0) {
    const UINT8 opcodeNumber = 0x05;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfBRegisterBefore = 0x0000;
    const UINT16 valueOfBRegisterAfter = 0xFF00;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.BC = valueOfBRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    set_flag_s(regCompare);
    set_flag_h(regCompare);
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 05_DEC_B_VALUE_R_REGISTER_0x80) {
    const UINT8 opcodeNumber = 0x05;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfRegisterBefore = 0x80;
    const UINT16 valueOfBRegisterBefore = 0x0000;
    const UINT16 valueOfBRegisterAfter = 0xFF00;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.R = valueOfRegisterBefore;
    regToSet.BC = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.BC = valueOfBRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;

    clear_flag_n(regCompare);
	set_flag_s(regCompare);
    set_flag_h(regCompare);
    set_flag_pv(regCompare);
    regCompare.R = 0x80;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 0B_DEC_BC) {
    const UINT8 opcodeNumber = 0x0B;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfBCRegisterBefore = 0x1100;
    const UINT16 valueOfBCRegisterAfter =  0x10ff;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.BC = valueOfBCRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}



TEST(Z80CPUModule_Alu, 80_ADD_A_B) {
    const UINT8 opcodeNumber = 0x80;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 valueOfARegisterBefore = 0x12;
    const UINT8 valueOfBRegisterBefore = 0x4;

    const UINT8 valueOfARegisterAfter = 0x16;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_z(regCompare);
    clear_flag_s(regCompare);
    clear_flag_n(regCompare);
    clear_flag_h(regCompare);
    clear_flag_pv(regCompare);
    clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 80_ADD_A_B_OVERFLOW_1) {
    const UINT8 opcodeNumber = 0x80;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 valueOfARegisterBefore = 0b01000000; // 64
    const UINT8 valueOfBRegisterBefore = 0b01000000; // 64

    const UINT8 valueOfARegisterAfter = 0b10000000;  // 128

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    clear_flag_z(regCompare);
    clear_flag_n(regCompare);
    clear_flag_h(regCompare);
    clear_flag_c(regCompare);
    set_flag_pv(regCompare);
    set_flag_s(regCompare);
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 80_ADD_A_B_OVERFLOW_2) {
    const UINT8 opcodeNumber = 0x80;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const INT8 valueOfARegisterBefore = -128;
    const INT8 valueOfBRegisterBefore = -128;

    const INT8 valueOfARegisterAfter = 0;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    clear_flag_s(regCompare);
    clear_flag_n(regCompare);
    clear_flag_h(regCompare);
    set_flag_pv(regCompare);
    set_flag_c(regCompare);
    set_flag_z(regCompare);
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}



TEST(Z80CPUModule_Alu, 80_ADD_A_B_CARRY_1) {
    const UINT8 opcodeNumber = 0x80;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const INT8 valueOfARegisterBefore = -1;
    const INT8 valueOfBRegisterBefore = 1;

    const INT8 valueOfARegisterAfter = 0;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    clear_flag_s(regCompare);
    set_flag_c(regCompare);
    set_flag_h(regCompare);
    set_flag_z(regCompare);
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 80_ADD_A_B_CARRY_2) {
    const UINT8 opcodeNumber = 0x80;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const INT8 valueOfARegisterBefore = 1;
    const INT8 valueOfBRegisterBefore = -1;

    const INT8 valueOfARegisterAfter = 0;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    clear_flag_s(regCompare);
    set_flag_c(regCompare);
    set_flag_h(regCompare);
    set_flag_z(regCompare);
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}



TEST(Z80CPUModule_Alu, 80_ADD_A_B_CARRY_3) {
    const UINT8 opcodeNumber = 0x80;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const INT8 valueOfARegisterBefore = 127;
    const INT8 valueOfBRegisterBefore = -127;

    const INT8 valueOfARegisterAfter = 0;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    clear_flag_s(regCompare);
    set_flag_c(regCompare);
    set_flag_h(regCompare);
    set_flag_z(regCompare);
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 80_ADD_A_B_CARRY_4) {
    const UINT8 opcodeNumber = 0x80;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const INT8 valueOfARegisterBefore = -127;
    const INT8 valueOfBRegisterBefore = 127;

    const INT8 valueOfARegisterAfter = 0;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    clear_flag_s(regCompare);
    set_flag_c(regCompare);
    set_flag_h(regCompare);
    set_flag_z(regCompare);
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 80_ADD_A_B_CARRY_5) {
    const UINT8 opcodeNumber = 0x80;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const INT8 valueOfARegisterBefore = -128;
    const INT8 valueOfBRegisterBefore = -128;

    const INT8 valueOfARegisterAfter = 0;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    clear_flag_h(regCompare);
    clear_flag_n(regCompare);
    clear_flag_s(regCompare);
    set_flag_c(regCompare);
    set_flag_pv(regCompare);
    set_flag_z(regCompare);
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 80_ADD_A_B_CARRY_6) {

    const UINT8 opcodeNumber = 0x80;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const INT8 valueOfARegisterBefore = -128;
    const INT8 valueOfBRegisterBefore = -127;

    const INT8 valueOfARegisterAfter = 1;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    set_flag_c(regCompare);
    set_flag_pv(regCompare);
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
	clear_flag_h(regCompare);
    clear_flag_n(regCompare);
    clear_flag_s(regCompare);
	clear_flag_z(regCompare);
    set_flag_c(regCompare);
    set_flag_pv(regCompare);

    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}

TEST(Z80CPUModule_Alu, 80_ADD_A_B_CARRY_7) {

    const UINT8 opcodeNumber = 0x80;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const INT8 valueOfARegisterBefore = -1;
    const INT8 valueOfBRegisterBefore = -128;

    const INT8 valueOfARegisterAfter = 127;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    set_flag_c(regCompare);
    set_flag_pv(regCompare);
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
	clear_flag_h(regCompare);
    clear_flag_n(regCompare);
    clear_flag_s(regCompare);
	clear_flag_z(regCompare);
    set_flag_c(regCompare);
    set_flag_pv(regCompare);

    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}



TEST(Z80CPUModule_Alu, 88_ADC_A_B) {
    const UINT8 opcodeNumber = 0x88;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 valueOfARegisterBefore = 0x16;
    const UINT8 valueOfBRegisterBefore = 0x10;

    const UINT8 valueOfARegisterAfter = 0x27;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    set_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();

    regCompare.A = valueOfARegisterAfter;
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    clear_flag_h(regCompare);
    clear_flag_s(regCompare);
    clear_flag_z(regCompare);
    clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 90_SUB_B) {
    const UINT8 opcodeNumber = 0x90;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 valueOfARegisterBefore = 0x16;
    const UINT8 valueOfBRegisterBefore = 0x4;

    const UINT8 valueOfARegisterAfter = 0x12;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
	clear_flag_pv(regCompare);
	clear_flag_z(regCompare);
	clear_flag_s(regCompare);
	clear_flag_h(regCompare);
	clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, 98_SBC_B) {
    const UINT8 opcodeNumber = 0x98;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 valueOfARegisterBefore = 0x29;
    const UINT8 valueOfBRegisterBefore = 0x11;

    const UINT8 valueOfARegisterAfter = 0x17;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_c(regToSet);
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.A = valueOfARegisterAfter;
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
	clear_flag_pv(regCompare);
	clear_flag_z(regCompare);
	clear_flag_s(regCompare);
	clear_flag_h(regCompare);
	clear_flag_c(regCompare);

    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, A0_AND_B) {
    const UINT8 opcodeNumber = 0xA0;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 valueOfARegisterBefore = 0b10101010;
    const UINT8 valueOfBRegisterBefore = 0b11110000;

    const UINT8 valueOfARegisterAfter = 0b10100000;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_h(regCompare);
    set_flag_pv(regCompare);
    set_flag_s(regCompare);

    clear_flag_n(regCompare);
    clear_flag_z(regCompare);
    clear_flag_c(regCompare);

    regCompare.A = valueOfARegisterAfter;
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, B0_OR_B) {
    const UINT8 opcodeNumber = 0xB0;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 valueOfARegisterBefore = 0b00001010;
    const UINT8 valueOfBRegisterBefore = 0b11110000;

    const UINT8 valueOfARegisterAfter = 0b11111010;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_s(regCompare);
    set_flag_pv(regCompare);
    regCompare.A = valueOfARegisterAfter;
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
	clear_flag_z(regCompare);
	clear_flag_h(regCompare);
	clear_flag_n(regCompare);
	clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, A8_XOR_B) {
    const UINT8 opcodeNumber = 0xA8;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 valueOfARegisterBefore = 0b10101011;
    const UINT8 valueOfBRegisterBefore = 0b01010101;

    const UINT8 valueOfARegisterAfter = 0b11111110;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_s(regCompare);
    regCompare.A = valueOfARegisterAfter;
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    clear_flag_h(regCompare);
/*    clear_flag_s(regCompare); */
    clear_flag_c(regCompare);
    clear_flag_z(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}



TEST(Z80CPUModule_Alu, B8_CP_B) {
    const UINT8 opcodeNumber = 0xB8;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 valueOfARegisterBefore = 0b10110111;
    const UINT8 valueOfBRegisterBefore = 0b10110111;

    const UINT8 valueOfARegisterAfter = 0b10110111;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();
    Z80Registers regCompare;
    regCompare.reset();
    clear_flag_s(regCompare);
    clear_flag_h(regCompare); 
    clear_flag_c(regCompare);
	set_flag_n(regCompare);
    set_flag_pv(regCompare);
    regCompare.A = valueOfARegisterAfter;
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Alu, B8_CP_B_NOT_EQUAL) {
    const UINT8 opcodeNumber = 0xB8;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 valueOfARegisterBefore = 0b10110111;
    const UINT8 valueOfBRegisterBefore = 0b10110011;

    const UINT8 valueOfARegisterAfter = 0b10110111;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_n(regCompare);
    set_flag_pv(regCompare); // todo check it

    clear_flag_s(regCompare);
    clear_flag_h(regCompare);
	clear_flag_z(regCompare);
    clear_flag_c(regCompare);

    regCompare.A = valueOfARegisterAfter;
    regCompare.B = valueOfBRegisterBefore;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}



TEST(Z80CPUModule_Alu, FE_CP_n) {
    const UINT8 opcodeNumber = 0xFE;
    const UINT16 valueOfPCRegisterAfter = 0x1;

    const UINT8 valueOfARegisterBefore = 0b10110111;

    const UINT8 valueOfARegisterAfter = 0b10110111;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(0b10110111));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.A = valueOfARegisterBefore;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    clear_flag_s(regCompare);
    clear_flag_h(regCompare); 
    clear_flag_c(regCompare);
	set_flag_n(regCompare);
    set_flag_pv(regCompare);


	regCompare.A = valueOfARegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}
