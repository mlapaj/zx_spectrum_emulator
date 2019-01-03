/*
 * File:   Z80Registers.hpp
 * Author: lapajmar
 *
 * Created on 18 marzec 2014, 16:39
 */

#ifndef Z80REGISTERS_HPP
#define	Z80REGISTERS_HPP

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include <endian.h>

#include "Z80Types.hpp"
#include "BuildDefs.h"

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

class Z80Registers {
private:
    LoggerPtr logger;
public:
    // 16 bit registers
    UINT16 PC;
    UINT16 SP;
    // 8 bit registers
	//

	union
    {
        UINT16 IX;
        struct
        {
#if ZXBigEndian == 1
            UINT8 IXH,IXL;
#else
            UINT8 IXL,IXH;
#endif

        };
    };


	union
    {
        UINT16 IY;
        struct
        {
#if ZXBigEndian == 1
            UINT8 IYH,IYL;
#else
            UINT8 IYL,IYH;
#endif

        };
    };


    union
    {
        UINT16 HL;
        struct
        {
#if ZXBigEndian == 1
            UINT8 H,L;
#else
            UINT8 L,H;
#endif

        };
    };

    union
    {
        UINT16 DE;
        struct
        {
#if ZXBigEndian == 1
            UINT8 D,E;
#else
            UINT8 E,D;
#endif
        };
    };

    union
    {
        UINT16 BC;
        struct
        {
#if ZXBigEndian == 1
            UINT8 B,C;
#else
            UINT8 C,B;
#endif
        };
    };

    union
    {
        UINT16 AF;
        struct
        {
#if ZXBigEndian == 1
            UINT8 A,F;
#else
            UINT8 F,A;
#endif
        };
    };

    union
    {
        UINT16 secHL;
        struct
        {
#if ZXBigEndian == 1
            UINT8 secH,secL;
#else
            UINT8 secL,secH;
#endif
        };
    };

    union
    {
        UINT16 secDE;
        struct
        {
#if ZXBigEndian == 1
            UINT8 secD,secE;
#else
            UINT8 secE,secD;
#endif
        };
    };

    union
    {
        UINT16 secBC;
        struct
        {
#if ZXBigEndian == 1
            UINT8 secB,secC;
#else
            UINT8 secC,secB;
#endif
        };
    };

    union
    {
        UINT16 secAF;
        struct
        {
#if ZXBigEndian == 1
            UINT8 secA,secF;
#else
            UINT8 secF,secA;
#endif
        };
    };

#define SET_BIT(p,n) ((p) |= (1 << (n)))
#define CLR_BIT(p,n) ((p) &= ~(1 << (n)))
#define TEST_BIT(Var, Pos)  (((Var) & (1 << (Pos))) > 0)

#define SET_FLAG_S() SET_BIT(reg.F,7)
#define CLR_FLAG_S() CLR_BIT(reg.F,7)
#define TEST_FLAG_S() TEST_BIT(reg.F,7)

#define SET_FLAG_Z() SET_BIT(reg.F,6)
#define CLR_FLAG_Z() CLR_BIT(reg.F,6)
#define TEST_FLAG_Z() TEST_BIT(reg.F,6)

#define SET_FLAG_F5() SET_BIT(reg.F,5)
#define CLR_FLAG_F5() CLR_BIT(reg.F,5)
#define TEST_FLAG_F5() TEST_BIT(reg.F,5)

#define SET_FLAG_H() SET_BIT(reg.F,4)
#define CLR_FLAG_H() CLR_BIT(reg.F,4)
#define TEST_FLAG_H() TEST_BIT(reg.F,4)

#define SET_FLAG_P3() SET_BIT(reg.F,3)
#define CLR_FLAG_P3() CLR_BIT(reg.F,3)
#define TEST_FLAG_P3() TEST_BIT(reg.F,3)

#define SET_FLAG_PV() SET_BIT(reg.F,2)
#define CLR_FLAG_PV() CLR_BIT(reg.F,2)
#define TEST_FLAG_PV() TEST_BIT(reg.F,2)

#define SET_FLAG_N() SET_BIT(reg.F,1)
#define CLR_FLAG_N() CLR_BIT(reg.F,1)
#define TEST_FLAG_N() TEST_BIT(reg.F,1)

#define SET_FLAG_C() SET_BIT(reg.F,0)
#define CLR_FLAG_C() CLR_BIT(reg.F,0)
#define TEST_FLAG_C() TEST_BIT(reg.F,0)

/*
    struct sZ80Flags
    {
        bool S;
        bool Z;
        bool F5;
        bool H;
        bool P3;
        bool PV;
        bool N;
        bool C;
    };
*/
    UINT8 I;
	UINT8 IM; /*interrupt mode*/
    UINT8 R;

//    struct sZ80Flags flags;
    bool isHalt;
	bool interruptsEnabled;

    Z80Registers();
    void reset();
    void zero();
    void dump();
    void dumpFull();
    virtual ~Z80Registers();
private:

};

#endif	/* Z80REGISTERS_HPP */

