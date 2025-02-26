#include <stdexcept>
#include "Z80CPUModuleTest.hpp"
#include "Z80Registers.hpp"
#include "Z80Opcodes.hpp"
#include "Z80CPUModule.hpp"
#include "Helpers.hpp"

TEST(Z80CPUModule_FDPrefix, FD_6E_LD_L_IX_plus_d) {
    const UINT8 opcodeNumber1 = 0xFD; // FD prefix
    const UINT8 opcodeNumber2 = 0x6E; // actual opcode
    const UINT8 opcodeNumber3 = 0x10; // 8 bit displacement
    const UINT16 valueOfPCRegisterAfter = 0x3;
	const UINT16 valueOfHLRegisterBefore=0;
	const UINT16 valueOfHLRegisterAfter=20;
	const UINT16 valueOfIYRegisterBefore=0x1234;

    MockZ80Memory oMockZ80Memory;

	UINT8 somePlaceInMemory = 20;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    EXPECT_CALL(oMockZ80Memory, get8(2)).WillOnce(Return(opcodeNumber3));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfIYRegisterBefore+opcodeNumber3)).WillOnce(Return(&somePlaceInMemory));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.HL = valueOfHLRegisterBefore;
    regToSet.IY = valueOfIYRegisterBefore;
    oZ80CPU->setRegisters(regToSet);
    oZ80CPU->getRegisters().dump();


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.HL = valueOfHLRegisterAfter;
    regCompare.IY = valueOfIYRegisterBefore;
    EXPECT_EQ(somePlaceInMemory,20);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_FDPrefix, FD_66_LD_H_IX_plus_d) {
    const UINT8 opcodeNumber1 = 0xFD; // FD prefix
    const UINT8 opcodeNumber2 = 0x66; // actual opcode
    const UINT8 opcodeNumber3 = 0x10; // 8 bit displacement
    const UINT16 valueOfPCRegisterAfter = 0x3;
	const UINT16 valueOfHLRegisterBefore=0;
	const UINT16 valueOfHLRegisterAfter=0x1400;
	const UINT16 valueOfIYRegisterBefore=0x1234;

    MockZ80Memory oMockZ80Memory;

	UINT8 somePlaceInMemory = 0x14;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    EXPECT_CALL(oMockZ80Memory, get8(2)).WillOnce(Return(opcodeNumber3));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfIYRegisterBefore+opcodeNumber3)).WillOnce(Return(&somePlaceInMemory));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.HL = valueOfHLRegisterBefore;
    regToSet.IY= valueOfIYRegisterBefore;
    oZ80CPU->setRegisters(regToSet);
    oZ80CPU->getRegisters().dump();


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.HL = valueOfHLRegisterAfter;
    regCompare.IY = valueOfIYRegisterBefore;
    EXPECT_EQ(somePlaceInMemory,20);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


TEST(Z80CPUModule_FDPrefix, FD_35_DEC_ix_plus_d) {
    const UINT8 opcodeNumber1 = 0xFD; // FD prefix
    const UINT8 opcodeNumber2 = 0x35; // actual opcode
    const UINT8 opcodeNumber3 = 0x10; // 8 bit displacement
    const UINT16 valueOfPCRegisterAfter = 0x3;
	const UINT16 valueOfIYRegisterBefore=0x1234;

    MockZ80Memory oMockZ80Memory;

	UINT8 somePlaceInMemory = 0x14;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    EXPECT_CALL(oMockZ80Memory, get8(2)).WillOnce(Return(opcodeNumber3));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfIYRegisterBefore+opcodeNumber3)).WillOnce(Return(&somePlaceInMemory));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.IY = valueOfIYRegisterBefore;
    oZ80CPU->setRegisters(regToSet);
    oZ80CPU->getRegisters().dump();


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    clear_flag_s(regCompare);
    clear_flag_h(regCompare); // TODO: to check
    clear_flag_pv(regCompare); // TODO: to check
    clear_flag_z(regCompare);
    set_flag_n(regCompare);
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.IY = valueOfIYRegisterBefore;
    EXPECT_EQ(somePlaceInMemory,19);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}

