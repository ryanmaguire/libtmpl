/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
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
 *                              tmpyl_common                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for wrapping C functions for use in the Python         *
 *      programming language. In particular, the CPython implementation.      *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) Python.h:                                                             *
 *          Header file that is part of the CPython implementation of the     *
 *          python programming language. It enables use of the Python-C API.  *
 *  2.) stdlib.h:                                                             *
 *          Standard C header file that contains the free function.           *
 *  3.) tmpl.h:                                                               *
 *          Header file for libtmpl.                                          *
 *  4.) tmpyl_common.h:                                                       *
 *          Header file containing declarations for all functions.            *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code relies on the Python-C API. Building this has been tested on    *
 *  Python 3.9 and Python 2.7. If you are running a different version and the *
 *  build fails, please raise report this to:                                 *
 *      https://github.com/ryanmaguire/libtmpl/issues                         *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       August 31, 2021                                               *
 ******************************************************************************/

/*  To avoid compiler warnings about deprecated numpy stuff. This is only     *
 *  needed if numpy is available. setup.py provides the TMPYL_HAS_NUMPY macro *
 *  and sets it to 1 if numpy is available, and 0 otherwise. Check this.      */
#if TMPYL_HAS_NUMPY == 1
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#endif

/*  The python documentation recommends defining this BEFORE including the    *
 *  Python.h header file.                                                     */
#define PY_SSIZE_T_CLEAN

/*  Python-C API tools here.                                                  */
#include <Python.h>

/*  free is here. Python.h should include this file already, but I've         *
 *  included it just in case.                                                 */
#include <stdlib.h>

/*  All libtmpl header files are included in this one file.                   */
#include <libtmpl/include/tmpl.h>

/*  Declarations for this files functions found here.                         */
#include "tmpyl_common.h"

/*  If numpy is available, we'll need to include the numpy header files.      */
#if TMPYL_HAS_NUMPY == 1
#include <numpy/ndarraytypes.h>
#include <numpy/ufuncobject.h>
#endif

/*  This function frees the memory allocated to a pointer by malloc when the  *
 *  corresponding variable is destroyed at the Python level.                  */
void tmpyl_capsule_cleanup(PyObject *capsule)
{
    /*  PyCapsule_GetPointer returns a pointer to the actual data inside the  *
     *  capsule. This is the data that needs to be freed when something like  *
     *  'del' is called at the Python level.                                  */
    void *memory = PyCapsule_GetPointer(capsule, NULL);

    /*  Free the data.                                                        */
    free(memory);
}
/*  End of tmpyl_capsule_cleanup.                                             */

/*  This function passes integer objects to C for computation.                */
PyObject *
tmpyl_Get_Py_Out_From_Int(PyObject *x, tmpl_Generic_Function_Obj *c_func)
{
    /*  If the the tmpl_Generic_Function_Obj pointer contains an integer      *
     *  function (integer in, integer out), use this.                         */
    if (c_func->long_func != NULL)
    {
        /*  Extract the data from Python as a long int.                       */
        long int x_int = PyLong_AsLong(x);

        /*  Pass the input to the C function.                                 */
        long int y_int = c_func->long_func(x_int);

        /*  Convert the integer into a PyObject pointer with PyLong_FromLong. */
        return PyLong_FromLong(y_int);
    }

    /*  If there's no integer-to-integer function, try a double-to-double     *
     *  function. The resulting PyObject will be a float object.              */
    else if (c_func->double_func != NULL)
    {
        /*  Convert the integer object into a double.                         */
        double x_val = PyLong_AsDouble(x);

        /*  Pass the data to the C function for computation.                  */
        double y_val = c_func->double_func(x_val);

        /*  Convert the double to a PyObject pointer for a float and return.  */
        return PyFloat_FromDouble(y_val);
    }

    /*  Lastly, check if there is a function that takes in a real value and   *
     *  returns a complex value. If there is, the output will be a complex    *
     *  Python object (i.e. complex number in Python).                        */
    else if (c_func->cdouble_from_real_func != NULL)
    {
        /*  Extract the data from the PyObject and convert it to a double.    */
        double x_in = PyLong_AsDouble(x);

        /*  Run the computation, creating a tmpl_ComplexDouble in the process.*/
        tmpl_ComplexDouble z_out = c_func->cdouble_from_real_func(x_in);

        /*  Python will not accept a tmpl_ComplexDouble struct as a valid     *
         *  complex number. We can create a complex object from two doubles,  *
         *  however. Extract the real and imaginary parts from z.             */
        double real = tmpl_CDouble_Real_Part(z_out);
        double imag = tmpl_CDouble_Imag_Part(z_out);

        /*  Create the complex object from two doubles and return.            */
        return PyComplex_FromDoubles(real, imag);
    }

    /*  If there is no function that can handle the input, return with error. */
    else
    {
        /*  If the function name pointer is NULL, print the following error.  */
        if (c_func->func_name == NULL)
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: Unknown\n\n"
                         "\rInteger input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.");

        /*  Otherwise, print the error with the function name included.       */
        else
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: %s\n\n"
                         "\rInteger input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.",
                         c_func->func_name);

        return NULL;
    }
}
/*  End of tmpl_Get_Py_Out_From_Int.                                          */

/*  Function for passing a float object to C for computation.                 */
PyObject *
tmpyl_Get_Py_Out_From_Float(PyObject *x, tmpl_Generic_Function_Obj *c_func)
{
    /*  Check if there's a double-to-double function. The resulting PyObject  *
     *  will by a float object.                                               */
    if (c_func->double_func != NULL)
    {
        /*  Convert the float object into a double.                           */
        double x_val = PyFloat_AsDouble(x);

        /*  Pass the data to the C function for computation.                  */
        double y_val = c_func->double_func(x_val);

        /*  Convert the double to a PyObject pointer for a float and return.  */
        return PyFloat_FromDouble(y_val);
    }

    /*  Lastly, check if there is a function that takes in a real value and   *
     *  returns a complex value. If there is, the output will be a complex    *
     *  Python object (i.e. complex number in Python).                        */
    else if (c_func->cdouble_from_real_func != NULL)
    {
        /*  Extract the data from the PyObject and convert it to a double.    */
        double x_in = PyFloat_AsDouble(x);

        /*  Run the computation, creating a tmpl_ComplexDouble in the process.*/
        tmpl_ComplexDouble z_out = c_func->cdouble_from_real_func(x_in);

        /*  Python will not accept a tmpl_ComplexDouble struct as a valid     *
         *  complex number. We can create a complex object from two doubles,  *
         *  however. Extract the real and imaginary parts from z.             */
        double real = tmpl_CDouble_Real_Part(z_out);
        double imag = tmpl_CDouble_Imag_Part(z_out);

        /*  Create the complex object from two doubles and return.            */
        return PyComplex_FromDoubles(real, imag);
    }

    /*  If there is no function that can handle the input, return with error. */
    else
    {
        /*  If the function name pointer is NULL, print the following error.  */
        if (c_func->func_name == NULL)
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: Unknown\n\n"
                         "\rFloat input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.");

        /*  Otherwise, print the error with the function name included.       */
        else
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: %s\n\n"
                         "\rFloat input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.",
                         c_func->func_name);

        return NULL;
    }
}
/*  tmpl_Get_Py_Out_From_Float.                                               */

/*  Function for passing complex Python objects to C for computation.         */
PyObject *
tmpyl_Get_Py_Out_From_Complex(PyObject *x, tmpl_Generic_Function_Obj *c_func)
{
    /*  Check if there is a function that takes a complex number in and       *
     *  returns a complex number.                                             */
    if (c_func->cdouble_from_complex_func)
    {
        /*  Extract the real and imaginary parts from the complex number.     */
        double real_in = PyComplex_RealAsDouble(x);
        double imag_in = PyComplex_ImagAsDouble(x);

        /*  Convert this data into a tmpl_ComplexDouble struct.               */
        tmpl_ComplexDouble z_in = tmpl_CDouble_Rect(real_in, imag_in);

        /*  Pass the data to the function.                                    */
        tmpl_ComplexDouble z_out = c_func->cdouble_from_complex_func(z_in);

        /*  Extract the real and imaginary parts from the output.             */
        double real_out = tmpl_CDouble_Real_Part(z_out);
        double imag_out = tmpl_CDouble_Imag_Part(z_out);

        /*  Convert this to a Python complex object and return.               */
        return PyComplex_FromDoubles(real_out, imag_out);
    }

    /*  Check if there's a complex-to-real function, like complex modulus.    */
    else if (c_func->double_from_cdouble_func)
    {
        /*  Extract the real and imaginary parts from the complex number.     */
        double real_in = PyComplex_RealAsDouble(x);
        double imag_in = PyComplex_ImagAsDouble(x);

        /*  Convert this data into a tmpl_ComplexDouble struct.               */
        tmpl_ComplexDouble z_in = tmpl_CDouble_Rect(real_in, imag_in);

        /*  Pass the data to the function.                                    */
        double out = c_func->double_from_cdouble_func(z_in);

        /*  Convert to a float Python object and return.                      */
        return PyFloat_FromDouble(out);
    }

    /*  If there is no function that can handle the input, return with error. */
    else
    {
        /*  If the function name pointer is NULL, print the following error.  */
        if (c_func->func_name)
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: %s\n\n"
                         "\rComplex input provided but this function does not\n"
                         "\rexcept complex arguments.", c_func->func_name);

        /*  Otherwise, print the error with the function name included.       */
        else
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: Unknown\n\n"
                         "\rComplex input provided but this function does not\n"
                         "\rexcept complex arguments.");

        puts("Bob");
        return NULL;
    }
}
/*  End of tmpyl_Get_Py_Out_From_Complex.                                     */

PyObject *
tmpyl_Get_Py_Out_From_List(PyObject *x, tmpl_Generic_Function_Obj *c_func)
{
    PyObject *nth_item;
    PyObject *current_item;
    unsigned long int dim = PyList_Size(x);
    PyObject *output = PyList_New(dim);
    unsigned long int n;

    for (n = 0UL; n < dim; ++n)
    {
        nth_item = PyList_GetItem(x, n);

        if (PyLong_Check(nth_item))
            current_item = tmpyl_Get_Py_Out_From_Int(nth_item, c_func);

        else if (PyFloat_Check(nth_item))
            current_item = tmpyl_Get_Py_Out_From_Float(nth_item, c_func);

        else if (PyComplex_Check(nth_item))
            current_item = tmpyl_Get_Py_Out_From_Complex(nth_item, c_func);

        else
        {
            if (c_func->func_name == NULL)
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: Unknown\n\n"
                         "\rInput list must contain real or\n"
                         "\rcomplex numbers only.\n");
            else
                PyErr_Format(PyExc_RuntimeError,
                             "\n\rError Encountered: tmpyl\n"
                             "\r\tFunction Name: %s\n\n"
                             "\rInput list must contain real or\n"
                             "\rcomplex numbers only.\n",
                             c_func->func_name);
            return NULL;
        }

        PyList_SET_ITEM(output, n, current_item);
    }

    return output;
}

PyObject *
tmpl_Get_Py_Func_From_C(PyObject *self, PyObject *args,
                        tmpl_Generic_Function_Obj *c_func)
{
    /*  Declare necessary variables.                                          */
    PyObject *capsule, *output, *x;
    unsigned long int n, dim;
    long int signed_dim;
    void *data, *out;
    int typenum;

#if TMPYL_HAS_NUMPY == 1
    PyArrayObject *x_as_arr;

    if(PyArray_API == NULL)
        import_array();
#endif

    /*  Parse the data from Python and try to convert it to a usable format.  */
    if (!PyArg_ParseTuple(args, "O", &x))
    {
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: tmpyl\n"
                     "\r\t%s\n\n"
                     "\rCould not parse inputs.\n",
                     c_func->func_name);
        return NULL;
    }

    if (PyLong_Check(x))
        return tmpyl_Get_Py_Out_From_Int(x, c_func);
    else if (PyFloat_Check(x))
        return tmpyl_Get_Py_Out_From_Float(x, c_func);
    else if (PyComplex_Check(x))
        return tmpyl_Get_Py_Out_From_Complex(x, c_func);
    else if (PyList_Check(x))
        return tmpyl_Get_Py_Out_From_List(x, c_func);

#if TMPYL_HAS_NUMPY == 1
    else if (!(PyArray_Check(x)))
        goto FAILURE;

    /*  If you get here, then the input is a numpy array. Grab some useful    *
     *  information about the data using numpy's API functions.               */
    x_as_arr = (PyArrayObject *)x;
    typenum  = PyArray_TYPE(x_as_arr);
    dim      = (unsigned long int)PyArray_DIM(x_as_arr, 0);
    data     = PyArray_DATA(x_as_arr);

    /*  Check the inputs to make sure they're valid.                         */
    if (PyArray_NDIM(x_as_arr) != 1)
    {
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: tmpyl\n"
                     "\r\tspecial_functions.%s\n"
                     "\n\rInput is not 1-dimensional.\n",
                     c_func->func_name);
        return NULL;
    }
    else if (dim == 0)
    {
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: tmpyl\n"
                     "\r\tspecial_functions.%s"
                     "\n\n\rInput numpy array is empty.\n",
                     c_func->func_name);
        return NULL;
    }

    switch (typenum)
    {
        case NPY_FLOAT:
            if (c_func->float_func == NULL)
                goto FAILURE;

            out = malloc(sizeof(float) * dim);
            tmpl_get_void_from_void_f2f(data, out, dim, c_func->float_func);
            break;

        case NPY_DOUBLE:
            if (c_func->double_func != NULL)
            {
                out = malloc(sizeof(double) * dim);
                tmpl_get_void_from_void_d2d(data, out, dim,
                                            c_func->double_func);
            }
            else if (c_func->cdouble_from_real_func != NULL)
            {
                out = malloc(sizeof(tmpl_ComplexDouble) * dim);
                tmpl_get_void_from_void_d2c(data, out, dim,
                                            c_func->cdouble_from_real_func);
            }
            else
                goto FAILURE;

            break;

        case NPY_LONGDOUBLE:
            if (c_func->ldouble_func == NULL)
                goto FAILURE;

            out = malloc(sizeof(long double) * dim);
            tmpl_get_void_from_void_ld2ld(data, out, dim, c_func->ldouble_func);
            break;

        case NPY_CDOUBLE:
            if (c_func->cdouble_from_complex_func == NULL)
                goto FAILURE;
            out = malloc(sizeof(long double) * dim);
                tmpl_get_void_from_void_c2c(data, out, dim,
                                            c_func->cdouble_from_complex_func);

            break;
        case NPY_LONG:
            if (c_func->long_func != NULL)
            {
                out = malloc(sizeof(long) * dim);
                tmpl_get_void_from_void_l2l(data, out, dim, c_func->long_func);
            }
            else if (c_func->double_func != NULL)
            {
                double *temp = malloc(sizeof(*temp) * dim);
                out = malloc(sizeof(double) * dim);
                for (n = 0UL; n < dim; ++n)
                    temp[n] = (double)((long *)data)[n];

                tmpl_get_void_from_void_d2d(temp, out, dim,
                                            c_func->double_func);
                free(temp);
                typenum = NPY_DOUBLE;
            }
            else if (c_func->cdouble_from_real_func != NULL)
            {
                double *temp = malloc(sizeof(*temp) * dim);
                out = malloc(sizeof(double) * dim);
                for (n = 0UL; n < dim; ++n)
                    temp[n] = (double)((long *)data)[n];

                tmpl_get_void_from_void_d2c(temp, out, dim,
                                            c_func->cdouble_from_real_func);
                free(temp);
                typenum = NPY_CDOUBLE;
            }

        default:
            goto FAILURE;

    }

    signed_dim = (long int)dim;
    output  = PyArray_SimpleNewFromData(1, &signed_dim, typenum, out);
    capsule = PyCapsule_New(out, NULL, tmpyl_capsule_cleanup);

    /*  This frees the variable at the Python level once it's destroyed.  */
    PyArray_SetBaseObject((PyArrayObject *)output, capsule);

    /*  Return the results to Python.                                     */
    return Py_BuildValue("N", output);

#else
    goto FAILURE;
#endif

FAILURE:
    if (c_func->func_name == NULL)
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: tmpyl\n"
                     "\r\tFunction Name: Unknown\n\n"
                     "\rCould not parse inputs.\n");
    else
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: tmpyl\n"
                     "\r\tFunction Name: %s\n\n"
                     "\rCould not parse inputs.\n",
                     c_func->func_name);
    return NULL;
}
