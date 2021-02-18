/*  Needed for puts.                                                          */
#include <stdio.h>

/*  Needed for exit and NULL.                                                 */
#include <stdlib.h>

/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

float tmpl_Real_Poly_Deriv_Float_Coeffs(float *coeffs,
                                         unsigned int degree,
                                         unsigned int deriv, float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float poly, factor;
    unsigned int n, N;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Check this and abort the computation  *
     *  if it's NULL.                                                         */
    if (coeffs == NULL)
    {
        puts("Error Encountered: libtmpl\n"
             "\tFunction: tmpl_Real_Poly_Deriv_Float_Coeffs\n\n"
             "The input coefficients pointer is NULL. Trying to access this\n"
             "will result in a segmentation fault. Aborting computation.\n\n");
        exit(0);
    }

    if (degree < deriv)
        poly = 0;
    else if (degree == deriv)
        poly = coeffs[degree];
    else
    {
        N = degree - deriv;

        /*  Set poly to a_{N}*z + a_{N-1} where N is the degree.              */
        factor = (float)tmpl_Falling_Factorial(degree, deriv);
        poly = factor*coeffs[0];

        /*  Use Horner's method of polynomial computation.                    */
        for (n=1; n<=N; ++n)
        {
            factor = (float)tmpl_Falling_Factorial(degree-n, deriv);
            poly = x*poly + factor*coeffs[degree-n];
        }
    }
    return poly;
}

double tmpl_Real_Poly_Deriv_Double_Coeffs(double *coeffs, unsigned int degree,
                                          unsigned int deriv, double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double poly, factor;
    unsigned int n, N;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Check this and abort the computation  *
     *  if it's NULL.                                                         */
    if (coeffs == NULL)
    {
        puts("Error Encountered: libtmpl\n"
             "\tFunction: tmpl_Real_Poly_Deriv_Double_Coeffs\n\n"
             "The input coefficients pointer is NULL. Trying to access this\n"
             "will result in a segmentation fault. Aborting computation.\n\n");
        exit(0);
    }

    if (degree < deriv)
        poly = 0;
    else if (degree == deriv)
        poly = coeffs[degree];
    else
    {
        N = degree - deriv;

        /*  Set poly to a_{N}*z + a_{N-1} where N is the degree.              */
        factor = (double)tmpl_Falling_Factorial(degree, deriv);
        poly = factor*coeffs[0];

        /*  Use Horner's method of polynomial computation.                    */
        for (n=1; n<=N; ++n)
        {
            factor = (double)tmpl_Falling_Factorial(degree-n, deriv);
            poly = x*poly + factor*coeffs[degree-n];
        }
    }
    return poly;
}

long double
tmpl_Real_Poly_Deriv_LDouble_Coeffs(long double *coeffs, unsigned int degree,
                                    unsigned int deriv, long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double poly, factor;
    unsigned int n, N;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Check this and abort the computation  *
     *  if it's NULL.                                                         */
    if (coeffs == NULL)
    {
        puts("Error Encountered: libtmpl\n"
             "\tFunction: tmpl_Real_Poly_Deriv_LDouble_Coeffs\n\n"
             "The input coefficients pointer is NULL. Trying to access this\n"
             "will result in a segmentation fault. Aborting computation.\n\n");
        exit(0);
    }

    if (degree < deriv)
        poly = 0;
    else if (degree == deriv)
        poly = coeffs[degree];
    else
    {
        N = degree - deriv;

        /*  Set poly to a_{N}*z + a_{N-1} where N is the degree.              */
        factor = (long double)tmpl_Falling_Factorial(degree, deriv);
        poly = factor*coeffs[0];

        /*  Use Horner's method of polynomial computation.                    */
        for (n=1; n<=N; ++n)
        {
            factor =
                (long double)tmpl_Falling_Factorial(degree-n, deriv);
            poly = x*poly + factor*coeffs[degree-n];
        }
    }
    return poly;
}
