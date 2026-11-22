/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                              tmpl_sqrt_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Sqrt                                                      *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique non-negative number y such that for  *
 *      non-negative x we have x = y^2.                                       *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (double):                                                      *
 *          The square root of x at double precision.                         *
 *  Called Functions:                                                         *
 *      sqrtsd / vsqrtsd (x86_64 instructions).                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_attributes.h:                                                    *
 *          Provides optional C23 attributes for optimization.                *
 *  2.) tmpl_math.h:                                                          *
 *          Header file providing the forward declaration.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 20, 2026                                             *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration.                                 */
extern double tmpl_Double_Sqrt(const double x);

/*  Function for computing square roots at double precision.                  */
TMPL_CONST_FUNC

/*  If SIMD_FAST_MATH mode is enabled, do not use always_inline. This will    *
 *  prevent the compiler from selecting the SIMD versions.                    */
#if TMPL_USE_SIMD_FAST_MATH != 1
TMPL_ALWAYS_INLINE
#endif

double
tmpl_Double_Sqrt(const double x)
TMPL_UNSEQUENCED
{
    /*  Variable for the output, sqrt(x).                                     */
    double sqrt_x;

    /*  Modern CPUs provide a VEX-encoded version of sqrt.                    */
#if defined(__AVX512F__) || defined(__AVX__) || defined(__AVX2__)
    __asm__("vsqrtsd %1, %1, %0" : "=x" (sqrt_x) : "x" (x));

    /*  The scalar square root function has been provided as an instruction   *
     *  since SSE 2, released in 2000.                                        */
#else
    __asm__("sqrtsd %0, %0" : "=x" (sqrt_x) : "0" (x));

#endif
/*  End of #if defined(__AVX512F__) || defined(__AVX__) || defined(__AVX2__). */

    return sqrt_x;
}
/*  End of tmpl_Double_Sqrt.                                                  */
