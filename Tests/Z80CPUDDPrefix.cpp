#include <stdexcept>
#include "Z80CPUModuleTest.hpp"
#include "Z80Registers.hpp"
#include "Z80Opcodes.hpp"
#include "Z80CPUModule.hpp"
#include "Helpers.hpp"

TEST(Z80CPUModule_DDPrefix, DD_6E_LD_L_IX_plus_d) {
    const UINT8 opcodeNumber1 = 0xDD; // FD prefix
    const UINT8 opcodeNumber2 = 0x6E; // actual opcode
    const UINT8 opcodeNumber3 = 0x10; // 8 bit displacement
    const UINT16 valueOfPCRegisterAfter = 0x3;
	const UINT16 valueOfHLRegisterBefore=0;
	const UINT16 valueOfHLRegisterAfter=20;
	const UINT16 valueOfIXRegisterBefore=0x1234;

    MockZ80Memory oMockZ80Memory;

	UINT8 somePlaceInMemory = 20;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    EXPECT_CALL(oMockZ80Memory, get8(2)).WillOnce(Return(opcodeNumber3));
    EXPECT_CALL(oMockZ80Memory, getAddrPtr8(valueOfIXRegisterBefore+opcodeNumber3)).WillOnce(Return(&somePlaceInMemory));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.HL = valueOfHLRegisterBefore;
    regToSet.IX = valueOfIXRegisterBefore;
    oZ80CPU->setRegisters(regToSet);
    oZ80CPU->getRegisters().dump();


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.HL = valueOfHLRegisterAfter;
    regCompare.IX = valueOfIXRegisterBefore;
    EXPECT_EQ(somePlaceInMemory,20);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


