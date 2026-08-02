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
 *                             tmpl_doubledouble                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a software implementation of double-double.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_attributes.h:                                                    *
 *          Provides (optional) C23 attributes for optimization.              *
 *  2.) tmpl_doubledouble_double.h:                                           *
 *          Contains the double-double typedef.                               *
 *  3.) tmpl_doubledouble_ldouble.h:                                          *
 *          Contains the long-double-double typedef.                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 27, 2024                                                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_DOUBLEDOUBLE_H
#define TMPL_DOUBLEDOUBLE_H

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  The double-double and long-double-double typedefs are found here.         */
#include <libtmpl/include/types/tmpl_doubledouble_double.h>
#include <libtmpl/include/types/tmpl_doubledouble_ldouble.h>

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_DoubleDouble_Add                                                 *
 *  Purpose:                                                                  *
 *      Performs the (safe) sum of two double-doubles.                        *
 *  Arguments:                                                                *
 *      x (const tmpl_DoubleDouble * const):                                  *
 *          A double-double.                                                  *
 *      y (const tmpl_DoubleDouble * const):                                  *
 *          Another double-double.                                            *
 *  Output:                                                                   *
 *      sum (tmpl_DoubleDouble):                                              *
 *          The double-double sum x + y.                                      *
 *  Notes:                                                                    *
 *      1.) long double-double version is also provided.                      *
 ******************************************************************************/
TMPL_PURE_FUNC
extern tmpl_DoubleDouble
tmpl_DoubleDouble_Add(const tmpl_DoubleDouble * const x,
                      const tmpl_DoubleDouble * const y)
TMPL_UNSEQUENCED;

TMPL_PURE_FUNC
extern tmpl_LongDoubleDouble
tmpl_LDoubleDouble_Add(const tmpl_LongDoubleDouble * const x,
                       const tmpl_LongDoubleDouble * const y)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_DoubleDouble_Add_Scalar                                          *
 *  Purpose:                                                                  *
 *      Adds a double to a double-double.                                     *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A double-precision floating-point number.                         *
 *      y (const tmpl_DoubleDouble * const):                                  *
 *          A double-double real number.                                      *
 *  Output:                                                                   *
 *      sum (tmpl_DoubleDouble):                                              *
 *          The double-double sum x + y.                                      *
 *  Notes:                                                                    *
 *      1.) long double-double version is also provided.                      *
 ******************************************************************************/
TMPL_PURE_FUNC
extern tmpl_DoubleDouble
tmpl_DoubleDouble_Add_Scalar(const double x,
                             const tmpl_DoubleDouble * const y)
TMPL_UNSEQUENCED;

TMPL_PURE_FUNC
extern tmpl_LongDoubleDouble
tmpl_LDoubleDouble_Add_Scalar(const long double x,
                              const tmpl_LongDoubleDouble * const y)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_DoubleDouble_Quick_Add                                           *
 *  Purpose:                                                                  *
 *      Performs the (non-safe) sum of two double-doubles.                    *
 *  Arguments:                                                                *
 *      x (const tmpl_DoubleDouble * const):                                  *
 *          A double-double.                                                  *
 *      y (const tmpl_DoubleDouble * const):                                  *
 *          Another double-double.                                            *
 *  Output:                                                                   *
 *      sum (tmpl_DoubleDouble):                                              *
 *          The double-double sum x + y.                                      *
 *  Notes:                                                                    *
 *      1.) This algorithm works just as well as the safe add when x and y    *
 *          have the same sign. Problems arise if one is negative and one is  *
 *          positive. You may also use this algorithm safely if |x| >> |y|.   *
 *                                                                            *
 *      2.) long double-double version is also provided.                      *
 ******************************************************************************/
TMPL_PURE_FUNC
extern tmpl_DoubleDouble
tmpl_DoubleDouble_Quick_Add(const tmpl_DoubleDouble * const x,
                            const tmpl_DoubleDouble * const y)
TMPL_UNSEQUENCED;

TMPL_PURE_FUNC
extern tmpl_LongDoubleDouble
tmpl_LDoubleDouble_Quick_Add(const tmpl_LongDoubleDouble * const x,
                             const tmpl_LongDoubleDouble * const y)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_DoubleDouble_Multiply                                            *
 *  Purpose:                                                                  *
 *      Performs the product of two double-doubles.                           *
 *  Arguments:                                                                *
 *      x (const tmpl_DoubleDouble * const):                                  *
 *          A double-double.                                                  *
 *      y (const tmpl_DoubleDouble * const):                                  *
 *          Another double-double.                                            *
 *  Output:                                                                   *
 *      prod (tmpl_DoubleDouble):                                             *
 *          The double-double product x * y.                                  *
 *  Notes:                                                                    *
 *      long double-double is also provided.                                  *
 ******************************************************************************/
TMPL_PURE_FUNC
extern tmpl_DoubleDouble
tmpl_DoubleDouble_Multiply(const tmpl_DoubleDouble * const x,
                           const tmpl_DoubleDouble * const y)
TMPL_UNSEQUENCED;

TMPL_PURE_FUNC
extern tmpl_LongDoubleDouble
tmpl_LDoubleDouble_Multiply(const tmpl_LongDoubleDouble * const x,
                            const tmpl_LongDoubleDouble * const y)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_DoubleDouble_Multiply_Scalar                                     *
 *  Purpose:                                                                  *
 *      Multiplies a double and a double-double.                              *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A double-precision floating-point number.                         *
 *      y (const tmpl_DoubleDouble * const):                                  *
 *          A double-double real number.                                      *
 *  Output:                                                                   *
 *      prod (tmpl_DoubleDouble):                                             *
 *          The double-double product x * y.                                  *
 *  Notes:                                                                    *
 *      1.) long double-double version is also provided.                      *
 ******************************************************************************/
TMPL_PURE_FUNC
tmpl_DoubleDouble
tmpl_DoubleDouble_Multiply_Scalar(const double x,
                                  const tmpl_DoubleDouble * const y)
TMPL_UNSEQUENCED;

TMPL_PURE_FUNC
tmpl_LongDoubleDouble
tmpl_LDoubleDouble_Multiply_Scalar(const long double x,
                                   const tmpl_LongDoubleDouble * const y)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_DoubleDouble_Create                                              *
 *  Purpose:                                                                  *
 *      Creates a double-double from two doubles.                             *
 *  Arguments:                                                                *
 *      hi (double):                                                          *
 *          The high part of the double.                                      *
 *      lo (double):                                                          *
 *          The low part of the double.                                       *
 *  Output:                                                                   *
 *      val (tmpl_DoubleDouble):                                              *
 *          The double-double value hi + lo.                                  *
 *  Notes:                                                                    *
 *      long double-double is also provided.                                  *
 ******************************************************************************/
extern tmpl_DoubleDouble
tmpl_DoubleDouble_Create(double hi, double lo);

extern tmpl_LongDoubleDouble
tmpl_LDoubleDouble_Create(long double hi, long double lo);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
