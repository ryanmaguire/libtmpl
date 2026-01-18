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
 *                        tmpl_even_high_split_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Retrieves the higher order bits of a long double by splitting.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Even_High_Split                                          *
 *  Purpose:                                                                  *
 *      Returns the input "x" rounded to its higher order bits.               *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      x_hi (long double):                                                   *
 *          The high part of x.                                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      For all implementations besides double-double, we have:               *
 *                                                                            *
 *          xhi = (splitter * x) - ((splitter * x) - x)                       *
 *                                                                            *
 *      If (computer) arithmetic were associative, this would cancel yielding *
 *      xhi = x. Since (computer) arithmetic is not associative, this has the *
 *      effect of zeroing out the lower bits of x.                            *
 *                                                                            *
 *      For double-double, we cast to double and return (as a long double).   *
 *  Notes:                                                                    *
 *      Depending on compiler and architecture we may need to declare certain *
 *      variables as volatile. Failure to do so results in a poor split.      *
 *  References:                                                               *
 *      1.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          "Library for Double-Double and Quad-Double Arithmetic"            *
 *                                                                            *
 *      2.) Schewchuk, J. (October 1997).                                     *
 *          "Adaptive Precision Floating-Point Arithmetic                     *
 *              and Fast Robust Geometric Predicates."                        *
 *          Discrete & Computational Geometry Vol 18, Number 3: Pages 305-363 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_cast.h:                                                          *
 *          Provides a helper macro for C vs. C++ compatibility with casting. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 28, 2024                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_LDOUBLE_EVEN_HIGH_SPLIT_H
#define TMPL_LDOUBLE_EVEN_HIGH_SPLIT_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Following Schewchuk's paper, the split is 2^{1 + floor(p / 2)} + 1, where *
 *  p is the number of bits in the mantissa. Thus xhi and xlo have floor(p/2) *
 *  bits each. It is possible that p = 1 + 2 * floor(p / 2), in which case    *
 *  one might ask "what happens to the last bit?" This is recovered by the    *
 *  sign of xlo.                                                              */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/*  52-bit mantissa. The splitting factor is 2^27 + 1.                        */
#define TMPL_LDOUBLE_SPLITTER (+1.34217729E+08L)

/*  128-bit Quadruple format. 112-bit mantissa, splitter is 2^57 + 1          */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT
#define TMPL_LDOUBLE_SPLITTER (+1.44115188075855873E+17L)

/*  Portable and 80-bit extended. 63-bit mantissa, splitter is 2^32 + 1.      */
#elif TMPL_LDOUBLE_TYPE != TMPL_LDOUBLE_DOUBLEDOUBLE
#define TMPL_LDOUBLE_SPLITTER (+4.294967297E+09L)

#endif
/*  End of double vs. quadruple vs. extended / portable.                      */

/*  Double-double behaves differently than the rest.                          */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  Helper macros for casting with C vs. C++ compatibility.                   */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Function for splitting a long double. The high part is returned.          */
TMPL_INLINE_DECL
long double tmpl_LDouble_Even_High_Split(const long double x)
{
    /*  We just need to cast to double since double-double is already split.  */
    const double x_double = TMPL_CAST(x, double);
    return TMPL_CAST(x_double, long double);
}
/*  End of tmpl_LDouble_Even_High_Split.                                      */

/*  Depending on compiler and architecture, we may need to be very careful    *
 *  about how we split numbers. This first method is the most cautious.       */
#elif defined(TMPL_LDOUBLE_CAUTIOUS_SPLIT)

/*  Function for splitting a long double. The high part is returned.          */
TMPL_INLINE_DECL
long double tmpl_LDouble_Even_High_Split(const long double x)
{
    /*  On i386, using GCC, TCC, or Clang, extra volatile declarations are    *
     *  needed to get the splitting trick to work with double. It doesn't     *
     *  seem to be necessary for long double. Nevertheless, the overly        *
     *  cautious method declares each step as volatile and then splits.       */
    volatile const long double split = x * TMPL_LDOUBLE_SPLITTER;
    volatile const long double tmp = split - x;
    return split - tmp;
}
/*  End of tmpl_LDouble_Even_High_Split.                                      */

/*  For most architectures, one volatile declaration is sufficient.           */
#elif defined(TMPL_LDOUBLE_VOLATILE_SPLIT)

/*  Function for splitting a long double. The high part is returned.          */
TMPL_INLINE_DECL
long double tmpl_LDouble_Even_High_Split(const long double x)
{
    /*  For arm64, ppc64el, and other architectures, this first product must  *
     *  be declared as volatile in the double implementation. Again, for long *
     *  double this seems unnecessary.                                        */
    volatile const long double split = x * TMPL_LDOUBLE_SPLITTER;
    return split - (split - x);
}
/*  End of tmpl_LDouble_Even_High_Split.                                      */

/*  For x86_64 / amd64 we do not need to use volatile at all.                 */
#else

/*  Function for splitting a long double. The high part is returned.          */
TMPL_INLINE_DECL
long double tmpl_LDouble_Even_High_Split(const long double x)
{
    /*  This is the "standard" way to perform a split. It works on x86_64     *
     *  machines for double, and x86_64, arm64, and more for long double.     */
    const long double split = x * TMPL_LDOUBLE_SPLITTER;
    return split - (split - x);
}
/*  End of tmpl_LDouble_Even_High_Split.                                      */

#endif
/*  End of #if defined(TMPL_LDOUBLE_CAUTIOUS_SPLIT).                          */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_LDOUBLE_SPLITTER

#endif
/*  End of include guard.                                                     */
