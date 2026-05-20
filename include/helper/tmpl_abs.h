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
 *                                  tmpl_abs                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a helper macro for computing the absolute value of a number. *
 *  Notes:                                                                    *
 *      1.) The argument for this macro is expanded three times. Use this     *
 *          with variable-like expressions and not function calls.            *
 *                                                                            *
 *      2.) To avoid unexpected results, do not combine this macro with the   *
 *          ++ or -- operators.                                               *
 *                                                                            *
 *      3.) If the input is a signed integer (signed int, signed long, etc.), *
 *          then this macro may exhibit undefined behavior if the parameter   *
 *          has the most negative number allowed by the type. For example, if *
 *          signed int x = INT_MIN, then -x is undefined in two's complement, *
 *          but it is well-defined in the sign-and-magnitude representation.  *
 *          Avoid using this macro with such values.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 21, 2024                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_HELPER_ABS_H
#define TMPL_HELPER_ABS_H

/*  Computes the absolute value of a number (integer / floating point).       */
#define TMPL_ABS(x) ((x) < 0 ? -(x) : (x))

#endif
/*  End of include guard.                                                     */
