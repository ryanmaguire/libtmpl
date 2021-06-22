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
 *                        tmpl_polynomial_z_subtract                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for subtracting two elements of Z[x].                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialZ_Subtract                                             *
 *  Purpose:                                                                  *
 *      Subtract two polynomials in Z[x].                                     *
 *  Arguments:                                                                *
 *      P (tmpl_PolynomialZ *):                                               *
 *          A pointer to the first polynomial.                                *
 *      Q (tmpl_PolynomialZ *):                                               *
 *          A pointer to the second polynomial.                               *
 *      diff (tmpl_PolynomialZ *):                                            *
 *          A pointer to the resulting difference of P and Q.                 *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      malloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory.                  *
 *      realloc (stdlib.h):                                                   *
 *          Standard library function for re-allocating memory.               *
 *  Method:                                                                   *
 *      Subtract the coefficients term by term.                               *
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
 *          Header file where tmpl_strdup is declared. This is a clone of     *
 *          strdup function, which is a part of the POSIX C standard, but not *
 *          part of the C standard library.                                   *
 *  2.) tmpl_polynomial.h:                                                    *
 *          Header file containing the definition of polynomials and the      *
 *          functions prototype.                                              *
 *  3.) stdlib.h:                                                             *
 *          C Standard library header file containing malloc and realloc.     *
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
 *  Date:       June 19, 2021                                                 *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_stdup function declared here.                                        */
#include <libtmpl/include/tmpl_string.h>

/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial.h>

/*  malloc and realloc are found here.                                        */
#include <stdlib.h>

/*  Function for subtracting two polynomials in Z[x].                         */
void
tmpl_PolynomialZ_Subtract(tmpl_PolynomialZ *P,
                          tmpl_PolynomialZ *Q,
                          tmpl_PolynomialZ *diff)
{
    /*  Declare a variable for indexing.                                      */
    unsigned long int n;

    /*  Factor used later for the sign.                                       */
    signed long int factor;

    /*  Two polynomial pointers for ordering the inputs in terms of degree.   */
    tmpl_PolynomialZ *first, *second;

    /*  Temporary variable used in case realloc is needed.                    */
    signed long int *tmp;

    /*  If diff is NULL, nothing can be done.                                  */
    if (diff == NULL)
        return;

    /*  Similarly if the diff pointer has error_occurred set to true, abort   */
    if (diff->error_occurred)
        return;

    /*  If either P or Q are NULL, nothing can be done. Store an error        *
     *  message in diff.                                                      */
    if ((P == NULL) || (Q == NULL))
    {
        diff->error_occurred = tmpl_True;
        diff->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Subtract\n\n"
            "One of the input polynomials is NULL. Aborting.\n"
        );
        return;
    }

    /*  If either P or Q has a NULL coeffs pointer, nothing can be done.      */
    if ((P->coeffs == NULL) || (Q->coeffs == NULL))
    {
        diff->error_occurred = tmpl_True;
        diff->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Subtract\n\n"
            "One of the inputs has a NULL coeffs pointer. Aborting.\n"
        );
        return;
    }

    /*  Lastly, if one of the inputs has error_occurred set to true it may    *
     *  not be safe to proceed. Check for this.                               */
    if ((P->error_occurred) || (Q->error_occurred))
    {
        diff->error_occurred = tmpl_True;
        diff->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Subtract\n\n"
            "One of the inputs has its error_occurred Boolean set to true.\n"
        );
        return;   
    }

    /*  Order the polynomials in terms of their degree. For P - Q, if P has   *
     *  a higher degree the last terms of P - Q will be P. If Q has a higher  *
     *  degree, the last terms will be -Q. Store +1 or -1 in factor.          */
    if (P->degree <= Q->degree)
    {
        first = P;
        second = Q;
        factor = -1L;
    }
    else
    {
        first = Q;
        second = P;
        factor = 1L;
    }

    /*  If the diff coeffs pointer is NULL, allocate memory for it.           */
    if (diff->coeffs == NULL)
    {
        /*  The degree of the differernce is the degree of the larger of the  *
         *  two polynomials. That is, deg(P-Q) = max(deg(P), deg(Q)).         */
        diff->degree = second->degree;
        diff->coeffs = malloc(sizeof(*diff->coeffs) * (diff->degree + 1UL));

        /*  Check if malloc failed.                                           */
        if (diff->coeffs == NULL)
        {
            diff->error_occurred = tmpl_True;
            diff->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Subtract\n\n"
                "malloc failed to allocate memory for diff->coeffs.\n"
            );
            return;  
        }
    }

    /*  If diff does not have the correct size for it's degree, reallocate    *
     *  the coeffs pointer to be the max of the two others.                   */
    else if (diff->degree != second->degree)
    {
        diff->degree = second->degree;
        tmp = realloc(diff->coeffs, sizeof(*diff->coeffs)*(diff->degree + 1UL));

        /*  Check if realloc failed.                                          */
        if (tmp == NULL)
        {
            diff->error_occurred = tmpl_True;
            diff->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Subtract\n\n"
                "realloc failed to allocate memory for diff->coeffs.\n"
            );
            return;
        }

        /*  If realloc did not fail, have the coeffs pointer set to tmp.      */
        else
            diff->coeffs = tmp;
    }

    /*  For zero up to the degree of the smaller polynomial, polynomial       *
     *  subtraction is done component-wise.                                   */
    for (n = 0UL; n <= first->degree; ++n)
        diff->coeffs[n] = P->coeffs[n] - Q->coeffs[n];

    /*  For the rest of the coefficients, the diff is simply +/- the          *
     *  coefficients of the larger degree polynomial.                         */
    for (n = first->degree + 1UL; n <= second->degree; ++n)
        diff->coeffs[n] = factor*second->coeffs[n];

    /*  If P and Q have the same degree and the last coefficients are equal,  *
     *  diff->degree will be less than max(P->degree, Q->degree). Check this. */
    if (diff->coeffs[diff->degree] == 0L)
        tmpl_PolynomialZ_Shrink(diff);

    return;
}
/*  End of tmpl_PolynomialZ_Subtract.                                         */
