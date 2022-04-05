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
.globl tmpl_Double_Sqrt;
.type tmpl_Double_Sqrt,@function;

tmpl_Double_Sqrt:
    sqrtsd %xmm0, %xmm0
    ret

.size tmpl_Double_Sqrt, . - tmpl_Double_Sqrt
#endif

/* Enable stack protection */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
