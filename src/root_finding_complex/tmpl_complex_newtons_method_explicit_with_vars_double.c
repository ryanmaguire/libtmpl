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
 *           tmpl_complex_newtons_method_explicit_with_vars_double            *
 ******************************************************************************/

/*  Complex data types and complex functions provided here.                   */
#include <libtmpl/include/tmpl_complex.h>

/*  Prototype for the function given here.                                    */
#include <libtmpl/include/tmpl_root_finding_complex.h>

tmpl_ComplexDouble
tmpl_CDouble_Newtons_Method_Explicit_With_Vars(
    tmpl_ComplexDouble z,
    tmpl_ComplexDouble (*f)(tmpl_ComplexDouble),
    tmpl_ComplexDouble (*f_prime)(tmpl_ComplexDouble),
    unsigned int max_iters, double eps
)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ComplexDouble w, w_prime;
    double rcpr, norm_sq;
    unsigned int n;

    /*  To avoid working with redundant square roots, compute eps^2.          */
    const double eps_sq = eps*eps;

    /*  Perform Newton's method until the error is below the threshold.       */
    for (n = 0U; n < max_iters; ++n)
    {
        /*  Evaluate the functions at the current guess point.                */
        w = f(z);

        /*  Check if this point is close to a root.                           */
        if (tmpl_CDouble_Abs_Squared(w) < eps_sq)
            break;

        /*  If not, compute f' at the guess point.                            */
        w_prime = f_prime(z);

        /*  The modulus of the denominator appears in the final expression.   */
        norm_sq = w_prime.dat[0]*w_prime.dat[0] + w_prime.dat[1]*w_prime.dat[1];

        /*  Avoid a division by zero, check if the norm is zero.              */
        if (norm_sq == 0.0)
            return TMPL_CNAN;

        /*  Compute the reciprocal of |w'|.                                   */
        rcpr = 1.0 / norm_sq;

        /*  The update guess is z - f(z) / f'(z). We can save several         *
         *  function calls by expanding this expression out directly. This    *
         *  is the real part of the expression.                               */
        z.dat[0] = rcpr * (
            z.dat[0] * norm_sq -
                w.dat[0] * w_prime.dat[0] -
                    w.dat[1] * w_prime.dat[1]
        );

        /*  Imaginary part of the expression.                                 */
        z.dat[1] = rcpr * (
            z.dat[1] * norm_sq +
                w.dat[0] * w_prime.dat[1] -
                    w.dat[1] * w_prime.dat[0]
        );
    }
    /*  End of for-loop for Newton's method.                                  */

    return z;
}
/*  End of tmpl_CDouble_Newtons_Method_With_Vars.                             */
