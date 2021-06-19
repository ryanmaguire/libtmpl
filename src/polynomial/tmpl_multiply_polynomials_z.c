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
 *                        tmpl_create_zero_polynomial_z                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for creating a degree N polynomial in Z[x] with all coefficients *
 *      set to zero. Mathematically this is the same thing as the zero        *
 *      polynomial, but computer-wise the coefficients array will have more   *
 *      memory allocated to it.                                               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Create_Zero_PolynomialZ                                          *
 *  Purpose:                                                                  *
 *      Creates a polynomial in Z[x] with all coefficients set to zero.       *
 *  Arguments:                                                                *
 *      degree (unsigned long int):                                           *
 *          The degree of the polynomial. The array of coefficients will have *
 *          degree + 1 many elements allocated to it, and set to zero.        *
 *  Output:                                                                   *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          The polynomial 0 + 0 x + ... + 0 x^degree.                        *
 *  Called Functions:                                                         *
 *      malloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory.                  *
 *      calloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory and initializing  *
 *          all of the elements to zero.                                      *
 *  Method:                                                                   *
 *      Allocate memory for the polynomial pointer with malloc, and allocate  *
 *      and initialize to zero memory for the pointer to the coefficients     *
 *      array using calloc.                                                   *
 *  Notes:                                                                    *
 *      If malloc fails, a NULL pointer is returned. If malloc succeeds, but  *
 *      calloc fails, the error_occurred Boolean is set to true and an        *
 *      error message is stored in the struct. Check these before using       *
 *      the polynomial.                                                       *
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

/*  malloc and calloc are found here.                                         */
#include <stdlib.h>

/*  Function for creating a polynomial with all coefficients set to zero.     */
void
tmpl_PolynomialZ_Multiply(tmpl_PolynomialZ *P,
                          tmpl_PolynomialZ *Q,
                          tmpl_PolynomialZ *prod)
{
    /*  Declare a variable for indexing.                                      */
    unsigned long int n, k;

    /*  Two polynomial pointers for ordering the inputs in terms of degree.   */
    tmpl_PolynomialZ *first, *second;

    /*  Temporary variable used in case realloc is needed.                    */
    signed long int *tmp;

    /*  If prod is NULL, nothing can be done.                                 */
    if (prod == NULL)
        return;

    /*  If either P or Q are NULL, nothing can be done. Store an error        *
     *  message in prod.                                                      */
    if ((P == NULL) || (Q == NULL))
    {
        prod->error_occurred = tmpl_True;
        prod->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Multiply\n\n"
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
            "\r\ttmpl_PolynomialZ_Multiply\n\n"
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
            "\r\ttmpl_PolynomialZ_Multiply\n\n"
            "One of the inputs has its error_occurred Boolean set to true.\n"
        );
        return;   
    }

    /*  If the prod coeffs pointer is NULL, allocate memory for it.           */
    if (prod->coeffs == NULL)
    {
        prod->degree = P->degree + Q->degree;
        prod->coeffs = malloc(sizeof(*prod->coeffs) * prod->degree + 1UL);

        /*  Check if malloc failed.                                           */
        if (prod->coeffs == NULL)
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Multiply\n\n"
                "malloc failed to allocate memory for prod->coeffs.\n"
            );
            return;  
        }
    }

    /*  If prod does not have the correct size for it's degree, reallocate    *
     *  the coeffs pointer to be the sum of the two others.                   */
    else if (prod->degree != (P->degree + Q->degree))
    {
        prod->degree = P->degree + Q->degree;
        tmp = realloc(prod->coeffs, sizeof(*prod->coeffs) * prod->degree + 1UL);

        /*  Check if realloc failed.                                          */
        if (tmp == NULL)
        {
            prod->error_occurred = tmpl_True;
            prod->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Multiply\n\n"
                "realloc failed to allocate memory for prod->coeffs.\n"
            );
            return;
        }
        prod->coeffs = tmp;
    }

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

    /*  Perform the Cauchy product on P and Q.                                */
    for (n = 0UL; n < first->degree; ++n)
    {
        prod->coeffs[n] = first->coeffs[n] * second->coeffs[0];
        for (k = 1UL; k <= n; ++k)
            prod->coeffs[n] += first->coeffs[n-k] * second->coeffs[k];
    }

    for (n = first->degree; n < second->degree; ++n)
    {
        prod->coeffs[n] = 0UL;
        for (k = n - first->degree; k <= n; ++k)
            prod->coeffs[n] += first->coeffs[n-k] * second->coeffs[k];
    }

    for (n = second->degree; n <= prod->degree; ++n)
    {
        prod->coeffs[n] = 0UL;
        for (k = n - first->degree; k <= second->degree; ++k)
            prod->coeffs[n] += first->coeffs[n-k] * second->coeffs[k];
    }
}
/*  End of tmpl_Create_Zero_PolynomialZ.                                      */
