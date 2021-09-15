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
 *                    tmpl_two_vector_euclidean_orthogonal                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a vector orthogonal to a given input.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_TwoVector_Euclidean_Orthogonal                             *
 *      tmpl_Double_TwoVector_Euclidean_Orthogonal                            *
 *      tmpl_LDouble_TwoVector_Euclidean_Orthogonal                           *
 *  Purpose:                                                                  *
 *      Given a point in the plane (x, y), computes a point orthogonal to     *
 *      this with respect to the origin. In particular, it returns (-y, x)    *
 *      since <(x, y) | (-y, x)> = x(-y) + yx = 0, where < | > is the usual   *
 *      Euclidean dot product.                                                *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVector):                                                   *
 *          A point in the plane.                                             *
 *  Output:                                                                   *
 *      P_perp (tmpl_TwoVector):                                              *
 *          A point orthogonal to P.                                          *
 *  Called Functions:                                                         *
 *      tmpl_Float_Sqrt         (tmpl_math.h)                                 *
 *      tmpl_Double_Sqrt        (tmpl_math.h)                                 *
 *      tmpl_LDouble_Sqrt       (tmpl_math.h)                                 *
 *          Computes the square root of a float/double/long double.           *
 *      tmpl_CFloat_Real_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Real_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Real_Part (tmpl_complex.h)                              *
 *          Returns the real part of a complex number.                        *
 *      tmpl_CFloat_Imag_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Imag_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Imag_Part (tmpl_complex.h)                              *
 *          Returns the imaginary part of a complex number.                   *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts of z and return sqrt(x^2 + y^2). *
 *  Notes:                                                                    *
 *      This code is a fork of the code I wrote for rss_ringoccs.             *
 *      librssringoccs is also released under GPL3.                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing basic math functions.                      *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
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

/*  Single precision version of tmpl_DoubleTwoVector_Euclidean_Orthogonal.    */
tmpl_FloatTwoVector
tmpl_FloatTwoVector_Euclidean_Orthogonal(tmpl_FloatTwoVector V)
{
    /*  Extract the x and y values from the input vector.                     */
    const float x = tmpl_FloatTwoVector_X(V);
    const float y = tmpl_FloatTwoVector_Y(V);

    /*  Simply return (-y, x) since this will be orthogonal. That is, the dot *
     *  product is <V|U> = <(x,y)|(-y,x)> = -xy + yx = 0.                     */
    return tmpl_FloatTwoVector_Rect(-y, x);;
}
/*  End of tmpl_DoubleTwoVector_Euclidean_Orthogonal.                         */

/*  Given a vector V, returns an orthogonal vector U with respect to the      *
 *  standard Euclidean dot product. That is, a vector U with <V|U> = 0        *
 *  (using bra-ket notation).                                                 */
tmpl_DoubleTwoVector
tmpl_DoubleTwoVector_Euclidean_Orthogonal(tmpl_DoubleTwoVector V)
{
    /*  Extract the x and y values from the input vector.                     */
    const double x = tmpl_DoubleTwoVector_X(V);
    const double y = tmpl_DoubleTwoVector_Y(V);

    /*  Simply return (-y, x) since this will be orthogonal. That is, the dot *
     *  product is <V|U> = <(x,y)|(-y,x)> = -xy + yx = 0.                     */
    return tmpl_DoubleTwoVector_Rect(-y, x);;
}
/*  End of tmpl_DoubleTwoVector_Euclidean_Orthogonal.                         */

/*  Long double version of tmpl_DoubleTwoVector_Euclidean_Orthogonal.         */
tmpl_LDoubleTwoVector
tmpl_LDoubleTwoVector_Euclidean_Orthogonal(tmpl_LDoubleTwoVector V)
{
    /*  Extract the x and y values from the input vector.                     */
    const long double x = tmpl_LDoubleTwoVector_X(V);
    const long double y = tmpl_LDoubleTwoVector_Y(V);

    /*  Simply return (-y, x) since this will be orthogonal. That is, the dot *
     *  product is <V|U> = <(x,y)|(-y,x)> = -xy + yx = 0.                     */
    return tmpl_LDoubleTwoVector_Rect(-y, x);;
}
/*  End of tmpl_LDoubleTwoVector_Euclidean_Orthogonal.                        */
