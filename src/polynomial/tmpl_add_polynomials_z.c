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
 *                          tmpl_add_polynomials_z                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for adding two elements of Z[x].                                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialZ_Add                                                  *
 *  Purpose:                                                                  *
 *      Add two polynomials in Z[x].                                          *
 *  Arguments:                                                                *
 *      P (tmpl_PolynomialZ *):                                               *
 *          A pointer to the first polynomial.                                *
 *      Q (tmpl_PolynomialZ *):                                               *
 *          A pointer to the second polynomial.                               *
 *      sum (tmpl_PolynomialZ *):                                             *
 *          A pointer to the resulting sum of P and Q.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      malloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory.                  *
 *      realloc (stdlib.h):                                                   *
 *          Standard library function for re-allocating memory.               *
 *  Method:                                                                   *
 *      Add the coefficients term by term.                                    *
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

/*  Function for adding two polynomials in Z[x].                              */
void
tmpl_PolynomialZ_Add(tmpl_PolynomialZ *P,
                     tmpl_PolynomialZ *Q,
                     tmpl_PolynomialZ *sum)
{
    /*  Declare a variable for indexing.                                      */
    unsigned long int n;

    /*  Two polynomial pointers for ordering the inputs in terms of degree.   */
    tmpl_PolynomialZ *first, *second;

    /*  Temporary variable used in case realloc is needed.                    */
    signed long int *tmp;

    /*  If sum is NULL, nothing can be done.                                  */
    if (sum == NULL)
        return;

    /*  Similarly if the sum pointer has error_occurred set to true, abort    */
    if (sum->error_occurred)
        return;

    /*  If either P or Q are NULL, nothing can be done. Store an error        *
     *  message in sum.                                                       */
    if ((P == NULL) || (Q == NULL))
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Add\n\n"
            "One of the input polynomials is NULL. Aborting.\n"
        );
        return;
    }

    /*  If either P or Q has a NULL coeffs pointer, nothing can be done.      */
    if ((P->coeffs == NULL) || (Q->coeffs == NULL))
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Add\n\n"
            "One of the inputs has a NULL coeffs pointer. Aborting.\n"
        );
        return;
    }

    /*  Lastly, if one of the inputs has error_occurred set to true it may    *
     *  not be safe to proceed. Check for this.                               */
    if ((P->error_occurred) || (Q->error_occurred))
    {
        sum->error_occurred = tmpl_True;
        sum->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Add\n\n"
            "One of the inputs has its error_occurred Boolean set to true.\n"
        );
        return;   
    }

    /*  Order the polynomials in terms of their degree.                       */
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

    /*  If the sum coeffs pointer is NULL, allocate memory for it.            */
    if (sum->coeffs == NULL)
    {
        /*  The degree of the sum is the degree of the larger of the two      *
         *  polynomials. That is, deg(P+Q) = max(deg(P), deg(Q)).             */
        sum->degree = second->degree;
        sum->coeffs = malloc(sizeof(*sum->coeffs) * (sum->degree + 1UL));

        /*  Check if malloc failed.                                           */
        if (sum->coeffs == NULL)
        {
            sum->error_occurred = tmpl_True;
            sum->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Add\n\n"
                "malloc failed to allocate memory for sum->coeffs.\n"
            );
            return;  
        }
    }

    /*  If sum does not have the correct size for it's degree, reallocate     *
     *  the coeffs pointer to be the max of the two others.                   */
    else if (sum->degree != second->degree)
    {
        sum->degree = second->degree;
        tmp = realloc(sum->coeffs, sizeof(*sum->coeffs) * (sum->degree + 1UL));

        /*  Check if realloc failed.                                          */
        if (tmp == NULL)
        {
            sum->error_occurred = tmpl_True;
            sum->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Multiply\n\n"
                "realloc failed to allocate memory for sum->coeffs.\n"
            );
            return;
        }

        /*  If realloc did not fail, have the coeffs pointer set to tmp.      */
        else
            sum->coeffs = tmp;
    }

    /*  For zero up to the degree of the smaller polynomial, polynomial       *
     *  addition is done component-wise.                                      */
    for (n = 0UL; n <= first->degree; ++n)
        sum->coeffs[n] = first->coeffs[n] + second->coeffs[n];

    /*  For the rest of the coefficients, the sum is simply the coefficient   *
     *  of the larger degree polynomial.                                      */
    for (n = first->degree + 1UL; n <= second->degree; ++n)
        sum->coeffs[n] = second->coeffs[n];

    return;
}
/*  End of tmpl_PolynomialZ_Add.                                              */
