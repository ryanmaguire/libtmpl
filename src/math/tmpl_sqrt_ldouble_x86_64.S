#if defined(_WIN64)

/*  Not yet. */
#error "Wait a bit. Getting to this file soon."

#elif defined(__APPLE__)
.globl _tmpl_Double_Sqrt
.align 4,0x90;

_tmpl_Double_Sqrt:
    sqrtsd %xmm0, %xmm0
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
