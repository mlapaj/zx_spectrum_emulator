find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories("${CMAKE_SOURCE_DIR}/Z80CPU")

find_package(GMock REQUIRED)
include_directories(${GMOCK_INCLUDE_DIRS})

message(${GMOCK_INCLUDE_DIRS})

find_package(PkgConfig)
pkg_check_modules(LOG4CXX REQUIRED liblog4cxx)
include_directories(${LOG4CXX_INCLUDE_DIRS})
link_directories(${LOG4CXX_LIBRARY_DIRS})


add_executable(ZX_Spectrum_Emulator_Tests Main.cpp Helpers.cpp Z80MemoryTests.cpp Z80CPUOpcodesStackTests.cpp Z80CPUOpcodesCallRetTests.cpp Z80CPUOpcodesALUTests.cpp Z80CPUModuleTests.cpp Z80CPUOpcodesLoadTests.cpp Z80CPUOpcodesJumpTests.cpp Z80CPUShitRotateTests.cpp Z80CPUBlockOpcodesTests.cpp ../Z80CPU/Z80CPUModule.cpp ../Z80CPU/Z80Memory.cpp ../Z80CPU/Z80Opcodes.cpp ../Z80CPU/Z80OpcodesNormal.cpp ../Z80CPU/Z80OpcodesCB.cpp ../Z80CPU/Z80OpcodesED.cpp ../Z80CPU/Z80Registers.cpp ../Z80CPU/Z80OpcodesPrint.cpp) 
SET_TARGET_PROPERTIES(ZX_Spectrum_Emulator_Tests PROPERTIES COMPILE_DEFINITIONS "Z80TESTS")
target_link_libraries(ZX_Spectrum_Emulator_Tests  ${LOG4CXX_LIBRARIES} ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} pthread  )
