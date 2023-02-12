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

/*  free is declared here.                                                    */
#include <stdlib.h>

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Function prototype and polynomial typedefs are here.                      */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for freeing all memory in a polynomial.                          */
void tmpl_IntPolynomial_Destroy(tmpl_IntPolynomial *poly)
{
    /*  If the input is NULL there is nothing to be done.                     */
    if (!poly)
        return;

    /*  If the coefficients are also NULL there is nothing to be done.        */
    if (poly->coeffs)
        free(poly->coeffs);

    /*  If an error occurred, the error_message variable may have been set.   *
     *  Check if this data also needs to be freed.                            */
    if (poly->error_message)
        free(poly->error_message);

    /*  Set the pointers to NULL to avoid trying to free them twice.          */
    poly->coeffs = NULL;
    poly->error_message = NULL;

    /*  Set the remaining variables to their default zero values.             */
    poly->degree = (size_t)0;
    poly->error_occurred = tmpl_False;
    return;
}
/*  End of tmpl_IntPolynomial_Destroy.                                        */
