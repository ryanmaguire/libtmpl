
#ifndef TMPL_WINDOW_FUNCTIONS_COMPLEX_H
#define TMPL_WINDOW_FUNCTIONS_COMPLEX_H

/*  complex data types are defined here.                                      */
#include <libtmpl/include/tmpl_complex.h>

extern double
tmpl_Complex_Window_Normalization(tmpl_ComplexDouble *ker,
                                  long dim, double dx, double f_scale);

#endif

