#include <gtest/gtest.h>

#include <stdexcept>
#include "Z80CPUModuleTest.hpp"
#include "Z80Registers.hpp"
#include "Z80Opcodes.hpp"
#include "Z80CPUModule.hpp"
#include "Helpers.hpp"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;


TEST(Z80CPUModule, 00_NOP) {
    const UINT8 opcodeNumber = 0x0;
    const UINT16 valueOfPCRegisterAfter = 0x1;    
    
    MockZ80Memory oMockZ80Memory;    
    EXPECT_CALL(oMockZ80Memory, get8(0)).WillOnce(Return(opcodeNumber));
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



TEST(Z80CPUModule, 2F_CPL) {
    const UINT8 opcodeNumber = 0x2F;
    const UINT16 valueOfPCRegisterAfter = 0x01;    
    const UINT16 valueOfARegisterBefore = 0x0F;    
    const UINT16 valueOfARegisterAfter = 0xF0;    
    
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
    regCompare.reset();
    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.A = valueOfARegisterAfter;
    set_flag_h(regCompare);
    set_flag_n(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;
}


TEST(Z80CPUModule, 37_SCF) {
    const UINT8 opcodeNumber = 0x37;
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

TEST(Z80CPUModule, 3F_CCF_0_1) {
    const UINT8 opcodeNumber = 0x3F;
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
    
    oZ80CPU->setRegisters(regToSet);
    
    oZ80CPU->executeStep();       
    Z80Registers regOut = oZ80CPU->getRegisters();
    
    Z80Registers regCompare;
    regCompare.reset();
    
    regCompare.PC = valueOfPCRegisterAfter;
    set_flag_c(regCompare);    
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;
}

TEST(Z80CPUModule, 3F_CCF_1_0) {
    const UINT8 opcodeNumber = 0x3F;
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
    set_flag_c(regToSet);
    oZ80CPU->setRegisters(regToSet);
    
    oZ80CPU->executeStep();       
    Z80Registers regOut = oZ80CPU->getRegisters();
    
    Z80Registers regCompare;
    regCompare.reset();
    
    regCompare.PC = valueOfPCRegisterAfter;
    set_flag_h(regCompare);
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;
}




TEST(Z80CPUModule, ED_44_NEG) {
    const UINT8 opcodeNumber1 = 0xED;
    const UINT8 opcodeNumber2 = 0x44;
    const UINT16 valueOfPCRegisterAfter = 0x2;
    const UINT16 valueOfARegisterBefore = (INT16) 16;
    const UINT16 valueOfARegisterAfter = (INT16) -16;

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
    regCompare.reset();
    set_flag_s(regCompare);
    set_flag_c(regCompare);
    set_flag_n(regCompare);
    // todo: trzeba to sprawdzić
    set_flag_h(regCompare);

    regCompare.PC = valueOfPCRegisterAfter;
    regCompare.A = valueOfARegisterAfter;
    checkRegisters(regOut,regCompare);
    delete oZ80CPU;
}
