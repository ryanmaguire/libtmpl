
#ifndef __TMPL_VOID_POINTER_H__
#define __TMPL_VOID_POINTER_H__

#include <libtmpl/include/tmpl_complex.h>

extern void
tmpl_get_void_from_void_c2c(void *in, void *out,
                            unsigned long int dim,
                            tmpl_ComplexDouble (*f)(tmpl_ComplexDouble));
extern void
tmpl_get_void_from_void_d2c(void *in, void * out,
                            unsigned long int dim,
                            tmpl_ComplexDouble (*f)(double));

extern void
tmpl_get_void_from_void_d2d(void *in, void * out,
                            unsigned long int dim,
                            double (*f)(double));

extern void
tmpl_get_void_from_void_f2f(void *in, void * out,
                            unsigned long int dim,
                            float (*f)(float));

extern void
tmpl_get_void_from_void_l2l(void *in, void * out,
                            unsigned long int dim,
                            long int (*f)(long int));

extern void
tmpl_get_void_from_void_ld2ld(void *in, void * out,
                              unsigned long int dim,
                              long double (*f)(long double));
#endif

