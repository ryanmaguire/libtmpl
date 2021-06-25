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
 *                        tmpl_polynomial_q_multiply                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for multiplying two polynomials in Q[x].                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialQ_Multiply                                             *
 *  Purpose:                                                                  *
 *      Multiply two polynomials in Q[x].                                     *
 *  Arguments:                                                                *
 *      P (tmpl_PolynomialQ *):                                               *
 *          A pointer to the first polynomial.                                *
 *      Q (tmpl_PolynomialQ *):                                               *
 *          A pointer to the second polynomial.                               *
 *      prod (tmpl_PolynomialQ *):                                            *
 *          A pointer to the resulting product of P and Q.                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      malloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory.                  *
 *      realloc (stdlib.h):                                                   *
 *          Standard library function for re-allocating memory.               *
 *  Method:                                                                   *
 *      Use the Cauchy product formula to multiply the polynomials.           *
 *  Notes:                                                                    *
 *      It is assumed none of the three polynomial pointers are NULL. If they *
 *      are, nothing is done. If malloc fails, the error_occurred Boolean is  *
 *      set to true. Similarly with realloc.                                  *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  2.) tmpl_string.h:                                                        *
 *          Header file where the tmpl_strdup function is declared. This is   *
 *          a clone of the strdup function, which is part of the POSIX        *
 *          standard library, but not the C standard library.                 *
 *  3.) tmpl_polynomial.h:                                                    *
 *          Header file containing the definition of polynomials and the      *
 *          functions prototype.                                              *
 *  4.) stdlib.h:                                                             *
 *          C Standard library header file containing malloc and calloc.      *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       June 15, 2021                                                 *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_stdup function declared here.                                        */
#include <libtmpl/include/tmpl_string.h>

/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial.h>

/*  malloc and realloc are found here.                                        */
#include <stdlib.h>

/*  Function for multiplying two polynomials.                                 */
void
tmpl_PolynomialQ_Multiply(tmpl_PolynomialQ *P,
                          tmpl_PolynomialQ *Q,
                          tmpl_PolynomialQ *prod)
{
    /*  Declare variables for indexing.                                       */
    unsigned long int n, k;

    /*  Two polynomial pointers for ordering the inputs in terms of degree.   */
    tmpl_PolynomialQ *first, *second;
    tmpl_RationalNumber *first_coeffs, *second_coeffs;
    unsigned long int first_deg, second_deg;

    /*  Temporary variable used in case realloc is needed.                    */
    tmpl_RationalNumber *tmp;

    /*  If prod is NULL, nothing can be done.                                 */
    if (prod == NULL)
        return;

    /*  Similarly if the error_occurred Boolean is true.                      */
    if (prod->error_occurred)
        return;

    /*  If either P or Q are NULL, nothing can be done. Store an error        *
     *  message in prod.                                                      */
    if ((P == NULL) || (Q == NULL))
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialQ_Multiply\n\n"
            "One of the input polynomials is NULL. Aborting.\n"
        );
        return;
    }

    /*  If either P or Q has a NULL coeffs pointer, nothing can be done.      */
    if ((P->coeffs == NULL) || (Q->coeffs == NULL))
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialQ_Multiply\n\n"
            "One of the inputs has a NULL coeffs pointer. Aborting.\n"
        );
        return;
    }

    /*  Lastly, if one of the inputs has error_occurred set to true it may    *
     *  not be safe to proceed. Check for this.                               */
    if ((P->error_occurred) || (Q->error_occurred))
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialQ_Multiply\n\n"
            "One of the inputs has its error_occurred Boolean set to true.\n"
        );
        return;   
    }

    /*  Order the polynomials by degree.                                      */
    if (P->degree <= Q->degree)
    {
        first = P;
        second = Q;
    }
    else
    {
        first = Q;
        second = P;
    }

    /*  Copy the data from first and second, rather than using them directly. *
     *  If either P or Q are also the same as the prod pointer, their coeffs  *
     *  pointers will be changed as the Cauchy sum is performed. This will    *
     *  result in the wrong values for the product polynomial. To prevent P   *
     *  and Q from being changed in transit, make copies of their data and    *
     *  work with that.                                                       */
    first_deg = first->degree;
    first_coeffs = malloc(sizeof(*first_coeffs) * (first_deg + 1UL));

    /*  Check if malloc failed.                                               */
    if (first_coeffs == NULL)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialQ_Multiply\n\n"
            "malloc failed to allocate memory for first_coeffs.\n"
        );
        return;
    }

    /*  If malloc was successful, copy the data from first.                   */
    for (n = 0UL; n <= first->degree; ++n)
        first_coeffs[n] = first->coeffs[n];

    /*  Do the same thing with the second pointer.                            */
    second_deg = second->degree;
    second_coeffs = malloc(sizeof(*second_coeffs) * (second_deg + 1UL));

    /*  Check if malloc failed.                                               */
    if (second_coeffs == NULL)
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialQ_Multiply\n\n"
            "realloc failed to allocate memory for second_coeffs.\n"
        );

        /*  Free the memory allocated to first_coeffs, since malloc was       *
         *  successful for that one.                                          */
        free(first_coeffs);
        return;
    }

    /*  Otherwise, copy the data.                                             */
    for (n = 0UL; n <= second->degree; ++n)
        second_coeffs[n] = second->coeffs[n];

    /*  If the prod coeffs pointer is NULL, allocate memory for it.           */
    if (prod->coeffs == NULL)
    {
        /*  The degree of a product is the sum of the degrees.                */
        prod->degree = first_deg + second_deg;
        prod->coeffs = malloc(sizeof(*prod->coeffs) * (prod->degree + 1UL));

        /*  Check if malloc failed.                                           */
        if (prod->coeffs == NULL)
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialQ_Multiply\n\n"
                "malloc failed to allocate memory for prod->coeffs.\n"
            );
            return;  
        }
    }

    /*  If prod does not have the correct size for it's degree, reallocate    *
     *  the coeffs pointer to be the sum of the two others.                   */
    else if (prod->degree != (first_deg + second_deg))
    {
        /*  The degree of a product is the sum of the degrees.                */
        prod->degree = first_deg + second_deg;
        tmp = realloc(prod->coeffs, sizeof(*prod->coeffs)*(prod->degree + 1UL));

        /*  Check if realloc failed.                                          */
        if (tmp == NULL)
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialQ_Multiply\n\n"
                "realloc failed to allocate memory for prod->coeffs.\n"
            );
            return;
        }

        /*  If realloc was successful, set prod->coeffs to the result.        */
        prod->coeffs = tmp;
    }

    /*  Perform the first part of the Cauchy product. We arrange coefficients *
     *  P_m, Q_n in a rectangular array. Suppose P->degree = 5 and            *
     *  Q->degree = 3, we get the following:                                  *
     *      P0*Q0 P0*Q1 P0*Q2 P0*Q3                                           *
     *      P1*Q0 P1*Q1 P1*Q2 P1*Q3                                           *
     *      P2*Q0 P2*Q1 P2*Q2 P2*Q3                                           *
     *      P3*Q0 P3*Q1 P3*Q2 P3*Q3                                           *
     *      P4*Q0 P4*Q1 P4*Q2 P4*Q3                                           *
     *      P5*Q0 P5*Q1 P5*Q2 P5*Q3                                           *
     *  The Cauchy product for infinite sums is defined by:                   *
     *      /  infty     \ /  infty     \     infty                           *
     *      |  -----     | |  -----     |     -----                           *
     *      |  \         | |  \         |     \                               *
     *      |  /     a_m | |  /     b_n |  =  /     c_n                       *
     *      |  -----     | |  -----     |     -----                           *
     *      \  m = 0     / \   n = 0    /     n = 0                           *
     *  Where:                                                                *
     *              n                                                         *
     *            -----                                                       *
     *            \                                                           *
     *      c_n = /    a_k * b_{n-k}                                          *
     *            -----                                                       *
     *            k = 0                                                       *
     *  To make this well defined for finite sums we need to limit the range  *
     *  of the sum for c_n. The first leg of this is going to be:             *
     *        00   01   02   03                                               *
     *                                                                        *
     *        10   11   12   13                                               *
     *      -----                                                             *
     *      | 20 | 21   22   23                                               *
     *      |     ----                                                        *
     *      | 30   31 | 32   33                                               *
     *      |          ----                                                   *
     *      | 40   41   42 | 43                                               *
     *      |               ----                                              *
     *      | 50   51   52   53 |                                             *
     *      --------------------                                              *
     *  Perform this part of the sum.                                         */
    for (n = 0UL; n < first_deg; ++n)
    {
        prod->coeffs[n] = tmpl_RationalNumber_Multiply(first_coeffs[n],
                                                       second_coeffs[0]);
        for (k = 1UL; k <= n; ++k)
            prod->coeffs[n] = tmpl_RationalNumber_Add(
                prod->coeffs[n],
                tmpl_RationalNumber_Multiply(first_coeffs[n-k],
                                             second_coeffs[k])
            );
    }

    /*  In the next part, the sum can't start at zero since Q does not have   *
     *  a fifth coefficient. We can pretend it does by adding 0 x^4, or we    *
     *  start the sum at 1, and then the next one starts at 2, and so on.     *
     *  This leg of the sum is the following:                                 *
     *       ----                                                             *
     *      | 00 | 01   02   03                                               *
     *      |     ----                                                        *
     *      | 10   11 | 12   13                                               *
     *      -----      ----                                                   *
     *        20 | 21   22 | 23                                               *
     *            ----      ----                                              *
     *        30   31 | 32   33 |                                             *
     *                 ----     |                                             *
     *        40   41   42 | 43 |                                             *
     *                      ----                                              *
     *        50   51   52   53                                               *
     *  Perform this part of the sum.                                         */
    for (n = first_deg; n < second_deg; ++n)
    {
        prod->coeffs[n] = tmpl_RationalNumber_Zero;
        for (k = n - first_deg; k <= n; ++k)
            prod->coeffs[n] = tmpl_RationalNumber_Add(
                prod->coeffs[n],
                tmpl_RationalNumber_Multiply(first_coeffs[n-k],
                                             second_coeffs[k])
            );
    }

    /*  In the last part, the sum can't go too high since P may not have the  *
     *  corresponding coefficient. Here we compute the following portion:     *
     *          --------------                                                *
     *      00 | 01   02   03 |                                               *
     *          ----          |                                               *
     *      10   11 | 12   13 |                                               *
     *               ----     |                                               *
     *      20   21   22 | 23 |                                               *
     *                    ----                                                *
     *      30   31   32   33                                                 *
     *                                                                        *
     *      40   41   42   43                                                 *
     *                                                                        *
     *      50   51   52   53                                                 *
     *  Perform this part of the sum.                                         */
    for (n = second_deg; n <= prod->degree; ++n)
    {
        prod->coeffs[n] = tmpl_RationalNumber_Zero;
        for (k = n - first_deg; k <= second_deg; ++k)
            prod->coeffs[n] = tmpl_RationalNumber_Add(
                prod->coeffs[n],
                tmpl_RationalNumber_Multiply(first_coeffs[n-k],
                                             second_coeffs[k])
            );
    }

    /*  Free the memory allocated to first and second.                        */
    free(first_coeffs);
    free(second_coeffs);
    return;
}
/*  End of tmpl_PolynomialQ_Multiply.                                         */
