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
 *                         tmpl_polynomial_z_shrink                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code to remove all zero coefficents after the largest non-zero term.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialZ_Shrink                                               *
 *  Purpose:                                                                  *
 *      Remove all coefficients that are zero after the largest non-zero term.*
 *      This reduces the memory allocated to the coeffs array. If the last    *
 *      term is non-zero, nothing is done.                                    *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to the polynomial.                                      *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      realloc (stdlib.h):                                                   *
 *          Standard library function for re-allocating memory.               *
 *  Method:                                                                   *
 *      Find the last non-zero term and reallocate the coeffs pointer.        *
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
 *  Date:       June 22, 2021                                                 *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_stdup function declared here.                                        */
#include <libtmpl/include/tmpl_string.h>

/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial.h>

/*  malloc and realloc are found here.                                        */
#include <stdlib.h>

/*  Function for removing redundant elements of a polynomials coeffs array.   */
void tmpl_PolynomialZ_Shrink(tmpl_PolynomialZ *poly)
{
    /*  Variable for indexing.                                                */
    unsigned long int last, n;

    /*  Temporary variable used in case realloc is needed.                    */
    signed long int *tmp;

    /*  If poly is NULL, there's nothing to be done.                          */
    if (poly == NULL)
        return;

    /*  If the coeffs array is empty, return.                                 */
    if (poly->coeffs == NULL)
        return;

    /*  And if an error occurred, it may not be safe to parse things. Abort.  */
    if (poly->error_occurred)
        return;

    /*  Find the last non-zero term.                                          */
    last = 0UL;
    for (n = 0UL; n <= poly->degree; ++n)
        if (poly->coeffs[n] != 0L)
            last = n;

    /*  If the highest term is non-zero, there's nothing to be done.          */
    if (last == poly->degree)
        return;

    /*  Otherwise, resize the coeffs pointer.                                 */
    tmp = realloc(poly->coeffs, sizeof(*poly->coeffs) * (last + 1UL));

    /*  Check if realloc failed.                                              */
    if (tmp == NULL)
    {
        poly->error_occurred = tmpl_True;
        poly->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_PolynomialZ_Shrink\n\n"
            "realloc failed and returned NULL.\n"
        );
        return;
    }

    /*  If realloc did not fail, set poly->coeffs to tmp.                     */
    else
        poly->coeffs = tmp;

    /*  Reset the degree and return.                                          */
    poly->degree = last;
    return;
}
/*  End of tmpl_PolynomialZ_Shrink.                                           */
