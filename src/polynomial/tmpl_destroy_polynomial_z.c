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
 *                         tmpl_destroy_polynomial_z                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for safely free'ing all of the memory in a tmpl_PolynomialZ      *
 *      pointer and then setting the pointers to NULL.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Destroy_PolynomialZ                                              *
 *  Purpose:                                                                  *
 *      Free all of the memory in a polynomial pointer.                       *
 *  Arguments:                                                                *
 *      poly_ptr (tmpl_PolynomialZ **):                                       *
 *          A pointer to the polynomial pointer that needs to be freed.       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      free (stdlib.h):                                                      *
 *          Standard library function for freeing memory allocated by malloc. *
 *  Method:                                                                   *
 *      Check if any pointers are NULL, free'ing them if not, and then        *
 *      setting the pointers to NULL to avoid freeing them twice in the event *
 *      that this function is accidentally called twice.                      *
 *  Notes:                                                                    *
 *      This function should always be called when one is done with a         *
 *      polynomial to avoid memory leaks.                                     *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_polynomial.h:                                                    *
 *          Header file containing the definition of polynomials and the      *
 *          functions prototype.                                              *
 *  2.) stdlib.h:                                                             *
 *          C Standard library header file containing free.                   *
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
 *  Date:       June 19, 2021                                                 *
 ******************************************************************************/

/*  Function prototype and polynomials found here.                            */
#include <libtmpl/include/tmpl_polynomial.h>

/*  free is located here.                                                     */
#include <stdlib.h>

/*  Function for freeing all of the memory in a polynomial pointer.           */
void tmpl_Destroy_PolynomialZ(tmpl_PolynomialZ **poly_ptr)
{
    /*  Declare a variable for a pointer to a polynomial.                     */
    tmpl_PolynomialZ *poly;

    /*  Check if the input is NULL, aborting if it is.                        */
    if (poly_ptr == NULL)
        return;

    /*  Check if the pointer to the polynomial is NULL as well. Trying to     *
     *  dereference a NULL pointer could cause a segmentation fault.          */
    if (*poly_ptr == NULL)
        return;

    /*  Set poly to the pointer being pointed to by poly_ptr.                 */
    poly = *poly_ptr;

    /*  All of the functions that deal with polynomials set poly->coeffs to   *
     *  NULL if memory was not successfully allocated for it. If the coeffs   *
     *  pointer is not NULL, it is safe to assume it can be freed.            */
    if (poly->coeffs != NULL)
    {
        free(poly->coeffs);

        /*  Set the pointer to NULL to avoid freeing it twice.                */
        poly->coeffs = NULL;
    }

    /*  Similarly for the error_message pointer.                              */
    if (poly->error_message != NULL)
    {
        free(poly->error_message);
        poly->error_message = NULL;
    }

    /*  Free the pointer itself, and set it to NULL to avoid free'ing twice.  */
    free(poly);
    poly = NULL;
    return;
}
/*  End of tmpl_Destroy_PolynomialZ.                                          */
