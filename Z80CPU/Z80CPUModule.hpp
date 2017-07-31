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
#include <list>

template<typename tZ80Memory>
class Z80CPUModule{
public:
    Z80CPUModule(tZ80Memory *cZ80Memory);      
    virtual ~Z80CPUModule();
	void executeStep();
    void getOpcode();
    Z80Registers getRegisters();
    void setRegisters(Z80Registers toSet);
	bool checkPCBreakpoints();
	void addPCBreakpoint(UINT16 val);
	void delPCBreakpoint(UINT16 val);
	std::list<UINT16> getPCBreakpoints(){
		return PCBreakpoints;
	}
	void clearPCBreakpoints(){
		PCBreakpoints.clear();
	}
	bool quit;
private:
    LoggerPtr logger;
    tZ80Memory *oZ80Memory;
    Z80Registers *oZ80Registers;
    Z80Opcodes<tZ80Memory> *oZ80Opcodes;
	std::list<UINT16> PCBreakpoints;

};

#endif	/* Z80CPUMODULE_H */

