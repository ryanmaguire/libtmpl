#ifndef __TMPL_NPY_C_API_H__
#define __TMPL_NPY_C_API_H__

/*  To avoid compiler warnings about deprecated numpy stuff.                  */
#define PY_SSIZE_T_CLEAN
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include "tmpl_py_c_api.h"
#include <Python.h>
#include <numpy/ndarraytypes.h>
#include <numpy/ufuncobject.h>

extern PyObject *
tmpl_Get_Py_Func_From_C(PyObject *self, PyObject *args,
                        tmpl_Generic_Function_Obj *c_func);

#endif
