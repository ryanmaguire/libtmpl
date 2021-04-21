#ifndef __TMPL_SPECIAL_FUNCTIONS_COMPLEX_H__
#define __TMPL_SPECIAL_FUNCTIONS_COMPLEX_H__

/*  complex data types are defined here.                                      */
#include <libtmpl/include/tmpl_complex.h>

extern tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Integral_Real(double z);

extern tmpl_ComplexDouble
tmpl_CDouble_Bessel_J0(tmpl_ComplexDouble z);

extern tmpl_ComplexDouble
tmpl_CDouble_Bessel_I0(tmpl_ComplexDouble z);

extern tmpl_ComplexDouble
tmpl_CDouble_LambertW(tmpl_ComplexDouble z);

extern tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Cos(tmpl_ComplexDouble z);

extern tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Sin(tmpl_ComplexDouble z);


#endif

