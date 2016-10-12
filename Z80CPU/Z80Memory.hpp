/* 
 * File:   Z80_Memory.h
 * Author: lapajmar
 *
 * Created on 18 marzec 2014, 13:29
 */

#ifndef Z80_MEMORY_H
#define	Z80_MEMORY_H

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "Z80Types.hpp"
#include <string.h>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;


class Z80Memory
{
private:
    LoggerPtr logger;
    UINT8 *memory;
    int size;
    union
    {
    UINT16 fullWord;
    UINT8 bytes[ sizeof( UINT16 ) ];
    };
public:    
    UINT8 get8(UINT16 address);
    UINT16 get16(UINT16 address);
    UINT8 *getAddrPtr8(UINT16 address);
    UINT16 *getAddrPtr16(UINT16 address);
    Z80Memory(unsigned int size);        
    ~Z80Memory();
    int LoadRom(string romName);
    void clearMemory();
};

#endif	/* Z80_MEMORY_H */

