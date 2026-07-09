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
#ifndef TMPL_TWO_PROD_H
#define TMPL_TWO_PROD_H

/*  TMPL_USE_INLINE macro provided here, as is TMPL_RESTRICT.                 */
#include <libtmpl/include/tmpl_config.h>

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Two_Prod                                                  *
 *  Purpose:                                                                  *
 *      Performs the 2Prod algorithm for floating-point multiplication.       *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      out (double * const):                                                 *
 *          The floating-point product x * y is stored here.                  *
 *      err (double * const):                                                 *
 *          The error, prod(x, y) - (x * y), is stored here.                  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern void
tmpl_Double_Two_Prod(const double x,
                     const double y,
                     double * const TMPL_RESTRICT out,
                     double * const TMPL_RESTRICT err);

extern void
tmpl_Float_Two_Prod(const float x,
                    const float y,
                    float * const TMPL_RESTRICT out,
                    float * const TMPL_RESTRICT err);

extern void
tmpl_LDouble_Two_Prod(const long double x,
                      const long double y,
                      long double * const TMPL_RESTRICT out,
                      long double * const TMPL_RESTRICT err);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Two_Square                                                *
 *  Purpose:                                                                  *
 *      Performs the 2Square algorithm for floating-point multiplication.     *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      out (double * const):                                                 *
 *          The floating-point product fl(x * x) is stored here.              *
 *      err (double * const):                                                 *
 *          The error, (x * y) - fl(x * y), is stored here.                   *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern void
tmpl_Double_Two_Square(const double x,
                       double * const TMPL_RESTRICT out,
                       double * const TMPL_RESTRICT err);

extern void
tmpl_Float_Two_Square(const float x,
                      float * const TMPL_RESTRICT out,
                      float * const TMPL_RESTRICT err);

extern void
tmpl_LDouble_Two_Square(const long double x,
                        long double * const TMPL_RESTRICT out,
                        long double * const TMPL_RESTRICT err);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
