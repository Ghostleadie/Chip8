﻿# CMakeList.txt : CMake project for RaylibApp, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (RaylibApp "RaylibApp.cpp" "RaylibApp.h" "log/log.cpp" "log/log.h" "cpu/cpu.cpp" "cpu/cpu.h" "cpu/rom.cpp" "cpu/rom.h" "cpu/opcodes.cpp" "cpu/opcodes.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RaylibApp PROPERTY CXX_STANDARD 20)
endif()

target_precompile_headers(RaylibApp PUBLIC pch.h)

target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} spdlog)
target_link_libraries(${PROJECT_NAME} rlimgui)
target_link_libraries(${PROJECT_NAME} imgui)
#target_include_directories(RaylibApp INTERFACE "${raygui_SOURCE_DIR}")
# TODO: Add tests and install targets if needed.
