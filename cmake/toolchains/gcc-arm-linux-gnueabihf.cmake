set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
# sudo apt-get install g++-arm-linux-gnueabihf gcc-arm-linux-gnueabihf
set(ARCH_TUPLE arm-linux-gnueabihf)

find_program(GCC ${ARCH_TUPLE}-gcc PATHS /usr/bin)

if(NOT GCC)
    message(
        FATAL_ERROR
        "Install this compiler with "
        "   sudo apt-get install  gcc-arm-linux-gnueabihf"
    )
endif()

find_program(GPP ${ARCH_TUPLE}-g++ PATHS /usr/bin)
if(NOT GPP)
    message(
        FATAL_ERROR
        "Install this compiler with "
        "   sudo apt-get install g++-arm-linux-gnueabihf"
    )
endif()

set(CMAKE_C_COMPILER ${GCC})
set(CMAKE_CXX_COMPILER ${GPP})

find_program(CMAKE_AR ${ARCH_TUPLE}-ar PATHS /usr/bin REQUIRED)
find_program(CMAKE_LINKER ${ARCH_TUPLE}-ld PATHS /usr/bin REQUIRED)
find_program(CMAKE_OBJCOPY ${ARCH_TUPLE}-objcopy PATHS /usr/bin REQUIRED)
find_program(CMAKE_RANLIB ${ARCH_TUPLE}-ranlib PATHS /usr/bin REQUIRED)
find_program(CMAKE_SIZE ${ARCH_TUPLE}-size PATHS /usr/bin REQUIRED)
find_program(CMAKE_STRIP ${ARCH_TUPLE}-strip PATHS /usr/bin REQUIRED)

set(CMAKE_FIND_ROOT_PATH
    /usr/${ARCH_TUPLE}/
    /usr/${ARCH_TUPLE}/include/
    /usr/lib/${ARCH_TUPLE}/
    /lib/${ARCH_TUPLE}/
)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

if(NOT DEFINED QEMU_HOME)
    set(QEMU_HOME "/usr/bin")
endif()

find_program(QEMU_ARM qemu-arm PATHS ${QEMU_HOME})

if(NOT QEMU_ARM)
    message(
        FATAL_ERROR
        "Install this emulator with "
        "   sudo apt-get install qemu-user qemu-user-static"
    )
else()
    execute_process(
        COMMAND ${QEMU_ARM} -version
        OUTPUT_VARIABLE QEMU_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if(QEMU_VERSION)
        message(STATUS "Found ${QEMU_VERSION}")
    endif()
endif()

set(CROSSCOMPILING_EMULATOR "${QEMU_ARM};-L;/usr/${ARCH_TUPLE}/"
    CACHE INTERNAL ""
)
