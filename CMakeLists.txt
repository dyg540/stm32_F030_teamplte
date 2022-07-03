cmake_minimum_required(VERSION 3.10)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

#set(CMAKE_SYSROOT /home/devel/rasp-pi-rootfs)
#set(CMAKE_STAGING_PREFIX /home/devel/stage)


set(tools /opt/gcc-arm-none-eabi-10.3-2021.10)
set(CMAKE_C_COMPILER ${tools}/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER ${tools}/bin/arm-none-eabi-as)


include_directories("/opt/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/include")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs") 

project(testapp LANGUAGES C ASM)
enable_language(C ASM)

add_executable(test1 src/main.c)
set(target test1)
message("target name:" ${target})
#add_custom_target(${target})
