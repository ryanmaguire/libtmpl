/******************************************************************************
 *                                 LICENSE                                    *
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
 *                             tmpl_polynomial                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide data types for working with polynomials.                      *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  2.) tmpl_Rational.h:                                                      *
 *          Header file containing a data type for working with rational      *
 *          numbers.                                                          *
 *  3.) tmpl_complex.h:                                                       *
 *          Header file containing complex data types.                        *
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
 *  Date:       June 15, 2021                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_POLYNOMIAL_H
#define TMPL_POLYNOMIAL_H

/*  Booleans located here.                                                    */
#include <libtmpl/include/tmpl_bool.h>

/*  Rational numbers found here.                                              */
#include <libtmpl/include/tmpl_rational.h>

/*  And lastly, complex numbers are here.                                     */
#include <libtmpl/include/tmpl_complex.h>

/*  Data type for working with elements of Z[x]. That is, polynomials with    *
 *  integer coefficients.                                                     */
typedef struct _tmpl_PolynomialZ {
    /*  A single pointer to a SIGNED long int array will contain the          *
     *  coefficients in the order a_0 + a_1 x + ... + a_N x^N.                */
    signed long int *coeffs;

    /*  The degree of the polynomial. A polynomial will have degree + 1       *
     *  elements.                                                             */
    unsigned long int degree;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_PolynomialZ;

typedef struct _tmpl_PolynomialQ {
    tmpl_RationalNumber *coeffs;
    unsigned long int degree;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_PolynomialQ;

typedef struct _tmpl_PolynomialZMatrix {
    tmpl_PolynomialZ **data;
    unsigned long int number_of_rows;
    unsigned long int number_of_columns;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_PolynomialZMatrix;

typedef struct _tmpl_PolynomialQMatrix {
    tmpl_PolynomialQ **data;
    unsigned long int number_of_rows;
    unsigned long int number_of_columns;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_PolynomialQMatrix;

extern tmpl_PolynomialZ *
tmpl_Create_Zero_PolynomialZ(unsigned long int degree);

extern void
tmpl_PolynomialZ_Multiply(tmpl_PolynomialZ *P,
                          tmpl_PolynomialZ *Q,
                          tmpl_PolynomialZ *prod);

extern void
tmpl_PolynomialZ_Add(tmpl_PolynomialZ *P,
                     tmpl_PolynomialZ *Q,
                     tmpl_PolynomialZ *sum);

extern void
tmpl_PolynomialQ_Add(tmpl_PolynomialQ *P,
                     tmpl_PolynomialQ *Q,
                     tmpl_PolynomialQ *sum);

extern void
tmpl_PolynomialQ_Multiply(tmpl_PolynomialQ *P,
                          tmpl_PolynomialQ *Q,
                          tmpl_PolynomialQ *prod);

#endif
