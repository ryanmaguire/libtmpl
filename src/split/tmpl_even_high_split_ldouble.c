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
 *      xhi (long double):                                                    *
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
 *      1.) Depending on compiler and architecture we may need to declare     *
 *          certain variables as volatile. Failure to do so results in a poor *
 *          split. If this function fails to produce a correct split, set     *
 *          USE_VOLATILE to true when building libtmpl.                       *
 *  References:                                                               *
 *      1.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          Library for Double-Double and Quad-Double Arithmetic              *
 *                                                                            *
 *      2.) Schewchuk, J. (October 1997).                                     *
 *          Adaptive Precision Floating-Point Arithmetic                      *
 *          and Fast Robust Geometric Predicates.                             *
 *          Discrete & Computational Geometry Vol 18, Number 3: Pages 305-363 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Contains the TMPL_ALWAYS_INLINE and TMPL_VOLATILE macros.         *
 *  2.) tmpl_float_barrier.h:                                                 *
 *          Provides macros to protect against aggressive optimizations.      *
 *  3.) tmpl_split.h:                                                         *
 *          Function prototype / forward declaration provided here.           *
 *  4.) tmpl_cast.h:                                                          *
 *          Provides the TMPL_CAST macro for C vs. C++ compatibility.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 28, 2024                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/07/07: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added float barrier.           *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE and TMPL_VOLATILE macros found here.                   */
#include <libtmpl/include/tmpl_config.h>

/*  Macros preventing aggressive compiler optimizations given here.           */
#include <libtmpl/include/tmpl_float_barrier.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_split.h>

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

/*  The double-double version only needs to make a cast.                      */
#else

/*  Helper macros for casting with C vs. C++ compatibility.                   */
#include <libtmpl/include/compat/tmpl_cast.h>

#endif
/*  End of double vs. quadruple vs. extended / portable.                      */

/*  Double-double behaves differently than the rest.                          */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  Function for splitting a long double. The high part is returned.          */
TMPL_ALWAYS_INLINE
long double tmpl_LDouble_Even_High_Split(const long double x)
{
    /*  We just need to cast to double since double-double is already split.  */
    const double x_double = TMPL_CAST(x, double);
    return TMPL_CAST(x_double, long double);
}
/*  End of tmpl_LDouble_Even_High_Split.                                      */

/*  All other representations follow the usual splitting algorithm.           */
#else

/*  Function for splitting a long double evenly down the middle.              */
TMPL_ALWAYS_INLINE
long double tmpl_LDouble_Even_High_Split(const long double x)
{
    /*  For compilers / architectures where the barrier macro has no effect,  *
     *  the product variable needs to be declared volatile to correctly       *
     *  perform the split. TMPL_VOLATILE expands to volatile on such systems, *
     *  and nothing otherwise.                                                */
    TMPL_VOLATILE long double prod;

    /*  The remaining variables do not need a volatile qualifier.             */
    long double diff, result;

    /*  The splitting factor saved as a variable.                             */
    const long double splitter = TMPL_LDOUBLE_SPLITTER;

    /*  Scaling the input by the factor rounds off the lower order bits.      */
    prod = x * splitter;

    /*  x * splitter - x may be treated as a single FMA instruction, yielding *
     *  1 round instead of 2. This ruins the split, guard against this.       */
    TMPL_LDOUBLE_BARRIER(prod);

    /*  Remove the lower order bits of the product, which are the higher      *
     *  order bits of the input.                                              */
    diff = prod - x;

    /*  (x * splitter) - ((x * splitter) - x) simplifies to x if the compiler *
     *  aggressively reorders operations. Prevent this with a barrier.        */
    TMPL_LDOUBLE_BARRIER(prod);

    /*  prod now has the higher order bits of x times a scale factor, and     *
     *  diff has only the scale factor. Subtracting recovers the higher order *
     *  bits of the input.                                                    */
    result = prod - diff;

    /*  A final barrier to separate the end of this function from any calling *
     *  functions. This is necessary since this function will likely be       *
     *  inlined when link-time optimization is enabled.                       */
    TMPL_LDOUBLE_BARRIER(result);
    return result;
}
/*  End of tmpl_Double_Even_High_Split.                                       */

#endif
/*  End of double-double vs. everything else.                                 */

/*  Undefine the splitter macro to avoid collisions with other files.         */
#undef TMPL_LDOUBLE_SPLITTER
