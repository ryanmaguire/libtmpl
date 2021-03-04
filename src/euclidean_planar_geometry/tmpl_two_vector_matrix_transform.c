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
 *                     tmpl_two_vector_matrix_transform                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Multiply a tmpl_TwoVector by a tmpl_TwoByTwoMatrix.                   *
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
 *  Date:       September 28, 2020                                            *
 ******************************************************************************/

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_euclidean_planar_geometry.h>

/*  Function for multiplying a 2-vector by a 2x2 matrix.                      */
tmpl_TwoVector tmpl_TwoVector_Matrix_Transform(tmpl_TwoByTwoMatrix A,
                                               tmpl_TwoVector P)
{
    tmpl_TwoVector out;
    double x_new, y_new;
    double x0, y0;
    double a, b, c, d;

    x0 = tmpl_TwoVector_X(P);
    y0 = tmpl_TwoVector_Y(P);

    a = tmpl_TwoByTwoMatrix_Component(A, 0, 0);
    b = tmpl_TwoByTwoMatrix_Component(A, 0, 1);
    c = tmpl_TwoByTwoMatrix_Component(A, 1, 0);
    d = tmpl_TwoByTwoMatrix_Component(A, 1, 1);

    x_new = a*x0 + b*y0;
    y_new = c*x0 + d*y0;

    out = tmpl_TwoVector_Rect(x_new, y_new);
    return out;
}
/*  End of tmpl_TwoVector_Matrix_Transform.                                   */

