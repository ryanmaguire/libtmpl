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
 *                        tmpl_make_zero_intpolynomial                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Converts an already initialized polynomial to a zero polynomial.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Make_Zero                                          *
 *  Purpose:                                                                  *
 *      Converts a polynomial into an zero polynomial (zero coefficient).     *
 *  Arguments:                                                                *
 *      poly (tmpl_IntPolynomial *):                                          *
 *          A pointer to the polynomial that is to be made zero.              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      realloc (stdlib.h):                                                   *
 *          Resizes an array.                                                 *
 *  Method:                                                                   *
 *      Resize the coeffs array to one element and set it to zero.            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library file where realloc is provided.                  *
 *  2.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 27, 2023                                                *
 ******************************************************************************/

/*  realloc is provided here.                                                 */
#include <stdlib.h>

/*  tmpl_strdup given here.                                                   */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for converting a polynomial into a zero polynomial.              */
void tmpl_IntPolynomial_Make_Zero(tmpl_IntPolynomial *poly)
{
    /*  Temporary pointer for calling realloc without possible memory leaks.  */
    void *tmp;

    /*  If the pointer is NULL there is nothing to be done.                   */
    if (!poly)
        return;

    /*  Similarly if the input polynomial is flawed, consider this an error.  */
    if (poly->error_occurred)
        return;

    /*  The zero polynomial can be efficiently represented with a single      *
     *  element coefficient array containing zero. Try to resize the array.   */
    tmp = realloc(poly->coeffs, sizeof(*poly->coeffs));

    /*  realloc returns NULL on failure. Check this.                          */
    if (!tmp)
    {
        /*  Set an error message and abort the computation.                   */
        poly->error_occurred = tmpl_True;
        poly->error_message = tmpl_strdup(
            "\nError Encountered:\n"
            "    tmpl_IntPolynomial_Make_Zero\n\n"
            "realloc failed and returned NULL. Aborting.\n\n"
        );

        return;
    }

    /*  Otherwise set the data pointer and make the coefficient zero.         */
    else
    {
        poly->coeffs = tmp;
        poly->degree = (size_t)0;
        poly->coeffs[0] = 0;
    }
}
/*  End of tmpl_IntPolynomial_Make_Zero.                                      */
