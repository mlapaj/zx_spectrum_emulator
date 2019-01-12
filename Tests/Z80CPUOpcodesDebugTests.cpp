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

TEST(Z80CPUOpcodesDebugTests, 00_NOP) {
    const UINT8 opcodeVal = 0x0;
    const UINT8 pcVal = 0x0;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfBCRegisterBefore = 0x1100;
    const UINT16 valueOfBCRegisterAfter = 0x1101;

    MockZ80Memory oMockZ80Memory;
    opcodeInfo opcode;

    Z80Registers regIn;
    regIn.reset();
    Z80Opcodes<MockZ80Memory> *oZ80Opcodes = new Z80Opcodes<MockZ80Memory>(oMockZ80Memory,regIn);
    opcode = oZ80Opcodes->debugOpcode(opcodeVal,pcVal);
	EXPECT_STREQ(opcode.mnemonic.c_str(),"NOP");
	cout << opcode.mnemonic;
    delete oZ80Opcodes;
}


TEST(Z80CPUOpcodesDebugTests, DD6E_LD_L_IXd) {
    const UINT8 opcodeVal1 = 0xDD;
    const UINT8 opcodeVal2 = 0x6E;
    const UINT8 opcodeVal3 = 34;
    const UINT8 pcVal = 0x0;
    const UINT16 valueOfPCRegisterAfter = 0x1;
    const UINT16 valueOfBCRegisterBefore = 0x1100;
    const UINT16 valueOfBCRegisterAfter = 0x1101;

    MockZ80Memory oMockZ80Memory;
    EXPECT_CALL(oMockZ80Memory, get8(1)).WillOnce(Return(opcodeVal2));
    EXPECT_CALL(oMockZ80Memory, get8(2)).WillOnce(Return(opcodeVal3));
    opcodeInfo opcode;

    Z80Registers regIn;
    regIn.reset();
    Z80Opcodes<MockZ80Memory> *oZ80Opcodes = new Z80Opcodes<MockZ80Memory>(oMockZ80Memory,regIn);
    opcode = oZ80Opcodes->debugOpcode(opcodeVal1,pcVal);
	EXPECT_STREQ(opcode.mnemonic.c_str(),"LD L,(IX+d) d is: 34");
	cout << opcode.mnemonic;
    delete oZ80Opcodes;
}
