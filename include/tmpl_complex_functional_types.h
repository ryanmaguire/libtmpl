#ifndef TMPL_COMPLEX_FUNCTIONAL_TYPES_H
#define TMPL_COMPLEX_FUNCTIONAL_TYPES_H

#include <libtmpl/include/tmpl_complex_double.h>
#include <libtmpl/include/tmpl_complex_float.h>
#include <libtmpl/include/tmpl_complex_ldouble.h>

typedef double (*tmpl_ComplexDoubleFunctional)(tmpl_ComplexDouble);
typedef float (*tmpl_ComplexFloatFunctional)(tmpl_ComplexFloat);
typedef long double (*tmpl_ComplexLongDoubleFunctional)(tmpl_ComplexLongDouble);

#endif
