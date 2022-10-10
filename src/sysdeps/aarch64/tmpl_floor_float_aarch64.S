#ifdef __APPLE__
.section  __TEXT,__text,regular,pure_instructions
.globl    _tmpl_Float_Floor
.p2align  2

_tmpl_Float_Floor:
    frintm  s0, s0
    ret

#else

.text
.align  2
.global tmpl_Float_Floor
.type   tmpl_Float_Floor, %function

tmpl_Float_Floor:
    frintm  s0, s0
    ret

.size   tmpl_Float_Floor, .-tmpl_Float_Floor

#if defined(__ELF__)
.section .note.GNU-stack,"",@progbits
#endif

#endif
/* End of #ifdef __APPLE__ */
