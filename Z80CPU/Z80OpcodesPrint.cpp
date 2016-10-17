#ifdef Z80TESTS
#include "../Tests/Z80CPUModuleTest.hpp"
#endif


#include <sstream>
#include "Z80Opcodes.hpp"

template<typename tZ80Memory>
inline string Z80Opcodes<tZ80Memory>::debugCondition(int y) {
	string cond;
	switch (y) {
	case 0: {
		cond = "NZ";
		break;
	}
	case 1: {
		cond = "Z";
		break;
	}
	case 2: {
		cond = "NC";
		break;
	}
	case 3: {
		cond = "C";
		break;
	}
	case 4: {
		cond = "PO";
		break;
	}
	case 5: {
		cond = "PE";
		break;
	}
	case 6: {
		cond = "P";
		break;
	}
	case 7: {
		cond = "M";
		break;
	}
	}
	return cond;
}

template<typename tZ80Memory>
inline string Z80Opcodes<tZ80Memory>::debugGet16BRegisterPair1(int p) {
	string dst;
	switch (p) {
	case 0: {
		dst = "BC";
		break;
	}
	case 1: {
		dst = "DE";
		break;
	}
	case 2: {
		dst = "HL";
		break;
	}
	case 3: {
		dst = "SP";
		break;
	}
		defaut: {
			throw "error";
		}
	}
	return dst;
}

template<typename tZ80Memory>
inline string Z80Opcodes<tZ80Memory>::debugGet8BRegisterPair(int y) {
	string dst;
	switch (y) {
	case 0: {
		dst = "B";
		break;
	}
	case 1: {
		dst = "C";
		break;
	}
	case 2: {
		dst = "D";
		break;
	}
	case 3: {
		dst = "E";
		break;
	}
	case 4: {
		dst = "H";
		break;
	}
	case 5: {
		dst = "L";
		break;
	}
	case 6: {
		dst = "(HL)";
		break;
	}
	case 7: {
		dst = "A";
		break;
	}

	}
	return dst;

}

template<typename tZ80Memory>
inline string Z80Opcodes<tZ80Memory>::debugALUOperation(int y) {
	string cond;
	switch (y) {
	case 0: {
		cond = "ADD";
		break;
	}
	case 1: {
		cond = "ADC";
		break;
	}
	case 2: {
		cond = "SUB";
		break;
	}
	case 3: {
		cond = "SBC";
		break;
	}
	case 4: {
		cond = "AND";
		break;
	}
	case 5: {
		cond = "XOR";
		break;
	}
	case 6: {
		cond = "OR";
		break;
	}
	case 7: {
		cond = "CP";
		break;
	}
	}
	return cond;
}

template<typename tZ80Memory>
inline string Z80Opcodes<tZ80Memory>::debugGet16BRegisterPair2(int p) {
	string dst;
	switch (p) {
	case 0: {
		dst = "BC";
		break;
	}
	case 1: {
		dst = "DE";
		break;
	}
	case 2: {
		dst = "HL";
		break;
	}
	case 3: {
		dst = "AF";
		break;
	}
		defaut: {
			throw "error";
		}
	}
	return dst;
}

template<typename tZ80Memory>
opcodeInfo Z80Opcodes<tZ80Memory>::debugNormalOpcode(UINT8 opcode) {
	opcodeInfo retVal;

	UINT8 z, y, x, p, q = 0;
	z = opcode & 0b111;
	y = (opcode >> 3) & 0b111;
	x = (opcode >> 6) & 0b11;
	p = y >> 1 & 0b11;
	q = y & 0b1;
	switch (x) {
	case 0: {
		switch (z) {
		// completed
		case 0: {
			switch (y) {
			case 0: {
				retVal.mnemonic = "NOP";
				retVal.size = 1;
				break;
			}
			case 1: {
				retVal.mnemonic = "EX AF,sAF";
				retVal.size = 1;
				break;
			}
			case 2: {
				retVal.mnemonic = "DJNZ";
				retVal.size = 2;
				break;
			}
			case 3: {
				retVal.mnemonic = "JR";
				retVal.size = 2;
				break;
			}
			case 4:
			case 5:
			case 6:
			case 7: {
				string cond = debugCondition(y - 4);
				retVal.mnemonic = "JR " + cond + " nn";
				retVal.size = 2;
				break;
			}
			}
			break;
		}
			// completed
		case 1: {
			string dst;
			dst = debugGet16BRegisterPair1(p);
			switch (q) {
			case 0: {
				retVal.mnemonic = "LD " + dst + " nn";
				retVal.size = 3;
				break;
			}
			case 1: {
				retVal.mnemonic = "ADD HL," + dst;
				retVal.size = 3;
				break;
			}
			}
			break;
		}
		case 2: {
			UINT16* dst16;
			UINT8* dst8;
			switch (q) {
			case 0: {
				switch (p) {
				case 0: {
					retVal.mnemonic = "LD (BC), A";
					retVal.size = 1;
					break;
				}
				case 1: {
					retVal.mnemonic = "LD (DE), A";
					retVal.size = 1;
					break;
				}
				case 2: {
					retVal.mnemonic = "LD (nn), HL";
					retVal.size = 3;
					break;
				}
				case 3: {
					retVal.mnemonic = "LD (nn), A";
					retVal.size = 3;
					break;
				}
				}
				break;
			}
			case 1: {
				switch (p) {
				case 0: {
					retVal.mnemonic = "LD A,(BC)";
					retVal.size = 1;
					break;
				}
				case 1: {
					retVal.mnemonic = "LD A,(DE)";
					retVal.size = 1;
					break;
				}
				case 2: {
					retVal.mnemonic = "LD (HL),nn";
					retVal.size = 3;
					break;
				}
				case 3: {
					retVal.mnemonic = "LD A,(nn)";
					retVal.size = 3;
					break;
				}
				}
				break;
			}

			}

			break;
		}
			// completed
		case 3: {
			string dst;
			dst = debugGet16BRegisterPair1(p);
			switch (q) {
			case 0: {
				retVal.mnemonic = "INC " + dst;
				retVal.size = 1;
				break;
			}
			case 1: {
				retVal.mnemonic = "DEC " + dst;
				retVal.size = 1;
				break;
			}
			}
			break;
		}

			// completed
		case 4: {
			string dst;
			dst = debugGet8BRegisterPair(y);
			retVal.mnemonic = "INC " + dst;
			retVal.size = 1;
			break;
		}
			// completed
		case 5: {
			string dst;
			dst = debugGet8BRegisterPair(y);
			retVal.mnemonic = "DEC " + dst;
			retVal.size = 1;
			break;
		}
			// completed
		case 6: {
			string dst;
			dst = debugGet8BRegisterPair(y);
			retVal.mnemonic = "LD " + dst + " n";
			retVal.size = 2;
			break;
		}
			// add DAA
		case 7: {
			switch (y) {
			case 0: {
				retVal.mnemonic = "RLCA";
				retVal.size = 1;
				break;
			}
			case 1: {
				retVal.mnemonic = "RRCA";
				retVal.size = 1;
				break;
			}
			case 2: {
				retVal.mnemonic = "RLA";
				retVal.size = 1;
				break;
			}
			case 3: {
				retVal.mnemonic = "RRA";
				retVal.size = 1;
				break;
			}
			case 4: {
				retVal.mnemonic = "DAA";
				retVal.size = 1;
				break;
			}
			case 5: {
				retVal.mnemonic = "CPL";
				retVal.size = 1;
				break;
			}
			case 6: {
				retVal.mnemonic = "SCF";
				retVal.size = 1;
				break;
			}
			case 7: {
				retVal.mnemonic = "CCF";
				retVal.size = 1;
				break;
			}
				break;
			}

		}
		default:
			break;
		}
		break;
	}
	case 1: {
		if (6 == y) {
			retVal.mnemonic = "HALT";
			retVal.size = 1;
		} else {
			string src, dst;
			src = debugGet8BRegisterPair(y);
			dst = debugGet8BRegisterPair(z);
			retVal.mnemonic = "LD " + src + "," + dst;
			retVal.size = 1;
		}
		break;
	}
	case 2: {
		// complete
		string dst = debugGet8BRegisterPair(z);
		string operation = debugALUOperation(y);
		retVal.mnemonic = operation + " " + dst;
		retVal.size = 1;
		break;
	}
	case 3: {
		switch (z) {
		case 0: {

			string cond = debugCondition(y);
			retVal.mnemonic = "RET " + cond;
			retVal.size = 1;
			break;
		}
		case 1: {

			switch (q) {
			case 0: {
				string dst;
				dst = debugGet16BRegisterPair1(p);
				retVal.mnemonic = "POP " + dst;
				retVal.size = 1;
				break;
			}
			case 1: {
				switch (p) {
				case 0: {
					retVal.mnemonic = "RET";
					retVal.size = 1;
					break;
				}
				case 1: {
					retVal.mnemonic = "EXX";
					retVal.size = 1;
					break;
				}
				case 2: {
					retVal.mnemonic = "JP (HL)";
					retVal.size = 1;
					break;
				}
				case 3: {
					retVal.mnemonic = "LD SP,HL";
					retVal.size = 1;
					break;
				}
				}
				break;
			}
			}
			break;
		}
		case 2: {
			string cond = debugCondition(y);
			retVal.mnemonic = "JP " + cond + " nn";
			retVal.size = 3;
			break;
		}
		case 3: {
			switch (y) {
			case 0: {
				retVal.mnemonic = "JP nn";
				retVal.size = 3;
				break;
			}
			case 1: {
				// retVal = debugCBPrefixOpcode();
				break;
			}
			case 2: {
				retVal.mnemonic = "OUT (n),A";
				retVal.size = 2;
				break;
			}
			case 3: {
				retVal.mnemonic = "IN (n),A";
				retVal.size = 2;
				break;
			}
			case 4: {
				retVal.mnemonic = "EX (SP),HL";
				retVal.size = 1;
				break;
			}
			case 5: {
				retVal.mnemonic = "EX DE,HL";
				retVal.size = 1;
				break;
			}
			case 6: {
				retVal.mnemonic = "DI";
				retVal.size = 1;
				break;
			}
			case 7: {
				retVal.mnemonic = "EI";
				retVal.size = 1;
				break;
			}
			}
			break;
		}
		case 4: {
			string cond = debugCondition(y);
			retVal.mnemonic = "CALL " + cond + " nn";
			retVal.size = 3;
			break;
		}
		case 5: {
			switch (q) {
			case 0: {
				string dst;
				dst = debugGet16BRegisterPair2(p);
				retVal.mnemonic = "PUSH " + dst;
				retVal.size = 1;
				break;
			}
			case 1: {
				switch (p) {
				case 0: {
					retVal.mnemonic = "CALL nn";
					retVal.size = 3;
					break;
				}
				case 1: {
					// DD prefix
					break;
				}
				case 2: {
					// parseEDPrefixOpcode();
					break;
				}
				case 3: {
					// FD prefix
				}

				}
				break;
			}

			}
			break;
		}
		case 6: {
			string oper = debugALUOperation(y);
			retVal.mnemonic = oper;
			retVal.size = 2;
			break;
		}
		case 7: {
			retVal.mnemonic = "RST " + (int) y * 8;
			retVal.size = 1;
			break;
		}

		}
		break;
	}
	}

	return retVal;
}



template<typename tZ80Memory>
inline string Z80Opcodes<tZ80Memory>::debugROTOperation(int y)
{
    string rot;
	switch (y)
	{
            case 0: { rot = "RLC";break;}
            case 1: { rot = "RRC";break;}
            case 2: { rot = "RL";break;}
            case 3: { rot = "RR";break;}
            case 4: { rot = "SLA";break;}
            case 5: { rot = "SRA";break;}
            case 6: { rot = "SLL";break;}
            case 7: { rot = "SRL";break;}
	}
    return rot;
}



template<typename tZ80Memory>
opcodeInfo Z80Opcodes<tZ80Memory>::debugCBPrefixOpcode(UINT8 opcode)
{
	opcodeInfo retVal;
    UINT8 z,y,x,p,q = 0;
    z = opcode & 0b111;
    y = (opcode >> 3) & 0b111;
    x = (opcode >> 6) & 0b11;
    p = y >> 1 & 0b11;
    q = y & 0b1;
    stringstream ss;
    switch (x)
    {
        case 0:
        {
            string oper = debugROTOperation(y);
            string dst = debugGet8BRegisterPair(z);
            retVal.mnemonic =  oper + " " + dst;
            retVal.size = 2;
            break;
        }
        case 1:
        {
            string dst;
            dst = debugGet8BRegisterPair(z);
            ss << "BIT " << (int)y << "," << dst;
            retVal.mnemonic = ss.str();
            retVal.size = 2;
            break;
        }
        case 2:
        {
            string dst;
            dst = debugGet8BRegisterPair(z);
            ss << "RES " << (int) y << "," << dst;
            retVal.mnemonic = ss.str();
            retVal.size = 2;
            break;
        }
        case 3:
        {
            string dst;
            dst = debugGet8BRegisterPair(z);
            ss << "set " << (int) y << "," << dst;
            retVal.mnemonic = ss.str();
            retVal.size = 2;
            break;
        }
    }

    return retVal;

}



#ifdef Z80TESTS
template class Z80Opcodes<MockZ80Memory>;
#else
template class Z80Opcodes<Z80Memory> ;
#endif