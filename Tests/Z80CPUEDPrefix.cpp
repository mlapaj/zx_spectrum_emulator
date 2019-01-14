#include <stdexcept>
#include "Z80CPUModuleTest.hpp"
#include "Z80Registers.hpp"
#include "Z80Opcodes.hpp"
#include "Z80CPUModule.hpp"
#include "Helpers.hpp"

TEST(Z80CPUModule_EDPrefix, ED_4A_ADC_HL_BC) {
    const UINT8 opcodeNumber1 = 0xED; // ED prefix
    const UINT8 opcodeNumber2 = 0x4A; // actual opcode
    const UINT16 valueOfPCRegisterAfter = 0x2;

	const UINT16 valueOfHLRegisterBefore=1;
	const UINT16 valueOfHLRegisterAfter=3;
	const UINT16 valueOfBCRegisterBefore=1;
	const UINT16 valueOfBCRegisterAfter=1;

    MockZ80Memory oMockZ80Memory;

	UINT8 somePlaceInMemory = 20;

    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber1));
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeNumber2));
    Z80CPUModule<MockZ80Memory> *oZ80CPU;

    oZ80CPU = new Z80CPUModule<MockZ80Memory>(&oMockZ80Memory);

    Z80Registers regIn = oZ80CPU->getRegisters();
    checkRegistersHaveDefaultValues(regIn);
    regIn.dumpFull();

    Z80Registers regToSet;
    regToSet.reset();
    regToSet.HL = valueOfHLRegisterBefore;
    regToSet.BC = valueOfHLRegisterBefore;
    oZ80CPU->setRegisters(regToSet);
    oZ80CPU->getRegisters().dump();


    oZ80CPU->executeStep();
    Z80Registers regOut = oZ80CPU->getRegisters();

    Z80Registers regCompare;
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.HL = valueOfHLRegisterAfter;
    regCompare.BC = valueOfBCRegisterAfter;
    EXPECT_EQ(somePlaceInMemory,20);
    checkRegisters(regOut,regCompare);

    delete oZ80CPU;
}


