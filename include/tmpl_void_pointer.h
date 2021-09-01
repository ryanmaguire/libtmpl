
#ifndef TMPL_VOID_POINTER_H
#define TMPL_VOID_POINTER_H

#include <libtmpl/include/tmpl_complex.h>

extern void
tmpl_get_void_from_void_l2l(void *in, void * out,
                            unsigned long int dim,
                            long int (*f)(long int));

extern void
tmpl_get_void_from_void_d2d(void *in, void * out,
                            unsigned long int dim,
                            double (*f)(double));

extern void
tmpl_get_void_from_void_f2f(void *in, void * out,
                            unsigned long int dim,
                            float (*f)(float));

extern void
tmpl_get_void_from_void_ld2ld(void *in, void * out,
                              unsigned long int dim,
                              long double (*f)(long double));

extern void
tmpl_get_void_from_void_f2cf(void *in, void * out,
                             unsigned long int dim,
                             tmpl_ComplexFloat (*f)(float));

extern void
tmpl_get_void_from_void_d2cd(void *in, void * out,
                             unsigned long int dim,
                             tmpl_ComplexDouble (*f)(double));

extern void
tmpl_get_void_from_void_ld2cld(void *in, void * out,
                               unsigned long int dim,
                               tmpl_ComplexLongDouble (*f)(long double));

extern void
tmpl_get_void_from_void_cf2cf(void *in, void *out,
                              unsigned long int dim,
                              tmpl_ComplexFloat (*f)(tmpl_ComplexFloat));

extern void
tmpl_get_void_from_void_cd2cd(void *in, void *out,
                              unsigned long int dim,
                              tmpl_ComplexDouble (*f)(tmpl_ComplexDouble));

extern void
tmpl_get_void_from_void_cld2cld(void *in, void *out,
                                unsigned long int dim,
                                tmpl_ComplexLongDouble (*f)(tmpl_ComplexLongDouble));

#endif
