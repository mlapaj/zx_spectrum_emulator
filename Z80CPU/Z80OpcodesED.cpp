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
    UINT16 c = 0;
	c = reg.HL - *dst - (TEST_FLAG_C() ? 1 : 0);
	(c>reg.HL) ? SET_FLAG_C() : CLR_FLAG_C();
	OVERFLOW16(reg.HL,dst) ? SET_FLAG_PV() : CLR_FLAG_PV();
	HALF_BORROW16(reg.HL,*dst) ? SET_FLAG_H() : CLR_FLAG_H();
	SET_FLAG_N();
	reg.A = c;
	// set flags
	((INT16)c<0)  ? SET_FLAG_S() : CLR_FLAG_S();
    (c==0) ? SET_FLAG_Z() : CLR_FLAG_Z();
	reg.HL=c;
    reg.PC+=1;

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
	reg.IM = mode;
	LOG4CXX_DEBUG(logger,"PC val is: " << reg.PC);
	reg.PC=reg.PC+1; 
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
    LOG4CXX_DEBUG(logger,"bli" << (int) reg.PC);
	int countm = 0;
	switch (operType){
		case LDDR:
//			LOG4CXX_DEBUG(logger,"lddr de" << reg.DE << "<=HL" << reg.HL << "\n");
			while (reg.BC != 0)
			{
				LD(*mem.getAddrPtr8(reg.DE),mem.get8(reg.HL));
				reg.DE = reg.DE - 1;
				reg.HL = reg.HL - 1;
				reg.BC = reg.BC - 1;
				CLR_FLAG_H();
				CLR_FLAG_PV();
				CLR_FLAG_N();
			}
			break;
		case LDIR:
//			LOG4CXX_DEBUG(logger,"lddr de" << reg.DE << "<=HL" << reg.HL << "\n");
			while (reg.BC != 0)
			{
				LD(*mem.getAddrPtr8(reg.DE),mem.get8(reg.HL));
				reg.DE = reg.DE + 1;
				reg.HL = reg.HL + 1;
				reg.BC = reg.BC - 1;
				CLR_FLAG_H();
				CLR_FLAG_PV();
				CLR_FLAG_N();
			}
			break;
		case LDI:
				LOG4CXX_DEBUG(logger,"ldi de" << reg.DE << "<=HL" << reg.HL << "\n");
				LD(*mem.getAddrPtr8(reg.DE),mem.get8(reg.HL));
				reg.DE = reg.DE + 1;
				reg.HL = reg.HL + 1;
				reg.BC = reg.BC - 1;
				CLR_FLAG_H();
				(reg.BC != 0) ? SET_FLAG_PV() : CLR_FLAG_PV();
				CLR_FLAG_N();
				break;
		case LDD:
				LOG4CXX_DEBUG(logger,"ldd de" << reg.DE << "<=HL" << reg.HL << "\n");
				LD(*mem.getAddrPtr8(reg.DE),mem.get8(reg.HL));
				reg.DE = reg.DE - 1;
				reg.HL = reg.HL - 1;
				reg.BC = reg.BC - 1;
				CLR_FLAG_H();
				(reg.BC != 0) ? SET_FLAG_PV() : CLR_FLAG_PV();
				CLR_FLAG_N();
			break;
		case CPI:
			{
				LOG4CXX_DEBUG(logger,"cpi =HL" << reg.HL << "\n");
				UINT8 data;
				data = mem.get8(reg.HL);
				reg.HL = reg.HL + 1;
				reg.BC = reg.BC - 1;
				int wynik;
				wynik = reg.A - data;
				CLR_FLAG_H();
				(wynik < 0) ? SET_FLAG_S() : CLR_FLAG_S();
				(wynik == 0) ? SET_FLAG_Z() : CLR_FLAG_Z();
				(reg.BC != 0) ? SET_FLAG_PV() : CLR_FLAG_PV();
				HALF_BORROW8(reg.A,data)  ? SET_FLAG_H() : CLR_FLAG_H();
				SET_FLAG_N();
			}
			break;
		case CPIR:
			{
				LOG4CXX_DEBUG(logger,"cpi =HL" << reg.HL << "\n");
				UINT8 data;
				int wynik;
				while (reg.BC != 0)
				{
					data = mem.get8(reg.HL);
					reg.HL = reg.HL + 1;
					reg.BC = reg.BC - 1;
					wynik = reg.A - data;
					if (wynik == 0) break;
				}
				CLR_FLAG_H();
				(wynik < 0) ? SET_FLAG_S() : CLR_FLAG_S();
				(wynik == 0) ? SET_FLAG_Z() : CLR_FLAG_Z();
				(reg.BC != 0) ? SET_FLAG_PV() : CLR_FLAG_PV();
				HALF_BORROW8(reg.A,data)  ? SET_FLAG_H() : CLR_FLAG_H();
				SET_FLAG_N();
			}
			break;
		case CPD:
			{
				LOG4CXX_DEBUG(logger,"cpd =HL" << reg.HL << "\n");
				UINT8 data;
				data = mem.get8(reg.HL);
				reg.HL = reg.HL - 1;
				reg.BC = reg.BC - 1;
				int wynik;
				wynik = reg.A - data;
				CLR_FLAG_H();
				(wynik < 0) ? SET_FLAG_S() : CLR_FLAG_S();
				(wynik == 0) ? SET_FLAG_Z() : CLR_FLAG_Z();
				(reg.BC != 0) ? SET_FLAG_PV() : CLR_FLAG_PV();
				HALF_BORROW8(reg.A,data)  ? SET_FLAG_H() : CLR_FLAG_H();
				SET_FLAG_N();
			}
			break;
		case CPDR:
			{
				LOG4CXX_DEBUG(logger,"cpi =HL" << reg.HL << "\n");
				UINT8 data;
				int wynik;
				while (reg.BC != 0)
				{
					data = mem.get8(reg.HL);
					reg.HL = reg.HL - 1;
					reg.BC = reg.BC - 1;
					wynik = reg.A - data;
					if (wynik == 0) break;
				}
				CLR_FLAG_H();
				(wynik < 0) ? SET_FLAG_S() : CLR_FLAG_S();
				(wynik == 0) ? SET_FLAG_Z() : CLR_FLAG_Z();
				(reg.BC != 0) ? SET_FLAG_PV() : CLR_FLAG_PV();
				HALF_BORROW8(reg.A,data)  ? SET_FLAG_H() : CLR_FLAG_H();
				SET_FLAG_N();
			}
			break;
		default:
			LOG4CXX_DEBUG(logger,"unknown bli oper type!");
			break;
	}
	reg.PC = reg.PC + 1;

}


#ifdef Z80TESTS
template class Z80Opcodes<MockZ80Memory>;
#else
template class Z80Opcodes<Z80Memory>;
#endif
