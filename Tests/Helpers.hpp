/*
 * Helpers.hpp
 *
 *  Created on: 13 kwi 2014
 *      Author: cod3r
 */

#ifndef HELPERS_HPP_
#define HELPERS_HPP_

#include "Z80Registers.hpp"


void checkRegisters(Z80Registers regs,Z80Registers regs2);
void checkRegistersHaveDefaultValues(Z80Registers &regs);
void set_flag_c(Z80Registers &regs);
void set_flag_n(Z80Registers &regs);
void set_flag_pv(Z80Registers &regs);
void set_flag_p3(Z80Registers &regs);
void set_flag_h(Z80Registers &regs);
void set_flag_f5(Z80Registers &regs);
void set_flag_z(Z80Registers &regs);
void set_flag_s(Z80Registers &regs);

void clear_flag_c(Z80Registers &regs);
void clear_flag_n(Z80Registers &regs);
void clear_flag_pv(Z80Registers &regs);
void clear_flag_p3(Z80Registers &regs);
void clear_flag_h(Z80Registers &regs);
void clear_flag_f5(Z80Registers &regs);
void clear_flag_z(Z80Registers &regs);
void clear_flag_s(Z80Registers &regs);
void printFlags(UINT8 F);
#endif /* HELPERS_HPP_ */
