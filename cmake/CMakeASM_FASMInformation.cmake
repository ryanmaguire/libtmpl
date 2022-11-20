# support for the flat assembler http://flatassembler.net/download.php
set(ASM_DIALECT "_FASM")

set(CMAKE_ASM${ASM_DIALECT}_SOURCE_FILE_EXTENSIONS fasm)

if(NOT CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT)
    set(CMAKE_ASM${ASM_DIALECT}_COMPILE_OBJECT
        "<CMAKE_ASM${ASM_DIALECT}_COMPILER> <SOURCE> <OBJECT>"
    )
endif()
if(NOT CMAKE_ASM${ASM_DIALECT}_COMPILER_ID)
    set(CMAKE_ASM${ASM_DIALECT}_COMPILER_ID fasm)
endif()
include(CMakeASMInformation)
set(ASM_DIALECT)
