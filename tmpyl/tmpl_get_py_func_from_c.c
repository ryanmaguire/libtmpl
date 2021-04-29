
#include "tmpl_npy_c_api.h"

PyObject *
tmpl_Get_Py_Func_From_C(PyObject *self, PyObject *args,
                        tmpl_Generic_Function_Obj *c_func)
{
    /*  Declare necessary variables.                                          */
    PyObject *capsule, *output, *x;
    PyArrayObject *x_as_arr;
    unsigned long int n, dim;
    long int signed_dim;
    void *data, *out;
    int typenum;

    if(PyArray_API == NULL)
    {
        import_array();
    }


    if (c_func->func_name == NULL)
    {
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: rss_ringoccs\n"
                     "\r\ttmpl_Get_Py_Func_From_C\n\n"
                     "\rInput tmpl_Generic_Function_Obj does not\n"
                     "\rcontain a function name.\n\n");
        return NULL;
    }

    /*  Parse the data from Python and try to convert it to a usable format.  */
    if (!PyArg_ParseTuple(args, "O", &x))
    {
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: rss_ringoccs\n"
                     "\r\t%s\n\n"
                     "\rCould not parse inputs.\n",
                     c_func->func_name);
        return NULL;
    }

    if (PyLong_Check(x))
        return tmpl_Get_Py_Out_From_Int(x, c_func);
    else if (PyFloat_Check(x))
        return tmpl_Get_Py_Out_From_Float(x, c_func);
    else if (PyComplex_Check(x))
        return tmpl_Get_Py_Out_From_Complex(x, c_func);
    else if (PyList_Check(x))
    {
        PyObject *nth_item;
        dim    = PyList_Size(x);
        output = PyList_New(dim);

        for (n = 0UL; n < dim; ++n)
        {
            nth_item = PyList_GET_ITEM(x, n);
            if (PyLong_Check(nth_item))
                PyList_SET_ITEM(output, n,
                                tmpl_Get_Py_Out_From_Int(x, c_func));
            else if (PyFloat_Check(nth_item))
                PyList_SET_ITEM(output, n,
                                tmpl_Get_Py_Out_From_Float(x, c_func));
            else if (PyComplex_Check(nth_item))
                PyList_SET_ITEM(output, n,
                                tmpl_Get_Py_Out_From_Complex(x, c_func));
            else
            {
                if (c_func->func_name == NULL)
                PyErr_Format(PyExc_RuntimeError,
                                 "\n\rError Encountered: rss_ringoccs\n"
                                 "\r\tFunction Name: Unknown\n\n"
                                 "\rInput list must contain real or\n"
                                 "\rcomplex numbers only.\n");
                else
                    PyErr_Format(PyExc_RuntimeError,
                                 "\n\rError Encountered: rss_ringoccs\n"
                                 "\r\tFunction Name: %s\n\n"
                                 "\rInput list must contain real or\n"
                                 "\rcomplex numbers only.\n",
                                 c_func->func_name);
                return NULL;
            }
        }
        return output;
    }
    else if (!(PyArray_Check(x)))
    {
        if (c_func->func_name == NULL)
            PyErr_Format(PyExc_RuntimeError,
                 "\n\rError Encountered: rss_ringoccs\n"
                 "\r\tFunction Name: Unknown\n\n"
                 "\rCould not parse inputs.\n");
        else
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: rss_ringoccs\n"
                         "\r\tFunction Name: %s\n\n"
                         "\rCould not parse inputs.\n",
                         c_func->func_name);
        return NULL;
    }

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
                     "\n\rError Encountered: rss_ringoccs\n"
                     "\r\tspecial_functions.%s\n"
                     "\n\rInput is not 1-dimensional.\n",
                     c_func->func_name);
        return NULL;
    }
    else if (dim == 0)
    {
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: rss_ringoccs\n"
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
    capsule = PyCapsule_New(out, NULL, capsule_cleanup);

    /*  This frees the variable at the Python level once it's destroyed.  */
    PyArray_SetBaseObject((PyArrayObject *)output, capsule);

    /*  Return the results to Python.                                     */
    return Py_BuildValue("N", output);

FAILURE:
    PyErr_Format(PyExc_RuntimeError,
                 "\n\rError Encountered: rss_ringoccs\n"
                 "\r\t%s\n\n"
                 "\rCould not parse inputs.\n",
                 c_func->func_name);
    return NULL;
}
