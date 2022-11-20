# Find the flat assembler http://flatassembler.net/download.php

set(ASM_DIALECT "_FASM")
if(NOT CMAKE_ASM${ASM_DIALECT}_COMPILER)
    if(WIN32)
        set(_CMAKE_ENV_VARX86 "ProgramFiles(x86)")
        set(FASM_NAMES "FASM.exe")
        set(_CMAKE_ASM_FASM_COMPILER_PATHS
            "[HKEY_CURRENT_USER\\SOFTWARE\\fasm]"
            "$ENV{ProgramFiles}/fasm"
            "$ENV{${ENV_VARX86}}/fasm"
            "$ENV{LOCALAPPDATA}/fasm"
            "[HKEY_CURRENT_USER\\SOFTWARE\\fasmw]"
            "$ENV{ProgramFiles}/fasmw"
            "$ENV{${ENV_VARX86}}/fasmw"
            "$ENV{LOCALAPPDATA}/fasmw"
        )
    else()
        # For Linux, fasm has separate 32- and 64-bit executables
        if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
            set(FASM_NAMES "fasm.x64" "fasm")
        else()
            set(FASM_NAMES "fasm")
        endif()
    endif()

    if(NOT DEFINED FASM_HOME)
        if(WIN32)
            set(FASM_HOME "C:/Program Files/fasm")
        else()
            set(FASM_HOME "/usr/bin/")
        endif()
    endif()

    set(_CMAKE_ASM_FASM_COMPILER_PATHS
        "${FASM_HOME}"
        "$ENV{FASM_HOME}"
        ${_CMAKE_ASM_FASM_COMPILER_PATHS}
    )

    find_program(
        CMAKE_ASM${ASM_DIALECT}_COMPILER_INIT
        NAMES ${FASM_NAMES}
        PATHS ${_CMAKE_ASM_FASM_COMPILER_PATHS}
    )

    if(CMAKE_ASM${ASM_DIALECT}_COMPILER_INIT)
        set(FASM_FOUND TRUE)
        message(
            STATUS
            "FASM (flat assembler) found: ${CMAKE_ASM${ASM_DIALECT}_COMPILER_INIT}"
        )
    else()
        set(FASM_FOUND FALSE)
        message(
            FATAL_ERROR
            "FASM was not found at FASM_HOME '${FASM_HOME}' nor at the environment
    variable FASM_HOME: '$ENV{FASM_HOME}'."
        )
    endif()

    unset(_CMAKE_ENV_VARX86)
    unset(_CMAKE_ASM_FASM_COMPILER_PATHS)
endif()

include(CMakeDetermineASMCompiler)
set(ASM_DIALECT)
