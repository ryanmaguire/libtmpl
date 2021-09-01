/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                                   tmpyl                                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This file defines all of the function in the Python module tmpyl at   *
 *      the C level. There is no actual Python code, but rather the Python-C  *
 *      API is used to write python wrappers for libtmpl functions.           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) libtmpl:                                                              *
 *          libtmpl (the C library) must be built prior to building tmpyl.    *
 *          The setup.py script attempts to link libtmpl.so to this.          *
 *  2.) CPython:                                                              *
 *          The file Python.h is required, which comes part of the CPython    *
 *          implementation of the Python programming language.                *
 *  3.) numpy:                                                                *
 *          OPTIONAL. Macros are used to handle the case where numpy is not   *
 *          available. The Numpy C API is used so that numpy arrays can be    *
 *          used with the functions from libtmpl. If you do not have numpy,   *
 *          you can still use libtmpl with lists, floats, and ints in Python. *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       August 31, 2021                                               *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2021/08/31: Ryan Maguire                                                  *
 *      Added license and doc string.                                         *
 ******************************************************************************/

/*  To avoid compiler warnings about deprecated numpy stuff. This line is     *
 *  recommended in the numpy documentation. If TMPYL_HAS_NUMPY is 0, numpy is *
 *  not available so we don't need this macro.                                */
#if TMPYL_HAS_NUMPY == 1
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#endif

/*  The Python-C API is given here. The Python documentation recommends       *
 *  including Python.h before anything (even standard library headers).       */
#define PY_SSIZE_T_CLEAN
#include <Python.h>

/*  If numpy is available, we'll need to include the numpy header files.      */
#if TMPYL_HAS_NUMPY == 1
#include <numpy/ndarraytypes.h>
#include <numpy/ufuncobject.h>
#endif

/*  All of the needed Python-to-C tools are defined in these header files.    */
#include "tmpyl_common.h"
#include "tmpyl_special_functions.h"

/*  All of the methods of the tmpyl module are defined in this array.         */
static PyMethodDef tmpyl_methods[] =
{
    {
        "besselI0",
        tmpyl_besselI0,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "tmpyl.besselI0\n\r\t"
        "Purpose:\n\r\t\t"
        "Compute the Zeroth Modified Bessel Function of the First Kind (I0)."
        "\n\r\tArguments\n\r\t\t"
        "x (numpy.ndarray):\n\r\t\t\t"
        "Independent variable for I_0(x). Allowed inputs are int,\n\r\t\t\t"
        "float, complex, list (of ints, floats, and complex),\n\r\t\t\t"
        "and numpy arrays (if tmpyl was built with numpy support).\n\r\t"
        "Outputs:\n\r\t\t"
        "I0 (numpy.ndarray):\n\r\t\t\t"
        "The Bessel Function I0 as a function of x.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import tmpyl\n\r\t\t"
        ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"
        ">>> y = tmpyl.besselI0(x)"
    },
    {
        "besselJ0",
        tmpyl_besselJ0,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "tmpyl.besselJ0\n\r\t"
        "Purpose:\n\r\t\t"
        "Compute the Zeroth Bessel Function of the First Kind (J0).\n\r\t"
        "Arguments\n\r\t\t"
        "x (numpy.ndarray):\n\r\t\t\t"
        "Independent variable for J_0(x). Allowed inputs are\n\r\t\t\t"
        "int, float, list (of ints and floats), and\n\r\t\t\t"
        "numpy arrays (if tmpyl was built with numpy support).\n\r\t"
        "Outputs:\n\r\t\t"
        "J0\n\r\t\t\t"
        "The Bessel Function J0 as a function of x.\n\r\t"
        "Example:\n\r\t\t"
        ">>> import numpy\n\r\t\t"
        ">>> import tmpyl\n\r\t\t"
        ">>> x = numpy.arange(0, 100, 0.01)\n\r\t\t"
        ">>> y = tmpyl.besselJ0(x)"
    },
    {
        "fresnel_cos",
        tmpyl_fresnel_cos,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "tmpyl.fresnel_cos\n\r\t"
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
        ">>> import tmpyl\n\r\t\t"
        ">>> x = numpy.arange(0, 10, 0.01)\n\r\t\t"
        ">>> y = tmpyl.fresnel_cos(x)"
    },
    {
        "fresnel_sin",
        tmpyl_fresnel_sin,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "tmpyl.fresnel_sin\n\r\t"
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
        ">>> import tmpyl\n\r\t\t"
        ">>> x = numpy.arange(0, 10, 0.01)\n\r\t\t"
        ">>> y = tmpyl.fresnel_sin(x)"
    },
    {
        "lambertw",
        tmpyl_lambertw,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "tmpyl.lambertw\n\r\t"
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
        ">>> import tmpyl\n\r\t\t"
        ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"
        ">>> y = tmpyl.lambertw(x)"
    },
    {
        "sinc",
        tmpyl_sinc,
        METH_VARARGS,
        "\r\t"
        "Function:\n\r\t\t"
        "tmpyl.sinc\n\r\t"
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
        ">>> import tmpyl\n\r\t\t"
        ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"
        ">>> y = tmpyl.sinc(x)"
    },
    {NULL, NULL, 0, NULL}
};

/*  The following code uses the Python 3 API. Check the version first.        */
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "tmpyl",
    NULL,
    -1,
    tmpyl_methods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC PyInit_tmpyl(void)
{
    PyObject *m = PyModule_Create(&moduledef);
    if (!m)
        return NULL;

    /*  This line is REQUIRED for numpy support. Without it, a segmentation   *
     *  fault will occur crashing tmpyl.                                      */
#if TMPYL_HAS_NUMPY == 1
    import_array();
#endif

    return m;
}

/*  Below works with Python 2.                                                */
#else
PyMODINIT_FUNC inittmpyl(void)
{
    PyObject *m;

    m = Py_InitModule("tmpyl", tmpyl_methods);
    if (m == NULL)
        return;
}
#endif

