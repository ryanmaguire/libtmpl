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
 *                         tmpl_complex_dist_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the function f(z,w) = |z - w|.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Dist                                                    *
 *  Purpose:                                                                  *
 *      Computes the distance between two complex numbers:                    *
 *                                                                            *
 *          dist(z, w) = dist(a + ib, c + id)                                 *
 *                     = sqrt((c-a)^2 + (d-b)^2)                              *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexLongDouble):                                           *
 *          A complex number.                                                 *
 *      w (tmpl_ComplexLongDouble):                                           *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      dist (long double):                                                   *
 *          The distance between z and w.                                     *
 *  Called Functions:                                                         *
 *      tmpl_LDouble_Hypot (tmpl_math.h):                                     *
 *          Computes the magnitude of the vector (x, y).                      *
 *  Method:                                                                   *
 *      Treat the points as elements of the Euclidean plane and use           *
 *      the Pythagorean formula.                                              *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_USE_INLINE is found.                       *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 *  3.) tmpl_math.h:                                                          *
 *          Header containing various math functions.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
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
 ******************************************************************************/

/*  TMPL_USE_INLINE found here.                                               */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only used if inline support is not requested.                */
#if TMPL_USE_INLINE != 1

/*  Header file containing the hypot function.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Complex routines and data types defined here.                             */
#include <libtmpl/include/tmpl_complex.h>

/*  Long double precision distance function for complex variables.            */
long double
tmpl_CLDouble_Dist(tmpl_ComplexLongDouble z0, tmpl_ComplexLongDouble z1)
{
    /*  Compute the difference in both components and use Pythagoras.         */
    const long double dx = z0.dat[0] - z1.dat[0];
    const long double dy = z0.dat[1] - z1.dat[1];
    return tmpl_LDouble_Hypot(dx, dy);
}
/*  End of tmpl_CLDouble_Dist.                                                */

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
