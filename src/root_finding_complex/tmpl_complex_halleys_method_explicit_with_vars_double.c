/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *           tmpl_complex_halleys_method_explicit_with_vars_double            *
 ******************************************************************************/

/*  Complex data types and complex functions provided here.                   */
#include <libtmpl/include/tmpl_complex.h>

/*  Prototype for the function given here.                                    */
#include <libtmpl/include/tmpl_root_finding_complex.h>

tmpl_ComplexDouble
tmpl_CDouble_Halleys_Method_Explicit_With_Vars(
    tmpl_ComplexDouble z,
    tmpl_ComplexDouble (*f)(tmpl_ComplexDouble),
    tmpl_ComplexDouble (*f_prime)(tmpl_ComplexDouble),
    tmpl_ComplexDouble (*f_2prime)(tmpl_ComplexDouble),
    unsigned int max_iters, double eps
)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ComplexDouble w, w_prime, w_2prime, numer, denom;
    double norm_sq, rcpr;
    unsigned int n;

    /*  To avoid working with redundant square roots, compute eps^2.          */
    const double eps_sq = eps*eps;

    /*  Continuing this computation until the error is below the threshold.   */
    for (n = 0U; n < max_iters; ++n)
    {
        /*  Evaluate the functions at the current guess point.                */
        w = f(z);

        /*  Check if this point is close to a root.                           */
        if (tmpl_CDouble_Abs_Squared(w) < eps_sq)
            break;

        /*  If not, compute f' and f'' at the guess point.                    */
        w_prime = f_prime(z);
        w_2prime = f_2prime(z);

        /*  The expression for the Halley iterate has (f')^2 - (f)*(f'')/2    *
         *  in the denominator. Compute the real and imaginary parts of this. */
        denom.dat[0] =
            w_prime.dat[0]*w_prime.dat[0] -
                w_prime.dat[1]*w_prime.dat[1] -
                    0.5*(w.dat[0]*w_2prime.dat[0] - w.dat[1]*w_2prime.dat[1]);

        denom.dat[1] =
            2.0*w_prime.dat[0]*w_prime.dat[1] -
                0.5*(w.dat[0]*w_2prime.dat[1] + w.dat[1]*w_2prime.dat[0]);

        /*  The modulus of the denominator appears in the final expression.   */
        norm_sq = denom.dat[0]*denom.dat[0] + denom.dat[1]*denom.dat[1];

        /*  Avoid a division by zero, check if the norm is zero.              */
        if (norm_sq == 0.0)
            return TMPL_CNAN;

        /*  If denom != 0, compute the numerator. This is given by the        *
         *  expression f*f'.                                                  */
        numer.dat[0] = w.dat[0]*w_prime.dat[0] - w.dat[1]*w_prime.dat[1];
        numer.dat[1] = w.dat[0]*w_prime.dat[1] + w.dat[1]*w_prime.dat[0];

        /*  Compute the reciprocal of |denom|.                                */
        rcpr = 1.0 / norm_sq;

        /*  The update guess is z - numer / denom. We can save several        *
         *  function calls by expanding this expression out directly. This    *
         *  is the real part of the expression.                               */
        z.dat[0] -= rcpr * (
            numer.dat[0] * denom.dat[0] + numer.dat[1] * denom.dat[1]
        );

        /*  Imaginary part of the expression.                                 */
        z.dat[1] -= rcpr * (
            numer.dat[1] * denom.dat[0] - numer.dat[0] * denom.dat[1]
        );
    }
    /*  End of for-loop for Halley's method.                                  */

    return z;
}
/*  End of tmpl_CDouble_Halleys_Method_Explicit_With_Vars.                    */
