/*  Needed for puts.                                                          */
#include <stdio.h>

/*  Needed for exit and NULL.                                                 */
#include <stdlib.h>

#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

tmpl_ComplexDouble
tmpl_CDouble_Poly_Deriv_Real_Coeffs(double *coeffs, unsigned int degree,
                                    unsigned int deriv, tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble poly;
    double temp, factor;
    unsigned int n;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Check this and abort the computation  *
     *  if it's NULL.                                                         */
    if (coeffs == NULL)
    {
        puts("Error Encountered: libtmpl\n"
             "\tFunction: tmpl_CDouble_Poly_Deriv_Real_Coeffs\n\n"
             "The input coefficients pointer is NULL. Trying to access this\n"
             "will result in a segmentation fault. Aborting computation.\n\n");
        exit(0);
    }

    /*  Degree should be at least one, otherwise this is not a polynomial but *
     *  a constant. Check this. If degree is zero, we'll just return the      *
     *  zeroth coefficient (a constant polynomial).                           */
    if (degree < deriv)
        poly = tmpl_CDouble_Zero;
    else if (degree == deriv)
    {
        factor = (double)tmpl_Factorial(degree);
        poly = tmpl_CDouble_Rect(factor * coeffs[degree], 0.0);
    }
    else
    {
        /*  Set poly to a_{N}*z + a_{N-1} where N is the degree.              */
        factor = (double)tmpl_Falling_Factorial(degree, deriv);
        temp = factor*coeffs[degree];
        poly = tmpl_CDouble_Multiply_Real(temp, z);

        factor = (double)tmpl_Falling_Factorial(degree-1, deriv);
        temp   = factor*coeffs[degree-1];
        poly   = tmpl_CDouble_Add_Real(temp, poly);

        /*  Use Horner's method of polynomial computation.                    */
        for (n=2; n<=degree-deriv; ++n)
        {
            poly   =  tmpl_CDouble_Multiply(poly, z);
            factor = (double)tmpl_Falling_Factorial(degree-n, deriv);
            temp  *= coeffs[degree-n];
            poly   =  tmpl_CDouble_Add_Real(temp, poly);
        }
    }
    return poly;
}
