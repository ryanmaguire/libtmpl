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
 *                      tmpl_two_vector_rel_angle_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Source code for computing the vector sum of two points in the plane.  *
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
 ******************************************************************************/

/*  TMPL_NAN defined here.                                                    */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for computing the angle between the lines OP and OQ given three  *
 *  tmpl_TwoVector's O, P, and Q.                                             */
float
tmpl_2DFloat_Rel_Angle(const tmpl_TwoVectorFloat *O,
                       const tmpl_TwoVectorFloat *P,
                       const tmpl_TwoVectorFloat *Q)
{
    /*  We need to compute the vector from O to P and O to Q so declare these.*/
    const tmpl_TwoVectorFloat OP = tmpl_2DFloat_Subtract(P, O);
    const tmpl_TwoVectorFloat OQ = tmpl_2DFloat_Subtract(Q, O);

    /*  The angle formula is arccos(a dot b / norm(a)norm(b)). First we'll    *
     *  compute the dot product, then check that norm(a)norm(b) is non-zero.  */
    const float dot = tmpl_2DFloat_Dot_Product(&OP, &OQ);

    /*  abs_prod represents the quantity ||OP|| * ||OQ||.                     */
    const float prod = tmpl_2DFloat_L2_Norm(&OP)*tmpl_2DFloat_L2_Norm(&OQ);

    /*  If norm(OP)norm(OQ) is non-zero, we may use the angle formula.        */
    return tmpl_Float_Arccos(dot/prod);
}
/*  End of tmpl_2DFloat_Rel_Angle.                                            */
