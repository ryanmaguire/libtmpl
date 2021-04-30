
#include "tmpyl_special_functions_module.h"

PyObject *tmpyl_lambertw(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_LambertW;
    c_funcs.double_func = tmpl_Double_LambertW;
    c_funcs.ldouble_func = tmpl_LDouble_LambertW;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;
    c_funcs.func_name = "lambertw";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

