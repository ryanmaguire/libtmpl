#ifndef __TMPL_PY_C_API_H__
#define __TMPL_PY_C_API_H__

#include <Python.h>
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_complex.h>

typedef struct _tmpl_Generic_Function_Obj {
    long (*long_func)(long);
    float (*float_func)(float);
    double (*double_func)(double);
    long double (*ldouble_func)(long double);
    tmpl_ComplexDouble (*cdouble_from_real_func)(double);
    tmpl_ComplexDouble(*cdouble_from_complex_func)(tmpl_ComplexDouble);
    char *func_name;
} tmpl_Generic_Function_Obj;

/*  This function frees the memory allocated to a pointer by malloc when the  *
 *  corresponding variable is destroyed at the Python level.                  */
extern void capsule_cleanup(PyObject *capsule);

extern void
tmpl_get_void_from_void_c2c(void *in, void *out,
                            unsigned long int dim,
                            tmpl_ComplexDouble (*f)(tmpl_ComplexDouble));
extern void
tmpl_get_void_from_void_d2c(void *in, void * out,
                            unsigned long int dim,
                            tmpl_ComplexDouble (*f)(double));

extern void
tmpl_get_void_from_void_d2d(void *in, void * out,
                            unsigned long int dim,
                            double (*f)(double));

extern void
tmpl_get_void_from_void_f2f(void *in, void * out,
                            unsigned long int dim,
                            float (*f)(float));

extern void
tmpl_get_void_from_void_l2l(void *in, void * out,
                            unsigned long int dim,
                            long int (*f)(long int));

extern void
tmpl_get_void_from_void_ld2ld(void *in, void * out,
                              unsigned long int dim,
                              long double (*f)(long double));

extern PyObject *
tmpl_Get_Py_Out_From_Int(PyObject *x, tmpl_Generic_Function_Obj *c_func);

extern PyObject *
tmpl_Get_Py_Out_From_Float(PyObject *x, tmpl_Generic_Function_Obj *c_func);

extern PyObject *
tmpl_Get_Py_Out_From_Complex(PyObject *x, tmpl_Generic_Function_Obj *c_func);

#endif

