/*
 * File:   Z80CPUModule.cpp
 * Author: lapajmar
 *
 * Created on 18 marzec 2014, 16:29
 */

#include "Z80CPUModule.hpp"
#include "../Tests/Z80CPUModuleTest.hpp"


template<typename tZ80Memory>
Z80CPUModule<tZ80Memory>::Z80CPUModule(tZ80Memory *cZ80Memory):logger(Logger::getLogger("Z80Module")) {

    LOG4CXX_DEBUG(logger, "class created");
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
void Z80CPUModule<tZ80Memory>::cpuThread() {
    LOG4CXX_DEBUG(logger, "started main cpu thread");
    long long i=0;
	int debug = 0;
    while (i<955350)
    {
		if ((oZ80Registers->PC == 0x11DC) && (oZ80Registers->HL == 0x4001)){
			LOG4CXX_DEBUG(logger,"RAM_FILL OK.");
			oZ80Opcodes->debug = 1;
			debug = 1;
		}
		if (oZ80Registers->PC == 0x120D)
		{
			break;
		}
        oZ80Opcodes->executeOpcode();
		if (debug){
			oZ80Registers->dump();
		}
        i++;
    }
}

template<typename tZ80Memory>
void Z80CPUModule<tZ80Memory>::executeStep()
{
    oZ80Opcodes->executeOpcode();
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
