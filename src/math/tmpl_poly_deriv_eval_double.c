/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

double
tmpl_Double_Poly_Deriv_Eval(double *coeffs, unsigned int degree,
                            unsigned int deriv, double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double poly, factor;
    unsigned int n, N;
    unsigned long int fact;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Check this and abort the computation  *
     *  if it's NULL.                                                         */
    if (!coeffs)
        return TMPL_NAN;

    if (degree < deriv)
        poly = 0;
    else if (degree == deriv)
        poly = coeffs[degree];
    else
    {
        N = degree - deriv;

        /*  Set poly to a_{N}*z + a_{N-1} where N is the degree.              */
        fact = tmpl_Falling_Factorial(degree, deriv);
        factor = (double)fact;
        poly = factor*coeffs[0];

        /*  Use Horner's method of polynomial computation.                    */
        for (n = 1; n <= N; ++n)
        {
            factor *= (double)(degree - deriv - n + 1);
            factor = factor / (double)(degree - n + 1);
            poly = x*poly + factor*coeffs[degree-n];
        }
    }
    return poly;
}
/*  End of tmpl_Double_Poly_Deriv_Eval.                                       */
