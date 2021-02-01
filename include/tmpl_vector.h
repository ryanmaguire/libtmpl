#ifndef __TMPL_VECTOR_H__
#define __TMPL_VECTOR_H__

#include <libtmpl/include/tmpl_bool.h>

typedef struct tmpl_Vector {
    double *data;
    unsigned long length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_Vector;

extern tmpl_Vector *
tmpl_Create_Vector_From_Data(double *v, unsigned long length);

extern tmpl_Vector *tmpl_Create_Empty_Vector(unsigned long length);

extern tmpl_Vector *
rssringoccs_Create_Zero_Vector(unsigned long length);

extern void tmpl_Destroy_Vector(tmpl_Vector *v);

extern void rssringoccs_Vector_Add(tmpl_Vector *v,
                                   tmpl_Vector *u,
                                   tmpl_Vector *sum);

#endif
