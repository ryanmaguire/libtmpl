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
 *                               tmpl_three_prod                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides 3Prod and other 3Prod-like algorithms.                       *
 *  Notes:                                                                    *
 *      1.) On compilers supporting the restrict keyword, the output          *
 *          variables are declared as restrict pointers. This requires that   *
 *          these variables point to different locations. To properly use the *
 *          various 3Prod functions, this should be true regardless of        *
 *          whether or not restrict is supported.                             *
 *                                                                            *
 *      2.) None of the 3Prod functions check for NULL pointers.              *
 *                                                                            *
 *      3.) None of the 3Prod functions check for NaN or infinity.            *
 *                                                                            *
 *      4.) Float, double, and long double versions are provided.             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file providing TMPL_RESTRICT and other macros.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 29, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_THREE_PROD_H
#define TMPL_THREE_PROD_H

/*  TMPL_RESTRICT macro found here.                                           */
#include <libtmpl/include/tmpl_config.h>

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Three_Multiply_Add                                        *
 *  Purpose:                                                                  *
 *      Provides the 3FMA algorithm which exactly computes x * y + z.         *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      z (const double):                                                     *
 *          A third real number.                                              *
 *      sum_high (double * TMPL_RESTRICT const):                              *
 *          The high part of x * y + z.                                       *
 *      sum_mid (double * TMPL_RESTRICT const):                               *
 *          The middle part of x * y + z.                                     *
 *      sum_low (double * TMPL_RESTRICT const):                               *
 *          The low part of x * y + z.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_Double_Three_Multiply_Add(const double x,
                               const double y,
                               const double z,
                               double * TMPL_RESTRICT const sum_high,
                               double * TMPL_RESTRICT const sum_mid,
                               double * TMPL_RESTRICT const sum_low);

extern void
tmpl_Float_Three_Multiply_Add(const float x,
                              const float y,
                              const float z,
                              float * TMPL_RESTRICT const sum_high,
                              float * TMPL_RESTRICT const sum_mid,
                              float * TMPL_RESTRICT const sum_low);

extern void
tmpl_LDouble_Three_Multiply_Add(const long double x,
                                const long double y,
                                const long double z,
                                long double * TMPL_RESTRICT const sum_high,
                                long double * TMPL_RESTRICT const sum_mid,
                                long double * TMPL_RESTRICT const sum_low);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
