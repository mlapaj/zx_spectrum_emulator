#ifdef Z80TESTS
#include "../Tests/Z80CPUModuleTest.hpp"
#endif

#include "Z80Opcodes.hpp"


template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::NOP()
{
   reg.PC++;
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::EX_AF_sAF()
{
    SWAP16(reg.AF,reg.secAF);
    reg.PC+=1;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::EX_addr_SP_HL()
{
    UINT16 *toSwap = mem.getAddrPtr16(reg.SP);
    SWAP16(*toSwap,reg.HL);
    reg.PC+=1;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::EX_DE_HL()
{
    SWAP16(reg.DE,reg.HL);
    reg.PC+=1;
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::EXX()
{
    SWAP16(reg.BC,reg.secBC);
    SWAP16(reg.DE,reg.secDE);
    SWAP16(reg.HL,reg.secHL);

    reg.PC+=1;
}



template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::INC_r16(UINT16 *dst)
{
	INCrr(*dst);
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::DEC_r16(UINT16 *dst)
{
    DECrr(*dst);
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::INC_r8(UINT8 *dst)
{
	INCr(*dst);
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::DEC_r8(UINT8 *dst)
{
    DECr(*dst);
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::LD_r16_nn(UINT16 *dst)
{
	LD(*dst,mem.get16(reg.PC+1));
	reg.PC+=3;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::LD_r8_n(UINT8 *dst)
{
	LD(*dst,mem.get8(reg.PC+1));
	reg.PC+=2;
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::LD_A_addr_r16(UINT16 *dst)
{
	LD(reg.A,*mem.getAddrPtr8(*dst));
	reg.PC+=1;
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::LD_addr_nn_r16(UINT16 *dst)
{
	LD(*mem.getAddrPtr16(mem.get16(reg.PC+1)),*dst);
	reg.PC+=3;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::LD_addr_nn_r8(UINT8 *dst)
{
	LD(*mem.getAddrPtr8(mem.get16(reg.PC+1)),*dst);
	reg.PC+=3;
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::LD_r16_addr_nn(UINT16 *dst)
{
	LD(*dst,*mem.getAddrPtr16(mem.get16(reg.PC+1)));
	reg.PC+=3;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::LD_r8_addr_nn(UINT8 *dst)
{
	LD(*dst,*mem.getAddrPtr8(mem.get16(reg.PC+1)));
	reg.PC+=3;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::LD_addr_r16_A(UINT16 *dst)
{
	LD(*mem.getAddrPtr8(*dst),reg.A);
	reg.PC+=1;
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::LD_r8_r8(UINT8 *src,UINT8 *dst)
{
	LD(*src,*dst);
	reg.PC+=1;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::LD_r16_r16(UINT16 *src,UINT16 *dst)
{
	LD(*src,*dst);
	reg.PC+=1;
}



template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::RLCA()
{
   CHECK_BIT(reg.A,7) ? SET_FLAG_C() : CLR_FLAG_C();
   ROTL8(reg.A,1);
   CLR_FLAG_H();
   CLR_FLAG_N();
   reg.PC+=1;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::RRCA()
{
   CHECK_BIT(reg.A,0) ? SET_FLAG_C() : CLR_FLAG_C();
   ROTR8(reg.A,1);
   CLR_FLAG_H();
   CLR_FLAG_N();
   reg.PC+=1;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::RLA()
{
   bool oldC = TEST_FLAG_C();
   CHECK_BIT(reg.A,7) ? SET_FLAG_C():CLR_FLAG_C();
   oldC ? SET_BIT(reg.A,7) : CLR_BIT(reg.A,7);
   ROTL8(reg.A,1);
   CLR_FLAG_H();
   CLR_FLAG_N();
   reg.PC+=1;

}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::RRA()
{
   bool oldC = TEST_FLAG_C();
   CHECK_BIT(reg.A,0) ? SET_FLAG_C():CLR_FLAG_C();
   oldC ? SET_BIT(reg.A,0) : CLR_BIT(reg.A,0);
   ROTR8(reg.A,1);
   CLR_FLAG_H();
   CLR_FLAG_N();
   reg.PC+=1;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::DAA()
{
    LOG4CXX_WARN(logger, "class created");
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::CPL()
{
    reg.A = ~reg.A;
    SET_FLAG_H();
    SET_FLAG_N();
    reg.PC+=1;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::SCF()
{
    SET_FLAG_C();
    CLR_FLAG_H();
    CLR_FLAG_N();
    reg.PC+=1;

}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::CCF()
{
	TEST_FLAG_C() ? SET_FLAG_H() : CLR_FLAG_H();
	TEST_FLAG_C() ? CLR_FLAG_C() : SET_FLAG_C();
    CLR_FLAG_N();
    reg.PC+=1;
}



template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::HALT()
{
    reg.isHalt=true;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::RST(UINT16 val)
{
    PUSH16(&reg.PC);
    reg.PC = val;
    reg.isHalt=true;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::DI()
{
    /// todo !!!!!!!!!!!!
	reg.PC+= 1;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::EI()
{
    /// todo !!!!!!!!!!!!
	reg.PC += 1;
}


template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::ADD_HL_r16(UINT16 *dst){
// todo
	UINT16 c = reg.HL + *dst;
   (c<reg.HL) ? SET_FLAG_C() : CLR_FLAG_C();
   HALF_CARRY16(reg.HL,*dst) ? SET_FLAG_H(): CLR_FLAG_H();
   reg.HL = c;
   CLR_FLAG_Z();
   reg.PC+=1;
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::DJNZ()
{
    reg.B-=1;
    if (reg.B != 0)
    {
        reg.PC+= (INT8) mem.get8(reg.PC+1);
    }
    else
    {
        reg.PC+=2;
    }

}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::JR()
{
	INT8 dst = mem.get8(reg.PC+1);
    reg.PC+= dst + 2;
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::JP(UINT16 *dst)
{
    reg.PC= *dst;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::JP(UINT16 dst)
{
    reg.PC= dst;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::JR_cond_nn(condition cond)
{
	bool hasBeenJump = false;
	switch (cond)
    {
        case NZ:{if (TEST_FLAG_Z() == false){JR();hasBeenJump=true;} break;}
        case Z:{if (TEST_FLAG_Z() == true){JR();hasBeenJump=true;} break;}
        case NC:{if (TEST_FLAG_C()== false){JR();hasBeenJump=true;} break;}
        case C:{if (TEST_FLAG_C() == true){JR();hasBeenJump=true;} break;}
        case PO:{if (TEST_FLAG_PV() == false){JR();hasBeenJump=true;}break;}
        case PE:{if (TEST_FLAG_PV() == true){JR();hasBeenJump=true;}break;}
        case P:{if (TEST_FLAG_S() == false){JR();hasBeenJump=true;}break;}
        case M:{if (TEST_FLAG_S() == true){JR();hasBeenJump=true;}break;}
    }
	if (false == hasBeenJump)
	{
		reg.PC+= 2;
	}
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::JP_cond_nn(condition cond)
{
    bool hasBeenJump = false;
    switch (cond)
    {
        case NZ:{if (TEST_FLAG_Z() == false){JP_nn();hasBeenJump=true;} break;}
        case Z:{ if (TEST_FLAG_Z() == true){ JP_nn();hasBeenJump=true;} break;}
        case NC:{if (TEST_FLAG_C() == false){JP_nn();hasBeenJump=true;} break;}
        case C: {if (TEST_FLAG_C() == true){JP_nn();hasBeenJump=true;} break;}
        case PO:{if (TEST_FLAG_PV() == false){JP_nn();hasBeenJump=true;}break;}
        case PE:{if (TEST_FLAG_PV() == true){JP_nn();hasBeenJump=true;}break;}
        case P:{if (TEST_FLAG_S() == false){JP_nn();hasBeenJump=true;}break;}
        case M:{if (TEST_FLAG_S() == true){JP_nn();hasBeenJump=true;}break;}
    }

    if (false == hasBeenJump)
    {
        reg.PC+=3;
    }

}




template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::CALL_cond_nn(condition cond)
{
	bool hasBeenJump = false;
    switch (cond)
    {
        case NZ:{if (TEST_FLAG_Z() == false){CALL_nn();hasBeenJump=true;} break;}
        case Z:{if (TEST_FLAG_Z() == true){CALL_nn();hasBeenJump=true;} break;}
        case NC:{if (TEST_FLAG_C() == false){CALL_nn();hasBeenJump=true;} break;}
        case C:{if (TEST_FLAG_C() == true){CALL_nn();hasBeenJump=true;} break;}
        case PO:{if (TEST_FLAG_PV() == false){CALL_nn();hasBeenJump=true;}break;}
        case PE:{if (TEST_FLAG_PV() == true){CALL_nn();hasBeenJump=true;}break;}
        case P:{if (TEST_FLAG_S() == false){CALL_nn();hasBeenJump=true;}break;}
        case M:{if (TEST_FLAG_S() == true){CALL_nn();hasBeenJump=true;}break;}
    }
    if (false == hasBeenJump)
    {
        reg.PC+=3;
    }

}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::CALL_nn()
{
	PUSH16(&reg.PC);
	// we do not need to increase PC in next line because push function does this.
    reg.PC = mem.get16(reg.PC);
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::JP_nn()
{
    reg.PC = mem.get16(reg.PC+1);
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::RET(condition cond)
{
    bool action = false;
    switch (cond)
    {
        case NZ:{if (TEST_FLAG_Z() == false){action=true;} break;}
        case Z:{if (TEST_FLAG_Z() == true){action=true;} break;}
        case NC:{if (TEST_FLAG_C() == false){action=true;} break;}
        case C:{if (TEST_FLAG_C() == true){action=true;} break;}
        case PO:{if (TEST_FLAG_PV() == false){action=true;}break;}
        case PE:{if (TEST_FLAG_PV() == true){action=true;}break;}
        case P:{if (TEST_FLAG_S() == false){action=true;}break;}
        case M:{if (TEST_FLAG_S() == true){action=true;}break;}
    }

    if (action)
    {
        reg.PC= mem.get16(reg.SP);
        reg.SP+=2;
    }
    else
    {
        reg.PC+=1;
    }
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::RET()
{
    reg.PC= mem.get16(reg.SP);
    reg.SP+=2;
}


/**
 * Check number of set bits
 * @param value
 * @return
 */
unsigned int bitCount (unsigned int value);


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::ALU(aluOperation operType,UINT8 *dst)
{
    UINT8 c = 0;
    switch (operType)
    {
        case ADD_A:{

        	c = reg.A + *dst;

            OVERFLOW8(reg.A,dst) ? SET_FLAG_PV() : CLR_FLAG_PV();
            (c<reg.A) ? SET_FLAG_C() : CLR_FLAG_C();
            HALF_CARRY8(reg.A,*dst)  ? SET_FLAG_H() : CLR_FLAG_H();
            CLR_FLAG_N();

            reg.A =c;
            break;
        }
        case ADC_A:{
            c = reg.A + *dst + (TEST_FLAG_C() ? 1 : 0);
            OVERFLOW8(reg.A,dst) ? SET_FLAG_PV() : CLR_FLAG_PV();
            (c<reg.A) ? SET_FLAG_C() : CLR_FLAG_C();
            HALF_CARRY8(reg.A,*dst)  ? SET_FLAG_H() : CLR_FLAG_H();
            CLR_FLAG_N();
            reg.A = c;
            break;
        }
        case SUB:{
            c = reg.A - *dst;
            (c>reg.A) ? SET_FLAG_C() : CLR_FLAG_C();
            OVERFLOW8(reg.A,dst) ? SET_FLAG_PV() : CLR_FLAG_PV();
            HALF_BORROW8(reg.A,*dst)  ? SET_FLAG_H() : CLR_FLAG_H();
            SET_FLAG_N();
            reg.A = c;
            break;}
        case SBC_A:{
            c = reg.A - *dst - (TEST_FLAG_C() ? 1 : 0);
            (c>reg.A) ? SET_FLAG_C() : CLR_FLAG_C();
            OVERFLOW8(reg.A,dst) ? SET_FLAG_PV() : CLR_FLAG_PV();
            HALF_BORROW8(reg.A,*dst) ? SET_FLAG_H() : CLR_FLAG_H();
            SET_FLAG_N();
            reg.A = c;
            break;
        }
        case AND:{
            c = reg.A & *dst;
            reg.A = c;
            SET_FLAG_H();
            CLR_FLAG_N();
            CLR_FLAG_C();
            (0 == bitCount(c) % 2) ? SET_FLAG_PV() : CLR_FLAG_PV();
            break;
        }

        case XOR:{
            c = reg.A ^ *dst;
            reg.A = c;
            (0 == bitCount(c) % 2) ? SET_FLAG_PV() : CLR_FLAG_PV();
            CLR_FLAG_H();
            CLR_FLAG_N();
            CLR_FLAG_C();
            break;
        }
        case OR:{
            c = reg.A | *dst;
            reg.A = c;
            (0 == bitCount(c) % 2) ? SET_FLAG_PV() : CLR_FLAG_PV();
            CLR_FLAG_H();
            CLR_FLAG_N();
            CLR_FLAG_C();
            break;
        }
        case CP:{
            c = reg.A - *dst;
            OVERFLOW8(reg.A,dst) ? SET_FLAG_PV() : CLR_FLAG_PV();
            (c>reg.A) ? SET_FLAG_C() : CLR_FLAG_C();
            //BORROW8(reg.A,*dst,c) ? SET_FLAG_C() : CLR_FLAG_C();
            HALF_BORROW8(reg.A,*dst) ? SET_FLAG_H() : CLR_FLAG_H();
            SET_FLAG_N();
            break;
        }
    }


    ((INT8)c<0)  ? SET_FLAG_S() : CLR_FLAG_S();
    (c==0) ? SET_FLAG_Z() : CLR_FLAG_Z();
    reg.PC+=1;
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::ALU_n(aluOperation operType)
{
	UINT8 dst;
    dst = mem.get8(reg.PC+1);
    ALU(operType,&dst);
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::POP16(UINT16 *dst)
{
    *dst =  mem.get16(reg.SP);
    reg.SP+=2;
    reg.PC+=1;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::PUSH16(UINT16 *dst)
{
    *mem.getAddrPtr16(reg.SP) = *dst;
    reg.SP-=2;
    reg.PC+=1;
}


template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::OUT_addr_n_A()
{
    // !!!!!!!!!!! TODO !!!!!!!
    reg.PC+=2;
}

template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::IN_A_addr_n()
{
    // !!!!!!!!!!! TODO !!!!!!!
    reg.PC+=2;
}



template<typename tZ80Memory>void Z80Opcodes<tZ80Memory>::loadNormalInstructions()
{
    // we will prepare later instruction table
}


#ifdef Z80TESTS
template class Z80Opcodes<MockZ80Memory>;
#else
template class Z80Opcodes<Z80Memory>;
#endif

