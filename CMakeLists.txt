cmake_minimum_required (VERSION 2.6)

project (ZX_Spectrum_Emulator)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

find_package(PkgConfig)
pkg_check_modules(LOG4CXX REQUIRED liblog4cxx)
include_directories(${LOG4CXX_INCLUDE_DIRS})
link_directories(${LOG4CXX_LIBRARY_DIRS})

INCLUDE(CPack)
INCLUDE(TestBigEndian)

TEST_BIG_ENDIAN(BIGENDIAN)

# The version number.
set (Emulator_VERSION_MAJOR 1)
set (Emulator_VERSION_MINOR 0)
set (BigEndian ${BIGENDIAN})


configure_file (
  "${PROJECT_SOURCE_DIR}/BuildDefs.h.in"
  "${PROJECT_BINARY_DIR}/BuildDefs.h"
  )

include_directories("${PROJECT_BINARY_DIR}")
add_subdirectory(Z80CPU)
add_executable(ZX_Spectrum_Emulator Main.cpp Z80CPU/Z80CPUModule.cpp Z80CPU/Z80OpcodesPrint.cpp Z80CPU/Z80Memory.cpp Z80CPU/Z80Opcodes.cpp Z80CPU/Z80OpcodesNormal.cpp Z80CPU/Z80OpcodesCB.cpp Z80CPU/Z80OpcodesED.cpp Z80CPU/Z80Registers.cpp) 
target_link_libraries (ZX_Spectrum_Emulator ${LOG4CXX_LIBRARIES})
configure_file(Log4cxxConfig.xml Log4cxxConfig.xml COPYONLY)
configure_file(roms/48.rom roms/48.rom COPYONLY)


add_subdirectory(Tests)


