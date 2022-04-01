#include "tmpl_asm_x86_64.inc"

ENTRY(tmpl_Double_Sqrt)
	sqrtsd	%xmm0, %xmm0
	ret
END(tmpl_Double_Sqrt)

/* Enable stack protection */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
