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
 *                      tmpl_two_by_two_matrix_scale                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Multiply a 2x2 matrix by a real number.                               *
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

/*  Function for multiplying a 2x2 matrix by a real number.                   */
tmpl_FloatTwoByTwoMatrix
tmpl_FloatTwoByTwoMatrix_Scale(float r, tmpl_FloatTwoByTwoMatrix A)
{
    /*  Extract the components of the matrix.                                 */
    const float a00 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 0);
    const float a01 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 1);
    const float a10 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 0);
    const float a11 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 1);

    /*  Multiply each component by the scalar and return.                     */
    return tmpl_FloatTwoByTwoMatrix_New(r*a00, r*a01, r*a10, r*a11);
}
/*  End of tmpl_FloatTwoByTwoMatrix_Scale.                                    */

/*  Function for multiplying a 2x2 matrix by a real number.                   */
tmpl_DoubleTwoByTwoMatrix
tmpl_DoubleTwoByTwoMatrix_Scale(double r, tmpl_DoubleTwoByTwoMatrix A)
{
    /*  Extract the components of the matrix.                                 */
    const double a00 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 0);
    const double a01 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 1);
    const double a10 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 0);
    const double a11 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 1);

    /*  Multiply each component by the scalar and return.                     */
    return tmpl_DoubleTwoByTwoMatrix_New(r*a00, r*a01, r*a10, r*a11);
}
/*  End of tmpl_DoubleTwoByTwoMatrix_Scale.                                   */

/*  Function for multiplying a 2x2 matrix by a real number.                   */
tmpl_LDoubleTwoByTwoMatrix
tmpl_LDoubleTwoByTwoMatrix_Scale(long double r, tmpl_LDoubleTwoByTwoMatrix A)
{
    /*  Extract the components of the matrix.                                 */
    const long double a00 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 0);
    const long double a01 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 0, 1);
    const long double a10 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 0);
    const long double a11 = tmpl_GET_2x2_MATRIX_COMPONENT(A, 1, 1);

    /*  Multiply each component by the scalar and return.                     */
    return tmpl_LDoubleTwoByTwoMatrix_New(r*a00, r*a01, r*a10, r*a11);
}
/*  End of tmpl_LDoubleTwoByTwoMatrix_Scale.                                  */
