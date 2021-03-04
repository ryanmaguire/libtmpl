/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                            tmpl_complex_dist                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the function f(z,w) = |z-w|.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Dist:                                                     *
 *      tmpl_CDouble_Dist:                                                    *
 *      tmpl_CLDouble_Dist:                                                   *
 *  Purpose:                                                                  *
 *      Computes the distance between two complex numbers:                    *
 *                                                                            *
 *          dist(z, w) = dist(a + ib, c + id)                                 *
 *                     = sqrt((c-a)^2 + (d-b)^2)                              *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *      w (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      dist (float/double/long double):                                      *
 *          The distance between z and w.                                     *
 *  Method:                                                                   *
 *      Treat the points as elements of the Euclidean plane and use           *
 *      the Pythagorean formula.                                              *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 *  2.) tmpl_math.h:                                                          *
 *          Header containing various math functions like the square root.    *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
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
 ******************************************************************************/

/*  Header file containing the square root functions.                         */
#include <libtmpl/include/tmpl_math.h>

/*  Complex routines and data types defined here.                             */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision distance function for complex variables.                 */
float tmpl_CFloat_Dist(tmpl_ComplexFloat z0, tmpl_ComplexFloat z1)
{
    /*  Declare necessary variables C89 requires this at the top.             */
    float x0, y0, x1, y1, dx, dy, dist;

    /*  Extract the real and imaginary parts from z0.                         */
    x0 = tmpl_CFloat_Real_Part(z0);
    y0 = tmpl_CFloat_Imag_Part(z0);

    /*  Extract the real and imaginary parts from z1.                         */
    x1 = tmpl_CFloat_Real_Part(z1);
    y1 = tmpl_CFloat_Imag_Part(z1);

    /*  Compute the x and y differences from z0 and z1.                       */
    dx = x1-x0;
    dy = y1-y0;

    /*  Use the Pythagorean formula to compute the distance and return.       */
    dist = tmpl_Float_Sqrt(dx*dx + dy*dy);
    return dist;
}
/*  End of tmpl_CFloat_Dist.                                                  */

/*  Double precision distance function for complex variables.                 */
double tmpl_CDouble_Dist(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Declare necessary variables C89 requires this at the top.             */
    double x0, y0, x1, y1, dx, dy, dist;

    /*  Extract the real and imaginary parts from z0.                         */
    x0 = tmpl_CDouble_Real_Part(z0);
    y0 = tmpl_CDouble_Imag_Part(z0);

    /*  Extract the real and imaginary parts from z1.                         */
    x1 = tmpl_CDouble_Real_Part(z1);
    y1 = tmpl_CDouble_Imag_Part(z1);

    /*  Compute the x and y differences from z0 and z1.                       */
    dx = x1-x0;
    dy = y1-y0;

    /*  Use the Pythagorean formula to compute the distance and return.       */
    dist = tmpl_Double_Sqrt(dx*dx + dy*dy);
    return dist;
}
/*  End of tmpl_CDouble_Dist.                                                 */

/*  Long double precision distance function for complex variables.            */
long double
tmpl_CLDouble_Dist(tmpl_ComplexLongDouble z0, tmpl_ComplexLongDouble z1)
{
    /*  Declare necessary variables C89 requires this at the top.             */
    long double x0, y0, x1, y1, dx, dy, dist;

    /*  Extract the real and imaginary parts from z0.                         */
    x0 = tmpl_CLDouble_Real_Part(z0);
    y0 = tmpl_CLDouble_Imag_Part(z0);

    /*  Extract the real and imaginary parts from z1.                         */
    x1 = tmpl_CLDouble_Real_Part(z1);
    y1 = tmpl_CLDouble_Imag_Part(z1);

    /*  Compute the x and y differences from z0 and z1.                       */
    dx = x1-x0;
    dy = y1-y0;

    /*  Use the Pythagorean formula to compute the distance and return.       */
    dist = tmpl_LDouble_Sqrt(dx*dx + dy*dy);
    return dist;
}
/*  End of tmpl_CLDouble_Dist.                                                */

