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
 *                   tmpl_addto_product_cauchy_intpolynomial                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs the operation p += q * r for polynomials p, q, and r.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_AddTo_Product_Cauchy                               *
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
 *      src/polynomial_integer/                                               *
 *          tmpl_IntPolynomial_AddTo_Product_Cauchy_Kernel:                   *
 *              Performs p += q * r without error checking or shrinking.      *
 *          tmpl_IntPolynomial_Shrink:                                        *
 *              Shrinks a polynomial by removing all terms past the largest   *
 *              non-zero coefficient.                                         *
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
 *      1.) There are several possible ways for an error to occur.            *
 *              a.) The "p" variable is NULL, or has error_occurred = true.   *
 *              b.) An input polynomial (q or r) has error_occurred = true.   *
 *              c.) realloc fails to resize the coefficient array.            *
 *          One can safely handle all cases by inspecting "p" after using     *
 *          this function. First check if it is NULL, then if                 *
 *          error_occurred = true.                                            *
 *                                                                            *
 *      2.) This runs in O(deg(q) * deg(r)), quadratic time. It is much       *
 *          slower than the Karatsuba and FFT / DFT methods for large         *
 *          polynomials. For smaller polynomials (degree less than 30 or so), *
 *          the overhead in the Karatsuba and FFT methods outweigh the        *
 *          benefits and it is faster to use this method.                     *
 *                                                                            *
 *      3.) It does not matter if p = q or p = r, the data in p is not        *
 *          overwritten until the end of the function.                        *
 *                                                                            *
 *      4.) If p is NULL or p->error_occurred is true, nothing is done.       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  2.) tmpl_polynomial_int.h:                                                *
 *          Header where the tmpl_IntPolynomial typedef is given.             *
 *  3.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 21, 2023                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/12/05: Ryan Maguire                                                  *
 *      Moved Cauchy algorithm to its own file.                               *
 ******************************************************************************/

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Integer polynomial typedef provided here.                                 */
#include <libtmpl/include/types/tmpl_polynomial_int.h>

/*  Polynomial functions provided here, as is the function prototype.         */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for computing p += q * r for integer polynomials.                */
void
tmpl_IntPolynomial_AddTo_Product_Cauchy(tmpl_IntPolynomial * const p,
                                        const tmpl_IntPolynomial * const q,
                                        const tmpl_IntPolynomial * const r)
{
    /*  If the output pointer is NULL there's nothing to be done.             */
    if (!p)
        return;

    /*  If an error occurred before this function was called, abort.          */
    if (p->error_occurred)
        return;

    /*  Treat NULL polynomials as zero. Product with a zero polyomial is zero.*/
    if (!q || !r)
    {
        /*  Remove redundant zero terms and return.                           */
        tmpl_IntPolynomial_Shrink(p);
        return;
    }

    /*  If either q or r have an error, abort the computation. Treat this as  *
     *  an error, set the Boolean and an error message.                       */
    if (q->error_occurred || r->error_occurred)
    {
        p->error_occurred = tmpl_True;
        p->error_message =
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_AddTo_Product_Cauchy\n\n"
            "Input polynomial has error_occurred set to true.\n\n";

        return;
    }

    /*  If either polynomial is empty do nothing. p + 0 = p.                  */
    if (!q->coeffs || !r->coeffs)
    {
        /*  Remove redundant zero terms and return.                           */
        tmpl_IntPolynomial_Shrink(p);
        return;
    }

    /*  Special case, if p points to the same polynomial as either q or r, we *
     *  need to avoid overwriting the data.                                   */
    if ((p == q) || (p == r))
    {
        /*  TODO:
         *      Optimize this better. If p = q, we have:
         *          p := p + q*r
         *             = p + p*r
         *             = p*(1 + r)
         *      Similarly if p = r. We can simplify the computation using this.
         */
        tmpl_IntPolynomial tmp;
        tmpl_IntPolynomial_Copy(&tmp, p);
        tmpl_IntPolynomial_AddTo_Product_Cauchy_Kernel(&tmp, q, r);
        tmpl_IntPolynomial_Destroy(p);
        *p = tmp;
    }

    /*  Multiply the polynomials using the Cauchy product algorithm.          */
    else
        tmpl_IntPolynomial_AddTo_Product_Cauchy_Kernel(p, q, r);

    /*  Shrink the result by removing redundant terms.                        */
    tmpl_IntPolynomial_Shrink(p);
}
/*  End of tmpl_IntPolynomial_AddTo_Product_Cauchy.                           */
