
#include "tmpyl_special_functions.h"

/*  Python wrapper for the Bessel I0 function from libtmpl.                   */
PyObject *tmpyl_besselI0(PyObject *self, PyObject *args)
{
    /*  Function object that will contain all of the function pointers.       */
    tmpl_Generic_Function_Obj c_funcs;

    /*  Integer valued functions.                                             */
    c_funcs.long_func = NULL;

    /*  Real valued functions that take real arguments.                       */
    c_funcs.float_func = tmpl_Float_Bessel_I0;
    c_funcs.double_func = tmpl_Double_Bessel_I0;
    c_funcs.ldouble_func = tmpl_LDouble_Bessel_I0;

    /*  Real valued functions that take complex arguments.                    */
    c_funcs.float_from_cfloat_func = NULL;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.ldouble_from_cldouble_func = NULL;

    /*  Complex valued functions that take real arguments.                    */
    c_funcs.cfloat_from_float_func = NULL;
    c_funcs.cdouble_from_double_func = NULL;
    c_funcs.cldouble_from_ldouble_func = NULL;

    /*  Complex valued functions that take complex arguments.                 */
    c_funcs.cfloat_from_cfloat_func = NULL;
    c_funcs.cdouble_from_cdouble_func = tmpl_CDouble_Bessel_I0;
    c_funcs.cdouble_from_cldouble_func = NULL;

    /*  Name of the function.                                                 */
    c_funcs.func_name = "besselI0";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}
/*  End of tmpyl_besselI0.                                                    */

/*  Python wrapper for the Bessel J0 function from libtmpl.                   */
PyObject *tmpyl_besselJ0(PyObject *self, PyObject *args)
{
    /*  Function object that will contain all of the function pointers.       */
    tmpl_Generic_Function_Obj c_funcs;

    /*  Integer valued functions.                                             */
    c_funcs.long_func = NULL;

    /*  Real valued functions that take real arguments.                       */
    c_funcs.float_func = tmpl_Float_Bessel_J0;
    c_funcs.double_func = tmpl_Double_Bessel_J0;
    c_funcs.ldouble_func = tmpl_LDouble_Bessel_J0;

    /*  Real valued functions that take complex arguments.                    */
    c_funcs.float_from_cfloat_func = NULL;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.ldouble_from_cldouble_func = NULL;

    /*  Complex valued functions that take real arguments.                    */
    c_funcs.cfloat_from_float_func = NULL;
    c_funcs.cdouble_from_double_func = NULL;
    c_funcs.cldouble_from_ldouble_func = NULL;

    /*  Complex valued functions that take complex arguments.                 */
    c_funcs.cfloat_from_cfloat_func = NULL;
    c_funcs.cdouble_from_cdouble_func = NULL;
    c_funcs.cdouble_from_cldouble_func = NULL;

    /*  Name of the function.                                                 */
    c_funcs.func_name = "besselJ0";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}
/*  End of tmpyl_besselJ0.                                                    */

/*  Python wrapper for the Fresnel Cos function from libtmpl.                 */
PyObject *tmpyl_fresnel_cos(PyObject *self, PyObject *args)
{
    /*  Function object that will contain all of the function pointers.       */
    tmpl_Generic_Function_Obj c_funcs;

    /*  Integer valued functions.                                             */
    c_funcs.long_func = NULL;

    /*  Real valued functions that take real arguments.                       */
    c_funcs.float_func = tmpl_Float_Fresnel_Cos;
    c_funcs.double_func = tmpl_Double_Fresnel_Cos;
    c_funcs.ldouble_func = tmpl_LDouble_Fresnel_Cos;

    /*  Real valued functions that take complex arguments.                    */
    c_funcs.float_from_cfloat_func = NULL;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.ldouble_from_cldouble_func = NULL;

    /*  Complex valued functions that take real arguments.                    */
    c_funcs.cfloat_from_float_func = NULL;
    c_funcs.cdouble_from_double_func = NULL;
    c_funcs.cldouble_from_ldouble_func = NULL;

    /*  Complex valued functions that take complex arguments.                 */
    c_funcs.cfloat_from_cfloat_func = NULL;
    c_funcs.cdouble_from_cdouble_func = NULL;
    c_funcs.cdouble_from_cldouble_func = NULL;

    /*  Name of the function.                                                 */
    c_funcs.func_name = "fresnel_cos";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}
/*  End of tmpyl_fresnel_cos.                                                 */

/*  Python wrapper for the Fresnel Sin function from libtmpl.                 */
PyObject *tmpyl_fresnel_sin(PyObject *self, PyObject *args)
{
    /*  Function object that will contain all of the function pointers.       */
    tmpl_Generic_Function_Obj c_funcs;

    /*  Integer valued functions.                                             */
    c_funcs.long_func = NULL;

    /*  Real valued functions that take real arguments.                       */
    c_funcs.float_func = tmpl_Float_Fresnel_Sin;
    c_funcs.double_func = tmpl_Double_Fresnel_Sin;
    c_funcs.ldouble_func = tmpl_LDouble_Fresnel_Sin;

    /*  Real valued functions that take complex arguments.                    */
    c_funcs.float_from_cfloat_func = NULL;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.ldouble_from_cldouble_func = NULL;

    /*  Complex valued functions that take real arguments.                    */
    c_funcs.cfloat_from_float_func = NULL;
    c_funcs.cdouble_from_double_func = NULL;
    c_funcs.cldouble_from_ldouble_func = NULL;

    /*  Complex valued functions that take complex arguments.                 */
    c_funcs.cfloat_from_cfloat_func = NULL;
    c_funcs.cdouble_from_cdouble_func = NULL;
    c_funcs.cdouble_from_cldouble_func = NULL;

    /*  Name of the function.                                                 */
    c_funcs.func_name = "fresnel_sin";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}
/*  End of tmpyl_fresnel_sin.                                                 */

/*  Python wrapper for the Lambert W function from libtmpl.                   */
PyObject *tmpyl_lambertw(PyObject *self, PyObject *args)
{
    /*  Function object that will contain all of the function pointers.       */
    tmpl_Generic_Function_Obj c_funcs;

    /*  Integer valued functions.                                             */
    c_funcs.long_func = NULL;

    /*  Real valued functions that take real arguments.                       */
    c_funcs.float_func = tmpl_Float_LambertW;
    c_funcs.double_func = tmpl_Double_LambertW;
    c_funcs.ldouble_func = tmpl_LDouble_LambertW;

    /*  Real valued functions that take complex arguments.                    */
    c_funcs.float_from_cfloat_func = NULL;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.ldouble_from_cldouble_func = NULL;

    /*  Complex valued functions that take real arguments.                    */
    c_funcs.cfloat_from_float_func = NULL;
    c_funcs.cdouble_from_double_func = NULL;
    c_funcs.cldouble_from_ldouble_func = NULL;

    /*  Complex valued functions that take complex arguments.                 */
    c_funcs.cfloat_from_cfloat_func = NULL;
    c_funcs.cdouble_from_cdouble_func = NULL;
    c_funcs.cdouble_from_cldouble_func = NULL;

    /*  Name of the function.                                                 */
    c_funcs.func_name = "lambertw";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}
/*  End of tmpyl_lambertw.                                                    */

/*  Python wrapper for the sinc function from libtmpl.                        */
PyObject *tmpyl_sinc(PyObject *self, PyObject *args)
{
    /*  Function object that will contain all of the function pointers.       */
    tmpl_Generic_Function_Obj c_funcs;

    /*  Integer valued functions.                                             */
    c_funcs.long_func = NULL;

    /*  Real valued functions that take real arguments.                       */
    c_funcs.float_func = tmpl_Float_Sinc;
    c_funcs.double_func = tmpl_Double_Sinc;
    c_funcs.ldouble_func = tmpl_LDouble_Sinc;

    /*  Real valued functions that take complex arguments.                    */
    c_funcs.float_from_cfloat_func = NULL;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.ldouble_from_cldouble_func = NULL;

    /*  Complex valued functions that take real arguments.                    */
    c_funcs.cfloat_from_float_func = NULL;
    c_funcs.cdouble_from_double_func = NULL;
    c_funcs.cldouble_from_ldouble_func = NULL;

    /*  Complex valued functions that take complex arguments.                 */
    c_funcs.cfloat_from_cfloat_func = NULL;
    c_funcs.cdouble_from_cdouble_func = NULL;
    c_funcs.cdouble_from_cldouble_func = NULL;

    /*  Name of the function.                                                 */
    c_funcs.func_name = "sinc";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}
/*  End of tmpyl_sinc.                                                        */

