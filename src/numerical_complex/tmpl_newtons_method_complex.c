
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_numerical_complex.h>

tmpl_ComplexDouble
tmpl_Newton_Raphson_Complex(tmpl_ComplexDouble z,
                            tmpl_ComplexDouble (*f)(tmpl_ComplexDouble),
                            tmpl_ComplexDouble (*f_prime)(tmpl_ComplexDouble),
                            unsigned int max_iters, double eps)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ComplexDouble dz, w, w_prime;
    unsigned int n;

    /*  Evaluate the perturbation term, then compute the next iteration.      */
    w = (*f)(z);
    w_prime = (*f_prime)(z);

    /*  If the derivative is zero at your initial guess, Newton-Raphson       *
     *  fails. Return Not-a-Number in this case.                              */
    if (tmpl_CDouble_Compare(w_prime, tmpl_CDouble_Zero))
        return tmpl_CDouble_Rect(tmpl_NaN, tmpl_NaN);

    /*  Compute the first iteration of Newton-Raphson.                        */
    dz = tmpl_CDouble_Divide(w, w_prime);
    z  = tmpl_CDouble_Subtract(z, dz);

    /*  The first iteration has been computed above, so set n to 1.           */
    n = 1;

    /*  Continuing this computation until the error is below the threshold.   */
    while(tmpl_CDouble_Abs(dz) > eps)
    {
        w = (*f)(z);
        w_prime = (*f_prime)(z);

        if (tmpl_CDouble_Compare(w_prime, tmpl_CDouble_Zero))
            return tmpl_CDouble_Rect(tmpl_NaN, tmpl_NaN);

        dz = tmpl_CDouble_Divide(w, w_prime);
        z  = tmpl_CDouble_Subtract(z, dz);
        ++n;

        /*  Break if too many iterations have been run.                       */
        if (n > max_iters)
            break;
    }

    return z;
}
