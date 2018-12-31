int Z80CyclesForMainInstructions[256] = 
{
// 00
	4,	// NOP
	10,	// LD BC,nn
	7,	// LD (BC)ma
	6,	// INC bc
	4,	// INC b
	4,	// DEC b
	7,	// LD b,n
	4,	// RLCA
	4,	// EX AF,AF'
	11,	// ADD HL,BC
	7,	// LD A,(BC)
	6,	// DEC BC
	4,	// INC C
	4,	// DEC C
	7,	// LD C,n
	4,  // RRCA
// 0F
	8,	// DJNZ 13/8
	10,	// LD DE,nn
	7,	// LD (DE),a
	6,	// INC DE
	4,	// INC D
	4,	// DEC D
	7,	// LD D,n
	4,	// RLA
	12,	// JR
	11,	// ADD HL,DE
	7,	// LD A,(DE)
	6,	// DEC DE
	4,	// INC E
	4,	// DEC E
	7,	// LD E,*
	4,	// RRA
// 1F
	7,	// JR nz,* 12/7
	10,	// LD HL,nn
	16,	// LD (nn), HL
	6,	// INC HL
	4,	// INC H
	4,	// DEC H
	7,	// LD HL,nn
	4,	// DAA
	7,	// JR Z,nn 12/7
	11,	// ADD HL,HL
	16,	// LD HL,(nn)
	6,	// DEC HL
	4,	// INC L
	4,	// DEC L
	7,	// LD L,*
	4,  // CPI
// 2F
	7,	// JR nc,nn 12,7
	10, // LD SP,nn
	13,	// LD (nn),A
	6,	// INC SP
	11,	// INC (HL)
	11, // DEC (HL)
	10,	// LD (HL),nn
	4,	// SCF
	7,  // JR C,* 12/7
	11,	// ADD HL,SP
	13,	// LD A,(nn)
	6,	// DEC SP
	4,	// INC A
	4,	// DEC A
	7,	// LD A,n
	4,	// CCF
// 3F
	4,	// LD B,B
	4,	// LD B,C
	4,	// LD B,D
	4,	// LD B,E
	4,	// LD B,H
	4,	// LD B,L
	7,	// LD B,(HL)
	4,	// LD B,A
	4,	// LD C,B
	4,	// LD C,C
	4,	// LD C,D
	4,	// LD C,E
	4,	// LD C,H
	4,	// LD C,L
	7,	// LD C,(HL)
	4,	// LD C,A
// 4F
	4,	// LD D,B
	4,	// LD D,C
	4,	// LD D,D
	4,	// LD D,E
	4,	// LD D,H
	4,	// LD D,L
	7,	// LD D,(HL)
	4,	// LD D,A
	4,	// LD E,B
	4,	// LD E,C
	4,	// LD E,D
	4,	// LD E,E
	4,	// LD E,H
	4,	// LD E,L
	7,	// LD E,(HL)
	4,	// LD E,A
// 5F
	4,	// LD H,B
	4,	// LD H,C
	4,	// LD H,D
	4,	// LD H,E
	4,	// LD H,H
	4,	// LD H,L
	7,	// LD H,(HL)
	4,	// LD H,A
	4,	// LD H,B
	4,	// LD H,C
	4,	// LD H,D
	4,	// LD H,E
	4,	// LD L,H
	4,	// LD L,L
	7,	// LD L,(HL)
	4,	// LD L,A
// 6F
	7,	// LD (HL),B
	7,	// LD (HL),C
	7,	// LD (HL),D
	7,	// LD (HL),E
	7,	// LD (HL),H
	7,	// LD (HL),L
	4,	// HALT
	7,	// LD (HL),A
	4,	// LD A,B
	4,	// LD A,C
	4,	// LD A,D
	4,	// LD A,E
	4,	// LD A,H
	4,	// LD A,L
	7,	// LD A,(HL)
	4,	// LD A,A
//	7F
	4,	// ADD A,B
	4,	// ADD A,C
	4,	// ADD A,D
	4,	// ADD A,E
	4,	// ADD A,H
	4,	// ADD A,L
	7,	// ADD A,(HL)
	4,	// ADD A,A
	4,	// ADC A,B
	4,	// ADC A,B
	4,	// ADC A,D
	4,	// ADC A,E
	4,	// ADC A,H
	4,	// ADC A,L
	7,	// ADC A,(HL)
	4,	// ADC A,A
//	8F
	4,	// SUB B
	4,	// SUB C
	4,	// SUB D
	4,	// SUB E
	4,	// SUB H
	4,	// SUB L
	7,	// SUB (HL)
	4,	// SUB A
	4,	// SBC A,B
	4,	// SBC A,C
	4,	// SBC A,D
	4,	// SBC A,E
	4,	// SBC A,H
	4,	// SBC A,L
	7,	// SBC A,(HL)
	4,	// SBC A,A
//	9F
	4,	// AND B
	4,	// AND C
	4,	// AND D
	4,	// AND E
	4,	// AND H
	4,	// AND L
	7,	// AND (HL)
	4,	// AND A
	4,	// XOR B
	4,	// XOR C
	4,	// XOR D
	4,	// XOR E
	4,	// XOR H
	4,	// XOR L
	7,	// XOR (HL)
	4,	// XOR A
// AF
	4,	// OR B
	4,	// OR C
	4,	// OR D
	4,	// OR E
	4,	// OR H
	4,	// OR L
	7,	// OR (HL)
	4,	// OR A
	4,	// CP B
	4,	// CP C
	4,	// CP D
	4,	// CP E
	4,	// CP H
	4,	// CP L
	7,	// CP (HL)
	4,	// CP A
// BF
	5,	// RET Z 11,5
	10,	// POP BC
	10,	// JP nz,**
	10,	// JP nn
	10,	// CALL nz,nn 17/10
	11,	// PUSH BC
	7,	// ADD A,n
	11,	// RST 00h
	5,	// RET z 11/5
	10,	// RET
	10,	// JP Z,nn
	0,	// BITS CD prefix!!!!!!!!!!!!!
	10,	// CALL z,nn 17/10
	17,	// CALL nn
	7,	// ADC A,n
	11,	// RST 08H
// CF
	5,	// RET 11/5
	10,	// POP DE
	10,	// JP nc,nn
	11,	// OUT (nn),a
	10,	// CALL nc,nn 17/10
	11,	// PUSH DE
	7,	// SUB n
	11,	// RST 10H
	5,	// RET C 11/5
	4,	// EXX
	10,	// JP C,*
	11,	// IN A,(n)
	10,	// CALL C,nn 17/10
	0,  // IX prefix !!!!!!!!!!!!!!!!!!!!!!
	7,	// SBC A,n
	11,	// RST 18h
// DF
	5,	// RET po 11/5
	10,	// POP HL
	10,	// JP PO,nn
	19,	// EX (SP),HL
	10,	// CALL PO,** 17/10
	11,	// PUSH HL
	7,	// AND n
	11, // RST 20H
	5,	// RET PE
	4,	// JP (HL)
	10,	// JP PE,nn
	4,	// EX DE,HL
	10,	// CALL PE,nn 17/10
	0,	// EXTD !!!!!!!!!!!!!!!!!!!!!!
	7,	// XOR n
	11,	// RST 28h
// EF
	5,	// RET p 11/5
	10,	// POP af
	10, // JP P,nn
	4,	// DI
	10,	// CALL P,nn 17/10
	11,	// PUSH AF
	7,	// XOR N
	11,	// RST 30H
	5,	// RET m 11/5
	6,	// LD SP,HL
	10,	// JP M,NN
	4,	// EI
	10,	// CALL M,**  17/10
	0,	// IY !!!!!!!!!!!!!!!!!!!!!!
	7,	// CP *
	11,	// RST 38h
};

int Z80CyclesForExtendedInstructions[256] =
{
// 00
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
// 0F
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
// 1F
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
// 2F
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
// 3F
	12,	// IN B,(C)
	12,	// OUT (C),B
	15,	// SBC HL,BC
	20,	// LD (nn),BC
	8,	// NEG
	14,	// RETN
	8,	// IM 0
	9,	// LD I,A
	12,	// IN C,(C)
	12,	// OUT (C),C
	15,	// ADC HL,BC
	20,	// LD BC,(NN)
	8,	// NEG
	14,	// RETI
	8,	// IM 0/1
	9,	// LD R,A
// 4F
	12,	// IN D,(C)
	12, // OUT (C),D
	15,	// SBC HL,DE
	20,	// LD (nn),DE
	8,	// NEG
	14,	// RETN
	8,	// IM 1
	9,	// LD A,I
	12,	// IN E,(C)
	12,	// OUT (C),E
	15, // ADD HL,DE
	20,	// LD DE,(nn)
	8,	// NEG
	14,	// RETN
	8,	// IM 2
	9,	// LD A,R
// 5F
	12,	// IN H,(C)
	12,	// OUT C,(H)
	15,	// SBC HL,HL
	20,	// LD (nn),HL
	8,	// NEG
	14,	// RETN
	8,	// IM 0
	18,	// RRD
	12,	// IN L,(C)
	12,	// OUT (C),L
	15,	// ADC HL,HL
	20,	// LD HL,(nn)
	8,	// NEG
	14,	// RETN
	8,	// IM 0/1
	18,	// RLD
// 6F
	12,	// IN (c)
	12,	// OUT (C),0
	15,	// SBC HL,SP
	20,	// LD (nn),SP
	8,	// NEG
	14,	// RETN
	8,	// IM 1
	0,
	12,	// IN A,(c)
	12, // OUT (C),A
	15, // ADC HL,SP
	20,	// LD SP,(nn)
	8,	// NEG
	14,	// RETN
	8,	// IM2
	0,
// 7F
	16,	// LDI
	16,	// CPI
	16,	// INI
	16,	// OUTI
	0,
	0,
	0,
	0,
	16,	// LDD
	16, // CPD
	16,	// IND
	16,	// OUTD
	0,
	0,
	0,
	0,
// 8F
	0,	// LDIR 21/16
	0,	// CPIR 21/16
	0,	// INIR 21/16
	0,	// OUTIR 21/16
	0,
	0,
	0,
	0,
	0,	// LDDR 21/16
	0,	// CPDR	21/16
	0,	// INDR 21/16
	0,	// OUTDR 21/16
	0,
	0,
	0,
	0,
// 9F
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
// AF
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
// BF


};

int Z80CyclesForBitInstructions[16] =
{
// 00
	8,
	8,
	8,
	8,
	8,
	8,
	15,
	8,
	8,
	8,
	8,
	8,
	8,
	8,
	15,
	8,
// 0F
};

int Z80CyclesForIXIYInstructions[256] =
{
// 00
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	15, // ADD IX,BC
	0,
	0,
	0,
	0,
	0,
	0,
// 0F
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	15, //ADD IX,DE
	0,
	0,
	0,
	0,
	0,
	0,
// 1F
	0,
	14,	// LD IX,nn
	20,	// LD (nn), ix
	10,	// INC IX
	8,	// INC ixh
	8,	// DEC ixh
	11,	// LD IXH,n
	0,
	0,
	15,	// ADD IX,IX
	20,	// LD IX,(nn)
	10,	// DEC IX
	8,	// INC IXL
	8,	// DEC IXL
	11,	// LD IXL,n
	0,
// 2F
	0,
	0,
	0,
	0,
	23, // INC (IX+N)
	23,	// DEC (IX+N)
	19,	// LD (IX+N),n
	0,
	0,
	15, // ADD IX,SP
	0,
	0,
	0,
	0,
	0,
	0,
// 3F
	0,
	0,
	0,
	0,
	8,	// LD B,IXH
	8,	// LD B,IXL
	19,	// LD B,(IX+n)
	0,
	0,
	0,
	0,
	0,
	8,	// LD C,IXH
	8,	// LD C,IXL
	19,	// LD C,(IX+n)
	0,
// 4F
	0,
	0,
	0,
	0,
	8,	// LD D,IXH
	8,	// LD D,IXL
	19,	// LD D,(IX+n)
	0,
	0,
	0,
	0,
	0,
	8,	// LD E,IXH
	8,	// LD E,IXL
	19,	// LD E,(IX+n)
	0,
// 5F
	8,	// LD IXH,B
	8,	// LD IXH,C
	8,	// LD IXH,D
	8,	// LD IXH,E
	8,	// LD IXH,H
	8,	// LD IXH,L
	19,	// LD H,(IX+n)
	8,	// LD IXH,A
	8,	// LD IXL,B
	8,	// LD IXL,C
	8,	// LD IXL,D
	8,	// LD IXL,E
	8,	// LD IXL,H
	8,	// LD IXL,L
	19,	// LD L,(IX+n)
	8,	// LD IXL,A
// 6F
	19,	// LD (IX+n),b
	19,	// LD (IX+n),c
	19,	// LD (IX+n),d
	19,	// LD (IX+n),e
	19,	// LD (IX+n),h
	19,	// LD (IX+n),h
	0,
	19,	// LD (IX+n),a
	0,
	0,
	0,
	0,
	8,	// LD A,IXH
	8,	// LD A,IXL
	19,	// LD A,(IX+N)
	0,
// 7F
	0,
	0,
	0,
	0,
	8,	// ADD A,IXH
	8,	// ADD A,IXL
	19,	// ADD A,(IX+n)
	0,
	0,
	0,
	0,
	0,
	8,	// ADC A,IXH
	8,	// ADC A,IXL
	19,	// ADC A,(IX+n)
	0,
// 8F
	0,
	0,
	0,
	0,
	8,	// SUB A,IXH
	8,	// SUB A,IXL
	19,	// SUB A,(IX+n)
	0,
	0,
	0,
	0,
	0,
	8,	// SBC A,IXH
	8,	// SBC A,IXL
	19,	// SBC A,(IX+n)
	0,
// 9F
	0,
	0,
	0,
	0,
	8,	// AND A,IXH
	8,	// AND A,IXL
	19,	// AND A,(IX+n)
	0,
	0,
	0,
	0,
	0,
	8,	// XOR A,IXH
	8,	// XOR A,IXL
	19,	// XOR A,(IX+n)
	0,
// AF
	0,
	0,
	0,
	0,
	8,	// OR A,IXH
	8,	// OR A,IXL
	19,	// OR A,(IX+n)
	0,
	0,
	0,
	0,
	0,
	8,	// CP A,IXH
	8,	// CP A,IXL
	19,	// CP A,(IX+n)
	0,
// BF
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
// CF
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
// DF
	0,
	14,	// POP IX
	0,
	23,	// EX (SP),IX
	0,
	15,	// PUSH IX
	0,
	0,
	0,
	8,	// JP (IX)
	0,
	0,
	0,
	0,
	0,
	0,
// EF
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	10,	 // LD SP,IX
	0,
	0,
	0,
	0,
	0,
	0,
// FF

};

int Z80CyclesForIXIYBitInstructions[256] =
{
// 00
	23,	// RLC (IX+*),b
	23,	// RLC (IX+*),c
	23,	// RLC (IX+*),d
	23,	// RLC (IX+*),e
	23,	// RLC (IX+*),h
	23,	// RLC (IX+*),l
	23,	// RLC (IX+*)
	23,	// RLC (IX+*),a
	23,	// RRC (IX+*),b
	23,	// RRC (IX+*),c
	23,	// RRC (IX+*),d
	23,	// RRC (IX+*),e
	23,	// RRC (IX+*),h
	23,	// RRC (IX+*),l
	23,	// RRC (IX+*),
	23,	// RRC (IX+*),a
// 0F
	23,	// RL (IX+*),b
	23,	// RL (IX+*),c
	23,	// RL (IX+*),d
	23,	// RL (IX+*),e
	23,	// RL (IX+*),h
	23,	// RL (IX+*),l
	23,	// RL (IX+*)
	23,	// RL (IX+*),a
	23,	// RR (IX+*),b
	23,	// RR (IX+*),c
	23,	// RR (IX+*),d
	23,	// RR (IX+*),e
	23,	// RR (IX+*),h
	23,	// RR (IX+*),l
	23,	// RR (IX+*),
	23,	// RR (IX+*),a
// 1F
	23,	// SLA (IX+*),b
	23,	// SLA (IX+*),c
	23,	// SLA (IX+*),d
	23,	// SLA (IX+*),e
	23,	// SLA (IX+*),h
	23,	// SLA (IX+*),l
	23,	// SLA (IX+*)
	23,	// SLA (IX+*),a
	23,	// SRA (IX+*),b
	23,	// SRA (IX+*),c
	23,	// SRA (IX+*),d
	23,	// SRA (IX+*),e
	23,	// SRA (IX+*),h
	23,	// SRA (IX+*),l
	23,	// SRA (IX+*),
	23,	// SRA (IX+*),a
// 2F
	23,	// SLL (IX+*),b
	23,	// SLL (IX+*),c
	23,	// SLL (IX+*),d
	23,	// SLL (IX+*),e
	23,	// SLL (IX+*),h
	23,	// SLL (IX+*),l
	23,	// SLL (IX+*)
	23,	// SLL (IX+*),a
	23,	// SRL (IX+*),b
	23,	// SRL (IX+*),c
	23,	// SRL (IX+*),d
	23,	// SRL (IX+*),e
	23,	// SRL (IX+*),h
	23,	// SRL (IX+*),l
	23,	// SRL (IX+*),
	23,	// SRL (IX+*),a
// 3F
	20,	// BIT 0,(IX+*)
	20,	// BIT 0,(IX+*)
	20,	// BIT 0,(IX+*)
	20,	// BIT 0,(IX+*)
	20,	// BIT 0,(IX+*)
	20,	// BIT 0,(IX+*)
	20,	// BIT 0,(IX+*)
	20,	// BIT 0,(IX+*)
	20,	// BIT 1,(IX+*)
	20,	// BIT 1,(IX+*)
	20,	// BIT 1,(IX+*)
	20,	// BIT 1,(IX+*)
	20,	// BIT 1,(IX+*)
	20,	// BIT 1,(IX+*)
	20,	// BIT 1,(IX+*)
	20,	// BIT 1,(IX+*)
// 4F
	20,	// BIT 2,(IX+*)
	20,	// BIT 2,(IX+*)
	20,	// BIT 2,(IX+*)
	20,	// BIT 2,(IX+*)
	20,	// BIT 2,(IX+*)
	20,	// BIT 2,(IX+*)
	20,	// BIT 2,(IX+*)
	20,	// BIT 2,(IX+*)
	20,	// BIT 3,(IX+*)
	20,	// BIT 3,(IX+*)
	20,	// BIT 3,(IX+*)
	20,	// BIT 3,(IX+*)
	20,	// BIT 3,(IX+*)
	20,	// BIT 3,(IX+*)
	20,	// BIT 3,(IX+*)
	20,	// BIT 3,(IX+*)
// 5F
	20,	// BIT 4,(IX+*)
	20,	// BIT 4,(IX+*)
	20,	// BIT 4,(IX+*)
	20,	// BIT 4,(IX+*)
	20,	// BIT 4,(IX+*)
	20,	// BIT 4,(IX+*)
	20,	// BIT 4,(IX+*)
	20,	// BIT 4,(IX+*)
	20,	// BIT 5,(IX+*)
	20,	// BIT 5,(IX+*)
	20,	// BIT 5,(IX+*)
	20,	// BIT 5,(IX+*)
	20,	// BIT 5,(IX+*)
	20,	// BIT 5,(IX+*)
	20,	// BIT 5,(IX+*)
	20,	// BIT 5,(IX+*)
// 6F
	20,	// BIT 6,(IX+*)
	20,	// BIT 6,(IX+*)
	20,	// BIT 6,(IX+*)
	20,	// BIT 6,(IX+*)
	20,	// BIT 6,(IX+*)
	20,	// BIT 6,(IX+*)
	20,	// BIT 6,(IX+*)
	20,	// BIT 6,(IX+*)
	20,	// BIT 7,(IX+*)
	20,	// BIT 7,(IX+*)
	20,	// BIT 7,(IX+*)
	20,	// BIT 7,(IX+*)
	20,	// BIT 7,(IX+*)
	20,	// BIT 7,(IX+*)
	20,	// BIT 7,(IX+*)
	20,	// BIT 7,(IX+*)
// 7F
	23,	// RES 0,(IX+*)
	23,	// RES 0,(IX+*)
	23,	// RES 0,(IX+*)
	23,	// RES 0,(IX+*)
	23,	// RES 0,(IX+*)
	23,	// RES 0,(IX+*)
	23,	// RES 0,(IX+*)
	23,	// RES 0,(IX+*)
	23,	// RES 1,(IX+*)
	23,	// RES 1,(IX+*)
	23,	// RES 1,(IX+*)
	23,	// RES 1,(IX+*)
	23,	// RES 1,(IX+*)
	23,	// RES 1,(IX+*)
	23,	// RES 1,(IX+*)
	23,	// RES 1,(IX+*)
// 8F
	23,	// RES 2,(IX+*)
	23,	// RES 2,(IX+*)
	23,	// RES 2,(IX+*)
	23,	// RES 2,(IX+*)
	23,	// RES 2,(IX+*)
	23,	// RES 2,(IX+*)
	23,	// RES 2,(IX+*)
	23,	// RES 2,(IX+*)
	23,	// RES 3,(IX+*)
	23,	// RES 3,(IX+*)
	23,	// RES 3,(IX+*)
	23,	// RES 3,(IX+*)
	23,	// RES 3,(IX+*)
	23,	// RES 3,(IX+*)
	23,	// RES 3,(IX+*)
	23,	// RES 3,(IX+*)
// 9F
	23,	// RES 4,(IX+*)
	23,	// RES 4,(IX+*)
	23,	// RES 4,(IX+*)
	23,	// RES 4,(IX+*)
	23,	// RES 4,(IX+*)
	23,	// RES 4,(IX+*)
	23,	// RES 4,(IX+*)
	23,	// RES 4,(IX+*)
	23,	// RES 5,(IX+*)
	23,	// RES 5,(IX+*)
	23,	// RES 5,(IX+*)
	23,	// RES 5,(IX+*)
	23,	// RES 5,(IX+*)
	23,	// RES 5,(IX+*)
	23,	// RES 5,(IX+*)
	23,	// RES 5,(IX+*)
// AF
	23,	// RES 6,(IX+*)
	23,	// RES 6,(IX+*)
	23,	// RES 6,(IX+*)
	23,	// RES 6,(IX+*)
	23,	// RES 6,(IX+*)
	23,	// RES 6,(IX+*)
	23,	// RES 6,(IX+*)
	23,	// RES 6,(IX+*)
	23,	// RES 7,(IX+*)
	23,	// RES 7,(IX+*)
	23,	// RES 7,(IX+*)
	23,	// RES 7,(IX+*)
	23,	// RES 7,(IX+*)
	23,	// RES 7,(IX+*)
	23,	// RES 7,(IX+*)
	23,	// RES 7,(IX+*)
// BF
	23,	// SET 0,(IX+*)
	23,	// SET 0,(IX+*)
	23,	// SET 0,(IX+*)
	23,	// SET 0,(IX+*)
	23,	// SET 0,(IX+*)
	23,	// SET 0,(IX+*)
	23,	// SET 0,(IX+*)
	23,	// SET 0,(IX+*)
	23,	// SET 1,(IX+*)
	23,	// SET 1,(IX+*)
	23,	// SET 1,(IX+*)
	23,	// SET 1,(IX+*)
	23,	// SET 1,(IX+*)
	23,	// SET 1,(IX+*)
	23,	// SET 1,(IX+*)
	23,	// SET 1,(IX+*)
// CF
	23,	// SET 2,(IX+*)
	23,	// SET 2,(IX+*)
	23,	// SET 2,(IX+*)
	23,	// SET 2,(IX+*)
	23,	// SET 2,(IX+*)
	23,	// SET 2,(IX+*)
	23,	// SET 2,(IX+*)
	23,	// SET 2,(IX+*)
	23,	// SET 3,(IX+*)
	23,	// SET 3,(IX+*)
	23,	// SET 3,(IX+*)
	23,	// SET 3,(IX+*)
	23,	// SET 3,(IX+*)
	23,	// SET 3,(IX+*)
	23,	// SET 3,(IX+*)
	23,	// SET 3,(IX+*)
// DF
	23,	// SET 4,(IX+*)
	23,	// SET 4,(IX+*)
	23,	// SET 4,(IX+*)
	23,	// SET 4,(IX+*)
	23,	// SET 4,(IX+*)
	23,	// SET 4,(IX+*)
	23,	// SET 4,(IX+*)
	23,	// SET 4,(IX+*)
	23,	// SET 5,(IX+*)
	23,	// SET 5,(IX+*)
	23,	// SET 5,(IX+*)
	23,	// SET 5,(IX+*)
	23,	// SET 5,(IX+*)
	23,	// SET 5,(IX+*)
	23,	// SET 5,(IX+*)
	23,	// SET 5,(IX+*)
// EF
	23,	// SET 6,(IX+*)
	23,	// SET 6,(IX+*)
	23,	// SET 6,(IX+*)
	23,	// SET 6,(IX+*)
	23,	// SET 6,(IX+*)
	23,	// SET 6,(IX+*)
	23,	// SET 6,(IX+*)
	23,	// SET 6,(IX+*)
	23,	// SET 7,(IX+*)
	23,	// SET 7,(IX+*)
	23,	// SET 7,(IX+*)
	23,	// SET 7,(IX+*)
	23,	// SET 7,(IX+*)
	23,	// SET 7,(IX+*)
	23,	// SET 7,(IX+*)
	23,	// SET 7,(IX+*)
// FF
};
