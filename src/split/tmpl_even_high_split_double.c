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

/*  Inline assembly is only used when requested by the user.                  */
#if TMPL_USE_INLINE_ASM == 1

/*  GCC, Clang, and Solaris Developer Studio C all support inline assembly.   *
 *  Note, several compilers (AOCC, ICX, IBM Open XL C, etc.) define the       *
 *  __clang__ macro, and hence will also trigger this branch.                 */
#if defined(__GNUC__) || defined(__clang__) || defined(__SUNPRO_C)

/*  AVX, AVX2, and AVX-512 support VEX scalar operations that can be used.    */
#if defined(__AVX__) || defined(__AVX2__) || defined(__AVX512F__)

/******************************************************************************
 *                      x86-64 / amd64 with AVX Support                       *
 ******************************************************************************/

/*  Function for splitting a double evenly down the middle.                   */
TMPL_ALWAYS_INLINE
double tmpl_Double_Even_High_Split(const double x)
{
    /*  The scale factor for the split is 2^27 + 1.                           */
    const double c = 134217729.0;

    /*  Variables for the product, difference, and output, respectively.      */
    double prod, diff, result;

    /*  With AVX / AVX2 / AVX-512, the split can be performed in 3 lines.     */
    __asm__(

        /*  AVX, AVX2, and AVX-512 have VEX instructions. First set           *
         *  prod = x * c. This rounds out the lower order bits of the input.  */
        "vmulsd %[c], %[x], %[prod]\n\t"

        /*  Compute diff = prod - x, which clears out the lower order bits of *
         *  the product, which means the bits from "x" have been removed.     */
        "vsubsd %[x], %[prod], %[diff]\n\t"

        /*  Finally, compute result = prod - diff. Since diff contains only   *
         *  the higher bits of the product, and since prod contains the bits  *
         *  from the product and the higher bits from the input, this clears  *
         *  the higher bits from the product, leaving us only with the higher *
         *  bits from the input.                                              */
        "vsubsd %[diff], %[prod], %[result]"

        :

        /*  The difference requires the product and the input x to have been  *
         *  already computed. Use an early clobber (&) with the product and   *
         *  difference to prevent the compiler from overwriting registers.    */
        [prod] "=&x" (prod),
        [diff] "=&x" (diff),

        /*  The result is output only, and loaded into an SSE / AVX register. */
        [result] "=x"  (result)

        :

        /*  The input comes from a register, use "x" for this.                */
        [x] "x" (x),

        /*  The constant c will likely be stored in read-only memory, but it  *
         *  may also live in a register. "x" allows registers, "m" allows     *
         *  memory, provide both options to the compiler.                     */
        [c] "xm" (c)
    );

    return result;
}
/*  End of tmpl_Double_Even_High_Split.                                       */

/*  SSE2 support means we can use XMM registers.                              */
#elif defined(__SSE2__) || defined(__SSE3__) || defined(__SSE4_1__)

/******************************************************************************
 *                      x86-64 / amd64 with SSE Support                       *
 ******************************************************************************/

/*  Function for splitting a double evenly down the middle.                   */
TMPL_ALWAYS_INLINE
double tmpl_Double_Even_High_Split(const double x)
{
    /*  The scale factor for the split is 2^27 + 1.                           */
    const double c = 134217729.0;

    /*  Variables for the product, difference, and output, respectively.      */
    double prod, diff, result;

    /*  With SSE we operate on two operands at a time. This means extra moves *
     *  are required to perform something like prod = x * c.                  */
    __asm__(

        /*  Load the constant 2^27 + 1 into a register.                       */
        "movsd %[c], %[prod]\n\t"

        /*  prod now has c stored in it. Compute x * c and store it in prod.  */
        "mulsd %[x], %[prod]\n\t"

        /*  The difference is x * c - x. Store x * c in diff.                 */
        "movapd %[prod], %[diff]\n\t"

        /*  Compute diff = prod - x, which clears out the lower order bits of *
         *  the product, which means the bits from "x" have been removed.     */
        "subsd %[x], %[diff]\n\t"

        /*  Finally, compute result = prod - diff. Since diff contains only   *
         *  the higher bits of the product, and since prod contains the bits  *
         *  from the product and the higher bits from the input, this clears  *
         *  the higher bits from the product, leaving us only with the higher *
         *  bits from the input.                                              */
        "subsd %[diff], %[prod]\n\t"

        /*  Copy the final value into the result so it may be returned.       */
        "movapd %[prod], %[result]"

        :

        /*  Use "x" for SSE registers.                                        */
        [prod] "=&x" (prod),
        [diff] "=&x" (diff),
        [result] "=x" (result)

        :

        /*  The input comes from a register, use "x" for this.                */
        [x] "x" (x),

        /*  The constant will live in a register or memory. Use "xm".         */
        [c] "xm" (c)
    );

    return result;
}
/*  End of tmpl_Double_Even_High_Split.                                       */

/*  armv8 and higher have hardware floating-point instructions.               */
#elif defined(__aarch64__)

/******************************************************************************
 *                             armv8-a / aarch64                              *
 ******************************************************************************/

/*  Function for splitting a double evenly down the middle.                   */
TMPL_ALWAYS_INLINE
double tmpl_Double_Even_High_Split(const double x)
{
    /*  The scale factor for the split is 2^27 + 1.                           */
    const double c = 134217729.0;

    /*  Variables for the product, difference, and output, respectively.      */
    double prod, diff, result;

    /*  Splitting algorithm using armv8 (aarch64) instructions.               */
    __asm__(

        /*  Set prod = x * c.                                                 */
        "fmul %d[prod], %d[x], %d[c]\n\t"

        /*  Compute diff = prod - x = x * c - x.                              */
        "fsub %d[diff], %d[prod], %d[x]\n\t"

        /*  Lastly, compute result = prod - diff = (x * c) - ((x * c) - x).   */
        "fsub %d[result], %d[prod], %d[diff]"

        :

        /*  "w" is the identifier for 64-bit floating-point registers d0-d31. */
        [prod] "=&w" (prod),
        [diff] "=&w" (diff),
        [result] "=w" (result)

        :

        /*  The inputs live in registers, use "w" for this.                   */
        [x] "w" (x),
        [c] "w" (c)
    );

    return result;
}
/*  End of tmpl_Double_Even_High_Split.                                       */

/*  armv7 may have VFP registers but it may also use soft float. Check first. */
#elif defined(__arm__) && defined(__ARM_PCS_VFP) && defined(__VFP_FP__)

/******************************************************************************
 *                         armv7 with Hardware Float                          *
 ******************************************************************************/

/*  Function for splitting a double evenly down the middle.                   */
TMPL_ALWAYS_INLINE
double tmpl_Double_Even_High_Split(const double x)
{
    /*  The scale factor for the split is 2^27 + 1.                           */
    const double c = 134217729.0;

    /*  Variables for the product, difference, and output, respectively.      */
    double prod, diff, result;

    /*  Splitting algorithm using armv7 (armhf) instructions.                 */
    __asm__(

        /*  Set prod = x * c.                                                 */
        "vmul.f64 %P[prod], %P[x], %P[c]\n\t"

        /*  Compute diff = prod - x = x * c - x.                              */
        "vsub.f64 %P[diff], %P[prod], %P[x]\n\t"

        /*  Lastly, compute result = prod - diff = (x * c) - ((x * c) - x).   */
        "vsub.f64 %P[result], %P[prod], %P[diff]"

        :

        /*  "w" is the identifier for 64-bit floating-point registers d0-d31, *
         *  just like aarch64 / armv8.                                        */
        [prod] "=&w" (prod),
        [diff] "=&w" (diff),
        [result] "=w"  (result)

        :

        /*  The inputs live in registers, use "w" for this.                   */
        [x] "w" (x),
        [c] "w" (c)
    );

    return result;
}
/*  End of tmpl_Double_Even_High_Split.                                       */

/*  GCC can magically handle PowerPC, ppc64, and ppc64le with the same code.  */
#elif defined(__powerpc__)

/******************************************************************************
 *           PowerPC (32-bit / 64-bit / little-endian / big-endian)           *
 ******************************************************************************/

/*  Function for splitting a double evenly down the middle.                   */
TMPL_ALWAYS_INLINE
double tmpl_Double_Even_High_Split(const double x)
{
    /*  The scale factor for the split is 2^27 + 1.                           */
    const double c = 134217729.0;

    /*  Variables for the product, difference, and output, respectively.      */
    double prod, diff, result;

    /*  Splitting algorithm with PowerPC assembly.                            */
    __asm__(

        /*  Compute prod = x * c.                                             */
        "fmul %[prod], %[x], %[c]\n\t"

        /*  Compute diff = prod - x.                                          */
        "fsub %[diff], %[prod], %[x]\n\t"

        /*  Lastly, compute result = prod - diff.                             */
        "fsub %[result], %[prod], %[diff]"

        :

        /*  "f" is the identifier for 64-bit floating-point registers.        */
        [prod] "=&f" (prod),
        [diff] "=&f" (diff),
        [result] "=f"  (result)

        :

        /*  The inputs may live in memory or registers, use "fm" for this.    */
        [x] "fm" (x),
        [c] "fm" (c)
    );

    return result;
}
/*  End of tmpl_Double_Even_High_Split.                                       */

#else
/*  Else for AVX vs. SSE vs. ...                                              */

/*  Other architectures (HPPA, SH4, SPARC, SPARC64) use the default method.   */
#define TMPL_DOUBLE_EVEN_HIGH_SPLIT_USE_DEFAULT 1

#endif
/*  End of AVX vs SSE vs ...                                                  */

#else
/*  Else for GCC / Clang / Solaris C.                                         */

/*  Recent versions of IBM XL C and Intel's ICX provide the __clang__ macro,  *
 *  and hence will be handled by one of the versions above. Other compilers   *
 *  like TCC, PCC, and MSVC use the default method.                           */
#define TMPL_DOUBLE_EVEN_HIGH_SPLIT_USE_DEFAULT 1

#endif
/*  End of GCC / Clang / Solaris C.                                           */

#else
/*  Else for #if TMPL_USE_INLINE_ASM == 1.                                    */

/*  If inline assembly is not requested, we'll use the default method below.  */
#define TMPL_DOUBLE_EVEN_HIGH_SPLIT_USE_DEFAULT 1

#endif
/*  End of #if TMPL_USE_INLINE_ASM == 1.                                      */

/*  If this macro is set, we need to provide a generic implementation.        */
#ifdef TMPL_DOUBLE_EVEN_HIGH_SPLIT_USE_DEFAULT

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

/*  Undefine this macro to avoid collisions with other files.                 */
#undef TMPL_DOUBLE_EVEN_HIGH_SPLIT_USE_DEFAULT

#endif
/*  End of #ifdef TMPL_DOUBLE_EVEN_HIGH_SPLIT_USE_DEFAULT.                    */
