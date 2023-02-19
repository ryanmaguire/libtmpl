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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 8, 2023                                              *
 ******************************************************************************/

/*  TODO: Add "doc-string" above, description of function, etc.               */

/*  calloc is here.                                                           */
#include <stdlib.h>

/*  tmpl_Bool, tmpl_False, and tmpl_True are given here.                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup found here.                                                   */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototypes contained here.               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for creating a polynomial and setting all coefficients to zero.  */
tmpl_IntPolynomial tmpl_IntPolynomial_Calloc(size_t deg)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IntPolynomial P;

    /*  A degree "deg" polynomial has deg+1 coefficients since the constant   *
     *  term is included as well. Try to allocate and set to 0 deg+1 elements.*/
    P.coeffs = calloc(sizeof(*P.coeffs), deg + (size_t)1);

    /*  calloc returns NULL on failure. Check for this.                       */
    if (!P.coeffs)
    {
        /*  Set the degree to zero and create an error message.               */
        P.coeffs = NULL;
        P.degree = (size_t)0;
        P.error_occurred = tmpl_True;
        P.error_message = tmpl_strdup(
            "\nError Encountered: libtmpl\n"
            "    tmpl_IntPolynomial_Calloc\n\n"
            "calloc failed and returned NULL. Aborting.\n\n"
        );
    }

    /*  Otherwise if calloc didn't fail initialize all error variables to     *
     *  zero, and set the degree of the polynomial.                           */
    else
    {
        P.degree = deg;
        P.error_occurred = tmpl_False;
        P.error_message = NULL;
    }

    return P;
}
/*  End of tmpl_IntPolynomial_Calloc.                                         */
