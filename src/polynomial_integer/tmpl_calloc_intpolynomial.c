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
 ******************************************************************************
 *                         tmpl_calloc_intpolynomial                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Allocates memory for a polynomial and sets entries to zero.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Calloc                                             *
 *  Purpose:                                                                  *
 *      Creates a polynomial, allocates memory for the coeffs pointer, and    *
 *      initializes all entries to zero.                                      *
 *  Arguments:                                                                *
 *      length (size_t):                                                      *
 *          The number of elements to be allocated in the coeffs array.       *
 *  Outputs:                                                                  *
 *      poly (tmpl_IntPolynomial):                                            *
 *          A polynomial with its coeffs pointer allocated memory.            *
 *  Called Functions:                                                         *
 *      calloc (stdlib.h):                                                    *
 *          Creates an array an initializes all elements to zero.             *
 *      tmpl_strdup (tmpl_string.h):                                          *
 *          Duplicates a string. Equivalent to the POSIX function strdup.     *
 *  Method:                                                                   *
 *      Call calloc and check for errors.                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library file where calloc is provided.                   *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  3.) tmpl_string.h:                                                        *
 *          Header file where tmpl_strdup is declared.                        *
 *  4.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 8, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/25: Ryan Maguire                                                  *
 *      Added doc-string and comments.                                        *
 ******************************************************************************/

/*  calloc is here.                                                           */
#include <stdlib.h>

/*  tmpl_Bool, tmpl_False, and tmpl_True are given here.                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup found here.                                                   */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototypes contained here.               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for creating a polynomial and setting all coefficients to zero.  */
tmpl_IntPolynomial tmpl_IntPolynomial_Calloc(size_t length)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IntPolynomial poly;

    /*  Special case. If length = 0 the output is the empty polynomial.       */
    if (length == (size_t)0)
    {
        poly.degree = (size_t)0;
        poly.coeffs = NULL;
        poly.error_occurred = tmpl_False;
        poly.error_message = NULL;
        return poly;
    }

    /*  length is positive so try to allocate and set to zero this many terms.*/
    poly.coeffs = calloc(sizeof(*poly.coeffs), length);

    /*  calloc returns NULL on failure. Check for this.                       */
    if (!poly.coeffs)
    {
        /*  Set the degree to zero and create an error message.               */
        poly.degree = (size_t)0;
        poly.coeffs = NULL;
        poly.error_occurred = tmpl_True;
        poly.error_message = tmpl_strdup(
            "\nError Encountered: libtmpl\n"
            "    tmpl_IntPolynomial_Calloc\n\n"
            "calloc failed and returned NULL. Aborting.\n\n"
        );
    }

    /*  Otherwise initialize all error variables to zero and set degree.      */
    else
    {
        poly.error_occurred = tmpl_False;
        poly.error_message = NULL;
        poly.degree = length - (size_t)1;
    }

    return poly;
}
/*  End of tmpl_IntPolynomial_Calloc.                                         */
