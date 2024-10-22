/*
 * File:   Z80Opcodes.cpp
 * Author: lapajmar
 *
 * Created on 18 marzec 2014, 16:45
 */
#include "Z80Types.hpp"
#include "Z80Opcodes.hpp"
#include "Z80CPUModule.hpp"
#include "Z80Memory.hpp"
#include "Z80Timing.hpp"
#include <iostream>

using namespace std;

template<typename tZ80Memory>
inline void Z80Opcodes<tZ80Memory>::executeOpcode()
    {
		opcodeInfo opInfo;
        UINT8 opcode = mem.get8(reg.PC);
		if (debug){
			LOG4CXX_TRACE(logger, "executing opcode: " << static_cast<int>(opcode));
		}
		if (debug){
			opInfo = debugOpcode(opcode,reg.PC);
			cout << "\n" + opInfo.mnemonic + "\n";
		}
		LOG4CXX_DEBUG(logger,std::hex << "exec opcode");
		// debugNormalOpcode should be executed before parseNormalOpcode - this
		// will execute and might change some things in data/registers (especially PC register)
		parseNormalOpcode(opcode);
		if (getCpuCurrentInstructionCycles() == 0){
			cout << "Zero CurrentInstructionCycles" << (int) opcode << "next:" << (int) mem.get8(reg.PC+1) << "PC AT" << reg.PC << endl;
		}
		counterInstructionCycles += getCpuCurrentInstructionCycles();
		if (counterInstructionCycles > 4000){
			usleep(1000);
			counterInstructionCycles = 0;
			counterInterrupt+=1;
		}
		if (counterInterrupt > 20){
			if (reg.interruptsEnabled == true){
				//rst 0x38
				UINT16 val  = (reg.PC-1);
				PUSH16(&val);
				reg.PC = 0x38;
				// generate interrupt
				cout << "interrupt generated";
			}
			counterInterrupt = 0;
		}
    }



template<typename tZ80Memory>
Z80Opcodes<tZ80Memory>::Z80Opcodes(tZ80Memory &cZ80Memory,Z80Registers &cZ80Registers):
reg(cZ80Registers),mem(cZ80Memory),logger(Logger::getLogger("Z80Opcodes")){
    LOG4CXX_DEBUG(logger, "class created");
	debug = 0;
	additionalTCycles = 0;
	counterInterrupt = 0;
	currentInstructionCycles = 0;
	currentInstructionCycles = 0;
	fdPrefixUsed = false;
	ddPrefixUsed = false;
	debugHLReplaced = false;
	debugRegReplaced = false;
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
		case 2: {
					if (ddPrefixUsed){
						dst=&reg.IX;
					}
					else if (fdPrefixUsed){
						dst=&reg.IY;
					}
					else
					{
						dst=&reg.HL;
					}
					break;
				}
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
		case 2: {
					if (ddPrefixUsed){
						dst=&reg.IX;
					}
					else if (fdPrefixUsed){
						dst=&reg.IY;
					}
					else{
						dst=&reg.HL;
					}
					break;
				}
		case 3: {dst=&reg.AF; break;}
		defaut:
		{
			throw "error";
		}
	}
	return dst;
}
int reg_hl_replaced = 0;
int reg_replaced_prefix = 0;

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
		case 4: {
					if (ddPrefixUsed){
						reg_replaced_prefix = 1;
						dst=&reg.IXH;
					} else if (fdPrefixUsed)
					{
						dst=&reg.IYH;
						reg_replaced_prefix = 1;
					}
					else
					{
					dst=&reg.H;
					}
					break;
				}
		case 5: {
					if (ddPrefixUsed){
						dst=&reg.IXL;
						reg_replaced_prefix = 1;
					}
					else if (fdPrefixUsed)
					{
						dst=&reg.IYL;
						reg_replaced_prefix = 1;
					}
					else {
					dst=&reg.L;
					}
					break;
				}
		case 6: {
					/*cout << "LAPAJ2 dd " << (int) ddPrefixUsed << " df" << (int) fdPrefixUsed << "y: " << (int)y << endl;*/
					if (ddPrefixUsed){
						reg_hl_replaced = 1;
						reg_replaced_prefix = 1;
						// TODO: to check for LD IXH, (IX+d) does not exist
						INT8 d = mem.get8(reg.PC+1);
					/*	cout << "our case IX:" << dec << reg.IX + d << endl; */
						dst=mem.getAddrPtr8(reg.IX + d);
						reg.PC+=1;
					}
					else if (fdPrefixUsed)
					{
						reg_hl_replaced = 1;
						reg_replaced_prefix = 1;
						INT8 d = mem.get8(reg.PC+1);
					/*	cout << "our case IY:" << dec << reg.IY + d << endl; */
						dst=mem.getAddrPtr8(reg.IY + d);
						reg.PC+=1;
					}
					else {
						dst=mem.getAddrPtr8(reg.HL);
					}
					break;
				}
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
					/* TODO */
                    out = INDR;
                    break;
                }
                case 3:
                {
					/* TODO */
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
	if ((ddPrefixUsed == 0) and (fdPrefixUsed == 0)){
		currentInstructionCycles = 0;
	}
	additionalTCycles = 0;
	if (opcode == 0xFD)
	{
		/*
		cout << "fd prefix" << endl;
		*/
		LOG4CXX_WARN(logger,"FD PREFIX: " << int(opcode));
		fdPrefixUsed = true;
		reg.PC+=1;
		int newOpcode = mem.get8(reg.PC);
		currentInstructionCycles = Z80CyclesForIXIYInstructions[newOpcode];
		parseNormalOpcode(newOpcode);
		fdPrefixUsed = false;
		ddPrefixUsed = false;
	}
	else if (opcode == 0xDD){
		/*
		cout << "dd prefix" << endl;
		*/
		LOG4CXX_WARN(logger,"DD PREFIX: " << int(opcode));
		ddPrefixUsed = true;
		reg.PC+=1;
		int newOpcode = mem.get8(reg.PC);
		currentInstructionCycles = Z80CyclesForIXIYInstructions[newOpcode];
		parseNormalOpcode(newOpcode);
		fdPrefixUsed = false;
		ddPrefixUsed = false;
	}
	else
	{
		if (ddPrefixUsed == false && fdPrefixUsed == false){
			currentInstructionCycles = Z80CyclesForMainInstructions[opcode];
		}
/*		LOG4CXX_WARN(logger,"NORMAL (or FD/DD prefix) opcode: " << int(opcode)); */
		UINT8 z,y,x,p,q = 0;
		z = opcode & 0b111;
		y = (opcode >> 3) & 0b111;
		x = (opcode >> 6) & 0b11;
		p = y >> 1 & 0b11;
		q = y & 0b1;
		
		LOG4CXX_WARN(logger,"opcode val: " << int(opcode));
		LOG4CXX_WARN(logger,"x: " << int(x) << "z: " << int(z) << "q: " << int(q) << "y: " << int(y) << "p: " << int(p));
		
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
									case 1: {
												if (ddPrefixUsed){
													ADD_IX_r16(dst);
												} else if (fdPrefixUsed)
												{
													ADD_IY_r16(dst);
												}
												else
												{

													ADD_HL_r16(dst); break;
												}
											}
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
														if (ddPrefixUsed){
															dst16 = &reg.IX;
														}
														else if (fdPrefixUsed){
															dst16 = &reg.IY;
														}
														else{
															dst16 = &reg.HL;
														}

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
														if (ddPrefixUsed){
															dst16 = &reg.IX;
														}
														else if (fdPrefixUsed){
															dst16 = &reg.IY;
														}
														else{
															dst16 = &reg.HL;
														}
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
					if ((6 == z) && (6==y))
					{
						HALT();
					}
					else
					{
						UINT8 *dst,*src = 0;
						reg_hl_replaced = 0;
						reg_replaced_prefix = 0;
						//cout << "LAPAJ " << (int) fdPrefixUsed;
						//cout << "check dst y" << (int) y << endl;
						dst = parseGet8BRegisterPair(y);
						// second register must be H or L
						if (reg_hl_replaced == 1){
							ddPrefixUsed = false;
							fdPrefixUsed = false;
						//    cout << "replaced, check src" << endl;
							src = parseGet8BRegisterPair(z);
						} else {
						// "not replaced, check src" << endl;
							reg_hl_replaced = 0;
							src = parseGet8BRegisterPair(z);
							if (reg_hl_replaced == 1){
								ddPrefixUsed = false;
								fdPrefixUsed = false;
								dst = parseGet8BRegisterPair(y);
							}
						}
						LD_r8_r8(dst,src);
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
											dst = parseGet16BRegisterPair2(p);
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
														if (ddPrefixUsed){
															JP(&reg.IX);
														} else if (fdPrefixUsed) {
															JP(&reg.IY);
														} else
														{
															JP(&reg.HL);
														}
														break;
													}
												case 3:
													{
														if (ddPrefixUsed){
															LD_r16_r16(&reg.SP,&reg.IX);
														}
														else if (fdPrefixUsed) {
															LD_r16_r16(&reg.SP,&reg.IY);
														}
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
											if ((ddPrefixUsed) || (fdPrefixUsed)){
											    //LOG4CXX_DEBUG(logger,"DDCB/FDCB prefix");
												parseFDCBorDDCBPrefixOpcode();
											}
											else
											{
											    //LOG4CXX_DEBUG(logger,"CB prefix");
												parseCBPrefixOpcode();
											}
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
											if (ddPrefixUsed){
											EX_addr_SP_IX();
											}
											else if (fdPrefixUsed){
											EX_addr_SP_IY();
											}
											else
											{
											EX_addr_SP_HL();
											}
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
														ddPrefixUsed = true;
														goto end;
														break;
													}
												case 2:
													{
														parseEDPrefixOpcode();
														break;
													}
												case 3:
													{
														fdPrefixUsed = true;
														goto end;
														break;
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
		if ((currentInstructionCycles == 0)){
			cout << "zero" << (int) opcode << "dd" << ddPrefixUsed<< "fd" << fdPrefixUsed << endl ;
		}
		ddPrefixUsed = false;
		fdPrefixUsed = false;
	}
end:
	return;
}


template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::parseFDCBorDDCBPrefixOpcode(){
	UINT8 opcode = 0;
	opcode = mem.get8(reg.PC+2);
	INT8 d = 0;
	d = (INT8) mem.get8(reg.PC+1);

	UINT8 z,y,x,p,q = 0;
    z = opcode & 0b111;
    y = (opcode >> 3) & 0b111;
    x = (opcode >> 6) & 0b11;
    p = y >> 1 & 0b11;
    q = y & 0b1;
	reg.PC+=2;
	UINT8 *dst = 0;


	currentInstructionCycles = Z80CyclesForIXIYBitInstructions[opcode];
	if (currentInstructionCycles == 0){
		cout << "FDCB or DDCB zero" << endl;
	}
	switch (x){
		case 0:
			if (z!=6){
				cout << "LD #,rot #" << endl;
			}
			else
			{
				dst = 0;
                rotOperation oper = parseROTOperation(y);
				if (ddPrefixUsed){
					dst=mem.getAddrPtr8(reg.IX + d);
				} else if (fdPrefixUsed){
					dst=mem.getAddrPtr8(reg.IY + d);
				}
				ROT_r8(oper,dst);
			}
			break;
		case 1:
				dst = 0;
				if (ddPrefixUsed){
					dst=mem.getAddrPtr8(reg.IX + d);
				} else if (fdPrefixUsed){
					dst=mem.getAddrPtr8(reg.IY + d);
				}
				//cout << "!BIT!!!!!" << endl;
				BIT(y,dst);
			break;
		case 2:
			if (z!=6){
				cout << "LD #,res #" << endl;
			}
			else
			{
				dst = 0;
				if (ddPrefixUsed){
					dst=mem.getAddrPtr8(reg.IX + d);
				} else if (fdPrefixUsed){
					dst=mem.getAddrPtr8(reg.IY + d);
				}
				RES(y,dst);
			}
			break;
		case 3:
			if (z!=6){
				cout << "LD #,set #" << endl;
			}
			else
			{
				dst = 0;
				if (ddPrefixUsed){
					dst=mem.getAddrPtr8(reg.IX + d);
				} else if (fdPrefixUsed){
					dst=mem.getAddrPtr8(reg.IY + d);
				}
				SET(y,dst);
			}
			break;
	}
}

template<typename tZ80Memory>
void Z80Opcodes<tZ80Memory>::parseCBPrefixOpcode()
{
	UINT8 opcode = 0;
	opcode = mem.get8(reg.PC+1);

	UINT8 z,y,x,p,q = 0;
    z = opcode & 0b111;
    y = (opcode >> 3) & 0b111;
    x = (opcode >> 6) & 0b11;
    p = y >> 1 & 0b11;
    q = y & 0b1;
	reg.PC+=1;

	currentInstructionCycles = Z80CyclesForBitInstructions[opcode % 16];
	if (currentInstructionCycles == 0){
		cout << "CB zero" << (int) opcode<< endl;
	}

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
            cout << "BIT OPERATION z" << (int) z <<" dst " << (int) *dst << endl;
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


	currentInstructionCycles = Z80CyclesForExtendedInstructions[opcode];
	if ((currentInstructionCycles == 0) && (opcode != 0xED)){
			cout << "ED zero" << (int) opcode << endl;
	}

	//LOG4CXX_WARN(logger,"ED PARSE opcode: " << int(opcode) << " x: " << int(x) << "z: " << int(z) << "q: " << int(q));
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
			if (z <= 3 && y >= 4)
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
