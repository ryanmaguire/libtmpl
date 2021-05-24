#ifndef TMPL_COMPLEX_VECTOR_H
#define TMPL_COMPLEX_VECTOR_H

#include <libtmpl/include/tmpl_complex.h>

typedef struct tmpl_ComplexDoubleVector {
    tmpl_ComplexDouble *data;
    unsigned long length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_ComplexDoubleVector;

#endif
