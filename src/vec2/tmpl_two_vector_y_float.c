/******************************************************************************
 *                                  LICENSE                                   *
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
 *  Purpose:                                                                  *
 *      Returns the y component of a two dimensional vector/planar point.     *
 *      That is, given (x, y), return y.                                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/12/21: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *  2023/01/01: Ryan Maguire                                                  *
 *      Changed function to pass by addres. Moved float and long double to    *
 *      their own files.                                                      *
 ******************************************************************************/

/*  Function prototypes and two-vector typedef's found here.                  */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for returning the y component of a two dimensional vector.       */
float tmpl_2DFloat_Y(const tmpl_TwoVectorFloat *P)
{
    /*  The tmpl_FloatTwoVector mimics the method used by GSL for complex     *
     *  numbers, using a struct containing a float array with 2 elements.     *
     *  The y component is the first element. Return this.                    */
    return P->dat[1];
}
/*  End of tmpl_2DFloat_Y.                                                    */
