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

/*  Tests tmpl_IntPolynomial_Add_Same_Degree with same-sized polynomials.     */

#include <libtmpl/include/tmpl_polynomial_integer.h>
#include <stdio.h>

int main(void)
{
    /*  Input data for the test.                                              */
    const int P_data[4] = {1, 2, 3, 4};
    const int Q_data[4] = {5, 6, 7, 8};
    const int result[4] = {6, 8, 10, 12};

    /*  Variable for indexing over the arrays.                                */
    size_t n;

    /*  Lengths of the arrays defining the polynomials, including the sum.    */
    const size_t P_len = sizeof(P_data) / sizeof(P_data[0]);
    const size_t Q_len = sizeof(Q_data) / sizeof(Q_data[0]);
    const size_t result_len = sizeof(result) / sizeof(result[0]);

    /*  Initialize the polynomials from the data.                             */
    tmpl_IntPolynomial P = tmpl_IntPolynomial_Create_From_Data(P_data, P_len);
    tmpl_IntPolynomial Q = tmpl_IntPolynomial_Create_From_Data(Q_data, Q_len);

    /*  Create an empty polynomial for the sum, to be computed next.          */
    tmpl_IntPolynomial sum = tmpl_IntPolynomial_Empty();

    /*  Add P and Q and store the result in sum.                              */
    tmpl_IntPolynomial_Add_Same_Degree(&P, &Q, &sum);

    /*  Check for possible errors.                                            */
    if (!sum.coeffs)
    {
        puts("FAIL: realloc failed and returned NULL for sum.coeffs.");
        goto CLEANUP;
    }

    if (sum.error_occurred)
    {
        puts("FAIL: tmpl_IntPolynomial_Add_Same_Degree"
             "set sum.error_occurred = true.");
        goto CLEANUP;
    }

    /*  Check if the adding function succeeded.                               */
    for (n = (size_t)0; n < result_len; ++n)
    {
        if (sum.coeffs[n] != result[n])
        {
            puts("FAIL: sum.coeffs != result");
            goto CLEANUP;
        }
    }

    /*  Inform the user that the test passed and conclude.                    */
    puts("PASS");

CLEANUP:
    tmpl_IntPolynomial_Destroy(&P);
    tmpl_IntPolynomial_Destroy(&Q);
    tmpl_IntPolynomial_Destroy(&sum);
    return 0;
}
