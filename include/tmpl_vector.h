#ifndef __TMPL_VECTOR_H__
#define __TMPL_VECTOR_H__

#include <libtmpl/include/tmpl_bool.h>

typedef struct tmpl_DoubleVector {
    double *data;
    unsigned long length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_DoubleVector;

extern tmpl_DoubleVector *
tmpl_Create_DoubleVector_From_Data(double *v, unsigned long length);

extern tmpl_DoubleVector *
tmpl_Create_Empty_DoubleVector(unsigned long length);

extern tmpl_DoubleVector *
rssringoccs_Create_Zero_DoubleVector(unsigned long length);

extern void
tmpl_Destroy_DoubleVector(tmpl_DoubleVector *v);

extern void
tmpl_DoubleVector_Add(tmpl_DoubleVector *v,
                      tmpl_DoubleVector *u, tmpl_DoubleVector *sum);

#endif

