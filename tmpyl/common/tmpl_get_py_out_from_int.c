
#include <Python.h>
#include "tmpyl_common.h"

PyObject *
tmpl_Get_Py_Out_From_Int(PyObject *x, tmpl_Generic_Function_Obj *c_func)
{
    long x_int, y_int;
    double x_val, y_val;
    tmpl_ComplexDouble y_complex;

    if (c_func->long_func != NULL)
    {
        x_int = PyLong_AsLong(x);
        y_int = c_func->long_func(x_int);
        return PyLong_FromLong(y_int);
    }
    else if (c_func->double_func != NULL)
    {
        x_val = PyLong_AsDouble(x);
        y_val = c_func->double_func(x_val);
        return PyFloat_FromDouble(y_val);
    }
    else if (c_func->cdouble_from_real_func != NULL)
    {
        x_val     = PyLong_AsDouble(x);
        y_complex = c_func->cdouble_from_real_func(x_val);
        x_val     = tmpl_CDouble_Real_Part(y_complex);
        y_val     = tmpl_CDouble_Imag_Part(y_complex);
        return PyComplex_FromDoubles(x_val, y_val);
    }
    else
    {
        if (c_func->func_name == NULL)
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: libtmpl\n"
                         "\r\tFunction Name: Unknown\n\n"
                         "\rInteger input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.");
        else
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: libtmpl\n"
                         "\r\tFunction Name: %s\n\n"
                         "\rInteger input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.",
                         c_func->func_name);

        return NULL;
    }
}
