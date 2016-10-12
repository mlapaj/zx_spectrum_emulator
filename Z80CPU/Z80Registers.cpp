/* 
 * File:   Z80Registers.cpp
 * Author: lapajmar
 * 
 * Created on 18 marzec 2014, 16:39
 */

#include "Z80Registers.hpp"
#include <cstring>

Z80Registers::Z80Registers():logger(Logger::getLogger("Z80Registers")){
}


Z80Registers::~Z80Registers() {
}

void Z80Registers::reset() {
     LOG4CXX_DEBUG(logger, "registers reset");
     PC=0;
     SP=0;
     IX=0;
     IY=0;
     HL=0;
     DE=0;
     BC=0;
     AF=0;
     secHL=0;
     secDE=0;
     secBC=0;
     secAF=0;
     I=0;
     R=0;
     isHalt=false;
}

void Z80Registers::zero() {
     LOG4CXX_DEBUG(logger, "registers reset");
     PC=0;
     SP=0;
     IX=0;
     IY=0;
     HL=0;
     DE=0;
     BC=0;
     AF=0;
     secHL=0;
     secDE=0;
     secBC=0;
     secAF=0;
     I=0;
     R=0;
     isHalt=false;     
}


void Z80Registers::dump()
{
    LOG4CXX_DEBUG(logger,std::hex << std::uppercase << "dump PC:"<<PC<<" SP:"<<SP<<" IX:"<<IX<<" IY:"<<IY
                  <<" HL:"<<HL<<" DE:"<<DE<<" BC:"<<BC<<" AF:"<<AF
                  <<" secHL:"<<secHL<<" secDE:"<<secDE<<" secBC:"<<secBC<<" secAF:"<<secAF<<" I:"<<static_cast<int>(I)<<" R:"<<static_cast<int>(R));
}

void Z80Registers::dumpFull()
{
    LOG4CXX_DEBUG(logger,std::hex << std::uppercase << "dump full PC:"<<PC<<" SP:"<<SP<<" IX:"<<IX<<" IY:"<<IY
                  <<" HL:"<<HL<<" DE:"<<DE<<" BC:"<<BC<<" AF:"<<AF
                  <<" H:"<<static_cast<int>(H)<<" L:"<<static_cast<int>(L)<<" D:"<<static_cast<int>(D)
                  <<" E:"<<static_cast<int>(E)<<" B:"<<static_cast<int>(B)<<" C:"<<static_cast<int>(C)
                  <<" A:"<<static_cast<int>(A)<<" F:"<<static_cast<int>(F)
                  <<" secHL:"<<secHL<<" secDE:"<<secDE<<" secBC:"<<secBC<<" secAF:"<<secAF
                  <<" secH:"<<static_cast<int>(secH)<<" secL:"<<static_cast<int>(secL)<<" secD:"<<static_cast<int>(secD)
                  <<" secE:"<<static_cast<int>(secE)<<" B:"<<static_cast<int>(secB)<<" C:"<<static_cast<int>(secC)
                  <<" secA:"<<static_cast<int>(secA)<<" secF:"<<static_cast<int>(secF) <<" I:"<<static_cast<int>(I)<<" R:"<<static_cast<int>(R));
}