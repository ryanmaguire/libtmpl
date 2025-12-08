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
 *                tmpl_addto_product_naive_kernel_intpolynomial               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Multiply two polynomials with integer coefficients.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_AddTo_Product_Cauchy_Kernel                        *
 *  Purpose:                                                                  *
 *      Computes p += q * r where q * r is performed using the Cauchy product.*
 *      This is used as a utility function for the Karatsuba algorithm.       *
 *  Arguments:                                                                *
 *      p (tmpl_IntPolynomial * const):                                       *
 *          A pointer to a polynomial. The result is stored here.             *
 *      q (const tmpl_IntPolynomial * const):                                 *
 *          One of the polynomials being multiplied and added to p.           *
 *      r (const tmpl_IntPolynomial * const):                                 *
 *          The polynomial being multiplied with q and added to p.            *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdlib.h:                                                             *
 *          realloc:                                                          *
 *              Resizes an array.                                             *
 *  Method:                                                                   *
 *      We use the Cauchy product method. That is, if we have:                *
 *                                                                            *
 *                   N                      M                                 *
 *                 -----                  -----                               *
 *                 \         n            \         m                         *
 *          q(x) = /     a  x      r(x) = /     b  x                          *
 *                 -----  n               -----  m                            *
 *                 n = 0                  m = 0                               *
 *                                                                            *
 *      The product is defined by:                                            *
 *                                                                            *
 *                          N     M                                           *
 *                        ----- -----                                         *
 *                        \     \              n + m                          *
 *          q(x) * r(x) = /     /     a  * b  x                               *
 *                        ----- -----  n    m                                 *
 *                        n = 0 m = 0                                         *
 *                                                                            *
 *                        N + M   n                                           *
 *                        ----- -----                                         *
 *                        \     \                 n                           *
 *                      = /     /      a    * b  x                            *
 *                        ----- -----   n-m    m                              *
 *                        n = 0 m = 0                                         *
 *                                                                            *
 *      Where we pad a_n and b_m with zeros for indices beyond deg(q) and     *
 *      deg(r), respectively. That is, we form a grid and sum down the        *
 *      diagonals:                                                            *
 *                                                                            *
 *                 a0      a1      a3      a4      a5                         *
 *              ----------------------------------------                      *
 *             |        /       /       /       /       |                     *
 *          b0 | a0*b0 / a1*b0 / a2*b0 / a3*b0 / a4*b0 /|                     *
 *             |      /       /       /       /       / |                     *
 *             |     /       /       /       /       /  |                     *
 *             |    /       /       /       /       /   |                     *
 *             |   /   +   /   +   /   +   /   +   /    |                     *
 *             |  /       /       /       /       /     |                     *
 *             | /       /       /       /       /      |                     *
 *             |/       /       /       /       /       |                     *
 *          b1 | a0*b1 / a1*b1 / a2*b1 / a3*b1 / a4*b1 /|                     *
 *             |      /       /       /       /       / |                     *
 *             |     /       /       /       /       /  |                     *
 *             |    /       /       /       /       /   |                     *
 *             |   /   +   /   +   /   +   /   +   /    |                     *
 *             |  /       /       /       /       /     |                     *
 *             | /       /       /       /       /      |                     *
 *             |/       /       /       /       /       |                     *
 *          b2 | a0*b2 / a1*b2 / a2*b2 / a3*b2 / a4*b2 /|                     *
 *             |      /       /       /       /       / |                     *
 *              ----------------------------------------                      *
 *                                                                            *
 *      The terms along a given diagonal correspond to the same degree in the *
 *      product, so we may iteratively do p += c * x^n for each c in the      *
 *      diagonal.                                                             *
 *  Notes:                                                                    *
 *      1.) This function does not check for NULL pointers nor shrinks the    *
 *          end result. Use tmpl_IntPolynomial_AddTo_Product_Cauchy for a     *
 *          safer alternative. That function checks the inputs and then uses  *
 *          this function.                                                    *
 *                                                                            *
 *      2.) This function assumes p != q and p != r. It makes no assumption   *
 *          about q = r. If p = q or p = r, overwrites may occur and produce  *
 *          the wrong result.                                                 *
 *                                                                            *
 *      3.) If realloc fails, the error_occurred Boolean is set to true.      *
 *          The data in p is not free'd in this case, it is left alone.       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  2.) tmpl_string.h:                                                        *
 *          Header file where tmpl_String_Duplicate is declared.              *
 *  3.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 21, 2023                                                  *
 ******************************************************************************
 *  2025/12/05: Ryan Maguire                                                  *
 *      Moved Cauchy algorithm to its own file.                               *
 ******************************************************************************/

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  realloc and casting with C vs. C++ compatibility provided here.           */
#include <libtmpl/include/compat/tmpl_cast.h>
#include <libtmpl/include/compat/tmpl_realloc.h>

/*  Integer polynomial typedef provided here.                                 */
#include <libtmpl/include/types/tmpl_polynomial_int.h>

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Forward declaration / function prototype.                                 */
extern void
tmpl_IntPolynomial_AddTo_Product_Cauchy_Kernel(
    tmpl_IntPolynomial * const p,
    const tmpl_IntPolynomial * const q,
    const tmpl_IntPolynomial * const r
);

/*  Function for computing p += q * r for integer polynomials.                */
void
tmpl_IntPolynomial_AddTo_Product_Cauchy_Kernel(
    tmpl_IntPolynomial * const p,
    const tmpl_IntPolynomial * const q,
    const tmpl_IntPolynomial * const r
)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t m, n;

    /*  The degree of the product is the sum of the two degrees.              */
    const size_t degree = q->degree + r->degree;

    /*  Get the polynomial with the smaller degree and set it to "first".     */
    const tmpl_IntPolynomial * const first = (q->degree < r->degree ? q : r);
    const tmpl_IntPolynomial * const second = (q->degree < r->degree ? r : q);

    /*  Check if p needs to be resized.                                       */
    if (p->degree < degree)
    {
        /*  The size of the array is degree + 1 (constant term is included).  */
        const size_t length = degree + 1;

        /*  Try to allocate memory for the product.                           */
        void * const tmp = TMPL_REALLOC(p->coeffs, length);

        /*  Check if realloc failed. Treat this as an error if it did.        */
        if (!tmp)
        {
            p->error_occurred = tmpl_True;
            p->error_message =
                "\nError Encountered:\n"
                "    tmpl_IntPolynomial_AddTo_Product_Cauchy_Kernel\n\n"
                "realloc failed and returned NULL.\n\n";

            return;
        }

        /*  Otherwise reset the coefficient pointer.                          */
        p->coeffs = TMPL_CAST(tmp, signed int *);

        /*  Initialize the new coefficients to zero so we can loop over them. */
        for (n = p->degree + 1; n < length; ++n)
            p->coeffs[n] = 0;

        /*  Reset the degree to reflect the size of the new array.            */
        p->degree = degree;
    }

    /*  First part of the Cauchy product.                                     *
     *                                                                        *
     *       -----------------------                                          *
     *    2 |   |   |   |   |   |   |                                         *
     *      |-----------------------|                                         *
     *    1 | x |   |   |   |   |   |                                         *
     *      |-----------------------|                                         *
     *    0 | x | x |   |   |   |   |                                         *
     *       -----------------------                                          *
     *        0   1   2   3   4   5                                           *
     *                                                                        */
    for (n = 0; n < first->degree; ++n)
        for (m = 0; m <= n; ++m)
            p->coeffs[n] += first->coeffs[n - m] * second->coeffs[m];

    /*  Second part of the Cauchy product.                                    *
     *                                                                        *
     *       -----------------------                                          *
     *    2 | x | x | x |   |   |   |                                         *
     *      |-----------------------|                                         *
     *    1 |   | x | x | x |   |   |                                         *
     *      |-----------------------|                                         *
     *    0 |   |   | x | x | x |   |                                         *
     *       -----------------------                                          *
     *        0   1   2   3   4   5                                           *
     *                                                                        */
    for (n = first->degree; n < second->degree; ++n)
        for (m = n - first->degree; m <= n; ++m)
            p->coeffs[n] += first->coeffs[n - m] * second->coeffs[m];

    /*  Third part of the Cauchy product.                                     *
     *                                                                        *
     *       -----------------------                                          *
     *    2 |   |   |   | x | x | x |                                         *
     *      |-----------------------|                                         *
     *    1 |   |   |   |   | x | x |                                         *
     *      |-----------------------|                                         *
     *    0 |   |   |   |   |   | x |                                         *
     *       -----------------------                                          *
     *        0   1   2   3   4   5                                           *
     *                                                                        */
    for (n = second->degree; n <= p->degree; ++n)
        for (m = n - first->degree; m <= second->degree; ++m)
            p->coeffs[n] += first->coeffs[n - m] * second->coeffs[m];
}
/*  End of tmpl_IntPolynomial_AddTo_Product_Cauchy_Kernel.                    */
