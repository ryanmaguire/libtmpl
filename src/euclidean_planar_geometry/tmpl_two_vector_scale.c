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
 *  Purpose:                                                                  *
 *      Source code for multiplying a two dimensional vector by a real number.*
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

/*  Function for multipyling a two-vector by a real number.                   */
tmpl_TwoVector tmpl_TwoVector_Scale(double a, tmpl_TwoVector P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double Px, Py, x, y;
    tmpl_TwoVector scale;

    /*  Extract the x and y components from P.                                */
    Px = tmpl_TwoVector_X(P);
    Py = tmpl_TwoVector_Y(P);

    /*  Multiplying a vector by a scalar simply multiplies the entries        *
     *  component-wise. Compute this.                                         */
    x = a*Px;
    y = a*Py;

    /*  Use tmpl_TwoVector_Rect to create the output and return.              */
    scale = tmpl_TwoVector_Rect(x, y);
    return scale;
}
/*  End of tmpl_TwoVector_Scale.                                              */

