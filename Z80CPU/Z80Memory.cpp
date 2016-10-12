#include "Z80Memory.hpp"
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <exception>
#include <stdexcept>

Z80Memory::Z80Memory(unsigned int size):logger(Logger::getLogger("Z80Memory"))
{
    LOG4CXX_DEBUG(logger, "class created");
    memory = new UINT8[size];
    this->size = size;
    memset(memory,0 ,sizeof(UINT8)* size);
    
}

Z80Memory::~Z80Memory()
{
    LOG4CXX_DEBUG(logger, "destructor called");
}

long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

int Z80Memory::LoadRom(string romName)
{
    
    
    int retVal = 0;
    ifstream romFile;
    try
    {
        romFile.open(("roms/" + romName).c_str(), ios::in | ios::binary);
    }
    catch (...)
    {   
        LOG4CXX_ERROR(logger,"could not open "<< romName <<" rom file");
        retVal = -1;
    }
    
    if (romFile.good())
    {
        int fileSize = GetFileSize("roms/" + romName);        
        if (fileSize>size)
        {
            return -2;
        }
    }
    
    if (romFile.is_open())
    {    
        romFile.read(reinterpret_cast<char*>(memory) , size);    
        LOG4CXX_DEBUG(logger, "rom file read into memory");
        romFile.close();    
    }
    else
    {
        LOG4CXX_ERROR(logger,"could not open "<< romName <<" rom file");
        retVal = -1;
    }

    return retVal;
}


UINT8 Z80Memory::get8(UINT16 address)
{
    if (address >= size || address < 0)
    {
        throw new runtime_error("out of range");
    }
    LOG4CXX_TRACE(logger,"read! memory address:"<<address<<" value:"<<static_cast<int>(memory[address]));
    return memory[address];
    
}

UINT16 Z80Memory::get16(UINT16 address)
{
    if (address+1 >= size || address < 0)
    {
        throw new runtime_error("out of range");
    }

    LOG4CXX_TRACE(logger,"read! memory address:"<<address<<" value:"<<static_cast<int>(memory[address]));
    bytes[0] = memory[address];
    bytes[1] = memory[address+1];
    return fullWord;
}

UINT8 *Z80Memory::getAddrPtr8(UINT16 address)
{
	LOG4CXX_DEBUG(logger, "getAddr8 adres:" << address);
    if (address > size || address < 0)
    {
        throw new runtime_error("out of range");
    }
	LOG4CXX_DEBUG(logger,"zwracam pamiec, adres" << address);
    return reinterpret_cast<UINT8*>(&memory[address]);
}


UINT16 *Z80Memory::getAddrPtr16(UINT16 address)
{
    if (address >= size || address < 0)
    {
        throw new runtime_error("out of range");
    }
    return reinterpret_cast<UINT16*>(&memory[address]);
}

void Z80Memory::clearMemory()
{
    memset(memory,0 ,sizeof(UINT8)* size);
}
