#include <stdexcept>
#include "Z80CPUModuleTest.hpp"
#include "Z80Registers.hpp"
#include "Z80Opcodes.hpp"
#include "Z80CPUModule.hpp"
#include "Helpers.hpp"


using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;


TEST(Z80CPUModule_Ret, C9_RET) {
    const UINT8 opcodeNumber = 0xC9;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfSPRegisterBefore)).WillOnce(Return(someValue));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore+2;
    regCompare.PC = someValue;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, C0_RET_NZ_YES) {
    const UINT8 opcodeNumber = 0xC0;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;
	

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfSPRegisterBefore)).WillOnce(Return(someValue));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
	clear_flag_z(regToSet);
    oZ80CPU->setRegisters(regToSet);

    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore+2;
    regCompare.PC = someValue;
	clear_flag_z(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}

TEST(Z80CPUModule_Ret, C0_RET_NZ_NO) {
    const UINT8 opcodeNumber = 0xC0;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_z(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    set_flag_z(regCompare);
    regCompare.PC = 1;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}



TEST(Z80CPUModule_Ret, C8_RET_Z_YES) {
    const UINT8 opcodeNumber = 0xC8;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfSPRegisterBefore)).WillOnce(Return(someValue));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    set_flag_z(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore+2;
    regCompare.PC = someValue;
    set_flag_z(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, C8_RET_Z_NO) {
    const UINT8 opcodeNumber = 0xC8;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
	clear_flag_z(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = 1;
	clear_flag_z(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


//
TEST(Z80CPUModule_Ret, D0_RET_NC_YES) {
    const UINT8 opcodeNumber = 0xD0;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfSPRegisterBefore)).WillOnce(Return(someValue));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
	clear_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore+2;
    regCompare.PC = someValue;
	clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}

TEST(Z80CPUModule_Ret, C0_RET_NC_NO) {
    const UINT8 opcodeNumber = 0xD0;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_c(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    set_flag_c(regCompare);
    regCompare.PC = 1;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, D8_RET_C_YES) {
    const UINT8 opcodeNumber = 0xD8;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfSPRegisterBefore)).WillOnce(Return(someValue));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    set_flag_c(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore+2;
    regCompare.PC = someValue;
    set_flag_c(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, D8_RET_C_NO) {
    const UINT8 opcodeNumber = 0xD8;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    clear_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = 1;
    clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, D0_RET_PO_YES) {
    const UINT8 opcodeNumber = 0xE0;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfSPRegisterBefore)).WillOnce(Return(someValue));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    clear_flag_pv(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore+2;
    regCompare.PC = someValue;
    clear_flag_pv(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}

TEST(Z80CPUModule_Ret, E8_RET_PO_NO) {
    const UINT8 opcodeNumber = 0xE0;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_pv(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    set_flag_pv(regCompare);
    regCompare.PC = 1;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, E8_RET_PE_YES) {
    const UINT8 opcodeNumber = 0xE8;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfSPRegisterBefore)).WillOnce(Return(someValue));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    set_flag_pv(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore+2;
    regCompare.PC = someValue;
    set_flag_pv(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, E8_RET_PE_NO) {
    const UINT8 opcodeNumber = 0xE8;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    clear_flag_pv(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = 1;
    clear_flag_pv(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}



TEST(Z80CPUModule_Ret, F0_RET_P_YES) {
    const UINT8 opcodeNumber = 0xF0;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfSPRegisterBefore)).WillOnce(Return(someValue));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    clear_flag_s(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore+2;
    regCompare.PC = someValue;
    clear_flag_s(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}

TEST(Z80CPUModule_Ret, F0_RET_P_NO) {
    const UINT8 opcodeNumber = 0xF0;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_s(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    set_flag_s(regCompare);
    regCompare.PC = 1;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, F8_RET_M_YES) {
    const UINT8 opcodeNumber = 0xF8;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfSPRegisterBefore)).WillOnce(Return(someValue));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    set_flag_s(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore+2;
    regCompare.PC = someValue;
    set_flag_s(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, F8_RET_M_NO) {
    const UINT8 opcodeNumber = 0xF8;
    const UINT16 valueOfSPRegisterBefore = 0x3210;

    const UINT16 someValue = 0x1234;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);


    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    clear_flag_s(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = 1;
    clear_flag_s(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;

}



TEST(Z80CPUModule_Ret, CD_CALL_nn) {
    const UINT8 opcodeNumber = 0xCD;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfPCRegisterBefore+1)).WillOnce(Return(someValue));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(valueOfSPRegisterBefore-2)).WillOnce(Return(&someValueOnStack));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore-2;
    regCompare.PC = someValue+3;
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}



TEST(Z80CPUModule_Ret, CD_CALL_NZ_nn_YES) {
    const UINT8 opcodeNumber = 0xC4;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfPCRegisterBefore+1)).WillOnce(Return(someValue));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(valueOfSPRegisterBefore)).WillOnce(Return(&someValueOnStack));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    clear_flag_z(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore-2;
    regCompare.PC = someValue;
    clear_flag_z(regCompare);
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, CD_CALL_NZ_nn_NO) {
    const UINT8 opcodeNumber = 0xC4;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_z(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_z(regCompare);
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = valueOfPCRegisterBefore + 3;
    checkRegisters(regOut,regCompare);
    EXPECT_NE(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}

TEST(Z80CPUModule_Ret, CC_CALL_Z_nn_YES) {
    const UINT8 opcodeNumber = 0xCC;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfPCRegisterBefore+1)).WillOnce(Return(someValue));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(valueOfSPRegisterBefore)).WillOnce(Return(&someValueOnStack));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_z(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_z(regCompare);
    regCompare.SP = valueOfSPRegisterBefore-2;
    regCompare.PC = someValue;
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, CC_CALL_Z_nn_NO) {
    const UINT8 opcodeNumber = 0xCC;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    clear_flag_z(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = valueOfPCRegisterBefore + 3;
    clear_flag_z(regCompare);
    checkRegisters(regOut,regCompare);
    EXPECT_NE(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, D4_CALL_NC_nn_YES) {
    const UINT8 opcodeNumber = 0xD4;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfPCRegisterBefore+1)).WillOnce(Return(someValue));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(valueOfSPRegisterBefore)).WillOnce(Return(&someValueOnStack));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;

    clear_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore-2;
    regCompare.PC = someValue;
    clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, D4_CALL_NC_nn_NO) {
    const UINT8 opcodeNumber = 0xD4;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_c(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_c(regCompare);
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = valueOfPCRegisterBefore + 3;
    checkRegisters(regOut,regCompare);
    EXPECT_NE(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, DC_CALL_C_nn_YES) {
    const UINT8 opcodeNumber = 0xDC;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfPCRegisterBefore+1)).WillOnce(Return(someValue));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(valueOfSPRegisterBefore)).WillOnce(Return(&someValueOnStack));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_c(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    set_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_c(regCompare);
    regCompare.SP = valueOfSPRegisterBefore-2;
    regCompare.PC = someValue;
    set_flag_c(regCompare);
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, DC_CALL_C_nn_NO) {
    const UINT8 opcodeNumber = 0xDC;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    clear_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = valueOfPCRegisterBefore + 3;
    clear_flag_c(regCompare);
    checkRegisters(regOut,regCompare);
    EXPECT_NE(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}

TEST(Z80CPUModule_Ret, E4_CALL_PO_nn_YES) {
    const UINT8 opcodeNumber = 0xE4;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfPCRegisterBefore+1)).WillOnce(Return(someValue));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(valueOfSPRegisterBefore)).WillOnce(Return(&someValueOnStack));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    clear_flag_pv(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore-2;
    regCompare.PC = someValue;
    clear_flag_pv(regCompare);
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, E4_CALL_PO_nn_NO) {
    const UINT8 opcodeNumber = 0xE4;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_pv(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_pv(regCompare);
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = valueOfPCRegisterBefore + 3;
    checkRegisters(regOut,regCompare);
    EXPECT_NE(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, EC_CALL_PE_nn_YES) {
    const UINT8 opcodeNumber = 0xEC;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfPCRegisterBefore+1)).WillOnce(Return(someValue));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(valueOfSPRegisterBefore)).WillOnce(Return(&someValueOnStack));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_pv(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_pv(regCompare);
    regCompare.SP = valueOfSPRegisterBefore-2;
    regCompare.PC = someValue;
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, EC_CALL_PE_nn_NO) {
    const UINT8 opcodeNumber = 0xEC;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    clear_flag_pv(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = valueOfPCRegisterBefore + 3;
    clear_flag_pv(regCompare);
    checkRegisters(regOut,regCompare);
    EXPECT_NE(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}



TEST(Z80CPUModule_Ret, F4_CALL_P_nn_YES) {
    const UINT8 opcodeNumber = 0xF4;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfPCRegisterBefore+1)).WillOnce(Return(someValue));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(valueOfSPRegisterBefore)).WillOnce(Return(&someValueOnStack));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    clear_flag_s(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore-2;
    regCompare.PC = someValue;
    clear_flag_s(regCompare);
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, F4_CALL_P_nn_NO) {
    const UINT8 opcodeNumber = 0xF4;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_s(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_s(regCompare);
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = valueOfPCRegisterBefore + 3;
    set_flag_s(regCompare);
    checkRegisters(regOut,regCompare);
    EXPECT_NE(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, FC_CALL_M_nn_YES) {
    const UINT8 opcodeNumber = 0xFC;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));
    EXPECT_CALL(oMockZ80Memory, get16(valueOfPCRegisterBefore+1)).WillOnce(Return(someValue));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr16(valueOfSPRegisterBefore)).WillOnce(Return(&someValueOnStack));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    set_flag_s(regToSet);
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    set_flag_s(regCompare);
    regCompare.SP = valueOfSPRegisterBefore-2;
    regCompare.PC = someValue;
    checkRegisters(regOut,regCompare);
    EXPECT_EQ(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}


TEST(Z80CPUModule_Ret, FC_CALL_PE_nn_NO) {
    const UINT8 opcodeNumber = 0xFC;
    const UINT16 valueOfSPRegisterBefore = 0x3210;
    const UINT16 valueOfPCRegisterBefore = 0x4321;
    UINT16 someValue = 0x1234;
    UINT16 someValueOnStack = 0x33;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(valueOfPCRegisterBefore)).WillOnce(Return(opcodeNumber));

    Z80CPUModule<MockZ80Memory> *oZ80CPU;
    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.SP = valueOfSPRegisterBefore;
    regToSet.PC = valueOfPCRegisterBefore;
    clear_flag_s(regToSet);
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.SP = valueOfSPRegisterBefore;
    regCompare.PC = valueOfPCRegisterBefore + 3;
    clear_flag_s(regCompare);
    checkRegisters(regOut,regCompare);
    EXPECT_NE(someValueOnStack,valueOfPCRegisterBefore);
    delete oZ80CPU;

}
