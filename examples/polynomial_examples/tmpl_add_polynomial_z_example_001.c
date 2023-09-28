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
 *      Provides an example of using polynomial addition in Z[x]. This        *
 *      example shows all of the steps necessary for checking for errors.     *
 *      The only time an error should occur is if malloc, calloc, or realloc  *
 *      fails inside one the called functions. To avoid segmentation faults,  *
 *      it's always best to check for errors. This compiles with GCC, TCC,    *
 *      clang, and PCC, with all pedantic compiler warnings enabled. The      *
 *      result is:                                                            *
 *          (-1 + x^8) + (1 + x^4) = x^4 + x^8                                *
 *                                                                            *
 *          Trying out tmpl_PolynomialZ_Print_String:                         *
 *          P = -1 + x^8                                                      *
 *          Q = 1 + x^4                                                       *
 *          P + Q = x^4 + x^8                                                 *
 *                                                                            *
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
    tmpl_PolynomialZ *P, *Q, *sum;
    char *Pstr, *Qstr, *sumstr;

    /*  Create polynomials for P and Q with all coefficients set to zero.     */
    P = tmpl_Create_Zero_PolynomialZ(8);
    Q = tmpl_Create_Zero_PolynomialZ(4);

    /*  Check if either failed.                                               */
    if ((P == NULL) || (Q == NULL))
    {
        fprintf(stderr,
                "tmpl_Create_Zero_PolynomialZ returned a NULL pointer. It is\n"
                "likely that malloc failed. Aborting computation.\n");

        /*  Free all of the memory allocated to the polynomials.              */
        tmpl_PolynomialZ_Destroy(&P);
        tmpl_PolynomialZ_Destroy(&Q);
        return -1;
    }

    /*  Check for errors as well.                                             */
    if ((P->error_occurred) || (Q->error_occurred))
    {
        fprintf(stderr,
                "tmpl_Create_Zero_PolynomialZ returned a pointer with the\n"
                "error_occurred Boolean set to True. It is likely calloc\n"
                "failed. Aborting computation.\n");

        /*  Free all of the memory allocated to the polynomials.              */
        tmpl_PolynomialZ_Destroy(&P);
        tmpl_PolynomialZ_Destroy(&Q);
        return -1;
    }

    /*  We'll set P to the polynomial x^8 - 1.                                */
    P->coeffs[0] = -1L;
    P->coeffs[8] = 1L;

    /*  We'll set Q to the polynomial x^4 + 1.                                */
    Q->coeffs[0] = 1L;
    Q->coeffs[4] = 1L;

    /*  Create an empty polynomial to store the sum in.                       */
    sum = tmpl_PolynomialZ_Create_Empty();

    /*  tmpl_PolynomialZ_Create_Empty returns NULL if malloc fails. Check for *
     *  this to avoid segmentation faults.                                    */
    if (sum == NULL)
    {
        fprintf(stderr,
                "tmpl_PolynomialZ_Create_Empty returned a NULL pointer.\n"
                "It is likely that malloc failed. Aborting computation.\n");

        /*  Free all of the memory allocated to the polynomials.              */
        tmpl_PolynomialZ_Destroy(&P);
        tmpl_PolynomialZ_Destroy(&Q);
        return -1;
    }

    /*  Compute the sum of P and Q, and store it in sum.                      */
    tmpl_PolynomialZ_Add(P, Q, sum);

    /*  Check if addition failed.                                             */
    if (sum->error_occurred)
    {
        fprintf(stderr,
                "tmpl_PolynomialZ_Add set the error_occurred Boolean to true\n"
                "for the sum. It is likely malloc or realloc failed.\n"
                "Aborting computation.\n");

        /*  Free all of the memory allocated to the polynomials.              */
        tmpl_PolynomialZ_Destroy(&P);
        tmpl_PolynomialZ_Destroy(&Q);
        tmpl_PolynomialZ_Destroy(&sum);
        return -1;
    }

    /*  Get the string form of the polynomials.                               */
    Pstr = tmpl_PolynomialZ_Get_String(P);

    /*  Check if the output string is NULL.                                   */
    if (Pstr == NULL)
    {
        fprintf(stderr,
                "tmpl_PolynomialZ_Get_String returned NULL. It is likely\n"
                "malloc or realloc failed. Aborting.\n");

        /*  Free all of the memory allocated to the polynomials.              */
        tmpl_PolynomialZ_Destroy(&P);
        tmpl_PolynomialZ_Destroy(&Q);
        tmpl_PolynomialZ_Destroy(&sum);
    }

    Qstr = tmpl_PolynomialZ_Get_String(Q);

    /*  Check if the output string is NULL.                                   */
    if (Qstr == NULL)
    {
        fprintf(stderr,
                "tmpl_PolynomialZ_Get_String returned NULL. It is likely\n"
                "malloc or realloc failed. Aborting.\n");

        /*  Free the memory allocated for Pstr, since                         *
         *  tmpl_PolynomialZ_Get_String was successfully called on it.        */
        free(Pstr);

        /*  Free all of the memory allocated to the polynomials.              */
        tmpl_PolynomialZ_Destroy(&P);
        tmpl_PolynomialZ_Destroy(&Q);
        tmpl_PolynomialZ_Destroy(&sum);
    }

    sumstr = tmpl_PolynomialZ_Get_String(sum);

    /*  Check if the output string is NULL.                                   */
    if (sumstr == NULL)
    {
        fprintf(stderr,
                "tmpl_PolynomialZ_Get_String returned NULL. It is likely\n"
                "malloc or realloc failed. Aborting.");

        /*  Free the memory allocated for Pstr and Qstr since                 *
         *  tmpl_PolynomialZ_Get_String was successfully called on them.      */
        free(Pstr);
        free(Qstr);

        /*  Free all of the memory allocated to the polynomials.              */
        tmpl_PolynomialZ_Destroy(&P);
        tmpl_PolynomialZ_Destroy(&Q);
        tmpl_PolynomialZ_Destroy(&sum);
    }

    /*  Print the result.                                                     */
    fprintf(stderr, "(%s) + (%s) = %s\n\n", Pstr, Qstr, sumstr);

    /*  Free the memory for the strings since we're done with them.           */
    free(sumstr);
    free(Qstr);
    free(Pstr);

    /*  Test the tmpl_PolynomialZ_Print_String, which prints the polynomial   *
     *  directly to a FILE pointer. Print to stderr.                          */
    fprintf(stderr, "Trying out tmpl_PolynomialZ_Print_String:\n");

    fprintf(stderr, "P = ");
    tmpl_PolynomialZ_Print_String(stderr, P);
    fprintf(stderr, "\n");

    fprintf(stderr, "Q = ");
    tmpl_PolynomialZ_Print_String(stderr, Q);
    fprintf(stderr, "\n");

    fprintf(stderr, "P + Q = ");
    tmpl_PolynomialZ_Print_String(stderr, sum);
    fprintf(stderr, "\n");

    /*  Free all of the memory in the polynomial pointers.                    */
    tmpl_PolynomialZ_Destroy(&P);
    tmpl_PolynomialZ_Destroy(&Q);
    tmpl_PolynomialZ_Destroy(&sum);
    return 0;
}
/*  End of main.                                                              */
