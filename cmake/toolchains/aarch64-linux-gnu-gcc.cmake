cmake_minimum_required(VERSION 3.15)
list(
    APPEND
    CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchains
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_HOST_SYSTEM_PROCESSOR x86_64)

find_program(GCC aarch64-linux-gnu-gcc PATHS /usr/bin)

if(NOT GCC)
    message(
        FATAL_ERROR
        "Install this compiler with "
        "   sudo apt-get install gcc-aarch64-linux-gnu"
    )
endif()

find_program(GPP aarch64-linux-gnu-g++ PATHS /usr/bin)
if(NOT GPP)
    message(
        FATAL_ERROR
        "Install this compiler with "
        "   sudo apt-get install g++-aarch64-linux-gnu"
    )
endif()

set(CMAKE_C_COMPILER ${GCC})
set(CMAKE_CXX_COMPILER ${GPP})

find_program(CMAKE_AR  aarch64-linux-gnu-ar PATHS /usr/bin REQUIRED)
find_program(CMAKE_LINKER  aarch64-linux-gnu-ld PATHS /usr/bin REQUIRED)
find_program(CMAKE_OBJCOPY aarch64-linux-gnu-objcopy PATHS /usr/bin REQUIRED)
find_program(CMAKE_RANLIB aarch64-linux-gnu-ranlib PATHS /usr/bin REQUIRED)
find_program(CMAKE_SIZE aarch64-linux-gnu-size PATHS /usr/bin REQUIRED)
find_program(CMAKE_STRIP aarch64-linux-gnu-strip PATHS /usr/bin REQUIRED)

set(CMAKE_FIND_ROOT_PATH /usr/aarch64-linux-gnu /usr/include/aarch64-linux-gnu
    /usr/lib/aarch64-linux-gnu /lib/aarch64-linux-gnu)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)



if(NOT DEFINED QEMU_HOME)
    set(QEMU_HOME "/usr/bin")
endif()

find_program(QEMU_AARCH64 qemu-aarch64 PATHS ${QEMU_HOME})

if(NOT QEMU_AARCH64)
    message(
        FATAL_ERROR
        "Install this emulator with "
        "   sudo apt-get install qemu-user qemu-user-static"
    )
else()
    execute_process(
        COMMAND ${QEMU_AARCH64} -version
        OUTPUT_VARIABLE QEMU_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if(QEMU_VERSION)
        message(STATUS "Found ${QEMU_VERSION}")
    endif()
endif()

# set(CMAKE_CROSSCOMPILING_EMULATOR "${QEMU_AARCH64};-L;/usr/aarch64-linux-gnu"
#     CACHE INTERNAL ""
# )
set(CROSSCOMPILING_EMULATOR "${QEMU_AARCH64};-L;/usr/aarch64-linux-gnu"
    CACHE INTERNAL ""
)
