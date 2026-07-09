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
 *      Returns the input "x" rounded to its higher order bits. The split     *
 *      is done "evenly" down the middle so that xhi and xlo both have the    *
 *      same number of bits of x.                                             *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      xhi (double):                                                         *
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
 *      1.) With GCC, Clang, ICX, AOCC, IBM Open XL C, and Solaris Developer  *
 *          Studio C, and on supported architectures (x86-64 with SSE or AVX  *
 *          support, armv7, armv8, and PowerPC), inline assembly is provided. *
 *          For other compilers and architectures, the standard Dekker        *
 *          algorithm is provided in C with the TMPL_VOLATILE macro. This     *
 *          expands to volatile if libtmpl was compiled with USE_VOLATILE at  *
 *          build time, and nothing otherwise. Depending on compiler flags    *
 *          and architecture, you may need to set USE_VOLATILE to true in     *
 *          order to produce a correct split.                                 *
 *                                                                            *
 *      2.) For compilers that support __asm__, the default C version uses    *
 *          floating-point barriers to protect against optimizations. On most *
 *          architectures (x86-64, aarch64, PowerPC, SPARC, and more), when   *
 *          used with GCC or Clang, the barriers become no-ops and results in *
 *          optimal code that produces a correct split. On some architectures *
 *          these barriers result in redundant move instructions. It is still *
 *          faster to use these barriers instead of using volatile.           *
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
 *          Contains several configuration macros.                            *
 *  2.) tmpl_float_barrier.h:                                                 *
 *          Provides macros to protect against aggressive optimizations.      *
 *  3.) tmpl_split.h:                                                         *
 *          Function prototype / forward declaration provided here.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 28, 2024                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/07/07: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added asm versions.            *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE, TMPL_VOLATILE, and TMPL_USE_INLINE_ASM found here.    */
#include <libtmpl/include/tmpl_config.h>

/*  Macros preventing aggressive compiler optimizations given here.           */
#include <libtmpl/include/tmpl_float_barrier.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_split.h>

/*  Function for splitting a double evenly down the middle.                   */
TMPL_ALWAYS_INLINE
double tmpl_Double_Even_High_Split(const double x)
{
    /*  For compilers / architectures where the barrier macro has no effect,  *
     *  the product variable needs to be declared volatile to correctly       *
     *  perform the split. TMPL_VOLATILE expands to volatile on such systems, *
     *  and nothing otherwise.                                                */
    TMPL_VOLATILE double prod;

    /*  The remaining variables do not need a volatile qualifier.             */
    double diff, result;

    /*  The splitting factor is 2^27 + 1. When link-time optimization is      *
     *  enabled, this function will usually be inlined across translation     *
     *  units since it produces only a few instructions (3 on CPUs with AVX   *
     *  support, 6 on armv8 CPUs). Because of this we may need a barrier at   *
     *  the start of the function to separate this function from any calling  *
     *  functions. Unit tests indicate this is unnecessary across all tested  *
     *  architectures, but if it is, replace the following line with:         *
     *                                                                        *
     *      double splitter = 134217729.0;                                    *
     *      TMPL_DOUBLE_BARRIER(splitter);                                    *
     *                                                                        *
     *  This may produce an additional move or load on some architectures,    *
     *  but it is the more cautious method. By default, we simply use a       *
     *  constant and avoid applying a barrier to it.                          */
    const double splitter = 134217729.0;

    /*  Scaling the input by 2^27 + 1 rounds off the lower order bits.        */
    prod = x * splitter;

    /*  x * splitter - x may be treated as a single FMA instruction, yielding *
     *  1 round instead of 2. This ruins the split, guard against this.       */
    TMPL_DOUBLE_BARRIER(prod);

    /*  Remove the lower order bits of the product, which are the higher      *
     *  order bits of the input.                                              */
    diff = prod - x;

    /*  (x * splitter) - ((x * splitter) - x) simplifies to x if the compiler *
     *  aggressively reorders operations. Prevent this with a barrier.        */
    TMPL_DOUBLE_BARRIER(diff);

    /*  prod now has the higher order bits of x times a scale factor, and     *
     *  diff has only the scale factor. Subtracting recovers the higher order *
     *  bits of the input.                                                    */
    result = prod - diff;

    /*  A final barrier to separate the end of this function from any calling *
     *  functions. This is necessary since this function will likely be       *
     *  inlined when link-time optimization is enabled.                       */
    TMPL_DOUBLE_BARRIER(result);
    return result;
}
/*  End of tmpl_Double_Even_High_Split.                                       */
