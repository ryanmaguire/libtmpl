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
 *                          tmpl_init_intpolynomial                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Initialize a polynomial by setting variables to their zero values.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Init                                               *
 *  Purpose:                                                                  *
 *      Initialize a polynomial by setting pointers to NULL and variables to  *
 *      their default zero values.                                            *
 *  Arguments:                                                                *
 *      poly (tmpl_IntPolynomial *):                                          *
 *          A pointer to the polynomial that is to be initialized.            *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Set all variables to their zero values.                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard library file where NULL is provided.                     *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  3.) tmpl_polynomial_integer.h:                                            *
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

/*  size_t data type and NULL are defined here.                               */
#include <stddef.h>

/*  Booleans declared here.                                                   */
#include <libtmpl/include/tmpl_bool.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for initializing a polynomial and setting all of its variables.  */
void tmpl_IntPolynomial_Init(tmpl_IntPolynomial *poly)
{
    /*  Check if the pointer is NULL before trying to access it.              */
    if (!poly)
        return;

    /*  Set the pointers to NULL. Many functions check if the pointers        *
     *  are NULL before trying to free them or access their data. Having them *
     *  initialized to NULL helps prevent double free's and seg faults.       */
    poly->coeffs = NULL;
    poly->error_message = NULL;

    /*  Set the remaining variables to their zero values.                     */
    poly->degree = (size_t)0;
    poly->error_occurred = tmpl_False;
}
/*  End of tmpl_IntPolynomial_Init.                                           */
