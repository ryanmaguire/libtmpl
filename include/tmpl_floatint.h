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
 *                               tmpl_floatint                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for type-punning floating point numbers as integers.   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_inttype.h:                                                       *
 *          Header file containing fixed-width integer data types.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with macros for IEEE-754 support.                     *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/08/10                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_FLOATINT_H
#define TMPL_FLOATINT_H

/*  TMPL_HAS_32_BIT_INT and TMPL_HAS_64_BIT_INT macros found here.            */
#include <libtmpl/include/tmpl_inttype.h>

/*  IEEE-754 support macros found here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  If float is represented using the 32-bit IEEE-754 format, and if 32-bit   *
 *  unsigned integers are available, provide a union for type-punning.        */
#if TMPL_HAS_IEEE754_FLOAT == 1 && TMPL_HAS_32_BIT_INT

/*  Union for type-punning a 32-bit float with a 32-bit int.                  */
typedef union tmpl_IEEE754_FloatInt32_Def {

    /*  The "word" the data represents. This splits the float into its bits.  */
    tmpl_IEEE754_Float w;

    /*  The integer value the 32-bits for the float represent.                */
    tmpl_UInt32 n;

    /*  The actual floating point number.                                     */
    float f;
} tmpl_IEEE754_FloatInt32;

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1 && TMPL_HAS_32_BIT_INT.            */

/*  If double is represented using the 64-bit IEEE-754 format, and if 64-bit  *
 *  unsigned integers are available, provide a union for type-punning.        */
#if TMPL_HAS_IEEE754_DOUBLE == 1 && TMPL_HAS_64_BIT_INT

/*  Union for type-punning a 64-bit double with a 64-bit int.                 */
typedef union tmpl_IEEE754_FloatInt64_Def {

    /*  The "word" the data represents. This splits the double into its bits. */
    tmpl_IEEE754_Double w;

    /*  The integer value the 64-bits for the double represent.               */
    tmpl_UInt64 n;

    /*  The actual floating point number.                                     */
    double f;
} tmpl_IEEE754_FloatInt64;

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1 && TMPL_HAS_64_BIT_INT.           */

#endif
/*  End of include guard.                                                     */
