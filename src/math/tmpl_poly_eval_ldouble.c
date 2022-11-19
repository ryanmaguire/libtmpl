/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  size_t defined here.                                                      */
#include <stdlib.h>

/*  Function for evaluating a polynomial via Horner's method.                 */
long double
tmpl_LDouble_Poly_Eval(long double *coeffs, size_t degree, long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double poly;
    size_t n;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Check this and abort the computation  *
     *  if it's NULL.                                                         */
    if (!coeffs)
        return TMPL_NANL;

    /*  Degree should be at least one, otherwise this is not a polynomial but *
     *  a constant. Check this. If degree is zero, we'll just return the      *
     *  zeroth coefficient (a constant polynomial).                           */
    if (degree == 0)
        poly = coeffs[0];

    /*  If not, compute the polynomial.                                       */
    else
    {
        /*  Set poly to a_{N}*z + a_{N-1} where N is the degree.              */
        poly = coeffs[degree]*x + coeffs[degree-1];

        /*  Use Horner's method of polynomial computation.                    */
        for (n = 2; n <= degree; ++n)
            poly = x*poly + coeffs[degree-n];
    }

    return poly;
}
/*  End of tmpl_LDouble_Poly_Eval.                                            */
