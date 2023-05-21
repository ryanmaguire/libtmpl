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

/*  Tests tmpl_IntPolynomial_Add with two empty polynomials.                  */

#include <libtmpl/include/tmpl_polynomial_integer.h>
#include <stdio.h>

int main(void)
{
    /*  Input data for the test.                                              */
    const int *P_data = NULL;
    const int *Q_data = NULL;

    /*  Lengths of the arrays defining the polynomials.                       */
    const size_t P_len = (size_t)0;
    const size_t Q_len = (size_t)0;

    /*  Initialize the polynomials from the data.                             */
    tmpl_IntPolynomial P = tmpl_IntPolynomial_Create_From_Data(P_data, P_len);
    tmpl_IntPolynomial Q = tmpl_IntPolynomial_Create_From_Data(Q_data, Q_len);

    /*  Create an empty polynomial for the sum, to be computed next.          */
    tmpl_IntPolynomial sum = tmpl_IntPolynomial_Empty();

    /*  Add P and Q and store the result in sum.                              */
    tmpl_IntPolynomial_Add(&P, &Q, &sum);

    /*  Check for possible errors.                                            */
    if (sum.error_occurred)
    {
        puts("FAIL: tmpl_IntPolynomial_Add set sum.error_occurred = true.");
        goto CLEANUP;
    }

    /*  Adding empty polynomials should result in an empty polynomial.        */
    if (sum.coeffs == NULL && sum.degree == (size_t)0)
        puts("PASS");
    else
        puts("FAIL: Output is not the empty polynomial.");

CLEANUP:
    tmpl_IntPolynomial_Destroy(&P);
    tmpl_IntPolynomial_Destroy(&Q);
    tmpl_IntPolynomial_Destroy(&sum);
    return 0;
}
