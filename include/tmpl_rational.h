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
 *                              tmpl_rational                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide data types for working with rational numbers.                 *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  2.) stdio.h:                                                              *
 *          C Standard header file containing FILE type.                      *
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
 *  Date:       June 24, 2021                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_RATIONAL_H
#define TMPL_RATIONAL_H

#include "tmpl_exports.h"

/*  Booleans are found here.                                                  */
#include <libtmpl/include/tmpl_bool.h>

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  Note:                                                                     *
 *      The data type defined below does not define arbitrary-precision       *
 *      rational numbers. On UNIX-like systems it will define 128-bit         *
 *      rationals, since signed long int is usually 64-bit, and on Windows it *
 *      will define 64-bit, since signed long int is 32-bit.                  */

/*  Data type for working with rational numbers.                              */
typedef struct tmpl_RationalNumber_Def {
    signed long int numerator;
    signed long int denominator;
} tmpl_RationalNumber;

/*  Commonly used rational numbers.                                           */
extern const tmpl_RationalNumber tmpl_RationalNumber_Zero;
extern const tmpl_RationalNumber tmpl_RationalNumber_One;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RationalNumber_Add                                               *
 *  Purpose:                                                                  *
 *      Adds two rational numbers.                                            *
 *  Arguments:                                                                *
 *      q (const tmpl_RationalNumber *):                                      *
 *          A rational number.                                                *
 *      p (const tmpl_RationalNumber *):                                      *
 *          Another rational number.                                          *
 *  Output:                                                                   *
 *      sum (tmpl_RationalNumber):                                            *
 *          The sum of p and q.                                               *
 *  Source Code:                                                              *
 *      libtmpl/src/rational/tmpl_rational_add.c                              *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_RationalNumber
tmpl_RationalNumber_Add(const tmpl_RationalNumber *p,
                        const tmpl_RationalNumber *q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RationalNumber_AddTo                                             *
 *  Purpose:                                                                  *
 *      Adds two rational numbers.                                            *
 *  Arguments:                                                                *
 *      q (tmpl_RationalNumber *):                                            *
 *          A rational number.                                                *
 *      p (const tmpl_RationalNumber *):                                      *
 *          Another rational number.                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/rational/tmpl_rational_add.c                              *
 ******************************************************************************/
TMPL_EXPORT extern void
tmpl_RationalNumber_AddTo(tmpl_RationalNumber *p, const tmpl_RationalNumber *q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RationalNumber_Create                                            *
 *  Purpose:                                                                  *
 *      Creates a rational number for two integers.                           *
 *  Arguments:                                                                *
 *      numer (signed long int):                                              *
 *          The numerator of the number.                                      *
 *      denom (signed long int):                                              *
 *          The denominator of the number.                                    *
 *  Output:                                                                   *
 *      q (tmpl_RationalNumber):                                              *
 *          The number numer/denom.                                           *
 *  Source Code:                                                              *
 *      libtmpl/src/rational/tmpl_rational_create.c                           *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_RationalNumber
tmpl_RationalNumber_Create(signed long int numer, signed long int denom);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RationalNumber_Are_Equal                                         *
 *  Purpose:                                                                  *
 *      Checks if two rationals are equal.                                    *
 *  Arguments:                                                                *
 *      q (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *      p (tmpl_RationalNumber):                                              *
 *          Another rational number.                                          *
 *  Output:                                                                   *
 *      are_equal (tmpl_Bool):                                                *
 *          A Boolean for if p and q are equal.                               *
 *  Source Code:                                                              *
 *      libtmpl/src/rational/tmpl_rational_are_equal.c                        *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_Bool
tmpl_RationalNumber_Are_Equal(const tmpl_RationalNumber *p,
                              const tmpl_RationalNumber *q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RationalNumber_Is_Zero                                           *
 *  Purpose:                                                                  *
 *      Checks if a rational number is zero.                                  *
 *  Arguments:                                                                *
 *      p (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *  Output:                                                                   *
 *      is_zero (tmpl_Bool):                                                  *
 *          A Boolean for if p is zero.                                       *
 *  Source Code:                                                              *
 *      libtmpl/src/rational/tmpl_rational_is_zero.c                          *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_Bool
tmpl_RationalNumber_Is_Zero(const tmpl_RationalNumber *p);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RationalNumber_Divide                                            *
 *  Purpose:                                                                  *
 *      Divides two rational numbers.                                         *
 *  Arguments:                                                                *
 *      q (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *      p (tmpl_RationalNumber):                                              *
 *          Another rational number.                                          *
 *  Output:                                                                   *
 *      quot (tmpl_RationalNumber):                                           *
 *          The quotient of p and q.                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/rational/tmpl_rational_divide.c                           *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_RationalNumber
tmpl_RationalNumber_Divide(const tmpl_RationalNumber *p,
                           const tmpl_RationalNumber *q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RationalNumber_Multiply                                          *
 *  Purpose:                                                                  *
 *      Multiplies two rational numbers.                                      *
 *  Arguments:                                                                *
 *      q (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *      p (tmpl_RationalNumber):                                              *
 *          Another rational number.                                          *
 *  Output:                                                                   *
 *      prod (tmpl_RationalNumber):                                           *
 *          The product of p and q.                                           *
 *  Source Code:                                                              *
 *      libtmpl/src/rational/tmpl_rational_multiply.c                         *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_RationalNumber
tmpl_RationalNumber_Multiply(const tmpl_RationalNumber *p,
                             const tmpl_RationalNumber *q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RationalNumber_Reduce                                            *
 *  Purpose:                                                                  *
 *      Reduces a rational number to the form a/b where a and b are coprime.  *
 *  Arguments:                                                                *
 *      p (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *  Output:                                                                   *
 *      q (tmpl_RationalNumber):                                              *
 *          The number p in reduced form.                                     *
 *  Source Code:                                                              *
 *      libtmpl/src/rational/tmpl_rational_reduce.c                           *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_RationalNumber
tmpl_RationalNumber_Reduce(const tmpl_RationalNumber *p);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RationalNumber_Subtract                                          *
 *  Purpose:                                                                  *
 *      Subtracts two rational numbers.                                       *
 *  Arguments:                                                                *
 *      q (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *      p (tmpl_RationalNumber):                                              *
 *          Another rational number.                                          *
 *  Output:                                                                   *
 *      diff (tmpl_RationalNumber):                                           *
 *          The difference of p and q.                                        *
 *  Source Code:                                                              *
 *      libtmpl/src/rational/tmpl_rational_subtract.c                         *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_RationalNumber
tmpl_RationalNumber_Subtract(const tmpl_RationalNumber *p,
                             const tmpl_RationalNumber *q);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RationalNumber_Print_String                                      *
 *  Purpose:                                                                  *
 *      Subtracts two rational numbers.                                       *
 *  Arguments:                                                                *
 *      fp (FILE *fp):                                                        *
 *          A pointer to the file to be printed to.                           *
 *      p (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/rational/tmpl_rational_print_string.c                     *
 ******************************************************************************/
TMPL_EXPORT extern void
tmpl_RationalNumber_Print_String(FILE *fp, tmpl_RationalNumber p);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RationalNumber_As_Float                                          *
 *  Purpose:                                                                  *
 *      Converts a rational number to a floating point one. Similar           *
 *      functions are provided for double and long double.                    *
 *  Arguments:                                                                *
 *      p (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *  Output:                                                                   *
 *      r (float):                                                            *
 *          The number p interpreted as a float.                              *
 *  Source Code:                                                              *
 *      libtmpl/src/rational/tmpl_rational_as_real.c                          *
 ******************************************************************************/
TMPL_EXPORT extern float tmpl_RationalNumber_As_Float(const tmpl_RationalNumber *p);
TMPL_EXPORT extern double tmpl_RationalNumber_As_Double(const tmpl_RationalNumber *p);
TMPL_EXPORT extern long double tmpl_RationalNumber_As_LDouble(const tmpl_RationalNumber *p);

#endif
/*  End of include guard.                                                     */
