
#include "tmpyl_special_functions.h"

PyObject *tmpyl_besselI0(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_Bessel_I0;
    c_funcs.double_func = tmpl_Double_Bessel_I0;
    c_funcs.ldouble_func = tmpl_LDouble_Bessel_I0;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = tmpl_CDouble_Bessel_I0;
    c_funcs.func_name = "besselI0";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

PyObject *tmpyl_besselJ0(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_Bessel_J0;
    c_funcs.double_func = tmpl_Double_Bessel_J0;
    c_funcs.ldouble_func = tmpl_LDouble_Bessel_J0;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;
    c_funcs.func_name = "besselJ0";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

PyObject *tmpyl_fresnel_cos(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_Fresnel_Cos;
    c_funcs.double_func = tmpl_Double_Fresnel_Cos;
    c_funcs.ldouble_func = tmpl_LDouble_Fresnel_Cos;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;
    c_funcs.func_name = "fresnel_cos";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

PyObject *tmpyl_fresnel_sin(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_Fresnel_Sin;
    c_funcs.double_func = tmpl_Double_Fresnel_Sin;
    c_funcs.ldouble_func = tmpl_LDouble_Fresnel_Sin;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;
    c_funcs.func_name = "fresnel_sin";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

PyObject *tmpyl_lambertw(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_LambertW;
    c_funcs.double_func = tmpl_Double_LambertW;
    c_funcs.ldouble_func = tmpl_LDouble_LambertW;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;
    c_funcs.func_name = "lambertw";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

PyObject *tmpyl_sinc(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_Sinc;
    c_funcs.double_func = tmpl_Double_Sinc;
    c_funcs.ldouble_func = tmpl_LDouble_Sinc;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;
    c_funcs.func_name = "sinc";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

