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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SPLIT_H
#define TMPL_SPLIT_H

/*  The TMPL_USE_INLINE macro is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Even_High_Split                                           *
 *  Purpose:                                                                  *
 *      Splits a double and retrieves the higher order bits.                  *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      x_hi (double):                                                        *
 *          The high part of x.                                               *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern double tmpl_Double_Even_High_Split(const double x);
extern float tmpl_Float_Even_High_Split(const float x);
extern long double tmpl_LDouble_Even_High_Split(const long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_High_Split                                                *
 *  Purpose:                                                                  *
 *      Splits a double and retrieves the higher order bits.                  *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      splitter (const double):                                              *
 *          The splitting factor. This should be 2^n + 1 if you want the      *
 *          higher 53 - n bits, assuming double has a 52-bit mantissa.        *
 *  Output:                                                                   *
 *      x_hi (double):                                                        *
 *          The high part of x.                                               *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern double tmpl_Double_High_Split(const double x, const double splitter);
extern float tmpl_Float_High_Split(const float x, const float splitter);

/*  Double-Double is split differently than the other implementations. Since  *
 *  double-double is literally two doubles together, the splitting factor is  *
 *  of type "double" instead of "long double."                                */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  Function for splitting a double-double into two parts using a             *
 *  double-precision splitter. The high part is returned.                     */
extern long double
tmpl_LDouble_High_Split(const long double x, const double splitter);

/*  All other versions are treated in a similar manner to float and double.   */
#else

/*  Function for splitting a long double into two parts. The high part        *
 *  is returned.                                                              */
extern long double
tmpl_LDouble_High_Split(const long double x, const long double splitter);

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE.                */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Left_Difference                                           *
 *  Purpose:                                                                  *
 *      Performs the subtraction (a - b) - c without associative reordering.  *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      z (const double):                                                     *
 *          A third real number.                                              *
 *  Output:                                                                   *
 *      left_diff (double):                                                   *
 *          The floating-point difference (a - b) - c, in that order.         *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern double
tmpl_Double_Left_Difference(const double a,
                            const double b,
                            const double c);

extern float
tmpl_Float_Left_Difference(const float a,
                           const float b,
                           const float c);

extern long double
tmpl_LDouble_Left_Difference(const long double a,
                             const long double b,
                             const long double c);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Right_Difference                                          *
 *  Purpose:                                                                  *
 *      Performs the subtraction a - (b - c) without associative reordering.  *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      z (const double):                                                     *
 *          A third real number.                                              *
 *  Output:                                                                   *
 *      right_diff (double):                                                  *
 *          The floating-point difference a - (b - c), in that order.         *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern double
tmpl_Double_Right_Difference(const double a,
                             const double b,
                             const double c);

extern float
tmpl_Float_Right_Difference(const float a,
                            const float b,
                            const float c);

extern long double
tmpl_LDouble_Right_Difference(const long double a,
                              const long double b,
                              const long double c);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
