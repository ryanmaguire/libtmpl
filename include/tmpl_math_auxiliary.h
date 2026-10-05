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
 *                            tmpl_math_auxiliary                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides helper functions for libtmpl's libm implementation.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_attributes.h:                                                    *
 *          Provides (optional) C23 attributes for optimization.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 1, 2026                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_AUXILIARY_H
#define TMPL_MATH_AUXILIARY_H

/*  Optional C23 attributes for optimization are found here.                  */
#include <libtmpl/include/tmpl_attributes.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Exp_Remez                                                 *
 *  Purpose:                                                                  *
 *      Computes exp(x) using a Remez polynomial for |x| < 1 / 8.             *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number in the interval [-1 / 8, 1 / 8].                    *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          exp(x) to double precision.                                       *
 ******************************************************************************/
TMPL_CONST_FUNC
extern double
tmpl_Double_Exp_Remez(const double x)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Exp_Remez(const float x)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Exp_Remez(const long double x)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Exp_Rat_Remez                                             *
 *  Purpose:                                                                  *
 *      Computes exp(x) using a rational Remez approximation for |x| < 1.     *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number in the interval [-1, 1].                            *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          exp(x) to double precision.                                       *
 ******************************************************************************/
TMPL_CONST_FUNC
extern double
tmpl_Double_Exp_Rat_Remez(const double x)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Exp_Rat_Remez(const float x)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Exp_Rat_Remez(const long double x)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Exp_Kernel                                                *
 *  Purpose:                                                                  *
 *      Computes exp(x) for |x| > 1.                                          *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      shift (const double):                                                 *
 *          The shift factor to avoid underflow or overflow.                  *
 *      scale (const double):                                                 *
 *          The scale factor used to cancel the shift factor.                 *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          exp(x) to double precision.                                       *
 ******************************************************************************/
TMPL_CONST_FUNC
extern double
tmpl_Double_Exp_Kernel(const double x,
                       const double shift,
                       const double scale)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Exp_Kernel(const float x,
                      const float shift,
                      const float scale)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Exp_Kernel(const long double x,
                        const long double shift,
                        const long double scale)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Exp_Neg_Kernel                                            *
 *  Purpose:                                                                  *
 *      Computes exp(x) for log(DBL_MIN) < x < -1.                            *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          The exponential function of x, exp(x).                            *
 ******************************************************************************/
TMPL_CONST_FUNC
extern double
tmpl_Double_Exp_Neg_Kernel(const double x)
TMPL_UNSEQUENCED;

#if 0
TMPL_CONST_FUNC
extern float
tmpl_Float_Exp_Neg_Kernel(const float x)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
long double
tmpl_LDouble_Exp_Neg_Kernel(const long double x)
TMPL_UNSEQUENCED;
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Exp_Pos_Kernel                                            *
 *  Purpose:                                                                  *
 *      Computes exp(x) for 1 < x < log(DBL_MAX).                             *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          The exponential function of x, exp(x).                            *
 ******************************************************************************/
TMPL_CONST_FUNC
extern double
tmpl_Double_Exp_Pos_Kernel(const double x)
TMPL_UNSEQUENCED;

#if 0
TMPL_CONST_FUNC
extern float
tmpl_Float_Exp_Pos_Kernel(const float x)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Exp_Pos_Kernel(const long double x)
TMPL_UNSEQUENCED;
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Expm1_Remez_Small                                         *
 *  Purpose:                                                                  *
 *      Computes exp(x) - 1 using a Remez polynomial for |x| < 1 / 256.       *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number in the interval [-1 / 256, 1 / 256].                *
 *  Output:                                                                   *
 *      expm1_x (double):                                                     *
 *          exp(x) - 1 to double precision.                                   *
 ******************************************************************************/
TMPL_CONST_FUNC
extern double
tmpl_Double_Expm1_Remez_Small(const double x)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Expm1_Remez_Small(const float x)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Expm1_Remez_Small(const long double x)
TMPL_UNSEQUENCED;

#endif
/*  End of include guard.                                                     */
