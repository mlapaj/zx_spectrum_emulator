# Find the QtWidgets library
find_package(Qt5Widgets)

include_directories("${PROJECT_BINARY_DIR}")
# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})

# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_library(z80cpu Z80CPUModule.cpp Z80OpcodesPrint.cpp Z80Memory.cpp Z80Opcodes.cpp Z80OpcodesNormal.cpp Z80OpcodesCB.cpp Z80OpcodesED.cpp Z80Registers.cpp Z80CPUModuleThread.cpp)
target_link_libraries (z80cpu Qt5::Widgets) 
