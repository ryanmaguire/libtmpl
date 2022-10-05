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
 *                          tmpl_rotation_matrix_2d                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the 2x2 rotation matrix corresponding to a real number.      *
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

/*  Trig functions found here.                                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for computing the rotation matrix corresponding to a real number.*/
tmpl_FloatTwoByTwoMatrix tmpl_Float_Rotation_Matrix2D(float theta)
{
    /*  The components of the rotation matrix are determined by cos and sin.  */
    const float cos_theta = tmpl_Float_Cos(theta);
    const float sin_theta = tmpl_Float_Sin(theta);

    return tmpl_FloatTwoByTwoMatrix_New(cos_theta, -sin_theta,
                                        sin_theta, cos_theta);
}
/*  End of tmpl_Float_Rotation_Matrix2D.                                      */

/*  Function for computing the rotation matrix corresponding to a real number.*/
tmpl_DoubleTwoByTwoMatrix tmpl_Double_Rotation_Matrix2D(double theta)
{
    /*  The components of the rotation matrix are determined by cos and sin.  */
    const double cos_theta = tmpl_Double_Cos(theta);
    const double sin_theta = tmpl_Double_Sin(theta);

    return tmpl_DoubleTwoByTwoMatrix_New(cos_theta, -sin_theta,
                                         sin_theta, cos_theta);
}
/*  End of tmpl_Double_Rotation_Matrix2D.                                     */

/*  Function for computing the rotation matrix corresponding to a real number.*/
tmpl_LDoubleTwoByTwoMatrix tmpl_LDouble_Rotation_Matrix2D(long double theta)
{
    /*  The components of the rotation matrix are determined by cos and sin.  */
    const long double cos_theta = tmpl_LDouble_Cos(theta);
    const long double sin_theta = tmpl_LDouble_Sin(theta);

    return tmpl_LDoubleTwoByTwoMatrix_New(cos_theta, -sin_theta,
                                          sin_theta, cos_theta);
}
/*  End of tmpl_LDouble_Rotation_Matrix2D.                                    */
