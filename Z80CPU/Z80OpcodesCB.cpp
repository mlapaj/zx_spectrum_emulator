#ifdef Z80TESTS
#include "../Tests/Z80CPUModuleTest.hpp"
#endif

#include "Z80Opcodes.hpp"

/**
 * Check number of set bits
 * @param value
 * @return 
 */
unsigned int bitCount (unsigned int value) {
    unsigned int count = 0;
    while (value > 0) {           // until all bits are zero
        if ((value & 1) == 1)     // check lower bit
            count++;
        value >>= 1;              // shift bits, removing lower bit
    }
    return count;
}


template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::ROT_r8(rotOperation rot,UINT8 *dst)
{
    switch (rot)
    {
        case RLC:
        {
            CHECK_BIT(*dst,7) ? SET_FLAG_C() : CLR_FLAG_C();
            ROTL8(*dst,1);
            break;
        }
        case RRC:
        {
            CHECK_BIT(*dst,0) ? SET_FLAG_C() : CLR_FLAG_C();
            ROTR8(*dst,1);
            break;
        }
        case RL:
        {
            bool oldC = TEST_FLAG_C();
            CHECK_BIT(*dst,7) ? SET_FLAG_C():CLR_FLAG_C();
            oldC ? SET_BIT(*dst,7) : CLR_BIT(*dst,7);
            ROTL8(*dst,1);            
            break;
        }
        case RR:
        {
            bool oldC = TEST_FLAG_C();
            CHECK_BIT(*dst,0) ? SET_FLAG_C():CLR_FLAG_C();
            oldC ? SET_BIT(*dst,0) : CLR_BIT(*dst,0);
            ROTR8(*dst,1);
            break;
        }
        case SLA:
        {
            CHECK_BIT(*dst,7) ? SET_FLAG_C():CLR_FLAG_C();
            *dst = *dst << 1;
            break;
        }
        case SRA:
        {
            CHECK_BIT(*dst,0) ? SET_FLAG_C():CLR_FLAG_C();
            bool toSetB7 = CHECK_BIT(*dst,7);
            *dst = *dst >> 1;
            toSetB7 ? SET_BIT(*dst,7) : CLR_BIT(*dst,7);
            
            break;
        }
        case SRL:
        {
            CHECK_BIT(*dst,0) ? SET_FLAG_C():CLR_FLAG_C();
            *dst = *dst >> 1;
            break;
        }
        // unofficial instruction
        case SLL:
        {
            
            CHECK_BIT(*dst,7) ? SET_FLAG_C():CLR_FLAG_C();
            *dst = *dst << 1;
            SET_BIT((*dst),0);
            break;
        }
        
        default:
        {
            
            LOG4CXX_WARN(logger,"unsupported operation ROT_r8");
            break;
        }
        
    }
    // set flags
    CLR_FLAG_H();
    CLR_FLAG_N();
    (0 == bitCount(*dst) % 2) ? SET_FLAG_PV() : CLR_FLAG_PV();
    (INT8(*dst)<0) ? SET_FLAG_S() : CLR_FLAG_S();
    (0 == *dst) ? SET_FLAG_Z() : CLR_FLAG_Z();
    // inc pc

    reg.PC+=1;

}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::BIT(UINT8 y,UINT8 *dst)
{
    CHECK_BIT(*dst,y) ? CLR_FLAG_Z():SET_FLAG_Z();
    SET_FLAG_H();
    CLR_FLAG_N();
    reg.PC+=1;
}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::RES(UINT8 y,UINT8 *dst)
{
    CLR_BIT(*dst,y);
    reg.PC+=1;
}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::SET(UINT8 y,UINT8 *dst)
{
    SET_BIT(*dst,y);
    reg.PC+=1;
}




#ifdef Z80TESTS
template class Z80Opcodes<MockZ80Memory>;
#else
template class Z80Opcodes<Z80Memory>;
#endif
