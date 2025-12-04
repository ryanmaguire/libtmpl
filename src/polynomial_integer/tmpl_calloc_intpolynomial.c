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
 *      stdlib.h:                                                             *
 *          calloc:                                                           *
 *              Creates an array and initializes all elements to zero.        *
 *  Method:                                                                   *
 *      Call calloc and check for errors. Set other variables to zero values. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  2.) tmpl_calloc.h:                                                        *
 *          Header providing TMPL_CALLOC.                                     *
 *  3.) tmpl_polynomial_int.h:                                                *
 *          Header where the tmpl_IntPolynomial typedef is given.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 8, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/25: Ryan Maguire                                                  *
 *      Added doc-string and comments.                                        *
 ******************************************************************************/

/*  TMPL_CALLOC macro found here.                                             */
#include <libtmpl/include/compat/tmpl_calloc.h>

/*  tmpl_Bool, tmpl_False, and tmpl_True are given here.                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Integer polynomial typedef provided here.                                 */
#include <libtmpl/include/types/tmpl_polynomial_int.h>

/*  Forward declaration / function prototype.                                 */
extern tmpl_IntPolynomial tmpl_IntPolynomial_Calloc(const size_t length);

/*  Function for creating a polynomial and setting all coefficients to zero.  */
tmpl_IntPolynomial tmpl_IntPolynomial_Calloc(const size_t length)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IntPolynomial poly;

    /*  Special case. If length = 0 the output is the empty polynomial.       */
    if (length == 0)
    {
        poly.degree = 0;
        poly.coeffs = NULL;
        poly.error_occurred = tmpl_False;
        poly.error_message = NULL;
        return poly;
    }

    /*  length is positive so try to allocate and set to zero this many terms.*/
    poly.coeffs = TMPL_CALLOC(signed int, length);

    /*  calloc returns NULL on failure. Check for this.                       */
    if (!poly.coeffs)
    {
        /*  Set the degree to zero and create an error message.               */
        poly.degree = 0;
        poly.coeffs = NULL;
        poly.error_occurred = tmpl_True;
        poly.error_message =
            "\nError Encountered: libtmpl\n"
            "    tmpl_IntPolynomial_Calloc\n\n"
            "calloc failed and returned NULL. Aborting.\n\n";
    }

    /*  Otherwise initialize all error variables to zero and set the degree.  */
    else
    {
        poly.error_occurred = tmpl_False;
        poly.error_message = NULL;
        poly.degree = length - 1;
    }

    return poly;
}
/*  End of tmpl_IntPolynomial_Calloc.                                         */
