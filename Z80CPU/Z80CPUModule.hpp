/* 
 * File:   Z80CPUModule.h
 * Author: lapajmar
 *
 * Created on 18 marzec 2014, 16:29
 */

#ifndef Z80CPUMODULE_H
#define	Z80CPUMODULE_H
#include "Z80Memory.hpp"
#include "Z80Registers.hpp"
#include "Z80Opcodes.hpp"

template<typename tZ80Memory>
class Z80CPUModule{
public:
    Z80CPUModule(tZ80Memory *cZ80Memory);      
    virtual ~Z80CPUModule();
    void executeStep();
    Z80Registers getRegisters();
    void setRegisters(Z80Registers toSet);
	bool quit;
	bool debugMode;
private:
    LoggerPtr logger;
    tZ80Memory *oZ80Memory;
    Z80Registers *oZ80Registers;
    Z80Opcodes<tZ80Memory> *oZ80Opcodes;

};

#endif	/* Z80CPUMODULE_H */

