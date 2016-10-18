#ifdef Z80TESTS
#include "../Tests/Z80CPUModuleTest.hpp"
#endif

#include "Z80Opcodes.hpp"

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::IN_r8_addr_C(UINT8 *dst)
{
    LOG4CXX_WARN(logger, "in stub");
}


template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::IN_addr_C()
{
    LOG4CXX_WARN(logger, "in c stub");
}



template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::OUT_addr_C_r8(UINT8 *dst)
{
    LOG4CXX_WARN(logger, "out c stub");
}


template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::OUT_addr_C()
{
    LOG4CXX_WARN(logger, "out addr c stub");
}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::SBC_HL_r16(UINT16 *dst)
{
    LOG4CXX_WARN(logger, "sbc hd r 16 stub");
}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::ADC_HL_r16(UINT16 *dst)
{
    LOG4CXX_WARN(logger, "adc hl r16 stub");
}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::NEG()
{
    (reg.A == 0x80) ? SET_FLAG_PV() : CLR_FLAG_PV();
    ((INT8) reg.A != 0) ? SET_FLAG_C() : CLR_FLAG_C();
	reg.A = (INT8) -reg.A;
    ((INT8) reg.A < 0) ? SET_FLAG_S() : CLR_FLAG_S();
    ((INT8) reg.A == 0) ? SET_FLAG_Z() : CLR_FLAG_Z();
    HALF_BORROW8((reg.A),4) ? SET_FLAG_H() : CLR_FLAG_H();
    SET_FLAG_N();
    reg.PC=reg.PC+1;
}


template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::RETN()
{
    LOG4CXX_WARN(logger, "retn stub");
}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::RETI()
{
    LOG4CXX_WARN(logger, "reti stub");
}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::IM(interruptMode mode)
{
/*	reg.IM = mode; */
/*	reg.PC=reg.PC+1; */
}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::RRD()
{
    LOG4CXX_WARN(logger, "rrd stub");
}


template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::RLD()
{
    LOG4CXX_WARN(logger, "stub");
}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::BLI(blockOperationType operType)
{
	int countm = 0;
	switch (operType){
		case LDDR:
			while (reg.BC != 0)
			{
				LOG4CXX_DEBUG(logger,"de" << reg.DE << "<=HL" << reg.HL << "\n");
				LD(*mem.getAddrPtr8(reg.DE),mem.get8(reg.HL));
				reg.DE = reg.DE - 1;
				reg.HL = reg.HL - 1;
				reg.BC = reg.BC - 1;
			}
			break;
		default:
			break;
	}
	reg.PC = reg.PC + 1;
	CLR_FLAG_PV();
}


#ifdef Z80TESTS
template class Z80Opcodes<MockZ80Memory>;
#else
template class Z80Opcodes<Z80Memory>;
#endif
