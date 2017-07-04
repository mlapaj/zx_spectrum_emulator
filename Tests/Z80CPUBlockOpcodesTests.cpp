#include <stdexcept>
#include "Z80CPUModuleTest.hpp"
#include "Z80Registers.hpp"
#include "Z80Opcodes.hpp"
#include "Z80CPUModule.hpp"
#include "Helpers.hpp"

TEST(Z80CPUModule_Block, ED_A0_LDI) {
    const UINT8 opcodeNumber1 = 0xED;
    const UINT8 opcodeNumber2 = 0xA0;
    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT16 valueOfBCRegisterBefore = 0x01;
    const UINT16 valueOfDERegisterBefore = 0x50;
    const UINT16 valueOfHLRegisterBefore = 0x60;


    MockZ80Memory oMockZ80Memory;

	UINT8 somePlaceInMemory = 0;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfDERegisterBefore)).WillOnce(Return(&somePlaceInMemory));
    EXPECT_CALL(oMockZ80Memory, get8(0x60)).WillOnce(Return(10));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBCRegisterBefore;
    regToSet.DE = valueOfDERegisterBefore;
    regToSet.HL = valueOfHLRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.DE = 0x51;
    regCompare.HL = 0x61;
    regCompare.BC = 0;
    clear_flag_h(regCompare);
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    EXPECT_EQ(somePlaceInMemory,10);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}




TEST(Z80CPUModule_Block, ED_A0_LDI_PV_SET) {
    const UINT8 opcodeNumber1 = 0xED;
    const UINT8 opcodeNumber2 = 0xA0;
    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT16 valueOfBCRegisterBefore = 0x02;
    const UINT16 valueOfDERegisterBefore = 0x50;
    const UINT16 valueOfHLRegisterBefore = 0x60;


    MockZ80Memory oMockZ80Memory;

	UINT8 somePlaceInMemory = 0;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfDERegisterBefore)).WillOnce(Return(&somePlaceInMemory));
    EXPECT_CALL(oMockZ80Memory, get8(0x60)).WillOnce(Return(10));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBCRegisterBefore;
    regToSet.DE = valueOfDERegisterBefore;
    regToSet.HL = valueOfHLRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.DE = 0x51;
    regCompare.HL = 0x61;
    regCompare.BC = 1;
    clear_flag_h(regCompare);
    clear_flag_n(regCompare);
    set_flag_pv(regCompare);
    EXPECT_EQ(somePlaceInMemory,10);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}






TEST(Z80CPUModule_Block, ED_A8_LDD) {
    const UINT8 opcodeNumber1 = 0xED;
    const UINT8 opcodeNumber2 = 0xA8;
    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT16 valueOfBCRegisterBefore = 0x01;
    const UINT16 valueOfDERegisterBefore = 0x50;
    const UINT16 valueOfHLRegisterBefore = 0x60;


    MockZ80Memory oMockZ80Memory;

	UINT8 somePlaceInMemory = 0;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfDERegisterBefore)).WillOnce(Return(&somePlaceInMemory));
    EXPECT_CALL(oMockZ80Memory, get8(0x60)).WillOnce(Return(10));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBCRegisterBefore;
    regToSet.DE = valueOfDERegisterBefore;
    regToSet.HL = valueOfHLRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.DE = 0x4F;
    regCompare.HL = 0x5F;
    regCompare.BC = 0;
    clear_flag_h(regCompare);
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    EXPECT_EQ(somePlaceInMemory,10);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}



TEST(Z80CPUModule_Block, ED_A8_LDD_PV_SET) {
    const UINT8 opcodeNumber1 = 0xED;
    const UINT8 opcodeNumber2 = 0xA8;
    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT16 valueOfBCRegisterBefore = 0x02;
    const UINT16 valueOfDERegisterBefore = 0x50;
    const UINT16 valueOfHLRegisterBefore = 0x60;


    MockZ80Memory oMockZ80Memory;

	UINT8 somePlaceInMemory = 0;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfDERegisterBefore)).WillOnce(Return(&somePlaceInMemory));
    EXPECT_CALL(oMockZ80Memory, get8(0x60)).WillOnce(Return(10));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBCRegisterBefore;
    regToSet.DE = valueOfDERegisterBefore;
    regToSet.HL = valueOfHLRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.DE = 0x4F;
    regCompare.HL = 0x5F;
    regCompare.BC = 1;
    clear_flag_h(regCompare);
    clear_flag_n(regCompare);
    set_flag_pv(regCompare);
    EXPECT_EQ(somePlaceInMemory,10);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}






TEST(Z80CPUModule_Block, ED_B8_LDDR) {
    const UINT8 opcodeNumber1 = 0xED;
    const UINT8 opcodeNumber2 = 0xB8;
    const UINT16 valueOfPCRegisterAfter = 0x2;

    const UINT16 valueOfBCRegisterBefore = 0x02;
    const UINT16 valueOfDERegisterBefore = 0x50;
    const UINT16 valueOfHLRegisterBefore = 0x60;


    MockZ80Memory oMockZ80Memory;

	UINT8 somePlaceInMemory1 = 0;
	UINT8 somePlaceInMemory2 = 0;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfDERegisterBefore)).WillOnce(Return(&somePlaceInMemory1));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfDERegisterBefore-1)).WillOnce(Return(&somePlaceInMemory2));
    EXPECT_CALL(oMockZ80Memory, get8(0x60)).WillOnce(Return(10));
    EXPECT_CALL(oMockZ80Memory, get8(0x5F)).WillOnce(Return(11));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.BC = valueOfBCRegisterBefore;
    regToSet.DE = valueOfDERegisterBefore;
    regToSet.HL = valueOfHLRegisterBefore;
    oZ80CPU->setRegisters(regToSet);


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.DE = 0x4E;
    regCompare.HL = 0x5E;
    regCompare.BC = 0;
    clear_flag_h(regCompare);
    clear_flag_n(regCompare);
    clear_flag_pv(regCompare);
    EXPECT_EQ(somePlaceInMemory1,10);
    EXPECT_EQ(somePlaceInMemory2,11);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}
