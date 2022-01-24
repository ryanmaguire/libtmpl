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
 *                        tmpl_two_vector_dot_product                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Compute the Euclidean dot product (a,b) . (c,d) = ac + bd.            *
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

/*  Function for returning the x component of a two dimensional vector.       */
float
tmpl_FloatTwoVector_Dot_Product(tmpl_FloatTwoVector P, tmpl_FloatTwoVector Q)
{
    /*  Extract the x and y components from P.                                */
    const float Px = tmpl_FloatTwoVector_X(P);
    const float Py = tmpl_FloatTwoVector_Y(P);

    /*  Extract the x and y components from Q.                                */
    const float Qx = tmpl_FloatTwoVector_X(Q);
    const float Qy = tmpl_FloatTwoVector_Y(Q);

    /*  Use the Euclidean dot product formula and return.                     */
    return Px*Qx + Py*Qy;
}
/*  End of tmpl_FloatTwoVector_Dot_Product.                                   */

/*  Function for returning the x component of a two dimensional vector.       */
double
tmpl_DoubleTwoVector_Dot_Product(tmpl_DoubleTwoVector P, tmpl_DoubleTwoVector Q)
{
    /*  Extract the x and y components from P.                                */
    const double Px = tmpl_DoubleTwoVector_X(P);
    const double Py = tmpl_DoubleTwoVector_Y(P);

    /*  Extract the x and y components from Q.                                */
    const double Qx = tmpl_DoubleTwoVector_X(Q);
    const double Qy = tmpl_DoubleTwoVector_Y(Q);

    /*  Use the Euclidean dot product formula and return.                     */
    return Px*Qx + Py*Qy;
}
/*  End of tmpl_DoubleTwoVector_Dot_Product.                                  */

/*  Function for returning the x component of a two dimensional vector.       */
long double
tmpl_LDoubleTwoVector_Dot_Product(tmpl_LDoubleTwoVector P,
                                  tmpl_LDoubleTwoVector Q)
{
    /*  Extract the x and y components from P.                                */
    const long double Px = tmpl_LDoubleTwoVector_X(P);
    const long double Py = tmpl_LDoubleTwoVector_Y(P);

    /*  Extract the x and y components from Q.                                */
    const long double Qx = tmpl_LDoubleTwoVector_X(Q);
    const long double Qy = tmpl_LDoubleTwoVector_Y(Q);

    /*  Use the Euclidean dot product formula and return.                     */
    return Px*Qx + Py*Qy;
}
/*  End of tmpl_LDoubleTwoVector_Dot_Product.                                 */
