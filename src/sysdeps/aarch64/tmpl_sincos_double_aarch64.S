#ifdef __APPLE__
.section        __TEXT,__text,regular,pure_instructions
.globl  _tmpl_Double_SinCos
.p2align  2

_tmpl_Double_SinCos:
    stp     x20, x19, [sp, #-32]!
    stp     x29, x30, [sp, #16]
    add     x29, sp, #16
    mov     x19, x1
    mov     x20, x0
    bl      ___sincos_stret
    str     d0, [x20]
    str     d1, [x19]
    ldp     x29, x30, [sp, #16]
    ldp     x20, x19, [sp], #32
    ret

#else

#endif
