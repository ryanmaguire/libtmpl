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
 *                            tmpl_polynomial_int                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a polynomial type with "int" coefficients.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 1, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/12/03: Ryan Maguire                                                  *
 *      Moved this typedef to the types directory.                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_POLYNOMIAL_INT_H
#define TMPL_TYPES_POLYNOMIAL_INT_H

/*  Booleans given here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  size_t typedef provided here.                                             */
#include <stddef.h>

/*  Polynomials with integer coefficients, elements of Z[x]. int data type.   */
typedef struct tmpl_IntPolynomial_Def {

    /*  A pointer to a signed int array containing the coefficients.          */
    signed int *coeffs;

    /*  The degree of the polynomial. coeffs has degree + 1 elements.         */
    size_t degree;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    const char *error_message;
} tmpl_IntPolynomial;

#endif
/*  End of include guard.                                                     */
