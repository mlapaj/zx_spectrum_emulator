/*
 * File:   Z80CPUModule.cpp
 * Author: lapajmar
 *
 * Created on 18 marzec 2014, 16:29
 */

#include "Z80CPUModule.hpp"
#include "../Tests/Z80CPUModuleTest.hpp"
#include "../Z80CPU/Z80Opcodes.hpp"

template<typename tZ80Memory>
Z80CPUModule<tZ80Memory>::Z80CPUModule(tZ80Memory *cZ80Memory):logger(Logger::getLogger("Z80Module")) {

    LOG4CXX_DEBUG(logger, "class created");
	quit = false;
    oZ80Memory = cZ80Memory;
    oZ80Registers = new Z80Registers();

    oZ80Registers->dumpFull();
    oZ80Registers->reset();
    oZ80Registers->dumpFull();

    oZ80Opcodes = new Z80Opcodes<tZ80Memory>(*oZ80Memory,*oZ80Registers);
}

template<typename tZ80Memory>
Z80CPUModule<tZ80Memory>::~Z80CPUModule() {
    LOG4CXX_DEBUG(logger, "destructor called");
    delete oZ80Opcodes;
    delete oZ80Registers;
}

template<typename tZ80Memory>
void Z80CPUModule<tZ80Memory>::executeStep()
{
    oZ80Opcodes->executeOpcode();
}


template<typename tZ80Memory>
void Z80CPUModule<tZ80Memory>::getOpcode()
{
    UINT8 opcode = oZ80Memory->get8(oZ80Registers->PC);
	opcodeInfo opInfo;
	opInfo = oZ80Opcodes->debugOpcode(opcode);
	cout << std::hex <<oZ80Registers->PC << ": " << opInfo.mnemonic + "\n"; 
}


template<typename tZ80Memory>
Z80Registers Z80CPUModule<tZ80Memory>::getRegisters()
{
    return *oZ80Registers;
}

template<typename tZ80Memory>
void Z80CPUModule<tZ80Memory>::setRegisters(Z80Registers toSet)
{
    *oZ80Registers = toSet;
}

// hack for templates
#ifdef Z80TESTS
template class Z80CPUModule<MockZ80Memory>;
#else
template class Z80CPUModule<Z80Memory>;
#endif
