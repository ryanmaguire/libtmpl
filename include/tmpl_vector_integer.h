#ifndef __TMPL_VECTOR_INTEGER_H__
#define __TMPL_VECTOR_INTEGER_H__

#include <libtmpl/include/tmpl_bool.h>

typedef struct _tmpl_ULongVector {
    unsigned long *data;
    unsigned long length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_ULongVector;

extern tmpl_ULongVector *
tmpl_Create_ULongVector_From_Data(unsigned long *v, unsigned long length);

extern tmpl_ULongVector *
tmpl_Create_Empty_ULongVector(unsigned long length);

extern tmpl_ULongVector *
rssringoccs_Create_Zero_ULongVector(unsigned long length);

extern void
tmpl_Destroy_ULongVector(tmpl_ULongVector **v);

extern void
tmpl_ULongVector_Add(tmpl_ULongVector *v,
                     tmpl_ULongVector *u, tmpl_ULongVector *sum);

#endif

