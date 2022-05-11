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
 *                         tmpl_polynomial_c_destroy                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for freeing all memory in a C[x] polynomial.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialC_Destroy                                              *
 *  Purpose:                                                                  *
 *      Free all memory in a tmpl_PolynomialC polynomial.                     *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialC **):                                           *
 *          The polynomial that is to be destroyed.                           *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      free (stdlib.h):                                                      *
 *          Standard library function for freeing allocated memory.           *
 *  Method:                                                                   *
 *      Check for NULL pointers and errors, and free the pointers in the      *
 *      polynomial struct if safe.                                            *
 *  Notes:                                                                    *
 *      Pointers are set to NULL after freeing, to avoid freeing them twice.  *
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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2022                                             *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_strdup function declared here.                                       */
#include <libtmpl/include/tmpl_string.h>

/*  Rational numbers found here.                                              */
#include <libtmpl/include/tmpl_rational.h>

/*  Complex numbers found here.                                               */
#include <libtmpl/include/tmpl_complex.h>

/*  Function prototypes are given here.                                       */
#include <libtmpl/include/tmpl_polynomial.h>

/*  malloc and calloc are found here.                                         */
#include <stdlib.h>

/*  Make sure this macro name is available. It should be anyways.             */
#ifdef TMPL_POLYNOMIAL_DESTROY_FUNC
#undef TMPL_POLYNOMIAL_DESTROY_FUNC
#endif

/******************************************************************************
 *  Macro for giving the definition of the free functions for Z/Q/R/C[x].     *
 *  Arguments:                                                                *
 *      type:                                                                 *
 *          The data type of the polynomial (the polynomial's typedef).       *
 *      fname:                                                                *
 *          The name of the function the macro defines.                       *
 ******************************************************************************/
#define TMPL_POLYNOMIAL_DESTROY_FUNC(type, fname)                              \
                                                                               \
/*  Function for freeing all memory for a polynomial.                        */\
void fname(type **poly_ptr)                                                    \
{                                                                              \
    /*  Variable for the polynomial that poly_ptr is pointing to.            */\
    type *poly;                                                                \
                                                                               \
    /*  If the input pointer is NULL, there's nothing to be done.            */\
    if (poly_ptr == NULL)                                                      \
        return;                                                                \
                                                                               \
    /*  Otherwise, it is safe to dereference.                                */\
    poly = *poly_ptr;                                                          \
                                                                               \
    /*  If the coeffs pointer is NULL, we also do not need to free it.       */\
    if (poly->coeffs != NULL)                                                  \
    {                                                                          \
        /*  It is possible that the coefficients pointer is simply a pointer */\
        /*  to a statically declared array. The coeffs_can_be_freed Boolean  */\
        /*  is set to False in this case.                                    */\
        if (poly->coeffs_can_be_freed)                                         \
            free(poly->coeffs);                                                \
                                                                               \
        /*  Set the coeffs pointer to NULL in case this function is          */\
        /*  accidentally called twice.                                       */\
        poly->coeffs = NULL;                                                   \
    }                                                                          \
                                                                               \
    /*  Check if there is anything stored in error_message. All functions    */\
    /*  either initialize this to NULL if no error occurred, or use the      */\
    /*  tmpl_strdup function to store an error message in it. tmpl_strdup    */\
    /*  returns NULL on failure, so we should still check for a NULL pointer.*/\
    if (poly->error_message != NULL)                                           \
    {                                                                          \
        /*  Free the data and set it equal to NULL.                          */\
        free(poly->error_message);                                             \
        poly->error_message = NULL;                                            \
    }                                                                          \
                                                                               \
    /*  Lastly, check if poly itself was malloc'd. Free it if so.            */\
    if (poly->poly_can_be_freed)                                               \
        free(poly);                                                            \
                                                                               \
    /*  Set the pointer to NULL to avoid attempting to free it twice.        */\
    *poly_ptr = NULL;                                                          \
    return;                                                                    \
}
/*  End of TMPL_POLYNOMIAL_DESTROY_FUNC.                                      */

/*  Define all of the create_empty functions using the macro.                 */
TMPL_POLYNOMIAL_DESTROY_FUNC(tmpl_PolynomialZ, tmpl_PolynomialZ_Destroy)
TMPL_POLYNOMIAL_DESTROY_FUNC(tmpl_PolynomialQ, tmpl_PolynomialQ_Destroy)
TMPL_POLYNOMIAL_DESTROY_FUNC(tmpl_PolynomialR, tmpl_PolynomialR_Destroy)
TMPL_POLYNOMIAL_DESTROY_FUNC(tmpl_PolynomialC, tmpl_PolynomialC_Destroy)

/*  Undefine the macro in case someone wants to #include this file directly.  */
#undef TMPL_POLYNOMIAL_DESTROY_FUNC
