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
 *                         tmpl_destroy_intpolynomial                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Free all memory associated with a polynomial.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Destroy                                            *
 *  Purpose:                                                                  *
 *      Free all memory in a tmpl_IntPolynomial and set pointers to NULL.     *
 *  Arguments:                                                                *
 *      poly (tmpl_IntPolynomial * const):                                    *
 *          A pointer to the polynomial that is to be destroyed.              *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdlib.h:                                                             *
 *          free:                                                             *
 *              Free's data allocated by malloc, calloc, or realloc.          *
 *  Method:                                                                   *
 *      Check for non-NULL pointers and free them. Then set these pointers to *
 *      NULL to prevent the possibility of double-free's.                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_free.h:                                                          *
 *          Header file with the TMPL_FREE macro for safely freeing data.     *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
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
 *  2025/12/03: Ryan Maguire                                                  *
 *      Removed free for error_message, variable is now declared const.       *
 *      Replaced free with TMPL_FREE macro.                                   *
 ******************************************************************************/

/*  TMPL_FREE macro for safely freeing and nullifying a pointer found here.   */
#include <libtmpl/include/compat/tmpl_free.h>

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Integer polynomial typedef provided here.                                 */
#include <libtmpl/include/types/tmpl_polynomial_int.h>

/*  Forward declaration / function prototype.                                 */
extern void tmpl_IntPolynomial_Destroy(tmpl_IntPolynomial *const poly);

/*  Function for freeing all memory in a polynomial.                          */
void tmpl_IntPolynomial_Destroy(tmpl_IntPolynomial *const poly)
{
    /*  If the input is NULL there is nothing to be done.                     */
    if (!poly)
        return;

    /*  Safely free the data and then set it to NULL to avoid double free's.  */
    TMPL_FREE(poly->coeffs);

    /*  The error_message variable is a const pointer, we do not need to free *
     *  it, simply set it to NULL. Since we are destroying the polynomial,    *
     *  any previous error message is now irrelevant.                         */
    poly->error_message = NULL;

    /*  Set the remaining variables to their default zero values.             */
    poly->degree = 0;
    poly->error_occurred = tmpl_False;
}
/*  End of tmpl_IntPolynomial_Destroy.                                        */
