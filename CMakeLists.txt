cmake_minimum_required(VERSION 3.10)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

#set(CMAKE_SYSROOT /home/devel/rasp-pi-rootfs)
#set(CMAKE_STAGING_PREFIX /home/devel/stage)


set(tools /opt/gcc-arm-none-eabi-10.3-2021.10)
set(CMAKE_C_COMPILER ${tools}/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER ${tools}/bin/arm-none-eabi-gcc)
set(CMAKE_OBJCOPY ${tools}/bin/arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP ${tools}/bin/arm-none-eabi-objdump)
set(SIZE ${tools}/bin/arm-none-eabi-size)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
#set(CMAKE_C_LINK_EXECUTABLE ld)
#set(CMAKE_CXX_LINK_EXECUTABLE ld)


#头文件
include_directories(/opt/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi/include fwlibs/inc CMSIS)

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

#此处报错了..
add_compile_options(-mcpu=cortex-m0 -mthumb)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

set(CMAKE_EXE_LINKER_FLAGS "-static -Wl,-cref,-u,Reset_Handler -Wl,-Map=${PROJECT_NAME}.map -Wl,--gc-sections -Wl,--defsym=malloc_getpagesize_P=0x80 -Wl,--start-group -lc -lm -Wl,--end-group,-print-memory-usage --specs=nano.specs --specs=nosys.specs")
 
set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_CXX_ASM_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_ASM_FLAGS_DEBUG "-g3")
#set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")
 
# set(CMAKE_C_FLAGS_RELEASE "-O3")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# set(CMAKE_ASM_FLAGS_RELEASE "-x assembler-with-cpp")
# set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto")

#设置值宏定义
add_definitions(-D STM32F030X6)

file(GLOB_RECURSE SOURCES "src/*.*" "hwlibs/*.*" "fwlibs/*.*" "CMSIS/*.*")
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/stm32_flash.ld)
#set(STARTUP_FILE ${CMAKE_SOURCE_DIR}/startup/startup_stm32f0xx.s) ## 启动文件.s
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT}) ## ${TARTUP_FILE}
 
set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
 
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")

#add_custom_target(${target})
