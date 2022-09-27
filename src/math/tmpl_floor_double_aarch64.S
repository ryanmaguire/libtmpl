#ifdef __APPLE__
.section	__TEXT,__text,regular,pure_instructions
.globl	_tmpl_Double_Floor
.p2align	2

_tmpl_Double_Floor:
	frintm  d0, d0
	ret

#else

.text
.align  2
.global tmpl_Double_Floor
.type   tmpl_Double_Floor, %function

tmpl_Double_Floor:
    frintm  d0, d0
    ret

.size   tmpl_Double_Floor, .-tmpl_Double_Floor

#if defined(__ELF__)
.section .note.GNU-stack,"",@progbits
#endif

#endif
/* End of #ifdef __APPLE__ */
