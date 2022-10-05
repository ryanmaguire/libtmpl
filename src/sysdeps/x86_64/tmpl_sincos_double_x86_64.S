#ifdef __APPLE__

#else
.text
.p2align 4
.globl  tmpl_Double_SinCos
.type   tmpl_Double_SinCos, @function

tmpl_Double_SinCos:
.LFB0:
        pushq   %rbp
        movq    %rdi, %rbp
        pushq   %rbx
        movq    %rsi, %rbx
        subq    $24, %rsp
        leaq    8(%rsp), %rdi
        movq    %rsp, %rsi
        call    sincos@PLT
        movsd   8(%rsp), %xmm0
        movsd   %xmm0, 0(%rbp)
        movsd   (%rsp), %xmm0
        movsd   %xmm0, (%rbx)
        addq    $24, %rsp
        popq    %rbx
        popq    %rbp
        ret

.size   tmpl_Double_SinCos, .-tmpl_Double_SinCos

#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
