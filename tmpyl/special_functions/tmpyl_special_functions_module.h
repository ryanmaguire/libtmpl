#ifndef __TMPYL_SPECIAL_FUNCTIONS_MODULE_H__
#define __TMPYL_SPECIAL_FUNCTIONS_MODULE_H__


#include <Python.h>
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions.h>
#include <libtmpl/include/tmpl_special_functions_complex.h>
#include "../common/tmpyl_common.h"

/*---------------------------DEFINE PYTHON FUNCTIONS--------------------------*
 *  This contains the Numpy-C and Python-C API parts that allow for the above *
 *  functions to be called in Python. Numpy arrays, as well as floating point *
 *  and integer valued arguments may then be passed into these functions for  *
 *  improvement in performance, as opposed to the routines written purely in  *
 *  Python. Successful compiling requires the Numpy and Python header files.  *
 *----------------------------------------------------------------------------*/

extern PyObject *tmpyl_besselI0(PyObject *self, PyObject *args);
extern PyObject *tmpyl_besselJ0(PyObject *self, PyObject *args);
extern PyObject *tmpyl_fresnel_cos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_fresnel_sin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_lambertw(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sinc(PyObject *self, PyObject *args);

#endif

