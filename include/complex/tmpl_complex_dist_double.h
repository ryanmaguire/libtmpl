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
 *                          tmpl_complex_dist_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the function f(z, w) = |z - w|.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Dist                                                     *
 *  Purpose:                                                                  *
 *      Computes the distance between two complex numbers:                    *
 *                                                                            *
 *          dist(z, w) = dist(a + ib, c + id)                                 *
 *                     = sqrt((c-a)^2 + (d-b)^2)                              *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 *      w (tmpl_ComplexDouble):                                               *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      dist (double):                                                        *
 *          The distance between z and w.                                     *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Hypot:                                                *
 *              Computes the magnitude of the vector (x, y).                  *
 *  Method:                                                                   *
 *      Treat the points as elements of the Euclidean plane and use           *
 *      the Pythagorean formula.                                              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is found.                      *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 *  3.) tmpl_math.h:                                                          *
 *          Header containing various math functions.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/23: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/12/23: Ryan Maguire                                                  *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2023/02/06: Ryan Maguire                                                  *
 *      Changed algorithm to be safe, avoid overflow for large elements.      *
 *      Moved float and long double versions to their own files.              *
 *      Added inline support.                                                 *
 *  2023/07/13: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_dist_double.c to include this file.  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_DIST_DOUBLE_H
#define TMPL_COMPLEX_DIST_DOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Header file containing the hypot function.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Complex routines and data types defined here.                             */
#include <libtmpl/include/tmpl_complex.h>

/*  Double precision distance function for complex variables.                 */
TMPL_INLINE_DECL
double tmpl_CDouble_Dist(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Compute the difference in both components and use Pythagoras.         */
    const double dx = z0.dat[0] - z1.dat[0];
    const double dy = z0.dat[1] - z1.dat[1];
    return tmpl_Double_Hypot(dx, dy);
}
/*  End of tmpl_CDouble_Dist.                                                 */

#endif
/*  End of include guard.                                                     */
