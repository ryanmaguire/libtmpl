#if defined(__APPLE__)
.globl    _tmpl_LDouble_Sin
.p2align  4, 0x90

_tmpl_LDouble_Sin:
    jmp    sin@PLT

#else
.text
.p2align 4
.globl  tmpl_LDouble_Sin
.type   tmpl_LDouble_Sin, @function

tmpl_LDouble_Sin:
        jmp     sinl@PLT

.size   tmpl_LDouble_Sin, .-tmpl_LDouble_Sin
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
