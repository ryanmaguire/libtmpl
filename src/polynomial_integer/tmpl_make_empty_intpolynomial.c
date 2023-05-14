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
 *                       tmpl_make_empty_intpolynomial                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Converts an already initialized polynomial to an empty polynomial.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Make_Empty                                         *
 *  Purpose:                                                                  *
 *      Converts a polynomial into an empty polynomial (NULL coefficients).   *
 *  Arguments:                                                                *
 *      poly (tmpl_IntPolynomial *):                                          *
 *          A pointer to the polynomial that is to be emptied.                *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      free (stdlib.h):                                                      *
 *          Free data allocated by malloc, calloc, or realloc.                *
 *  Method:                                                                   *
 *      Free data if necessary and set coefficients pointer to NULL.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library file where free is provided.                     *
 *  2.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 27, 2023                                                *
 ******************************************************************************/

/*  free function is given here.                                              */
#include <stdlib.h>

/*  Function prototype and polynomial typedefs.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for converting a polynomial into an empty polynomial.            */
void tmpl_IntPolynomial_Make_Empty(tmpl_IntPolynomial *poly)
{
    /*  If the input is NULL there is nothing to be done.                     */
    if (!poly)
        return;

    /*  Similarly consider a flawed polynomial to be an error, return.        */
    if (poly->error_occurred)
        return;

    /*  If the polynomial had data allocated free before setting to NULL.     */
    if (poly->coeffs)
        free(poly->coeffs);

    /*  Make the polynomial "empty" by setting the pointer to NULL.           */
    poly->coeffs = NULL;
    poly->degree = (size_t)0;
}
/*  End of tmpl_IntPolynomial_Make_Empty.                                     */
