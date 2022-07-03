cmake_minimum_required(VERSION 3.10)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

#set(CMAKE_SYSROOT /home/devel/rasp-pi-rootfs)
#set(CMAKE_STAGING_PREFIX /home/devel/stage)


set(tools /opt/gcc-arm-none-eabi-10.3-2021.10)
set(CMAKE_C_COMPILER ${tools}/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER ${tools}/bin/arm-none-eabi-as)
set(CMAKE_OBJCOPY ${tools}/bin/arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP ${tools}/bin/arm-none-eabi-objdump)
set(SIZE ${tools}/bin/arm-none-eabi-size)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
#set(CMAKE_C_LINK_EXECUTABLE ld)
#set(CMAKE_CXX_LINK_EXECUTABLE ld)

include_directories("/opt/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/include")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs") 

project(testapp LANGUAGES C ASM)
enable_language(C ASM)
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SOURCES "src/*.*" "startup/*.*" "hwlibs/*.*" "fwlibs/*.*" "CMSIS/*.*")
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F030F4Px_FLASH.ld)
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
 
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
 
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")

#add_custom_target(${target})
