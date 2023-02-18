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

/*  size_t data type and NULL are defined here.                               */
#include <stddef.h>

/*  Booleans declared here.                                                   */
#include <libtmpl/include/tmpl_bool.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for initializing a polynomial and setting all of its variables.  */
void tmpl_IntPolynomial_Init(tmpl_IntPolynomial *P)
{
    /*  Check if the pointer is NULL before trying to access it.              */
    if (!P)
        return;

    /*  Set the pointers to NULL. Many functions check if the pointers        *
     *  are NULL before trying to free them or access their data. Having them *
     *  initialized to NULL helps prevent double free's and seg faults.       */
    P->coeffs = NULL;
    P->error_message = NULL;

    /*  Set the remaining variables to their zero values.                     */
    P->degree = (size_t)0;
    P->error_occurred = tmpl_False;
}
/*  End of tmpl_IntPolynomial_Init.                                           */
