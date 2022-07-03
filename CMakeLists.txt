cmake_minimum_required(VERSION 3.11)

# CROSS COMPILER
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(tools /opt/gcc-arm-none-eabi-10.3-2021.10)
set(CMAKE_C_COMPILER ${tools}/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER ${tools}/bin/arm-none-eabi-as)

set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs" CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

project(testapp VERSION 1.0.0 LANGUAGES C ASM)
enable_language(C ASM)

#add_custom_target()


# set(LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/code/Project_Settings/Linker_Files/S32K144_64_flash.ld")
# set(STARTUP_FILE "${CMAKE_CURRENT_LIST_DIR}/code/Project_Settings/Startup_Code/startup_S32K144.S")


add_executable(test1 src/main.c)

message(WARNING "目标是:" ${target})