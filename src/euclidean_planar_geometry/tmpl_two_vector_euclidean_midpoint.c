/******************************************************************************
 *                                 LICENSE                                    *
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
 *                      tmpl_two_vector_euclidean_midpoint                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the midpoint of two vectors.                                 *
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
 *  Date:       June 29, 2021                                                 *
 ******************************************************************************/

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_euclidean_planar_geometry.h>

/*  Function for computing the midpoint of 2 two dimensional vectors.         */
tmpl_TwoVector
tmpl_TwoVector_Euclidean_Midpoint(tmpl_TwoVector P, tmpl_TwoVector Q)
{
    /*  Declare all necessary variables.                                      */
    double x0, y0;
    double x1, y1;
    double xmid, ymid;
    tmpl_TwoVector midpoint;

    /*  Extract the x and y components of the vector P.                       */
    x0 = tmpl_TwoVector_X(P);
    y0 = tmpl_TwoVector_Y(P);

    /*  Extract the x and y components of the vector Q.                       */
    x1 = tmpl_TwoVector_X(Q);
    y1 = tmpl_TwoVector_Y(Q);

    /*  Compute the midpoint of P and Q, which is simply 0.5*(P+Q).           */
    xmid = 0.5*(x0 + x1);
    ymid = 0.5*(y0 + y1);

    /*  Use tmpl_TwoVector_Rect to create the new output and return.          */
    midpoint = tmpl_TwoVector_Rect(xmid, ymid);
    return midpoint;
}
/*  End of tmpl_TwoVector_Euclidean_Midpoint.                                 */

