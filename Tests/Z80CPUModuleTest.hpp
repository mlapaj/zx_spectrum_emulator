/* 
 * File:   Z80CPuModuleTest.hpp
 * Author: lapajmar
 *
 * Created on 27 marzec 2014, 08:47
 */

#ifndef Z80CPUMODULETEST_HPP
#define	Z80CPUMODULETEST_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Z80CPU/Z80Types.hpp"
#include <string>

using namespace std;
using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;


class MockZ80Memory{
 public:  
  MOCK_METHOD1(get8, UINT8(UINT16));
  MOCK_METHOD1(get16, UINT16(UINT16));
  MOCK_METHOD1(getAddrPtr16, UINT16*(UINT16));
  MOCK_METHOD1(getAddrPtr8, UINT8*(UINT16));
  MOCK_METHOD1(LoadRom, int(string));
  MOCK_METHOD0(clearMemory, void());
};

#endif	/* Z80CPUMODULETEST_HPP */

