
#include "tmpyl_special_functions_module.h"

PyObject *tmpyl_sinc(PyObject *self, PyObject *args)
{
    tmpl_Generic_Function_Obj c_funcs;

    c_funcs.long_func = NULL;
    c_funcs.float_func = tmpl_Float_Sinc;
    c_funcs.double_func = tmpl_Double_Sinc;
    c_funcs.ldouble_func = tmpl_LDouble_Sinc;
    c_funcs.cdouble_from_real_func = NULL;
    c_funcs.cdouble_from_complex_func = NULL;
    c_funcs.func_name = "sinc";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}

