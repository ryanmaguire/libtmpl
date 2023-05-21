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
 ******************************************************************************/

/*  Tests tmpl_IntPolynomial_Add with two NULL polynomials.                   */

#include <libtmpl/include/tmpl_polynomial_integer.h>
#include <stdio.h>

int main(void)
{
    /*  The polynomials in this test are NULL.                                */
    tmpl_IntPolynomial *P_ptr = NULL;
    tmpl_IntPolynomial *Q_ptr = NULL;

    /*  Create an empty polynomial for the sum, to be computed next.          */
    tmpl_IntPolynomial sum = tmpl_IntPolynomial_Empty();

    /*  Add P and Q and store the result in sum.                              */
    tmpl_IntPolynomial_Add(P_ptr, Q_ptr, &sum);

    /*  Check for possible errors.                                            */
    if (sum.error_occurred)
    {
        puts("FAIL: tmpl_IntPolynomial_Add set sum.error_occurred = true.");
        goto CLEANUP;
    }

    /*  Adding NULL polynomials should result in an empty polynomial.         */
    if (sum.coeffs == NULL && sum.degree == (size_t)0)
        puts("PASS");
    else
        puts("FAIL: Output is not the empty polynomial.");

CLEANUP:
    tmpl_IntPolynomial_Destroy(&sum);
    return 0;
}
