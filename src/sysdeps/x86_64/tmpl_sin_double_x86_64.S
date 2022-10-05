#if defined(__APPLE__)
.globl  _tmpl_Double_Sin
.p2align        4, 0x90

_tmpl_Double_Sin:
	jmp     sin@PLT

#else
.text
.p2align 4
.globl  tmpl_Double_Sin
.type   tmpl_Double_Sin, @function

tmpl_Double_Sin:
        jmp     sin@PLT

.size   tmpl_Double_Sin, .-tmpl_Double_Sin
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
