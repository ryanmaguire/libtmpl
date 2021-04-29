/*  To avoid compiler warnings about deprecated numpy stuff.                  */
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <Python.h>
#include <numpy/ndarraytypes.h>
#include <numpy/ufuncobject.h>
#include <libtmpl/include/tmpl_special_functions.h>
#include <libtmpl/include/tmpl_math.h>

#include "tmpl_py_auxiliary.h"

/*---------------------------DEFINE PYTHON FUNCTIONS--------------------------*
 *  This contains the Numpy-C and Python-C API parts that allow for the above *
 *  functions to be called in Python. Numpy arrays, as well as floating point *
 *  and integer valued arguments may then be passed into these functions for  *
 *  improvement in performance, as opposed to the routines written purely in  *
 *  Python. Successful compiling requires the Numpy and Python header files.  *
 *----------------------------------------------------------------------------*/

static PyObject *besselI0(PyObject *self, PyObject *args)
{
    rssringoccs_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = rssringoccs_Float_Bessel_I0;
    c_funcs.double_func = rssringoccs_Double_Bessel_I0;
    c_funcs.ldouble_func = rssringoccs_LDouble_Bessel_I0;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = rssringoccs_CDouble_Bessel_I0;

    return rssringoccs_Get_Py_Func_From_C(self, args, &c_funcs);
}

static PyObject *besselJ0(PyObject *self, PyObject *args)
{
    rssringoccs_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = rssringoccs_Float_Bessel_J0;
    c_funcs.double_func = rssringoccs_Double_Bessel_J0;
    c_funcs.ldouble_func = rssringoccs_LDouble_Bessel_J0;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;

    return rssringoccs_Get_Py_Func_From_C(self, args, &c_funcs);
}

static PyObject *sinc(PyObject *self, PyObject *args)
{
    rssringoccs_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = rssringoccs_Float_Sinc;
    c_funcs.double_func = rssringoccs_Double_Sinc;
    c_funcs.ldouble_func = rssringoccs_LDouble_Sinc;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;

    return rssringoccs_Get_Py_Func_From_C(self, args, &c_funcs);
}

static PyObject *fresnel_sin(PyObject *self, PyObject *args)
{
    rssringoccs_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = rssringoccs_Float_Fresnel_Sin;
    c_funcs.double_func = rssringoccs_Double_Fresnel_Sin;
    c_funcs.ldouble_func = rssringoccs_LDouble_Fresnel_Sin;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;

    return rssringoccs_Get_Py_Func_From_C(self, args, &c_funcs);
}

static PyObject *fresnel_cos(PyObject *self, PyObject *args)
{
    rssringoccs_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = rssringoccs_Float_Fresnel_Cos;
    c_funcs.double_func = rssringoccs_Double_Fresnel_Cos;
    c_funcs.ldouble_func = rssringoccs_LDouble_Fresnel_Cos;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;

    return rssringoccs_Get_Py_Func_From_C(self, args, &c_funcs);
}

static PyObject *lambertw(PyObject *self, PyObject *args)
{
    rssringoccs_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = rssringoccs_Float_LambertW;
    c_funcs.double_func = rssringoccs_Double_LambertW;
    c_funcs.ldouble_func = rssringoccs_LDouble_LambertW;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;

    return rssringoccs_Get_Py_Func_From_C(self, args, &c_funcs);
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
    {
        "frequency_to_wavelength",
        frequency_to_wavelength,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "special_functions.frequency_to_wavelength\n\r\t"
        "Purpose\n\r\t\t"
        "Convert a non-zero frequency to the equivalent wavelength.\n\r\t"
        "Arguments:\n\r\t\t"
        "frequency (numpy.ndarray/int/float/list):\n\r\t\t\t"
        "A numpy array or list of real numbers, input frequency in Hz.\n\r\t\t"
        "Outputs:\n\r\t\t"
        "wavelength (numpy.ndarry/list/float):\n\r\t\t\t"
        "The corresponding wavelength in km.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import special_functions\n\r\t\t"
        ">>> x = numpy.arange(1,10,0.1)"
        ">>> y = special_functions.frequency_to_wavelength(x)"
    },
    {
        "wavelength_to_wavenumber",
        wavelength_to_wavenumber,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "special_functions.wavelength_to_wavenumber\n\r\t"
        "Purpose\n\r\t\t"
        "Convert a non-zero wavelength to the equivalent wavenumber.\n\r\t"
        "Arguments:\n\r\t\t"
        "wavelength (numpy.ndarray/int/float/list):\n\r\t\t\t"
        "A numpy array or list of real numbers, the input wavelength.\n\r\t\t"
        "Outputs:\n\r\t\t"
        "wavenumber (float):\n\r\t\t\t"
        "The corresponding wavenumber.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import special_functions\n\r\t\t"
        ">>> x = numpy.arange(1,10,0.1)"
        ">>> y = special_functions.wavelength_to_wavenumber(x)"
    },
    {
        "where_greater",
        where_greater,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "special_functions.where_greater\n\r\t"
        "Purpose\n\r\t\t"
        "Given a real-valued numpy array arr, and a real number\n\r\t\t"
        "threshold, compute the indices n such that arr[n] > threshold\n\r\t"
        "Arguments:\n\r\t\t"
        "arr (numpy.ndarray):\n\r\t\t\t"
        "A numpy array of real numbers.\n\r\t\t"
        "threshold (int or float):\n\r\t\t\t"
        "The threshold value for comparing arr with."
        "Outputs:\n\r\t\t"
        "where_arr (numpy.ndarray):\n\r\t\t\t"
        "The array of indices such that arr[n] > threshold.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import special_functions\n\r\t\t"
        ">>> x = numpy.arange(-5, 5, 0.01)\n\r\t\t"
        ">>> y = special_functions.where_greater(x, 1.0)"
    },
    {
        "where_lesser",
        where_lesser,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "special_functions.where_lesser\n\r\t"
        "Purpose\n\r\t\t"
        "Given a real-valued numpy array arr, and a real number\n\r\t\t"
        "threshold, compute the indices n such that arr[n] < threshold\n\r\t"
        "Arguments:\n\r\t\t"
        "arr (numpy.ndarray):\n\r\t\t\t"
        "A numpy array of real numbers.\n\r\t\t"
        "threshold (int or float):\n\r\t\t\t"
        "The threshold value for comparing arr with."
        "Outputs:\n\r\t\t"
        "where_arr (numpy.ndarray):\n\r\t\t\t"
        "The array of indices such that arr[n] < threshold.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import special_functions\n\r\t\t"
        ">>> x = numpy.arange(-5, 5, 0.01)\n\r\t\t"
        ">>> y = special_functions.where_lesser(x, 1.0)"
    },
    {
        "window_norm",
        window_norm,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "special_functions.window_norm\n\r\t"
        "Purpose\n\r\t\t"
        "Compute the window normalization scheme.\n\r\t"
        "Arguments:\n\r\t\t"
        "ker (numpy.ndarray):\n\r\t\t\t"
        "A numpy array of real numbers, the input function.\n\r\t\t"
        "dx (int or float):\n\r\t\t\t"
        "The sample spacing of the input function.\n\r\t\t"
        "f_scale (int or float):\n\r\t\t\t"
        "The Fresnel scale in the same units as dx.\n\r\t\t"
        "Outputs:\n\r\t\t"
        "window_norm (float):\n\r\t\t\t"
        "The normalization factor.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import special_functions\n\r\t\t"
        ">>> dx = 0.1"
        ">>> x = numpy.arange(-10,10,dx)\n\r\t\t"
        ">>> ker = special_functions.coss(x, 5)"
        ">>> f_scale = 0.5"
        ">>> y = special_functions.window_norm(ker, dx, f_scale)"
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
