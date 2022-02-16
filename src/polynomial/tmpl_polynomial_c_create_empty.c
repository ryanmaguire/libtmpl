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
 *                       tmpl_polynomial_c_create_empty                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for creating a polynomial in C[x] with all pointers set to NULL  *
 *      and all variables set to their zero values.                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialC_Create_Empty                                         *
 *  Purpose:                                                                  *
 *      Creates a pointer to a polynomial in C[x] with coeffs set to NULL,    *
 *      error_occurred set to false, error_message set to NULL, min_degree to *
 *      0, number_of_coeffs set to 0, and coeffs_can_be_freed set to false.   *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      poly (tmpl_PolynomialC *):                                            *
 *          A polynomial with its coeffs pointer set to NULL.                 *
 *  Called Functions:                                                         *
 *      malloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory.                  *
 *  Method:                                                                   *
 *      Allocate memory for the polynomial pointer with malloc, and then      *
 *      set the rest of the values of the polynomial struct to defaults.      *
 *  Notes:                                                                    *
 *      If malloc fails, a NULL pointer is returned.                          *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  2.) tmpl_polynomial.h:                                                    *
 *          Header file containing the definition of polynomials and the      *
 *          functions prototype.                                              *
 *  3.) stdlib.h:                                                             *
 *          C Standard library header file containing malloc.                 *
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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 15, 2022                                             *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial.h>

/*  malloc found here.                                                        */
#include <stdlib.h>

/*  Function for creating a polynomial with coeffs set to NULL.               */
tmpl_PolynomialC *tmpl_PolynomialC_Create_Empty(void)
{
    /*  Allocate memory with malloc. Per every coding standard one can find,  *
     *  the result of malloc is not cast. Malloc returns a void pointer which *
     *  is safely promoted to the type of poly.                               */
    tmpl_PolynomialC *poly = malloc(sizeof(*poly));

    /*  Check if malloc failed. It returns NULL if it does.                   */
    if (poly == NULL)
        return NULL;

    /*  Otherwise, set the default values for the polynomial.                 */
    poly->coeffs = NULL;
    poly->error_occurred = tmpl_False;
    poly->error_message = NULL;
    poly->min_degree = 0UL;
    poly->number_of_coeffs = 0UL;

    /*  coeffs is set to NULL. This cannot be safely freed.                   */
    poly->coeffs_can_be_freed = tmpl_False;
    return poly;
}
/*  End of tmpl_PolynomialC_Create_Empty.                                     */

