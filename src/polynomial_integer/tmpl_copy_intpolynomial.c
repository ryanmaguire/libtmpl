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
 *                          tmpl_copy_intpolynomial                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Copies the data in one polynomial to another.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Copy                                               *
 *  Purpose:                                                                  *
 *      Copies the coefficients of one polynomial into another.               *
 *  Arguments:                                                                *
 *      dest (tmpl_IntPolynomial *):                                          *
 *          A pointer to the "destination" polynomial. src is copied here.    *
 *      src (const tmpl_IntPolynomial *):                                     *
 *          A pointer to the "source" polynomial. This will be copied to dest.*
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdlib.h:                                                             *
 *          free:                                                             *
 *              Free's data allocated by malloc, calloc, or realloc.          *
 *      tmpl_string.h:                                                        *
 *          tmpl_strdup:                                                      *
 *              Duplicates a string. Equivalent to the POSIX function strdup. *
 *      tmpl_polynomial_integer.h:                                            *
 *          tmpl_IntPolynomial_Copy_Kernel:                                   *
 *              Copies polynomial data without error checks.                  *
 *          tmpl_IntPolynomial_Make_Empty:                                    *
 *              Makes a polynomial "empty" with NULL coefficients.            *
 *  Method:                                                                   *
 *      Check for valid inputs and call tmpl_IntPolynomial_Copy_Kernel.       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library file where free is provided.                     *
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
 *  2023/05/18: Ryan Maguire                                                  *
 *      Changed behavior so that copying a NULL pointer results in making the *
 *      "dest" polynomial empty.                                              *
 ******************************************************************************/

/*  free function declared here.                                              */
#include <stdlib.h>

/*  tmpl_Bool, tmpl_False, and tmpl_True are given here.                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup function found here.                                          */
#include <libtmpl/include/tmpl_string.h>

/*  Polynomial typedefs and function prototypes given here.                   */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for copying the coefficients of one polynomial to another.       */
void
tmpl_IntPolynomial_Copy(tmpl_IntPolynomial *dest,
                        const tmpl_IntPolynomial *src)
{
    /*  If the destination pointer is NULL, there's nothing to be done.       */
    if (!dest)
        return;

    /*  Similarly if the error_occurred Boolean is true. Return to caller.    */
    if (dest->error_occurred)
        return;

    /*  If src and dest are the same pointer, abort. Nothing to copy.         */
    if (dest == src)
        return;

    /*  If the src polynomial is NULL make the dest polynomial empty.         */
    if (!src)
    {
        /*  Safely free any data in the polynomial to make it empty.          */
        tmpl_IntPolynomial_Make_Empty(dest);
        return;
    }

    /*  If the src pointer is flawed in some manner, consider this an error.  */
    if (src->error_occurred)
    {
        /*  Set the error_occurred Boolean and add an error message.          */
        dest->error_occurred = tmpl_True;
        dest->error_message = tmpl_strdup(
            "\nError Encountered: libtmpl\n"
            "    tmpl_IntPolynomial_Copy\n\n"
            "src pointer has error_occurred set to True. Aborting.\n\n"
        );
        return;
    }

    /*  If the src coefficients are NULL, this is the empty polynomial. Set   *
     *  the dest polynomial to be empty as well.                              */
    if (!src->coeffs)
    {
        /*  Safely free any data in the polynomial to make it empty.          */
        tmpl_IntPolynomial_Make_Empty(dest);
        return;
    }

    /*  Call the kernel function to perform the copying and resizing.         */
    tmpl_IntPolynomial_Copy_Kernel(dest, src);
}
/*  End of tmpl_IntPolynomial_Copy.                                           */
