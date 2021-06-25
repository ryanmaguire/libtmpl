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
 *                       tmpl_create_zero_polynomial_q                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for creating a degree N polynomial in Q[x] with all coefficients *
 *      set to zero. Mathematically this is the same thing as the zero        *
 *      polynomial, but computer-wise the coefficients array will have more   *
 *      memory allocated to it.                                               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Create_Zero_PolynomialQ                                          *
 *  Purpose:                                                                  *
 *      Creates a polynomial in Q[x] with all coefficients set to zero.       *
 *  Arguments:                                                                *
 *      degree (unsigned long int):                                           *
 *          The degree of the polynomial. The array of coefficients will have *
 *          degree + 1 many elements allocated to it, and set to zero.        *
 *  Output:                                                                   *
 *      poly (tmpl_PolynomialQ *):                                            *
 *          The polynomial 0 + 0 x + ... + 0 x^degree.                        *
 *  Called Functions:                                                         *
 *      malloc (stdlib.h):                                                    *
 *          Standard library function for allocating memory.                  *
 *  Method:                                                                   *
 *      Allocate memory for the polynomial pointer with malloc, then allocate *
 *      memory for the coeffs pointer and initialize the elements to zero.    *
 *  Notes:                                                                    *
 *      If malloc fails, a NULL pointer is returned.                          *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  2.) tmpl_string.h:                                                        *
 *          Header file where the tmpl_strdup function is declared. This is   *
 *          a clone of the strdup function, which is part of the POSIX        *
 *          standard library, but not the C standard library.                 *
 *  3.) tmpl_rational.h:                                                      *
 *          Header file for working with rational numbers.                    *
 *  4.) tmpl_polynomial.h:                                                    *
 *          Header file containing the definition of polynomials and the      *
 *          functions prototype.                                              *
 *  5.) stdlib.h:                                                             *
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
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       June 25, 2021                                                 *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_stdup function declared here.                                        */
#include <libtmpl/include/tmpl_string.h>

/*  Rational numbers found here.                                              */
#include <libtmpl/include/tmpl_rational.h>

/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_polynomial.h>

/*  malloc is found here.                                                     */
#include <stdlib.h>

/*  Function for creating a polynomial with all coefficients set to zero.     */
tmpl_PolynomialQ *tmpl_Create_Zero_PolynomialQ(unsigned long int degree)
{
    /*  Declare necessary variables. The ISO C89/C90 standard forbids mixed   *
     *  code with declarations, so declare everything at the top.             */
    tmpl_PolynomialQ *poly;

    /*  And a variable for indexing.                                          */
    unsigned long int n;

    /*  Allocate memory with malloc. Per every coding standard one can find,  *
     *  the result of malloc is not cast. Malloc returns a void pointer which *
     *  is safely promoted to the type of poly.                               */
    poly = malloc(sizeof(*poly));

    /*  Check if malloc failed. It returns NULL if it does.                   */
    if (poly == NULL)
        return NULL;

    /*  Otherwise, allocate memory for the coefficients pointer.              */
    poly->coeffs = malloc(sizeof(*poly->coeffs) * (degree + 1UL));

    /*  Check if malloc failed.                                               */
    if (poly->coeffs == NULL)
    {
        /*  Set the error occured Boolean to True indicating an error.        */
        poly->error_occurred = tmpl_True;

        /*  Set an error message indicating what went wrong.                  */
        poly->error_message = tmpl_strdup(
            "Error Encountered: libtmpl\n"
            "\r\ttmpl_Create_Zero_PolynomialQ\n\n"
            "\rmalloc failed to allocate memory for the coefficients pointer\n"
            "\rand returned NULL. Returning with error.\n"
        );

        /*  Set the degree to zero since the coefficients pointer is NULL.    */
        poly->degree = 0UL;
    }

    /*  If malloc succeeded, set the remaining values in the polynomial.      */
    else
    {
        /*  Initialize all elements to zero.                                  */
        for (n = 0UL; n <= degree; ++n)
            poly->coeffs[n] = tmpl_Rational_Zero;

        /*  No error occurred, so set to false.                               */
        poly->error_occurred = tmpl_False;

        /*  Set the error message pointer to NULL. This is important. When    *
         *  trying to free all of the memory in a polynomial pointer other    *
         *  functions will check if this pointer is NULL before attempting    *
         *  to free it. free'ing a non-malloced pointer will crash the        *
         *  program.                                                          */
        poly->error_message = NULL;

        /*  Lastly, set the degree.                                           */
        poly->degree = degree;
    }

    return poly;
}
/*  End of tmpl_Create_Zero_PolynomialQ.                                      */
