#if defined(__APPLE__)
.globl    _tmpl_LDouble_Cos
.p2align  4, 0x90

_tmpl_LDouble_Cos:
    jmp    cosl@PLT

#else
.text
.p2align 4
.globl  tmpl_LDouble_Cos
.type   tmpl_LDouble_Cos, @function

tmpl_LDouble_Cos:
    jmp    cosl@PLT

.size   tmpl_LDouble_Cos, .-tmpl_LDouble_Cos
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
