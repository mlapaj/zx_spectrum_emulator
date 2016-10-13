/*
 * File:   Main.c
 * Author: lapajmar
 *
 * Created on 18 marzec 2014, 11:20
 */

#include <gtest/gtest.h>
#include <stdexcept>
#include "Z80Memory.hpp"

TEST(Z80CPU, OK_CASE) {
    Z80Memory oZ80Memory(65535);
    EXPECT_EQ(oZ80Memory.LoadRom("48.rom"),0);
}

TEST(Z80CPU, INVALID_FILE) {
    Z80Memory oZ80Memory(128);
    EXPECT_NE(oZ80Memory.LoadRom("bleble"),0);
}

TEST(Z80CPU, TOO_SMALL_MEMORY) {
    Z80Memory oZ80Memory(128);
    EXPECT_EQ(oZ80Memory.LoadRom("48.rom"),-2);
}

TEST(Z80CPU, CLEAR_MEMORY) {
    int size = 128;
    Z80Memory oZ80Memory(size);
    oZ80Memory.clearMemory();
    for (int x=0;x<size;x++)
    {
        EXPECT_EQ(oZ80Memory.get8(x),0x00);
        EXPECT_NO_THROW(oZ80Memory.getAddrPtr8(x));
    }

    for (int x=0;x<size/2;x++)
    {
        EXPECT_EQ(oZ80Memory.get16(x),0x00);
    }

}

TEST(Z80CPU, GET_MEMORY_OUT_OF_RANGE) {
    int size = 128;
    Z80Memory oZ80Memory(size);
    EXPECT_NO_THROW(oZ80Memory.get8(size-1));
    EXPECT_NO_THROW(oZ80Memory.get8(0));
    EXPECT_NO_THROW(oZ80Memory.get16(size-2));
    EXPECT_NO_THROW(oZ80Memory.get16(0));
    EXPECT_NO_THROW(oZ80Memory.getAddrPtr8(size-1));
    EXPECT_NO_THROW(oZ80Memory.getAddrPtr8(0));


    EXPECT_ANY_THROW(oZ80Memory.get8(size));
    EXPECT_ANY_THROW(oZ80Memory.get8(-1));
    EXPECT_ANY_THROW(oZ80Memory.get16(size-1));
    EXPECT_ANY_THROW(oZ80Memory.get16(-1));
    EXPECT_ANY_THROW(oZ80Memory.getAddrPtr8(size));
    EXPECT_ANY_THROW(oZ80Memory.getAddrPtr8(-1));

}
