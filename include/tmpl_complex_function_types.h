#ifndef TMPL_COMPLEX_FUNCTION_TYPES_H
#define TMPL_COMPLEX_FUNCTION_TYPES_H

#include <libtmpl/include/tmpl_complex_double.h>
#include <libtmpl/include/tmpl_complex_float.h>
#include <libtmpl/include/tmpl_complex_ldouble.h>

typedef tmpl_ComplexDouble (*tmpl_ComplexDoubleFunction)(tmpl_ComplexDouble);
typedef tmpl_ComplexFloat (*tmpl_ComplexFloatFunction)(tmpl_ComplexFloat);
typedef tmpl_ComplexLongDouble
    (*tmpl_ComplexLongDoubleFunction)(tmpl_ComplexLongDouble);

#endif
