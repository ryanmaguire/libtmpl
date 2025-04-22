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
 *          tmpl_complex_newtons_method_polynomial_with_vars_double           *
 ******************************************************************************/

/*
 *  TODO:
 *      Clean up a lot, and optimize a lot.
 */

#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_root_finding_complex.h>
#include <libtmpl/include/tmpl_bool.h>
#include <stddef.h>

tmpl_ComplexDouble
tmpl_CDouble_Newtons_Method_Polynomial_With_Vars(
    tmpl_ComplexDouble z,
    const double * const coeffs, size_t degree,
    unsigned int max_iters, double eps
)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ComplexDouble dz, w, wp;
    tmpl_Bool comp;
    size_t n;

    /*  Evaluate the perturbation term, then compute the next iteration.      */
    w = tmpl_CDouble_Poly_Eval_Real_Coeffs(coeffs, degree, z);
    wp = tmpl_CDouble_Poly_First_Deriv_Eval_Real_Coeffs(coeffs, degree, z);

    /*  If the derivative is zero at your initial guess, Newton-Raphson       *
     *  fails. Return Not-a-Number in this case.                              */
    comp = tmpl_CDouble_Are_Equal(wp, tmpl_CDouble_Zero);

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
        w = tmpl_CDouble_Poly_Eval_Real_Coeffs(coeffs, degree, z);
        wp = tmpl_CDouble_Poly_First_Deriv_Eval_Real_Coeffs(coeffs, degree, z);

        comp = tmpl_CDouble_Are_Equal(wp, tmpl_CDouble_Zero);

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
