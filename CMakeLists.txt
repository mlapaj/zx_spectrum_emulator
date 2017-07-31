cmake_minimum_required (VERSION 2.6)
project (ZX_Spectrum_Emulator)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets)

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})

# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

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
include_directories("${PROJECT_BINARY_DIR}"  ${QT_INCLUDES})
add_subdirectory(video)
add_subdirectory(console)
add_subdirectory(Z80CPU)
add_subdirectory(Tests)
add_executable(ZX_Spectrum_Emulator Main.cpp)
target_link_libraries (ZX_Spectrum_Emulator ${LOG4CXX_LIBRARIES} Qt5::Widgets GUI console z80cpu)
configure_file(Log4cxxConfig.xml Log4cxxConfig.xml COPYONLY)
configure_file(roms/48.rom roms/48.rom COPYONLY)
file(COPY scripts DESTINATION .)



