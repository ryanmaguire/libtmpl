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
 *                            tmpl_two_vector_add                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Source code for computing the vector sum of two points in the plane.  *
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
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/12/21: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 ******************************************************************************/

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_euclidean_planar_geometry.h>

/*  Function for adding 2 two-dimensional vectors.                            */
tmpl_DoubleTwoVector
tmpl_DoubleTwoVector_Add(tmpl_DoubleTwoVector P, tmpl_DoubleTwoVector Q)
{
    /*  Extract the x and y components from P.                                */
    const double Px = tmpl_DoubleTwoVector_X(P);
    const double Py = tmpl_DoubleTwoVector_Y(P);

    /*  Extract the x and y components from Q.                                */
    const double Qx = tmpl_DoubleTwoVector_X(Q);
    const double Qy = tmpl_DoubleTwoVector_Y(Q);

    /*  The sum of two vectors simply adds their components together.         */
    const double x = Px + Qx;
    const double y = Py + Qy;

    /*  Use tmpl_TwoVector_Rect to create the output vector and return.       */
    return tmpl_DoubleTwoVector_Rect(x, y);
}
/*  End of tmpl_DoubleTwoVector_Add.                                          */

/*  Function for adding 2 two-dimensional vectors.                            */
tmpl_LDoubleTwoVector
tmpl_LDoubleTwoVector_Add(tmpl_LDoubleTwoVector P, tmpl_LDoubleTwoVector Q)
{
    /*  Extract the x and y components from P.                                */
    const long double Px = tmpl_LDoubleTwoVector_X(P);
    const long double Py = tmpl_LDoubleTwoVector_Y(P);

    /*  Extract the x and y components from Q.                                */
    const long double Qx = tmpl_LDoubleTwoVector_X(Q);
    const long double Qy = tmpl_LDoubleTwoVector_Y(Q);

    /*  The sum of two vectors simply adds their components together.         */
    const long double x = Px + Qx;
    const long double y = Py + Qy;

    /*  Use tmpl_TwoVector_Rect to create the output vector and return.       */
    return tmpl_LDoubleTwoVector_Rect(x, y);
}
/*  End of tmpl_LDoubleTwoVector_Add.                                         */
