#if defined(_WIN64)
.p2align 4,0x90;
.globl tmpl_LDouble_Sqrt;
.section .drectve;
.ascii " -export:", "tmpl_LDouble_Sqrt";
.section .text;
.def tmpl_LDouble_Sqrt;
.scl 2;
.type 32;
.endef;

tmpl_LDouble_Sqrt:
	fldt 8(%rsp)
	fsqrt
	ret

#elif defined(__APPLE__)
.globl _tmpl_LDouble_Sqrt
.align 4,0x90;

_tmpl_LDouble_Sqrt:
    fldt 8(%rsp)
    fsqrt
    ret

#else
.text;
.p2align 4,0x90;
.globl tmpl_LDouble_Sqrt;
.type tmpl_LDouble_Sqrt,@function;

tmpl_LDouble_Sqrt:
    fldt 8(%rsp)
    fsqrt
    ret
#endif

/* Enable stack protection */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
