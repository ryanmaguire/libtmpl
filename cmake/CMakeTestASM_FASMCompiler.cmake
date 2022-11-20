# This file is used by EnableLanguage in cmGlobalGenerator to
# determine that the selected ASM_FASM "compiler" (should be masm or masm64)
# works. For assembler this can only check whether the compiler has been found,
# because otherwise there would have to be a separate assembler source file
# for each assembler on every architecture.

set(ASM_DIALECT "_FASM")
include(CMakeTestASMCompiler)
set(ASM_DIALECT)