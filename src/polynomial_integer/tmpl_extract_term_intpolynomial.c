
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
 *                      tmpl_extract_term_intpolynomial                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Returns the coefficient of a polynomial corresponding to a term.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Extract_Term                                       *
 *  Purpose:                                                                  *
 *      Returns the coefficient of the requested term in a polynomial.        *
 *  Arguments:                                                                *
 *      poly (const tmpl_IntPolynomial *):                                    *
 *          A pointer to a polynomial.                                        *
 *      term (size_t):                                                        *
 *          The term requested from the polynomial.                           *
 *  Outputs:                                                                  *
 *      coefficient (int):                                                    *
 *          The coefficient of the requested term.                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If the requested term does not exceed the degree of the polynomial,   *
 *      return the corresponding entry from the coeffs array. Otherwise treat *
 *      the coefficient as zero.                                              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard library file with size_t data type.                      *
 *  2.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 25, 2023                                                *
 ******************************************************************************/

/*  size_t data type found here.                                              */
#include <stddef.h>

/*  Polynomial typedefs and function prototype.                               */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for safely retrieving a coefficient from a polynomial.           */
int tmpl_IntPolynomial_Extract_Term(const tmpl_IntPolynomial *poly, size_t term)
{
    /*  The empty polynomial is identified with the zero polynomial here.     */
    if (!poly)
        return 0;

    /*  Similarly if the polynomial is flawed return zero.                    */
    if (poly->error_occurred)
        return 0;

    /*  Another case of the empty polynomial, treat it as zero.               */
    if (!poly->coeffs)
        return 0;

    /*  If the requested term is larger than the degree we can treat the      *
     *  coefficient as zero. Check for this.                                  */
    if (poly->degree < term)
        return 0;

    /*  Legal arguments, return the requested coefficient.                    */
    return poly->coeffs[term];
}
/*  End of tmpl_IntPolynomial_Extract_Term.                                   */
