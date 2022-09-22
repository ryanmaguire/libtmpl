/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

#define A0 (1.00000000000000000000E00)
#define A1 (-3.33333333333329318027E-01)
#define A2 (1.99999999998764832476E-01)
#define A3 (-1.42857142725034663711E-01)
#define A4 (1.11111104054623557880E-01)
#define A5 (-9.09088713343650656196E-02)

double tmpl_Double_Arctan_Asymptotic(double x)
{
    /*  Declare necessary variables.                                          */
    const double z = 1.0 / x;
    const double z2 = z*z;

    /*  Use Horner's method to compute the polynomial. The signs of the       *
     *  coefficients oscillate.                                               */
    return tmpl_Pi_By_Two -
           z*(A0 + z2*(A1 + z2*(A2 + z2*(A3 + z2*(A4 + z2*A5)))));
}

#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#endif
