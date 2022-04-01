#include "tmpl_asm_x86_64.inc"

ENTRY(tmpl_LDouble_Sqrt)
#ifndef _WIN64
	fldt	8(%rsp)
	fsqrt
#else
    fldt    (%rdx)
    fsqrt
    mov     %rcx,%rax
    movq    $0x0,0x8(%rcx)
    fstpt   (%rcx)
#endif
	ret

/* Enable stack protection */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
