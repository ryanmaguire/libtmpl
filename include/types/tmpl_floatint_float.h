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
 *                            tmpl_floatint_float                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for type-punning floating point numbers as integers.   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of TMPL_HAS_FLOATINT32.                                  *
 *  2.) tmpl_inttype.h:                                                       *
 *          Header file containing fixed-width integer data types.            *
 *  3.) tmpl_ieee754_float.h:                                                 *
 *          Header file with a union for IEEE-754 single precision numbers.   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/08/10                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_FLOATINT_FLOAT_H
#define TMPL_TYPES_FLOATINT_FLOAT_H

/*  Location of the TMPL_HAS_FLOATINT32 macro.                                */
#include <libtmpl/include/tmpl_config.h>

/*  If float is represented using the 32-bit IEEE-754 format, and if 32-bit   *
 *  unsigned integers are available, provide a union for type-punning.        */
#if TMPL_HAS_FLOATINT32 == 1

/*  Fixed-width integer data types found here.                                */
#include <libtmpl/include/tmpl_inttype.h>

/*  32-bit float union found here.                                            */
#include <libtmpl/include/types/tmpl_ieee754_float.h>

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
/*  End of #if TMPL_HAS_FLOATINT32 == 1.                                      */

#endif
/*  End of include guard.                                                     */
