
/*  Apple x86_64 machines. Works with clang and gcc.                          */
#if defined(__APPLE__)
.globl _tmpl_Float_Floor
.align 4,0x90;

_tmpl_Float_Floor:
    roundss $9, %xmm0, %xmm0
    ret

/*  GNU/Linux and FreeBSD (and others). Works with gcc, clang, and pcc.       */
#else
.text;
.p2align 4,0x90;
.globl tmpl_Float_Floor;
.type tmpl_Float_Floor,@function;

tmpl_Float_Floor:
    roundss $9, %xmm0, %xmm0
    ret

.size tmpl_Float_Floor, . - tmpl_Float_Floor
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
