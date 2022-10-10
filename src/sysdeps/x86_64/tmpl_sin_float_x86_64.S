#if defined(__APPLE__)
.globl    _tmpl_Float_Sin
.p2align  4, 0x90

_tmpl_Float_Sin:
    jmp    sinf@PLT

#else
.text
.p2align 4
.globl  tmpl_Float_Sin
.type   tmpl_Float_Sin, @function

tmpl_Float_Sin:
        jmp     sinf@PLT

.size   tmpl_Float_Sin, .-tmpl_Float_Sin
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
