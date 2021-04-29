/*  To avoid compiler warnings about deprecated numpy stuff.                  */
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include "tmpl_py_c_api.h"
#include "tmpl_npy_c_api.h"
#include <libtmpl/include/tmpl_special_functions.h>
#include <libtmpl/include/tmpl_math.h>

#include <Python.h>
#include <numpy/ndarraytypes.h>
#include <numpy/ufuncobject.h>

/*---------------------------DEFINE PYTHON FUNCTIONS--------------------------*
 *  This contains the Numpy-C and Python-C API parts that allow for the above *
 *  functions to be called in Python. Numpy arrays, as well as floating point *
 *  and integer valued arguments may then be passed into these functions for  *
 *  improvement in performance, as opposed to the routines written purely in  *
 *  Python. Successful compiling requires the Numpy and Python header files.  *
 *----------------------------------------------------------------------------*/

static PyObject *besselI0(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_Bessel_I0;
    c_funcs.double_func = tmpl_Double_Bessel_I0;
    c_funcs.ldouble_func = tmpl_LDouble_Bessel_I0;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

static PyObject *besselJ0(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_Bessel_J0;
    c_funcs.double_func = tmpl_Double_Bessel_J0;
    c_funcs.ldouble_func = tmpl_LDouble_Bessel_J0;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

static PyObject *sinc(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_Sinc;
    c_funcs.double_func = tmpl_Double_Sinc;
    c_funcs.ldouble_func = tmpl_LDouble_Sinc;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

static PyObject *fresnel_sin(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_Fresnel_Sin;
    c_funcs.double_func = tmpl_Double_Fresnel_Sin;
    c_funcs.ldouble_func = tmpl_LDouble_Fresnel_Sin;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

static PyObject *fresnel_cos(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_Fresnel_Cos;
    c_funcs.double_func = tmpl_Double_Fresnel_Cos;
    c_funcs.ldouble_func = tmpl_LDouble_Fresnel_Cos;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

static PyObject *lambertw(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_LambertW;
    c_funcs.double_func = tmpl_Double_LambertW;
    c_funcs.ldouble_func = tmpl_LDouble_LambertW;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

static PyMethodDef special_functions_methods[] =
{
    {
        "besselJ0",
        besselJ0,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "special_functions.besselJ0\n\r\t"
        "Purpose:\n\r\t\t"
        "Compute the Zeroth Bessel Function of the First Kind (J0).\n\r\t"
        "Arguments\n\r\t\t"
        "x (numpy.ndarray):\n\r\t\t\t"
        "A numpy array of real numbers. Independent variable for J_0(x)\n\r\t"
        "Outputs:\n\r\t\t"
        "J0\n\r\t\t\t"
        "The Bessel Function J0 as a function of x.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import special_functions\n\r\t\t"
        ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"
        ">>> y = special_functions.besselJ0(x)"
    },
    {
        "besselI0",
        besselI0,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "special_functions.besselI0\n\r\t"
        "Purpose:\n\r\t\t"
        "Compute the Zeroth Modified Bessel Function of the First Kind (I0)."
        "\n\r\tArguments\n\r\t\t"
        "x (numpy.ndarray):\n\r\t\t\t"
        "A numpy array of real numbers. Independent variable for I_0(x)\n\r\t"
        "Outputs:\n\r\t\t"
        "I0 (numpy.ndarray):\n\r\t\t\t"
        "The Bessel Function I0 as a function of x.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import special_functions\n\r\t\t"
        ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"
        ">>> y = special_functions.besselI0(x)"
    },
    {
        "fresnel_sin",
        fresnel_sin,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "special_functions.fresnel_sin\n\r\t"
        "Purpose:\n\r\t\t"
        "Compute the Fresnel sine function."
        "\n\r\tArguments\n\r\t\t"
        "x (numpy.ndarray):\n\r\t\t\t"
        "A numpy array of real numbers. Independent variable for fresnel_sin(x)"
        "\n\r\tOutputs:\n\r\t\t"
        "fresnel_sin (numpy.ndarray):\n\r\t\t\t"
        "The fresnel sine function of x.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import special_functions\n\r\t\t"
        ">>> x = numpy.arange(0, 10, 0.01)\n\r\t\t"
        ">>> y = special_functions.fresnel_sin(x)"
    },
    {
        "fresnel_cos",
        fresnel_cos,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "special_functions.fresnel_cos\n\r\t"
        "Purpose:\n\r\t\t"
        "Compute the Fresnel cosine function."
        "\n\r\tArguments\n\r\t\t"
        "x (numpy.ndarray):\n\r\t\t\t"
        "A numpy array of real numbers. Independent variable for fresnel_cos(x)"
        "\n\r\tOutputs:\n\r\t\t"
        "fresnel_cos (numpy.ndarray):\n\r\t\t\t"
        "The fresnel sine function of x.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import special_functions\n\r\t\t"
        ">>> x = numpy.arange(0, 10, 0.01)\n\r\t\t"
        ">>> y = special_functions.fresnel_cos(x)"
    },
    {
        "lambertw",
        lambertw,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "special_functions.lambertw\n\r\t"
        "Purpose:\n\r\t\t"
        "Compute the Lambert W function, inverse of x*exp(x)."
        "\n\r\tArguments\n\r\t\t"
        "x (numpy.ndarray):\n\r\t\t\t"
        "A numpy array of real numbers. Independent variable.\n\r\t"
        "Outputs:\n\r\t\t"
        "y (numpy.ndarray):\n\r\t\t\t"
        "The Lambert W function of x.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import special_functions\n\r\t\t"
        ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"
        ">>> y = special_functions.lambertw(x)"
    },
    {
        "sinc",
        sinc,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "special_functions.sinc\n\r\t"
        "Purpose:\n\r\t\t"
        "Compute the sinc function, sin(x)/x."
        "\n\r\tArguments\n\r\t\t"
        "x (numpy.ndarray):\n\r\t\t\t"
        "A numpy array of real numbers. Independent variable for sinc(x)\n\r\t"
        "Outputs:\n\r\t\t"
        "sinc (numpy.ndarray):\n\r\t\t\t"
        "The sinc function of x.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import special_functions\n\r\t\t"
        ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"
        ">>> y = special_functions.sinc(x)"
    },
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "special_functions",
    NULL,
    -1,
    special_functions_methods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC PyInit_special_functions(void)
{
    PyObject *m = PyModule_Create(&moduledef);
    if (!m) return NULL;

    import_array();

    return m;
}
