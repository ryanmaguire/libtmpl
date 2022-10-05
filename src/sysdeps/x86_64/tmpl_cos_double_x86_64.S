#if defined(__APPLE__)
.globl  _tmpl_Double_Cos
.p2align        4, 0x90

_tmpl_Double_Cos:
	jmp     cos@PLT

#else
.text
.p2align 4
.globl  tmpl_Double_Cos
.type   tmpl_Double_Cos, @function

tmpl_Double_Cos:
        jmp     cos@PLT

.size   tmpl_Double_Cos, .-tmpl_Double_Cos
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
