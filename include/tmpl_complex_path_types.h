#ifndef TMPL_COMPLEX_PATH_TYPES_H
#define TMPL_COMPLEX_PATH_TYPES_H

#include <libtmpl/include/tmpl_complex_double.h>
#include <libtmpl/include/tmpl_complex_float.h>
#include <libtmpl/include/tmpl_complex_ldouble.h>

typedef tmpl_ComplexDouble (*tmpl_ComplexDoublePath)(double);
typedef tmpl_ComplexFloat (*tmpl_ComplexFloatPath)(float);
typedef tmpl_ComplexLongDouble (*tmpl_ComplexLongDoublePath)(long double);

#endif
