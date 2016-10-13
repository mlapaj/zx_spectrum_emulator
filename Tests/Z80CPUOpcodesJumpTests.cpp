/*
 * Z80CPUOpcodesJump.cpp
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


using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;


TEST(Z80CPUModule_Jump, C3_JP_nn) {
    const UINT8 opcodeNumber = 0xC3;
    const UINT16 valueOfPCRegisterAfter = 0xFF00;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(addressNumber));
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
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}

TEST(Z80CPUModule_Jump, CA_JP_Z_nn_NO) {
    const UINT8 opcodeNumber = 0xCA;
    const UINT16 valueOfPCRegisterAfter = 0x0003;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();

    clear_flag_z(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();

    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_z(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, CA_JP_Z_nn_YES) {
    const UINT8 opcodeNumber = 0xCA;
    const UINT16 valueOfPCRegisterAfter = 0xFF00;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_z(regToSet);

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_z(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}







TEST(Z80CPUModule_Jump, D2_JP_NC_nn_NO) {
    const UINT8 opcodeNumber = 0xD2;
    const UINT16 valueOfPCRegisterAfter = 0x0003;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_c(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, D2_JP_NC_nn_YES) {
    const UINT8 opcodeNumber = 0xD2;
    const UINT16 valueOfPCRegisterAfter = 0xFF00;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    clear_flag_c(regToSet);

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();

    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}

TEST(Z80CPUModule_Jump, DA_JP_C_nn_NO) {
    const UINT8 opcodeNumber = 0xDA;
    const UINT16 valueOfPCRegisterAfter = 0x0003;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    clear_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, DA_JP_C_nn_YES) {
    const UINT8 opcodeNumber = 0xDA;
    const UINT16 valueOfPCRegisterAfter = 0xFF00;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_c(regToSet);

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_c(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_Jump, E2_JP_PO_nn_NO) {
    const UINT8 opcodeNumber = 0xE2;
    const UINT16 valueOfPCRegisterAfter = 0x0003;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_pv(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_pv(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, E2_JP_PO_nn_YES) {
    const UINT8 opcodeNumber = 0xE2;
    const UINT16 valueOfPCRegisterAfter = 0xFF00;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);


    Z80Registers regToSet;
    regToSet.reset();
	clear_flag_pv(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();

    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_pv(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_Jump, EA_JP_PE_nn_NO) {
    const UINT8 opcodeNumber = 0xEA;
    const UINT16 valueOfPCRegisterAfter = 0x0003;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    clear_flag_pv(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();

    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_pv(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, EA_JP_PE_nn_YES) {
    const UINT8 opcodeNumber = 0xEA;
    const UINT16 valueOfPCRegisterAfter = 0xFF00;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_pv(regToSet);

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_pv(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_Jump, F2_JP_P_nn_NO) {
    const UINT8 opcodeNumber = 0xF2;
    const UINT16 valueOfPCRegisterAfter = 0x0003;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_s(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    set_flag_s(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, F2_JP_P_nn_YES) {
    const UINT8 opcodeNumber = 0xF2;
    const UINT16 valueOfPCRegisterAfter = 0xFF00;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
	clear_flag_s(regToSet);

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();

    regCompare.PC = valueOfPCRegisterAfter;
	clear_flag_s(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, FA_JP_M_nn_NO) {
    const UINT8 opcodeNumber = 0xFA;
    const UINT16 valueOfPCRegisterAfter = 0x0003;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
	clear_flag_s(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();

    regCompare.PC = valueOfPCRegisterAfter;
	clear_flag_s(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, FA_JP_M_nn_YES) {
    const UINT8 opcodeNumber = 0xFA;
    const UINT16 valueOfPCRegisterAfter = 0xFF00;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_s(regToSet);

    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_s(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}
TEST(Z80CPUModule_Jump, C2_JP_NZ_nn_YES) {
    const UINT8 opcodeNumber = 0xC2;
    const UINT16 valueOfPCRegisterAfter = 0xFF00;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
	clear_flag_z(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
	clear_flag_z(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_Jump, C2_JP_NZ_nn_NO) {
    const UINT8 opcodeNumber = 0xC2;
    const UINT16 valueOfPCRegisterAfter = 0x0003;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_z(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_z(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, E9_JP_addr_HL) {
    const UINT8 opcodeNumber = 0xE9; // e9
    const UINT16 valueOfPCRegisterAfter = 0xFF00;

    const UINT16 addressNumber = 0xFF00;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.HL = addressNumber;
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.HL = addressNumber;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}




TEST(Z80CPUModule_Jump, 18_JR_n_127) {
    const UINT8 opcodeNumber = 0x18;
    const UINT16 valueOfPCRegisterAfter = 127;

    const UINT16 addressNumber = 127;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(addressNumber));
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
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, 18_JR_n_minus_128) {
    const UINT8 opcodeNumber = 0x18;
    const UINT16 valueOfPCRegisterAfter = -128;

    const UINT16 addressNumber = -128;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(addressNumber));
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
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, 20_JR_NZ_n_127_YES) {
    const UINT8 opcodeNumber = 0x20;
    const UINT16 valueOfPCRegisterAfter = 127;

    const UINT16 addressNumber = 127;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);
	Z80Registers regToSet;

	regToSet.reset();
    clear_flag_z(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_z(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, 20_JR_NZ_n_127_NO) {
    const UINT8 opcodeNumber = 0x20;
    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT16 addressNumber = 127;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_z(regToSet);
    oZ80CPU->setRegisters(regToSet);

    regIn.dumpFull();

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_z(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}

TEST(Z80CPUModule_Jump, 28_JR_Z_n_127_YES) {
    const UINT8 opcodeNumber = 0x28;
    const UINT16 valueOfPCRegisterAfter = 127;

    const UINT16 addressNumber = 127;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_z(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_z(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, 28_JR_Z_n_127_NO) {
    const UINT8 opcodeNumber = 0x28;
    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT16 addressNumber = 127;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    clear_flag_z(regToSet);
    oZ80CPU->setRegisters(regToSet);

    regIn.dumpFull();

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_z(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}

TEST(Z80CPUModule_Jump, 30_JR_NC_n_127_YES) {
    const UINT8 opcodeNumber = 0x30;
    const UINT16 valueOfPCRegisterAfter = 127;

    const UINT16 addressNumber = 127;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    clear_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();

    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, 30_JR_NC_n_127_NO) {
    const UINT8 opcodeNumber = 0x30;
    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT16 addressNumber = 127;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_c(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}

//
TEST(Z80CPUModule_Jump, 38_JR_C_n_127_YES) {
    const UINT8 opcodeNumber = 0x38;
    const UINT16 valueOfPCRegisterAfter = 127;

    const UINT16 addressNumber = 127;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_c(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, 38_JR_C_n_127_NO) {
    const UINT8 opcodeNumber = 0x38;
    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT16 addressNumber = 127;

    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    regIn.dumpFull();


    Z80Registers regToSet;
    regToSet.reset();
    clear_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();

    regCompare.PC = valueOfPCRegisterAfter;
    clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, 38_DJNZ_YES) {
    const UINT8 opcodeNumber = 0x10;
    const UINT16 addressNumber = 127;

    const UINT16 valueOfPCRegisterAfter = addressNumber;
    const UINT16 valueOfBRegisterBefore = 0x2;
    const UINT16 valueOfBRegisterAfter = 0x1;


    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(addressNumber));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.B = valueOfBRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_Jump, 38_DJNZ_NO) {
    const UINT8 opcodeNumber = 0x10;
    const UINT16 addressNumber = 127;

    const UINT16 valueOfPCRegisterAfter = 0x2;
    const UINT16 valueOfBRegisterBefore = 0x1;
    const UINT16 valueOfBRegisterAfter = 0x0;


    MockZ80Memory oMockZ80Memory;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.B = valueOfBRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.B = valueOfBRegisterAfter;
    regCompare.PC = valueOfPCRegisterAfter;
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}

