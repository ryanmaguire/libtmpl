
#ifndef TMPL_VOID_POINTER_H
#define TMPL_VOID_POINTER_H

#include <libtmpl/include/types/tmpl_complex_double.h>
#include <libtmpl/include/types/tmpl_complex_float.h>
#include <libtmpl/include/types/tmpl_complex_ldouble.h>
#include <libtmpl/include/types/tmpl_complex_function_double.h>
#include <libtmpl/include/types/tmpl_complex_function_float.h>
#include <libtmpl/include/types/tmpl_complex_function_ldouble.h>
#include <libtmpl/include/types/tmpl_complex_functional_double.h>
#include <libtmpl/include/types/tmpl_complex_functional_float.h>
#include <libtmpl/include/types/tmpl_complex_functional_ldouble.h>
#include <libtmpl/include/types/tmpl_complex_path_double.h>
#include <libtmpl/include/types/tmpl_complex_path_float.h>
#include <libtmpl/include/types/tmpl_complex_path_ldouble.h>
#include <libtmpl/include/types/tmpl_function_double.h>
#include <libtmpl/include/types/tmpl_function_float.h>
#include <libtmpl/include/types/tmpl_function_ldouble.h>

#include <libtmpl/include/types/tmpl_integer_function_types.h>
#include <stddef.h>

extern void
tmpl_Void_Array_L2L(const void * const in,
                    void * const out,
                    size_t length,
                    const tmpl_LongFunction func);

extern void
tmpl_Void_Array_L2D(const void * const in,
                    void * const out,
                    size_t length,
                    const tmpl_DoubleFunction func);

extern void
tmpl_Void_Array_L2CD(const void * const in,
                     void * const out,
                     size_t length,
                     const tmpl_ComplexDoublePath func);

extern void
tmpl_Void_Array_F2F(const void * const in,
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

extern void
tmpl_Void_Array_CF2F(const void * const in,
                     void * const out,
                     const size_t length,
                     const tmpl_ComplexFloatFunctional func);

extern void
tmpl_Void_Array_CD2D(const void * const in,
                     void * const out,
                     const size_t length,
                     const tmpl_ComplexDoubleFunctional func);

extern void
tmpl_Void_Array_CLD2LD(const void * const in,
                       void * const out,
                       const size_t length,
                       const tmpl_ComplexLongDoubleFunctional func);

#endif
