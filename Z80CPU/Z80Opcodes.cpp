/*
 * File:   Z80Opcodes.cpp
 * Author: lapajmar
 *
 * Created on 18 marzec 2014, 16:45
 */

#include "Z80Opcodes.hpp"
#include "Z80CPUModule.hpp"
#include "Z80Memory.hpp"

template<typename tZ80Memory>
Z80Opcodes<tZ80Memory>::Z80Opcodes(tZ80Memory &cZ80Memory,Z80Registers &cZ80Registers):
reg(cZ80Registers),mem(cZ80Memory),logger(Logger::getLogger("Z80Opcodes")){
    LOG4CXX_DEBUG(logger, "class created");
	debug = 0;
}
template<typename tZ80Memory>
Z80Opcodes<tZ80Memory>::~Z80Opcodes(){
    LOG4CXX_DEBUG(logger, "destructor called");
    LOG4CXX_DEBUG(logger, "deleting instruction table");
}


template<typename tZ80Memory>
inline UINT16 *Z80Opcodes<tZ80Memory>::parseGet16BRegisterPair1(int p)
{
	UINT16 *dst = 0;
	switch (p)
	{
		case 0: {dst=&reg.BC; break;}
		case 1: {dst=&reg.DE; break;}
		case 2: {dst=&reg.HL; break;}
		case 3: {dst=&reg.SP; break;}
		defaut:
		{
			throw "error";
		}
	}
	return dst;
}

template<typename tZ80Memory>
inline UINT16 *Z80Opcodes<tZ80Memory>::parseGet16BRegisterPair2(int p)
{
	UINT16 *dst = 0;
	switch (p)
	{
		case 0: {dst=&reg.BC; break;}
		case 1: {dst=&reg.DE; break;}
		case 2: {dst=&reg.HL; break;}
		case 3: {dst=&reg.AF; break;}
		defaut:
		{
			throw "error";
		}
	}
	return dst;
}



template<typename tZ80Memory>
inline UINT8 *Z80Opcodes<tZ80Memory>::parseGet8BRegisterPair(int y)
{
	UINT8 *dst = 0;
	switch (y)
	{
		case 0: {dst=&reg.B;break;}
		case 1: {dst=&reg.C;break;}
		case 2: {dst=&reg.D;break;}
		case 3: {dst=&reg.E;break;}
		case 4: {dst=&reg.H;break;}
		case 5: {dst=&reg.L;break;}
		case 6: {dst=mem.getAddrPtr8(reg.HL);break;}
		case 7: {dst=&reg.A;break;}

	}
	return dst;
}





template<typename tZ80Memory>
inline condition Z80Opcodes<tZ80Memory>::parseCondition(int y)
{
        condition cond;
	switch (y)
	{
            case 0: { cond = NZ;break;}
            case 1: { cond = Z;break;}
            case 2: { cond = NC;break;}
            case 3: { cond = C;break;}
            case 4: { cond = PO;break;}
            case 5: { cond = PE;break;}
            case 6: { cond = P;break;}
            case 7: { cond = M;break;}
	}
        return cond;
}


template<typename tZ80Memory>
inline aluOperation Z80Opcodes<tZ80Memory>::parseALUOperation(int y)
{
        aluOperation cond;
	switch (y)
	{
            case 0: { cond = ADD_A;break;}
            case 1: { cond = ADC_A;break;}
            case 2: { cond = SUB;break;}
            case 3: { cond = SBC_A;break;}
            case 4: { cond = AND;break;}
            case 5: { cond = XOR;break;}
            case 6: { cond = OR;break;}
            case 7: { cond = CP;break;}
	}
        return cond;
}


template<typename tZ80Memory>
inline rotOperation Z80Opcodes<tZ80Memory>::parseROTOperation(int y)
{
        rotOperation rot;
	switch (y)
	{
            case 0: { rot = RLC;break;}
            case 1: { rot = RRC;break;}
            case 2: { rot = RL;break;}
            case 3: { rot = RR;break;}
            case 4: { rot = SLA;break;}
            case 5: { rot = SRA;break;}
            case 6: { rot = SLL;break;}
            case 7: { rot = SRL;break;}
	}
        return rot;
}


template<typename tZ80Memory>
inline interruptMode Z80Opcodes<tZ80Memory>::parseInterruptModes(int y)
{
        interruptMode mode;
	switch (y)
	{
            case 0:
            case 4: { mode = MODE_0; break;}
            case 1:
            case 5: { mode = MODE_0_1;break;}
            case 2:
            case 6: { mode = MODE_1;break;}

            case 3:
            case 7: { mode = MODE_2; break;}
	}
        return mode;
}

template<typename tZ80Memory>
inline blockOperationType Z80Opcodes<tZ80Memory>::parseBlockOperation(int y,int z)
{
    blockOperationType out;
    switch (y)
    {
        case 4:
        {
            switch (z)
            {
                case 0:
                {
                    out = LDI;
                    break;
                }
                case 1:
                {
                    out = CPI;
                    break;
                }
                case 2:
                {
                    out = INI;
                    break;
                }
                case 3:
                {
                    out = OUTI;
                    break;
                }
            }
            break;
        }
        case 5:
        {
            switch (z)
            {
                case 0:
                {
                    out = LDD;
                    break;
                }
                case 1:
                {
                    out = CPD;
                    break;
                }
                case 2:
                {
                    out = IND;
                    break;
                }
                case 3:
                {
                    out = OUTD;
                    break;
                }
            }

            break;
        }
        case 6:
        {
            switch (z)
            {
                case 0:
                {
                    out = LDIR;
                    break;
                }
                case 1:
                {
                    out = CPIR;
                    break;
                }
                case 2:
                {
                    out = INIR;
                    break;
                }
                case 3:
                {
                    out = OUTIR;
                    break;
                }
            }
            break;
        }
        case 7:
        {
            switch (z)
            {
                case 0:
                {
                    out = LDDR;
                    break;
                }
                case 1:
                {
                    out = CPDR;
                    break;
                }
                case 2:
                {
                    out = INDR;
                    break;
                }
                case 3:
                {
                    out = OUTDR;
                    break;
                }
            }
            break;
        }
    }
	return out;
}


template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::parseNormalOpcode(UINT8 opcode)
{
    UINT8 z,y,x,p,q = 0;
    z = opcode & 0b111;
    y = (opcode >> 3) & 0b111;
    x = (opcode >> 6) & 0b11;
    p = y >> 1 & 0b11;
    q = y & 0b1;
//	LOG4CXX_WARN(logger,"x: " << int(x) << "z: " << int(z));
	switch (x)
	{
		case 0:
			{
				switch (z)
				{
					// completed
					case 0:
						{
							switch (y)
							{
								case 0:{ NOP(); break;}
								case 1:{ EX_AF_sAF(); break;}
								case 2:{ DJNZ(); break;}
								case 3:{ JR(); break;}
								case 4:
								case 5:
								case 6:
								case 7:
									   {
										   condition cond = parseCondition(y-4);
										   JR_cond_nn(cond);
										   break;
									   }
							}
							break;
						}
						// completed
					case 1:
						{
							UINT16 *dst = 0;
							dst = parseGet16BRegisterPair1(p);
							switch (q)
							{
								case 0: { LD_r16_nn(dst); break;}
								case 1: { ADD_HL_r16(dst); break;}
							}
							break;
						}
						// completed
					case 2:
						{
							UINT16* dst16 = 0;
							UINT8* dst8 = 0;
							switch (q)
							{
								case 0:
									{
										switch (p)
										{
											case 0:
												{
													dst16 = &reg.BC;
													LD_addr_r16_A(dst16);
													break;
												}
											case 1:
												{
													dst16 = &reg.DE;
													LD_addr_r16_A(dst16);
													break;
												}
											case 2:
												{
													dst16 = &reg.HL;
													LD_addr_nn_r16(dst16);
													break;
												}
											case 3:
												{
													dst8 = &reg.A;
													LD_addr_nn_r8(dst8);
													break;
												}
										}
										break;
									}
								case 1:
									{
										switch (p)
										{
											case 0:
												{
													dst16 = &reg.BC;
													LD_A_addr_r16(dst16);
													break;
												}
											case 1:
												{
													dst16 = &reg.DE;
													LD_A_addr_r16(dst16);
													break;
												}
											case 2:
												{
													dst16 = &reg.HL;
													LD_r16_addr_nn(dst16);
													break;
												}
											case 3:
												{
													dst8 = &reg.A;
													LD_r8_addr_nn(dst8);
													break;
												}
										}
										break;
									}

							}

							break;
						}
						// completed
					case 3:
						{
							UINT16 *dst = 0;
							dst = parseGet16BRegisterPair1(p);
							switch (q)
							{
								case 0: { INC_r16(dst); break;}
								case 1: { DEC_r16(dst); break;}
							}
							break;
						}

						// completed
					case 4:
						{
							UINT8 *dst = 0;
							dst = parseGet8BRegisterPair(y);
							INC_r8(dst);
							break;
						}
						// completed
					case 5:
						{
							UINT8 *dst = 0;
							dst = parseGet8BRegisterPair(y);
							DEC_r8(dst);
							break;
						}
						// completed
					case 6:
						{
							UINT8 *dst = 0;
							dst = parseGet8BRegisterPair(y);
							LD_r8_n(dst);
							break;
						}
						// add DAA
					case 7:
						{
							switch (y)
							{
								case 0: {RLCA(); break;}
								case 1: {RRCA(); break;}
								case 2: {RLA(); break;}
								case 3: {RRA(); break;}
								case 4: {DAA(); break;}
								case 5: {CPL(); break;}
								case 6: {SCF(); break;}
								case 7: {CCF(); break;}
										break;
							}

						}
					default:
						break;
				}
				break;
			}
		case 1:
			{
				if (6==y)
				{
					HALT();
				}
				else
				{
					UINT8 *src,*dst = 0;
					src = parseGet8BRegisterPair(y);
					dst = parseGet8BRegisterPair(z);
					LD_r8_r8(src,dst);
				}
				break;
			}
		case 2:
			{
				// complete
				UINT8 *dst = parseGet8BRegisterPair(z);
				aluOperation operation = parseALUOperation(y);
				ALU(operation,dst);
				break;
			}
		case 3:
			{
				switch (z)
				{
					case 0:
						{

							condition cond = parseCondition(y);
							RET(cond);
							break;
						}
					case 1:
						{

							switch (q)
							{
								case 0:
									{
										UINT16 *dst = 0;
										dst = parseGet16BRegisterPair1(p);
										POP16(dst);
										break;
									}
								case 1:
									{
										switch (p)
										{
											case 0:
												{
													RET();
													break;
												}
											case 1:
												{
													EXX();
													break;
												}
											case 2:
												{
													JP(&reg.HL);
													break;
												}
											case 3:
												{
													LD_r16_r16(&reg.SP,&reg.HL);
													break;
												}
										}
										break;
									}
							}
							break;
						}
					case 2:
						{
							condition cond = parseCondition(y);
							JP_cond_nn(cond);
							break;
						}
					case 3:
						{
							switch (y)
							{
								case 0:
									{
										JP_nn();
										break;
									}
								case 1:
									{
										LOG4CXX_DEBUG(logger,"CB prefix");
										parseCBPrefixOpcode();
										break;
									}
								case 2:
									{
										OUT_addr_n_A();;
										break;
									}
								case 3:
									{
										IN_A_addr_n();
										break;
									}
								case 4:
									{
										EX_addr_SP_HL();
										break;
									}
								case 5:
									{
										EX_DE_HL();
										break;
									}
								case 6:
									{
										DI();
										break;
									}
								case 7:
									{
										EI();
										break;
									}
							}
							break;
						}
					case 4:
						{
							condition cond = parseCondition(y);
							CALL_cond_nn(cond);
							break;
						}
					case 5:
						{
							switch (q)
							{
								case 0:
									{
										UINT16 *dst = 0;
										dst = parseGet16BRegisterPair2(p);
										PUSH16(dst);
										break;
									}
								case 1:
									{
										switch (p)
										{
											case 0:
												{
													CALL_nn();
													break;
												}
											case 1:
												{
													// DD prefix
													break;
												}
											case 2:
												{
													 parseEDPrefixOpcode();
													break;
												}
											case 3:
												{
													// FD prefix
												}

										}
										break;
									}

							}
							break;
						}
					case 6:
						{
							aluOperation oper = parseALUOperation(y);
							ALU_n(oper);
							break;
						}
					case 7:
						{
							RST(y*8);
							break;
						}

				}
				break;
			}
	}

}


template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::parseCBPrefixOpcode()
{

    UINT8 opcode =  mem.get8(reg.PC+1);
    std::cout << debugCBPrefixOpcode(opcode).mnemonic;
    UINT8 z,y,x,p,q = 0;
    z = opcode & 0b111;
    y = (opcode >> 3) & 0b111;
    x = (opcode >> 6) & 0b11;
    p = y >> 1 & 0b11;
    q = y & 0b1;
    reg.PC+=1;
    switch (x)
    {
        case 0:
        {
            rotOperation oper = parseROTOperation(y);
            UINT8 *dst = 0;
            dst = parseGet8BRegisterPair(z);
            ROT_r8(oper,dst);
            break;
        }
        case 1:
        {
            UINT8 *dst = 0;
            dst = parseGet8BRegisterPair(z);
            BIT(y,dst);
            break;
        }
        case 2:
        {
            UINT8 *dst = 0;
            dst = parseGet8BRegisterPair(z);
            RES(y,dst);
            break;
        }
        case 3:
        {
            UINT8 *dst = 0;
            dst = parseGet8BRegisterPair(z);
            SET(y,dst);
            break;
        }
    }

}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::parseEDPrefixOpcode()
{
    UINT8 opcode =  mem.get8(reg.PC+1);
    UINT8 z,y,x,p,q = 0;
    z = opcode & 0b111;
    y = (opcode >> 3) & 0b111;
    x = (opcode >> 6) & 0b11;
    p = y >> 1 & 0b11;
    q = y & 0b1;
    reg.PC+=1; // additional ED prefix

//	LOG4CXX_WARN(logger,"ED PARSE opcode: " << int(opcode) << " x: " << int(x) << "z: " << int(z) << "q: " << int(q));
	switch (x)
	{
		case 1:
		{
			switch (z)
			{
				case 0:
				{

					if (y!=6)
					{
						UINT8 *dst;
						dst = parseGet8BRegisterPair(y);
						IN_r8_addr_C(dst);
					}
					else
					{
						IN_addr_C();
					}
					break;
				}
				case 1:
				{
					if (y!=6)
					{
						UINT8 *dst;
						dst = parseGet8BRegisterPair(y);
						OUT_addr_C_r8(dst);
					}
					else
					{
						OUT_addr_C();
					}
					break;
				}
				case 2:
				{
					if (0==q)
					{
						UINT16 *dst;
						dst = parseGet16BRegisterPair1(p);
						SBC_HL_r16(dst);
					}
					if (1==q)
					{
						UINT16 *dst;
						dst = parseGet16BRegisterPair1(p);
						ADC_HL_r16(dst);
					}
					break;
				}
                case 3:
                {

                    if (0==q)
                    {
                        UINT16 *dst;
                        dst = parseGet16BRegisterPair1(p);
                        LD_addr_nn_r16(dst);
                    }
                    if (1==q)
                    {
                        UINT16 *dst;
                        dst = parseGet16BRegisterPair1(p);
                        LD_r16_addr_nn(dst);
                    }
                    break;
                }
                case 4:
                {
                    NEG();
                }
                case 5:
                {
                    if (y!=1)
                    {
                        RETN();
                    }
                    else
                    {
                        RETI();
                    }
                    break;
                }
                case 6:
                {
                    interruptMode mode;
                    mode = parseInterruptModes(y);
                    IM(mode);
					break;
                }

                case 7:
                {
                    switch (y)
                    {
                        case 0:
                        {
                            LD_r8_r8(&reg.I,&reg.A);
                            break;
                        }
                        case 1:
                        {
                            LD_r8_r8(&reg.R,&reg.A);
                            break;
                        }
                        case 2:
                        {
                            LD_r8_r8(&reg.A,&reg.I);
                            break;
                        }
                        case 3:
                        {
                            LD_r8_r8(&reg.A,&reg.R);
                            break;
                        }
                        case 4:
                        {
                            RRD();
                            break;
                        }
                        case 5:
                        {
                            RLD();
                            break;
                        }
                        case 6:
                        {
                            NOP();
                            break;
                        }
                        case 7:
                        {
                            NOP();
                            break;
                        }
                    }
                }

			}

			break;
		}
		case 2:
		{
			if (z<3 && y > 4)
			{
				blockOperationType oper;
				oper = parseBlockOperation(y,z);
				BLI(oper);
				break;
			}
		}


    }
}





#ifdef Z80TESTS
class MockZ80Memory;
template class Z80Opcodes<MockZ80Memory>;
#else
template class Z80Opcodes<Z80Memory>;
#endif
