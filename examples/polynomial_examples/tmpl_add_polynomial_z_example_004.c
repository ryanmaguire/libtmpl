/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *  Purpose:                                                                  *
 *      Provides an example of using polynomial addition in Z[x] without any  *
 *      error checks. This is the bare minimum needed for a computation. It   *
 *      is best to have error checks, since malloc can fail. The result is:   *
 *          (1 + x) + (1 + x) = 2 + 2x                                        *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       June 19, 2021                                                 *
 ******************************************************************************/

/*  Polynomials are found here, as well as all polynomial functions.          */
#include <libtmpl/include/tmpl_polynomial.h>

/*  The stderr FILE pointer is found here.                                    */
#include <stdio.h>

/*  And free is found here.                                                   */
#include <stdlib.h>

/*  Function for testing the use of polynomial addition in Z[x].              */
int main(void)
{
    /*  Declare pointers to polynomials, and char pointers for strings.       */
    tmpl_PolynomialZ *P, *sum;
    char *Pstr, *sumstr;

    /*  Create polynomials for P and Q with all coefficients set to zero.     */
    P = tmpl_Create_Zero_PolynomialZ(1);

    /*  We'll set P to the polynomial 1 + x.                                  */
    P->coeffs[0] = 1L;
    P->coeffs[1] = 1L;

    /*  Create an empty polynomial to store the sum in.                       */
    sum = tmpl_Create_Empty_PolynomialZ();

    /*  Compute the sum of P with itself, and store it in sum.                */
    tmpl_PolynomialZ_Add(P, P, sum);

    /*  Get the string form of the polynomials.                               */
    Pstr = tmpl_PolynomialZ_Get_String(P);
    sumstr = tmpl_PolynomialZ_Get_String(sum);

    /*  Print the result.                                                     */
    fprintf(stderr, "(%s) + (%s) = %s\n", Pstr, Pstr, sumstr);

    /*  Free everything.                                                      */
    free(sumstr);
    free(Pstr);
    tmpl_Destroy_PolynomialZ(&P);
    tmpl_Destroy_PolynomialZ(&sum);
    return 0;
}
/*  End of main.                                                              */
