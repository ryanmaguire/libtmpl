#if defined(__APPLE__)
.globl    _tmpl_Float_Cos
.p2align  4, 0x90

_tmpl_Float_Cos:
    jmp    cosf@PLT

#else
.text
.p2align 4
.globl  tmpl_Float_Cos
.type   tmpl_Float_Cos, @function

tmpl_Float_Cos:
    jmp    cosf@PLT

.size   tmpl_Float_Cos, .-tmpl_Float_Cos
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
