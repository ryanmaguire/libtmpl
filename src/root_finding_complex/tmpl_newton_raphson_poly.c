#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_root_finding_complex.h>
#include <libtmpl/include/tmpl_bool.h>

tmpl_ComplexDouble
tmpl_Newton_Raphson_CDouble_Poly_Real(tmpl_ComplexDouble z, double *coeffs,
                                      unsigned int degree,
                                      unsigned int max_iters, double eps)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ComplexDouble dz, w, wp;
    tmpl_Bool comp;
    unsigned int n;

    /*  Evaluate the perturbation term, then compute the next iteration.      */
    w = tmpl_CDouble_Poly_Real_Coeffs(coeffs, degree, z);
    wp = tmpl_CDouble_Poly_Deriv_Real_Coeffs(coeffs, degree, 1, z);

    /*  If the derivative is zero at your initial guess, Newton-Raphson       *
     *  fails. Return Not-a-Number in this case.                              */
    comp = tmpl_CDouble_Compare(wp, tmpl_CDouble_Zero);
    if (comp)
        return tmpl_CDouble_Rect(TMPL_NAN, TMPL_NAN);

    /*  Compute the first iteration of Newton-Raphson.                        */
    dz = tmpl_CDouble_Divide(w, wp);
    z  = tmpl_CDouble_Subtract(z, dz);

    /*  The first iteration has been computed above, so set n to 1.           */
    n = 1;

    /*  Continuing this computation until the error is below the threshold.   */
    while(tmpl_CDouble_Abs(dz) > eps)
    {
        w = tmpl_CDouble_Poly_Real_Coeffs(coeffs, degree, z);
        wp = tmpl_CDouble_Poly_Deriv_Real_Coeffs(coeffs, degree,
                                                              1, z);

        comp = tmpl_CDouble_Compare(wp, tmpl_CDouble_Zero);

        if (comp)
            return tmpl_CDouble_Rect(TMPL_NAN, TMPL_NAN);

        dz = tmpl_CDouble_Divide(w, wp);
        z  = tmpl_CDouble_Subtract(z, dz);
        ++n;

        /*  Break if too many iterations have been run.                       */
        if (n > max_iters)
            break;
    }

    return z;
}

