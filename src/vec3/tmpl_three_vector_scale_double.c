/******************************************************************************
 *                                  LICENSE                                   *
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
 *      Function for multiplying a three vector by a real number.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Multiply a three vector by a real number.                                 */
tmpl_ThreeVectorDouble tmpl_3DDouble_Scale(double a, tmpl_ThreeVectorDouble P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_ThreeVectorDouble scaled;

    /*  Scalar multiplication is done component-wise, so compute this.        */
    scaled.dat[0] = a*P.dat[0];
    scaled.dat[1] = a*P.dat[1];
    scaled.dat[2] = a*P.dat[2];
    return scaled;
}
/*  End of tmpl_3DDouble_Scale.                                               */
