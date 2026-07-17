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
 *                                tmpl_two_diff                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides 2Diff, Fast2Diff, and other 2Diff-like algorithms.           *
 *  Notes:                                                                    *
 *      1.) The 2Diff algorithms use the floating-point barriers found in     *
 *          tmpl_float_barrier.h to protect against aggressive compiler       *
 *          optimizations (associative reordering, FMA contraction, etc.).    *
 *          On some compilers (GCC and Clang, for example), these macros      *
 *          produce no-ops. On others these macros use the volatile keyword   *
 *          to safely carry out the arithmetic.                               *
 *                                                                            *
 *      2.) On compilers supporting the restrict keyword, the output          *
 *          variables are declared as restrict pointers. This requires that   *
 *          these variables point to different locations. To properly use the *
 *          various 2Diff functions, this should be true regardless of        *
 *          whether or not restrict is supported.                             *
 *                                                                            *
 *      3.) None of the 2Diff functions check for NULL pointers.              *
 *                                                                            *
 *      4.) None of the 2Diff functions check for NaN or infinity.            *
 *                                                                            *
 *      5.) Float, double, and long double versions are provided.             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file providing TMPL_INLINE_DECL and other macros.          *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 13, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TWO_DIFF_H
#define TMPL_TWO_DIFF_H

/*  TMPL_RESTRICT macro found here.                                           */
#include <libtmpl/include/tmpl_config.h>

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Fast_Two_Diff                                             *
 *  Purpose:                                                                  *
 *      Performs the Fast2Diff algorithm for floating-point subtraction.      *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      out (double * TMPL_RESTRICT const):                                   *
 *          The floating-point difference of x and y is stored here.          *
 *      err (double * TMPL_RESTRICT const):                                   *
 *          The error, (x - y) - fl(x - y), is stored here, where "-" denotes *
 *          exact subtraction, and "fl" is the floating-point round operation.*
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Fast2Diff assumes |x| >= |y|.                                     *
 ******************************************************************************/
extern void
tmpl_Double_Fast_Two_Diff(const double x,
                          const double y,
                          double * TMPL_RESTRICT const out,
                          double * TMPL_RESTRICT const err);

extern void
tmpl_Float_Fast_Two_Diff(const float x,
                         const float y,
                         float * TMPL_RESTRICT const out,
                         float * TMPL_RESTRICT const err);

extern void
tmpl_LDouble_Fast_Two_Diff(const long double x,
                           const long double y,
                           long double * TMPL_RESTRICT const out,
                           long double * TMPL_RESTRICT const err);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Two_Diff                                                  *
 *  Purpose:                                                                  *
 *      Performs the standard 2Diff algorithm for floating-point subtraction. *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      out (double * TMPL_RESTRICT const):                                   *
 *          The floating-point difference of x and y is stored here.          *
 *      err (double * TMPL_RESTRICT const):                                   *
 *          The error, (x - y) - fl(x - y), is stored here, where "-" denotes *
 *          exact subtraction, and "fl" is the floating-point round operation.*
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) 2Diff does not require |x| >= |y|, but it requires twice as many  *
 *          arithmetic operations as Fast2Diff.                               *
 ******************************************************************************/
extern void
tmpl_Double_Two_Diff(const double x,
                     const double y,
                     double * TMPL_RESTRICT const out,
                     double * TMPL_RESTRICT const err);

extern void
tmpl_Float_Two_Diff(const float x,
                    const float y,
                    float * TMPL_RESTRICT const out,
                    float * TMPL_RESTRICT const err);

extern void
tmpl_LDouble_Two_Diff(const long double x,
                      const long double y,
                      long double * TMPL_RESTRICT const out,
                      long double * TMPL_RESTRICT const err);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
