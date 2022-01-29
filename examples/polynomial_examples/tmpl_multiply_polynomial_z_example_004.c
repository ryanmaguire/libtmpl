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
 *      Provides an example of polynomial multiplication in Z[x] without any  *
 *      error checks. This is the bare minimum needed for a computation. It   *
 *      is best to have error checks, since malloc can fail. The result is:   *
 *          (1 + x) * (1 + x) = 1 + 2x + x^2                                  *
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

/*  Function for testing the use of polynomial multiplication in Z[x].        */
int main(void)
{
    /*  Declare pointers to polynomials, and char pointers for strings.       */
    tmpl_PolynomialZ *P, *Q, *prod;
    char *Pstr, *Qstr, *prodstr;

    /*  Create polynomials for P and Q with all coefficients set to zero.     */
    P = tmpl_Create_Zero_PolynomialZ(1);
    Q = tmpl_Create_Zero_PolynomialZ(1);

    /*  We'll set P to the polynomial x + 1.                                  */
    P->coeffs[0] = 1L;
    P->coeffs[1] = 1L;

    /*  We'll set Q to the polynomial x + 1.                                  */
    Q->coeffs[0] = 1L;
    Q->coeffs[1] = 1L;

    /*  Create an empty polynomial to store the product in.                   */
    prod = tmpl_Create_Empty_PolynomialZ();

    /*  Compute the product of P and Q, and store it in prod.                 */
    tmpl_PolynomialZ_Multiply(P, Q, prod);

    /*  Get the string form of the polynomials.                               */
    Pstr = tmpl_PolynomialZ_Get_String(P);
    Qstr = tmpl_PolynomialZ_Get_String(Q);
    prodstr = tmpl_PolynomialZ_Get_String(prod);

    /*  Print the result.                                                     */
    fprintf(stderr, "(%s) * (%s) = %s\n", Pstr, Qstr, prodstr);

    /*  Free everything.                                                      */
    free(prodstr);
    free(Qstr);
    free(Pstr);
    tmpl_Destroy_PolynomialZ(&P);
    tmpl_Destroy_PolynomialZ(&Q);
    tmpl_Destroy_PolynomialZ(&prod);
    return 0;
}
/*  End of main.                                                              */
