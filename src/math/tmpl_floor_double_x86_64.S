#if defined(__APPLE__)
.globl  _tmpl_Double_Floor
.p2align        4, 0x90

_tmpl_Double_Floor:
    roundsd $9, %xmm0, %xmm0
    ret

#else
.text;
.p2align 4,0x90;
.globl tmpl_Double_Floor;
.type tmpl_Double_Floor,@function;

tmpl_Double_Floor:
    roundsd $9, %xmm0, %xmm0
    ret

.size tmpl_Double_Floor, . - tmpl_Double_Floor
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
