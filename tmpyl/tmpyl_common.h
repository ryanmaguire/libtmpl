#ifndef TMPL_PY_C_API_H
#define TMPL_PY_C_API_H

#include <Python.h>
#include <libtmpl/include/tmpl.h>

typedef struct _tmpl_Generic_Function_Obj {
    /*  Integer valued functions.                                             */
    long (*long_func)(long);

    /*  Real valued functions that take real arguments.                       */
    float (*float_func)(float);
    double (*double_func)(double);
    long double (*ldouble_func)(long double);

    /*  Real valued functions that take complex arguments.                    */
    float (*float_from_cfloat_func)(tmpl_ComplexFloat);
    double (*double_from_cdouble_func)(tmpl_ComplexDouble);
    long double (*ldouble_from_cldouble_func)(tmpl_ComplexLongDouble);

    /*  Complex valued functions that take real arguments.                    */
    tmpl_ComplexFloat (*cfloat_from_float_func)(float);
    tmpl_ComplexDouble (*cdouble_from_double_func)(double);
    tmpl_ComplexLongDouble (*cldouble_from_ldouble_func)(long double);

    /*  Complex valued functions that take complex arguments.                 */
    tmpl_ComplexFloat (*cfloat_from_cfloat_func)(tmpl_ComplexFloat);
    tmpl_ComplexDouble (*cdouble_from_cdouble_func)(tmpl_ComplexDouble);
    tmpl_ComplexLongDouble (*cdouble_from_cldouble_func)(tmpl_ComplexLongDouble);

    /*  The name of the function.                                             */
    const char *func_name;
} tmpl_Generic_Function_Obj;

extern PyObject *
tmpl_Get_Py_Func_From_C(PyObject *self, PyObject *args,
                        tmpl_Generic_Function_Obj *c_func);

#endif

