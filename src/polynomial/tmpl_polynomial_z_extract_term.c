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
 *                      tmpl_polynomials_z_extract_term                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Return the coefficient of the requested term.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PolynomialZ_Extract_Term                                         *
 *  Purpose:                                                                  *
 *      Computes the coefficient of a given term for a polynomial.            *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to the polynomial.                                      *
 *      term (unsigned long int):                                             *
 *          The degree of the term that is requested.                         *
 *  Output:                                                                   *
 *      coefficient (signed long int):                                        *
 *          The coefficient of the requested term.                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Parse the poly pointer and returned the corresponding coefficient.    *
 *  Notes:                                                                    *
 *      If poly is NULL, poly->error_occurred is true, poly->degree < term,   *
 *      or if poly->coeffs = NULL, the value 0 is returned.                   *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_polynomial.h:                                                    *
 *          Header file containing the definition of polynomials and the      *
 *          functions prototype.                                              *
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
 *  Date:       June 22, 2021                                                 *
 ******************************************************************************/

/*  Function prototype is found here.                                         */
#include <libtmpl/include/tmpl_polynomial.h>

/*  Function for extracting the coefficient of a given term.                  */
signed long int
tmpl_PolynomialZ_Extract_Term(tmpl_PolynomialZ *poly, unsigned long int term)
{
    /*  If the pointer is NULL, return zero.                                  */
    if (poly == NULL)
        return 0L;

    /*  If an error occured, also return zero.                                */
    else if (poly->error_occurred)
        return 0L;

    /*  If poly->coeffs is NULL, the polynomial is "empty" which can be       *
     *  interpreted as the zero polynomial, so return zero.                   */
    else if (poly->coeffs == NULL)
        return 0L;

    /*  If the requested term has it's degree greater than the degree of the  *
     *  polynomial, the coefficient can be interpreted as zero. Return this.  */
    else if (poly->degree < term)
        return 0L;

    /*  Otherwise, return the coefficient of the requested term.              */
    else
        return poly->coeffs[term];
}
/*  End of tmpl_PolynomialZ_Extract_Term.                                     */
