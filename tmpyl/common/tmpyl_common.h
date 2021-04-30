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
    const char *func_name;
} tmpl_Generic_Function_Obj;

extern PyObject *
tmpl_Get_Py_Out_From_Int(PyObject *x, tmpl_Generic_Function_Obj *c_func);

extern PyObject *
tmpl_Get_Py_Out_From_Float(PyObject *x, tmpl_Generic_Function_Obj *c_func);

extern PyObject *
tmpl_Get_Py_Out_From_Complex(PyObject *x, tmpl_Generic_Function_Obj *c_func);

/*  This function frees the memory allocated to a pointer by malloc when the  *
 *  corresponding variable is destroyed at the Python level.                  */
extern void capsule_cleanup(PyObject *capsule);

extern PyObject *
tmpl_Get_Py_Func_From_C(PyObject *self, PyObject *args,
                        tmpl_Generic_Function_Obj *c_func);

#endif

