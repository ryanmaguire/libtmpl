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
 *                         tmpl_even_high_split_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Retrieves the higher order bits of a double by splitting.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Even_High_Split                                           *
 *  Purpose:                                                                  *
 *      Returns the input "x" truncated to its higher order bits. The split   *
 *      is done "evenly" down the middle so that x_hi and x_lo both have the  *
 *      same number of bits of x.                                             *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      x_hi (double):                                                        *
 *          The high part of x.                                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Assuming IEEE-754 format, we have:                                    *
 *                                                                            *
 *          xhi = (splitter * x) - ((splitter * x) - x)                       *
 *                                                                            *
 *      where splitter = 2^27 + 1. If (computer) arithmetic were associative, *
 *      this would cancel yielding xhi = x. Since (computer) arithmetic is    *
 *      not associative, this has the effect of zeroing out the lower bits    *
 *      of x. In particular, if double has a 52-bit mantissa, xhi has the     *
 *      upper 26 bits stored in it, correctly rounded.                        *
 *  Notes:                                                                    *
 *      Depending on compiler and architecture we may need to declare certain *
 *      variables as volatile. Failure to do so results in a poor split.      *
 *  References:                                                               *
 *      1.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          "Library for Double-Double and Quad-Double Arithmetic"            *
 *      2.) Schewchuk, J. (October 1997).                                     *
 *          "Adaptive Precision Floating-Point Arithmetic                     *
 *              and Fast Robust Geometric Predicates."                        *
 *          Discrete & Computational Geometry Vol 18, Number 3: Pages 305-363 *
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
#ifndef TMPL_DOUBLE_EVEN_HIGH_SPLIT_H
#define TMPL_DOUBLE_EVEN_HIGH_SPLIT_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Depending on compiler and architecture, we may need to be very careful    *
 *  about how we split numbers. This first method is the most cautious.       */
#if defined(TMPL_DOUBLE_CAUTIOUS_SPLIT)

/*  Function for splitting a double into two parts. The high part is returned.*/
TMPL_INLINE_DECL
double tmpl_Double_Even_High_Split(double x)
{
    /*  On i386, using GCC, TCC, or Clang, extra volatile declarations were   *
     *  needed to get the splitting trick to work. Without these volatile     *
     *  statements a call to FMA is used instead, which ruins the split.      */
    volatile const double split = x * 134217729.0;
    volatile const double tmp = split - x;
    return split - tmp;
}
/*  End of tmpl_Double_Even_High_Split.                                       */

/*  For most architectures, one volatile declaration is sufficient.           */
#elif defined(TMPL_DOUBLE_VOLATILE_SPLIT)

/*  Function for splitting a double into two parts. The high part is returned.*/
TMPL_INLINE_DECL
double tmpl_Double_Even_High_Split(double x)
{
    /*  For arm64, ppc64el, and other architectures, this first product must  *
     *  be declared as volatile. Failure to do so makes the compiler use FMA  *
     *  which ruins the split. This costs a bit of performance (about 1-3%)   *
     *  but the split is performed correctly.                                 */
    volatile const double split = x * 134217729.0;
    return split - (split - x);
}
/*  End of tmpl_Double_Even_High_Split.                                       */

/*  For x86_64 / amd64 we do not need to use volatile at all.                 */
#else

/*  Function for splitting a double into two parts. The high part is returned.*/
TMPL_INLINE_DECL
double tmpl_Double_Even_High_Split(double x)
{
    /*  This is the "standard" way to perform a split. It works on x86_64     *
     *  machines and no volatile declaration is required.                     */
    const double split = x * 134217729.0;
    return split - (split - x);
}
/*  End of tmpl_Double_Even_High_Split.                                       */

#endif
/*  End of #if defined(TMPL_DOUBLE_CAUTIOUS_SPLIT).                           */

#endif
/*  End of include guard.                                                     */
