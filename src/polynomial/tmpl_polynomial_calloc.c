/******************************************************************************
 *                                  LICENSE                                   *
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
 *                           tmpl_polynomial_calloc                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for creating a polynomial in Z[x], Q[x], R[x], or C[x] with      *
 *      coeffs pointer allocated a given number of elements, all of which are *
 *      initialized to zero. Mathematically this is the zero polynomial.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialZ_Calloc                                               *
 *      tmpl_PolynomialQ_Calloc                                               *
 *      tmpl_PolynomialR_Calloc                                               *
 *      tmpl_PolynomialC_Calloc                                               *
 *  Purpose:                                                                  *
 *      Creates a polynomial in Z[x], Q[x], R[x], or C[x], respectively,      *
 *      with all coefficients set to zero.                                    *
 *  Arguments:                                                                *
 *      number_of_coeffs (unsigned long int):                                 *
 *          The number of elements to be allocated for the coeffs pointer.    *
 *  Output:                                                                   *
 *      poly (tmpl_PolynomialZ/Q/R/C *):                                      *
 *          The polynomial 0 + 0 x + ... + 0 x^(number_of_coeffs - 1).        *
 *  Called Functions:                                                         *
 *      malloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory.                  *
 *      calloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory and initializing  *
 *          all of the elements to zero.                                      *
 *  Method:                                                                   *
 *      Allocate memory for the polynomial pointer with malloc, and allocate  *
 *      and initialize to zero memory for the pointer to the coefficients     *
 *      array using calloc.                                                   *
 *  Notes:                                                                    *
 *      If malloc fails, a NULL pointer is returned. If malloc succeeds, but  *
 *      calloc fails, the error_occurred Boolean is set to true and an        *
 *      error message is stored in the struct. Check these before using       *
 *      the polynomial.                                                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  2.) tmpl_string.h:                                                        *
 *          Header file where the tmpl_strdup function is declared.           *
 *  3.) tmpl_rational.h:                                                      *
 *          Header file containing rational numbers.                          *
 *  4.) tmpl_complex.h:                                                       *
 *          Header file containing complex numbers.                           *
 *  5.) tmpl_polynomial.h:                                                    *
 *          Header file containing the definition of polynomials and the      *
 *          functions prototype.                                              *
 *  6.) stdlib.h:                                                             *
 *          C Standard library header file containing malloc and calloc.      *
 ******************************************************************************
 *                             A NOTE ON COMMENTS                             *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                             A FRIENDLY WARNING                             *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 15, 2021                                             *
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
#ifdef TMPL_POLYNOMIAL_CALLOC_FUNC
#undef TMPL_POLYNOMIAL_CALLOC_FUNC
#endif

/******************************************************************************
 *  Macro for giving the definition of the calloc functions for Z/Q/R/C[x].   *
 *  Arguments:                                                                *
 *      type:                                                                 *
 *          The data type of the polynomial (the polynomial's typedef).       *
 *      fname:                                                                *
 *          The name of the function the macro defines.                       *
 ******************************************************************************/
#define TMPL_POLYNOMIAL_CALLOC_FUNC(type, fname)                               \
                                                                               \
/*  Function for creating a polynomial with all coefficients set to zero.    */\
type *fname(unsigned long int number_of_coeffs)                                \
{                                                                              \
    /*  Allocate memory with malloc. Per every coding standard one can find, */\
    /*  the result of malloc is not cast. Malloc returns a void pointer      */\
    /*  is safely promoted to the type of poly.                              */\
    type *poly = malloc(sizeof(*poly));                                        \
                                                                               \
    /*  Check if malloc failed. It returns NULL if it does.                  */\
    if (poly == NULL)                                                          \
        return NULL;                                                           \
                                                                               \
    /*  malloc was successful, set poly_can_be_freed to true.                */\
    poly->poly_can_be_freed = tmpl_True;                                       \
                                                                               \
    /*  Special case if number_of_coeffs is zero create the empty polynomial.*/\
    if (number_of_coeffs == 0UL)                                               \
    {                                                                          \
        /*  Set the coeffs array to NULL indicating empty.                   */\
        poly->coeffs = NULL;                                                   \
        poly->number_of_coeffs = 0UL;                                          \
        poly->min_degree = 0UL;                                                \
                                                                               \
        /*  NULL pointers can't be freed, set this to false.                 */\
        poly->coeffs_can_be_freed = tmpl_False;                                \
                                                                               \
        /*  malloc succeeded, calloc not needed, no error occurred.          */\
        poly->error_occurred = tmpl_False;                                     \
        poly->error_message = NULL;                                            \
        return poly;                                                           \
    }                                                                          \
                                                                               \
    /*  Otherwise allocate memory for the coefficients pointer.              */\
    poly->coeffs = calloc(sizeof(*poly->coeffs), number_of_coeffs);            \
                                                                               \
    /*  Check if calloc failed.                                              */\
    if (poly->coeffs == NULL)                                                  \
    {                                                                          \
        /*  Set the error occurred Boolean to True indicating an error.      */\
        poly->error_occurred = tmpl_True;                                      \
                                                                               \
        /*  Set an error message indicating what went wrong.                 */\
        poly->error_message = tmpl_strdup(                                     \
            "Error Encountered: libtmpl\n"                                     \
            "\r\t"#fname"\n\n"                                                 \
            "\rcalloc failed to allocate memory for the coefficients pointer\n"\
            "\rand returned NULL. Returning with error.\n\n"                   \
        );                                                                     \
                                                                               \
        /*  NULL pointers can not be freed.                                  */\
        poly->coeffs_can_be_freed = tmpl_False;                                \
                                                                               \
        /*  Set number_of_coeffs to zero since the coeffs pointer is NULL.   */\
        poly->number_of_coeffs = 0UL;                                          \
    }                                                                          \
                                                                               \
    /*  If calloc succeeded, set the remaining values in the polynomial.     */\
    else                                                                       \
    {                                                                          \
        /*  No error occurred, so set to false.                              */\
        poly->error_occurred = tmpl_False;                                     \
                                                                               \
        /*  Set the error message pointer to NULL. This is important. When   */\
        /*  trying to free all of the memory in a polynomial pointer other   */\
        /*  functions will check if this pointer is NULL before attempting   */\
        /*  to free it. free'ing a non-malloc'ed pointer will crash the      */\
        /*  program.                                                         */\
        poly->error_message = NULL;                                            \
                                                                               \
        /*  Since calloc succeeded, the coeffs pointer can safely be freed.  */\
        poly->coeffs_can_be_freed = tmpl_True;                                 \
                                                                               \
        /*  Lastly, set the number_of_coeffs attribute.                      */\
        poly->number_of_coeffs = number_of_coeffs;                             \
    }                                                                          \
                                                                               \
    /*  Whether or not calloc failed, set min_degree to zero.                */\
    poly->min_degree = 0UL;                                                    \
    return poly;                                                               \
}
/*  End of TMPL_POLYNOMIAL_CALLOC_FUNC.                                       */

/*  Define all of the calloc functions (Z, Q, R, and C, respectively).        */
TMPL_POLYNOMIAL_CALLOC_FUNC(tmpl_PolynomialZ, tmpl_PolynomialZ_Calloc)
TMPL_POLYNOMIAL_CALLOC_FUNC(tmpl_PolynomialQ, tmpl_PolynomialQ_Calloc)
TMPL_POLYNOMIAL_CALLOC_FUNC(tmpl_PolynomialR, tmpl_PolynomialR_Calloc)
TMPL_POLYNOMIAL_CALLOC_FUNC(tmpl_PolynomialC, tmpl_PolynomialC_Calloc)

/*  Undefine the macro in case someone wants to #include this file directly.  */
#undef TMPL_POLYNOMIAL_CALLOC_FUNC
