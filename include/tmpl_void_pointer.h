
#ifndef TMPL_VOID_POINTER_H
#define TMPL_VOID_POINTER_H

#include <libtmpl/include/tmpl_complex_double.h>
#include <libtmpl/include/tmpl_complex_float.h>
#include <libtmpl/include/tmpl_complex_ldouble.h>
#include <libtmpl/include/tmpl_complex_function_types.h>
#include <libtmpl/include/tmpl_complex_path_types.h>
#include <libtmpl/include/tmpl_real_function_types.h>
#include <stddef.h>

extern void
tmpl_get_void_from_void_l2l(void *in, void * out,
                            unsigned long int dim,
                            long int (*f)(long int));

extern void
tmpl_Void_Array_F2C(const void * const in,
                    void * const out,
                    const size_t length,
                    const tmpl_FloatFunction func);

extern void
tmpl_Void_Array_D2D(const void * const in,
                    void * const out,
                    const size_t length,
                    const tmpl_DoubleFunction func);

extern void
tmpl_Void_Array_LD2LD(const void * const in,
                      void * const out,
                      const size_t length,
                      const tmpl_LongDoubleFunction func);

extern void
tmpl_Void_Array_F2CF(const void * const in,
                     void * const out,
                     const size_t length,
                     const tmpl_ComplexFloatPath func);

extern void
tmpl_Void_Array_D2CD(const void * const in,
                     void * const out,
                     const size_t length,
                     const tmpl_ComplexDoublePath func);

extern void
tmpl_Void_Array_LD2CLD(const void * const in,
                       void * const out,
                       const size_t length,
                       const tmpl_ComplexLongDoublePath func);

extern void
tmpl_Void_Array_CF2CF(const void * const in,
                      void * const out,
                      const size_t length,
                      const tmpl_ComplexFloatFunction func);

extern void
tmpl_Void_Array_CD2CD(const void * const in,
                      void * const out,
                      const size_t length,
                      const tmpl_ComplexDoubleFunction func);

extern void
tmpl_Void_Array_CLD2CLD(const void * const in,
                        void * const out,
                        const size_t length,
                        const tmpl_ComplexLongDoubleFunction func);

#endif
