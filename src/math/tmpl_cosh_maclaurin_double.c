#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the polynonial. They are 1 / (2n)!.                      */
#define A0 (1.00000000000000000000000000000E+00)
#define A1 (0.50000000000000000000000000000E+00)
#define A2 (4.16666666666666666666666666666E-02)
#define A3 (1.38888888888888888888888888888E-03)

/*  Maclaurin series of hyperbolic cosine to 3 terms.                         */
double tmpl_Double_Cosh_Maclaurin(double x)
{
    /*  The function is even and the series is in terms of x^2.               */
    const double x2 = x*x;

    /*  Compute the polynomial via Horner's method and return.                */
    return A0 + x2*(A1 + x2*(A2 + x2*A3));
}
/*  End of tmpl_Double_Cosh_Maclaurin.                                        */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3
