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
 *                        tmpl_polynomials_z_set_term                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for setting the coefficient of a given term.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialZ_Set_Term                                             *
 *  Purpose:                                                                  *
 *      Add two polynomials in Z[x].                                          *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to the polynomial.                                      *
 *      term (unsigned long int):                                             *
 *          The term that is the be set.                                      *
 *      coefficient (signed long int):                                        *
 *          The value being set for the given term.                           *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      calloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory and initializing  *
 *          all of it to zero.                                                *
 *      realloc (stdlib.h):                                                   *
 *          Standard library function for re-allocating memory.               *
 *  Method:                                                                   *
 *      Check for errors, set the coefficient for the requested term if       *
 *      there are none. If the term has degree greater than the degree of the *
 *      polynomial, realloc will be called to resize the coeffs pointer. The  *
 *      terms between poly->degree and term will be set to zero.              *
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

/*  Function for setting the coefficient of a given term in a polynomial.     */
void
tmpl_PolynomialZ_Set_Term(tmpl_PolynomialZ *poly,
                          unsigned long int term,
                          signed long int coefficient)
{
    /*  Variable for indexing.                                                */
    unsigned long int n;

    /*  Temporary variable in case realloc is needed.                         */
    signed long int *tmp;

    /*  If the input is NULL, abort.                                          */
    if (poly == NULL)
        return;

    /*  Similarly if an error has occurred.                                   */
    if (poly->error_occurred)
        return;

    /*  If the coeffs pointer is NULL, allocate memory and set the value.     */
    if (poly->coeffs == NULL)
    {
        poly->coeffs = calloc(sizeof(*poly->coeffs), term + 1UL);

        /*  Check if calloc failed.                                           */
        if (poly->coeffs == NULL)
        {
            poly->error_occurred = tmpl_True;
            poly->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Set_Term\n\n"
                "calloc failed and returned NULL.\n"
            );  
        }

        /*  Set the "term" value to the requested coefficient.                */
        poly->coeffs[term] = coefficient;

        /*  Lastly, reset the degree.                                         */
        poly->degree = term;
    }

    /*  If the term is beyond the degree of the polynomial, reallocate memory *
     *  and make the coefficients array larger.                               */
    else if (poly->degree < term)
    {
        tmp = realloc(poly->coeffs, sizeof(*poly->coeffs) * (term + 1UL));

        /*  Check if realloc failed.                                          */
        if (tmp == NULL)
        {
            poly->error_occurred = tmpl_True;
            poly->error_message = tmpl_strdup(
                "Error Encountered: libtmpl\n"
                "\r\ttmpl_PolynomialZ_Set_Term\n\n"
                "realloc failed and returned NULL.\n"
            );   
        }

        /*  If not, set poly->coeffs to tmp.                                  */
        else
            poly->coeffs = tmp;

        /*  Set the values between poly->degree and term to zero.             */
        for (n = poly->degree + 1UL; n < term; ++n)
            poly->coeffs[n] = 0L;

        /*  And set the value of the term to the requested coefficient.       */
        poly->coeffs[term] = coefficient;

        /*  Lastly, reset the degree.                                         */
        poly->degree = term;
    }

    /*  Otherwise, simply set the coefficient.                                */
    else
        poly->coeffs[term] = coefficient;

    return;
}
