#include "tmpl_asm_x86_64.inc"

ENTRY(tmpl_Float_Sqrt)
	sqrtss	%xmm0, %xmm0
	ret
END(tmpl_Float_Sqrt)


/* Enable stack protection */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
