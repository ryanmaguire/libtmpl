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
 *                           tmpl_double_to_uint64                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Converts a double to an unsigned 64-bit integer via type-punning.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_To_UInt64                                                 *
 *  Purpose:                                                                  *
 *      Converts a 64-bit double into a 64-bit integer by type-punning.       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      n (tmpl_UInt64):                                                      *
 *          The integer representing the bits of x.                           *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a union to type-pun a double as a 64-bit integer and return.      *
 *  Notes:                                                                    *
 *      This function assumes 64-bit double is implemented using IEEE-754,    *
 *      and that 64-bit unsigned integers are available as well as            *
 *      type-punning. The config.c file should determine this for you when    *
 *      building libtmpl.                                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file with TMPL_HAS_FLOATINT64 macro.                       *
 *  2.) tmpl_inttype.h:                                                       *
 *          Header file containing fixed-width integer data types.            *
 *  3.) tmpl_floatint_double.h:                                               *
 *          Header file where the type-punning union is defined.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 10, 2023                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_DOUBLE_TO_UINT64_H
#define TMPL_DOUBLE_TO_UINT64_H

/*  Location of the TMPL_HAS_FLOATINT64 macro.                                */
#include <libtmpl/include/tmpl_config.h>

/*  This function only works if we have 64-bit double and 64-bit integers.    */
#if TMPL_HAS_FLOATINT64 == 1

/*  Fixed-width integers found here.                                          */
#include <libtmpl/include/tmpl_inttype.h>

/*  tmpl_IEEE754_FloatInt64 union is typedef'd here.                          */
#include <libtmpl/include/types/tmpl_floatint_double.h>

/*  Function for type-punning a double as a 64-bit unsigned integer.          */
TMPL_STATIC_INLINE
tmpl_UInt64 tmpl_Double_To_UInt64(double x)
{
    /*  Union for type-punning a double with an integer.                      */
    tmpl_IEEE754_FloatInt64 u;

    /*  Set the double part of the union to the input.                        */
    u.f = x;

    /*  Return the 64-bit unsigned integer part.                              */
    return u.n;
}
/*  End of tmpl_Double_To_UInt64.                                             */

#endif
/*  End of #if TMPL_HAS_FLOATINT64 == 1.                                      */

#endif
/*  End of include guard.                                                     */
