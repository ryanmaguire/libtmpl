/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

float tmpl_Real_Poly_Float_Coeffs(float *coeffs, unsigned int degree, float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float poly;
    unsigned int n;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Check this and abort the computation  *
     *  if it's NULL.                                                         */
    if (!coeffs)
        return TMPL_NANF;

    /*  Degree should be at least one, otherwise this is not a polynomial but *
     *  a constant. Check this. If degree is zero, we'll just return the      *
     *  zeroth coefficient (a constant polynomial).                           */
    if (degree == 0)
        poly = coeffs[0];
    else
    {
        /*  Set poly to a_{N}*z + a_{N-1} where N is the degree.              */
        poly = coeffs[degree]*x + coeffs[degree-1];

        /*  Use Horner's method of polynomial computation.                    */
        for (n=2; n<=degree; ++n)
            poly = x*poly + coeffs[degree-n];
    }

    return poly;
}

double tmpl_Real_Poly_Double_Coeffs(double *coeffs,
                                    unsigned int degree, double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double poly;
    unsigned int n;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Check this and abort the computation  *
     *  if it's NULL.                                                         */
    if (!coeffs)
        return TMPL_NAN;

    /*  Degree should be at least one, otherwise this is not a polynomial but *
     *  a constant. Check this. If degree is zero, we'll just return the      *
     *  zeroth coefficient (a constant polynomial).                           */
    if (degree == 0)
        poly = coeffs[0];
    else
    {
        /*  Set poly to a_{N}*z + a_{N-1} where N is the degree.              */
        poly = coeffs[degree]*x + coeffs[degree-1];

        /*  Use Horner's method of polynomial computation.                    */
        for (n=2; n<=degree; ++n)
            poly = x*poly + coeffs[degree-n];
    }

    return poly;
}

long double
tmpl_Real_Poly_LDouble_Coeffs(long double *coeffs,
                              unsigned int degree, long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double poly;
    unsigned int n;

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
    else
    {
        /*  Set poly to a_{N}*z + a_{N-1} where N is the degree.              */
        poly = coeffs[degree]*x + coeffs[degree-1];

        /*  Use Horner's method of polynomial computation.                    */
        for (n=2; n<=degree; ++n)
            poly = x*poly + coeffs[degree-n];
    }

    return poly;
}
