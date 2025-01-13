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
 *                            tmpl_uint32_to_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Converts an unsigned 32-bit integer to a float via type-punning.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UInt32_To_Float                                                  *
 *  Purpose:                                                                  *
 *      Converts an unsigned 32-bit integer to a float by type-punning.       *
 *  Arguments:                                                                *
 *      n (tmpl_UInt32):                                                      *
 *          The integer representing the bits of x.                           *
 *  Output:                                                                   *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a union to type-pun a 32-bit integer as a float and return.       *
 *  Notes:                                                                    *
 *      This function assumes 32-bit float is implemented using IEEE-754,     *
 *      and that 32-bit unsigned integers are available as well as            *
 *      type-punning. The config.c file should determine this for you when    *
 *      building libtmpl.                                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file with TMPL_HAS_FLOATINT32 macro.                       *
 *  2.) tmpl_inttype.h:                                                       *
 *          Header file containing fixed-width integer data types.            *
 *  3.) tmpl_floatint:                                                        *
 *          Header file where the type-punning union is defined.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 10, 2023                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_FLOAT_TO_UINT32_H
#define TMPL_FLOAT_TO_UINT32_H

/*  Location of the TMPL_HAS_FLOATINT32 macro.                                */
#include <libtmpl/include/tmpl_config.h>

/*  This function only works if we have 32-bit float and 32-bit integers.     */
#if TMPL_HAS_FLOATINT32 == 1

/*  Fixed-width integers found here.                                          */
#include <libtmpl/include/tmpl_inttype.h>

/*  tmpl_IEEE754_FloatInt32 union is typedef'd here.                          */
#include <libtmpl/include/tmpl_floatint.h>

/*  The TMPL_INLINE_DECL macro isn't quite what we want. Define the following.*/
#if TMPL_USE_INLINE == 1
#define TMPL_INLINE_FUNCTION static inline
#else
#define TMPL_INLINE_FUNCTION static
#endif

/*  Function for type-punning a 32-bit unsigned integer as a float.           */
TMPL_INLINE_FUNCTION
float tmpl_UInt32_To_Float(tmpl_UInt32 n)
{
    /*  Union for type-punning a float with an integer.                       */
    tmpl_IEEE754_FloatInt32 u;

    /*  Set the integer part of the union to the input.                       */
    u.n = n;

    /*  Return the floating point part.                                       */
    return u.f;
}
/*  End of tmpl_UInt32_To_Float.                                              */

/*  Undefine the macro in case someone wants to #include this file.           */
#undef TMPL_INLINE_FUNCTION

#endif
/*  End of #if TMPL_HAS_FLOATINT32 == 1.                                      */

#endif
/*  End of include guard.                                                     */
