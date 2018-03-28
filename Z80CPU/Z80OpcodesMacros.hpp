/* 
 * File:   Z80OpcodesMacros.hpp
 * Author: lapajmar
 *
 * Created on 31 marzec 2014, 13:12
 */

#ifndef Z80OPCODESMACROS_HPP
#define	Z80OPCODESMACROS_HPP

#define SET_BIT(p,n) ((p) |= (1 << (n)))
#define CLR_BIT(p,n) ((p) &= ~(1 << (n)))
#define TEST_BIT(Var, Pos)  (((Var) & (1 << (Pos))) > 0)

#define LD(X,Y) (X) = (Y)
#define ROTL8(X,SHIFT) (X) = ((X) << (SHIFT)) | ((X) >> (8 - (SHIFT)))
#define ROTR8(X,SHIFT) (X) = ((X) >> (SHIFT)) | ((X) << (8 - (SHIFT)))
#define CHECK_BIT(X,POS) ((X & (1 << POS)) == (1 << POS))
#define CHECK_NEGATIVE8(X) (CHECK_BIT((X),7)==1)
#define CHECK_NEGATIVE16(X) (CHECK_BIT((X),15)==1)


#define OVERFLOW8(A,B) (((INT8)(A)> 0 && *(INT8*)(B) > 0 && (INT8)(A) > 127 - *(INT8*)(B)) ||\
                       ((INT8)(A) < 0 && *(INT8*)(B) < 0 && (INT8)(A) < -128 - *(INT8*)(B)))

#define OVERFLOW16(A,B) (((INT16)(A) > 0 && *(INT16*)(B) > 0 && (INT16)(A) > 32767  - *(INT16*)(B)) ||\
                        ((INT16) (A) < 0 && *(INT16*)(B) < 0 && (INT16)(A) < -32768 - *(INT16*)(B)))

//#define CARRY16(A,B,C) 1 & ((((A) & (B) & ~(C)) | (~(A) & ~(B) & (C))) >> 15)

//  (~x7 & y7) | (y7 & r7) | (~y7 & x7); 
#define BORROW8(A,B,C)   (1 & ((((~A) ^ (B))| ((B) & (C))|(~B & A)) >> 7))
#define BORROW16(A,B,C)  (1 & ((((~A) ^ (B))| ((B) & (C))|(~B & A)) >> 15))

#define HALF_CARRY8(REG,VAL)  ((((REG) & 0xF  ) + ((VAL) & 0xF  )) > 0xF  )
#define HALF_CARRY16(REG,VAL) ((((REG) & 0xFFF) + ((VAL) & 0xFFF)) > 0xFFF)

#define HALF_BORROW8(REG,VAL) (((((INT8)REG)   & 0xF  ) - ((VAL) & 0xF  )) < 0x0)
#define HALF_BORROW16(REG,VAL) (((((INT16)REG) & 0xFFF) - ((VAL) & 0xFFF)) < 0x0)


#define SWAP8(X,Y) {UINT8 T;T=X;X=X;Y=T;}
#define SWAP16(X,Y) {UINT16 T;T=X;X=Y;Y=T;}


#define INCrr(X) (X)+=1; reg.PC+=1
#define DECrr(X) (X)-=1; reg.PC+=1


#define INCr(X) if (reg.R == 0x7F) { SET_FLAG_PV();}\
    else { CLR_FLAG_PV();}\
    HALF_CARRY8((X),1) ? SET_FLAG_H() : CLR_FLAG_H();\
    (X)+=1;\
    if (CHECK_NEGATIVE8((X))) { SET_FLAG_S(); }  else { CLR_FLAG_S(); } \
    if ((X) == 0){ SET_FLAG_Z();} else {CLR_FLAG_Z();} \
    CLR_FLAG_N();\
    reg.PC+=1


#define DECr(X)     if (reg.R == 0x80) { SET_FLAG_PV();}\
    else {CLR_FLAG_PV();}\
    HALF_BORROW8((X),1) ? SET_FLAG_H() : CLR_FLAG_H();\
    (X)-=1;\
    if (CHECK_NEGATIVE8((X))) { SET_FLAG_S(); } else { CLR_FLAG_S(); }\
    if ((X) == 0){ SET_FLAG_Z();} else { CLR_FLAG_Z(); }\
    SET_FLAG_N();\
    reg.PC+=1


#endif	/* Z80OPCODESMACROS_HPP */

