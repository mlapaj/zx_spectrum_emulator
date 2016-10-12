/*
 * Helpers.cpp
 *
 *  Created on: 13 kwi 2014
 *      Author: cod3r
 */
#include "Helpers.hpp"
#include <gtest/gtest.h>

void checkRegisters(Z80Registers regs,Z80Registers regs2)
{
     EXPECT_EQ(regs.AF,regs2.AF);
     EXPECT_EQ(regs.DE,regs2.DE);
     EXPECT_EQ(regs.BC,regs2.BC);
     EXPECT_EQ(regs.HL,regs2.HL);

     EXPECT_EQ(regs.secAF,regs2.secAF);
     EXPECT_EQ(regs.secDE,regs2.secDE);
     EXPECT_EQ(regs.secBC,regs2.secBC);
     EXPECT_EQ(regs.secHL,regs2.secHL);

     EXPECT_EQ(regs.SP,regs2.SP);
     EXPECT_EQ(regs.PC,regs2.PC);
     EXPECT_EQ(regs.IX,regs2.IX);
     EXPECT_EQ(regs.IY,regs2.IY);

     EXPECT_EQ(regs.R,regs2.R);
     EXPECT_EQ(regs.I,regs2.I);
}


void checkRegistersHaveDefaultValues(Z80Registers &regs)
{
     EXPECT_EQ(regs.AF,0);
     EXPECT_EQ(regs.DE,0);
     EXPECT_EQ(regs.BC,0);
     EXPECT_EQ(regs.HL,0);

     EXPECT_EQ(regs.secAF,0);
     EXPECT_EQ(regs.secDE,0);
     EXPECT_EQ(regs.secBC,0);
     EXPECT_EQ(regs.secHL,0);

     EXPECT_EQ(regs.SP,0);
     EXPECT_EQ(regs.PC,0);
     EXPECT_EQ(regs.IX,0);
     EXPECT_EQ(regs.IY,0);

     EXPECT_EQ(regs.R,0);
     EXPECT_EQ(regs.I,0);
}

void set_flag_c(Z80Registers &regs)
{
    SET_BIT(regs.F,0);
}

void set_flag_n(Z80Registers &regs)
{
    SET_BIT(regs.F,1);
}

void set_flag_pv(Z80Registers &regs)
{
    SET_BIT(regs.F,2);
}

void set_flag_p3(Z80Registers &regs)
{
    SET_BIT(regs.F,3);
}

void set_flag_h(Z80Registers &regs)
{
    SET_BIT(regs.F,4);
}

void set_flag_f5(Z80Registers &regs)
{
    SET_BIT(regs.F,5);
}

void set_flag_z(Z80Registers &regs)
{
    SET_BIT(regs.F,6);
}

void set_flag_s(Z80Registers &regs)
{
    SET_BIT(regs.F,7);
}
