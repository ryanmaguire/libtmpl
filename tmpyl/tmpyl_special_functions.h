#ifndef TMPYL_SPECIAL_FUNCTIONS_MODULE_H
#define TMPYL_SPECIAL_FUNCTIONS_MODULE_H

#include <Python.h>
#include <libtmpl/include/tmpl.h>
#include "tmpyl_common.h"

extern PyObject *tmpyl_besselI0(PyObject *self, PyObject *args);
extern PyObject *tmpyl_besselJ0(PyObject *self, PyObject *args);
extern PyObject *tmpyl_fresnel_cos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_fresnel_sin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_lambertw(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sinc(PyObject *self, PyObject *args);

#endif

