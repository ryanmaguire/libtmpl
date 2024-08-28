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
 *                           tmpl_high_split_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Retrieves the higher order bits of a float by splitting.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_High_Split                                                 *
 *  Purpose:                                                                  *
 *      Returns the input "x" truncated to its higher order bits.             *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *      splitter (float):                                                     *
 *          The splitting factor. This will most likely by 2^n + 1, where you *
 *          want the higher 23 - n bits to be returned, assuming float has    *
 *          23 bits in the mantissa.                                          *
 *  Output:                                                                   *
 *      x_hi (float):                                                         *
 *          The high part of x.                                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Assuming IEEE-754 format, we have:                                    *
 *                                                                            *
 *          xhi = (splitter * x) - ((splitter * x) - x)                       *
 *                                                                            *
 *      If (computer) arithmetic was associative, this would cancel yielding  *
 *      xhi = x. Since (computer) arithmetic is not associative, this has the *
 *      effect of zeroing out the lower bits of x.                            *
 *  Notes:                                                                    *
 *      Depending on compiler and architecture we may need to declare certain *
 *      variables as volatile. Failure to do so results in a poor split.      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 28, 2024                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_FLOAT_HIGH_SPLIT_H
#define TMPL_FLOAT_HIGH_SPLIT_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Depending on compiler and architecture, we may need to be very careful    *
 *  about how we split numbers. This first method is the most cautious.       */
#if defined(TMPL_FLOAT_CAUTIOUS_SPLIT)

/*  Function for splitting a float into two parts. The high part is returned. */
TMPL_INLINE_DECL
float tmpl_Float_High_Split(float x, float splitter)
{
    /*  Declaring everything as volatile almost guarantees the split works.   */
    volatile const float split = x * splitter;
    volatile const float tmp = split - x;
    return split - tmp;
}
/*  End of tmpl_Float_High_Split.                                             */

/*  For most architectures, one volatile declaration is sufficient.           */
#elif defined(TMPL_FLOAT_VOLATILE_SPLIT)

/*  Function for splitting a float into two parts. The high part is returned. */
TMPL_INLINE_DECL
float tmpl_Float_High_Split(float x, float splitter)
{
    /*  It is usually sufficient to declare the split product as volatile.    *
     *  With optimizations on this is only slightly slower (1-3%) than        *
     *  without the volatile declaration, but splits properly.                */
    volatile const float split = x * splitter;
    return split - (split - x);
}
/*  End of tmpl_Float_High_Split.                                             */

/*  For x86_64 / amd64 we do not need to use volatile at all.                 */
#else

/*  Function for splitting a float into two parts. The high part is returned. */
TMPL_INLINE_DECL
float tmpl_Float_High_Split(float x, float splitter)
{
    /*  This is the "standard" way to perform a split. No volatile used.      */
    const float split = x * splitter;
    return split - (split - x);
}
/*  End of tmpl_Float_High_Split.                                             */

#endif
/*  End of #if defined(TMPL_FLOAT_CAUTIOUS_SPLIT).                            */

#endif
/*  End of include guard.                                                     */
