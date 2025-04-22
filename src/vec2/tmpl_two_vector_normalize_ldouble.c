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
 *                     tmpl_two_vector_normalize_ldouble                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Normalize a non-zero vector to have length 1.                         *
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
 *      Moved float and long double versions to own files. Changed function   *
 *      to pass by address install of by value.                               *
 ******************************************************************************/

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for normalizing a non-zero vector to length 1.                   */
tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Normalize(const tmpl_TwoVectorLongDouble *P)
{
    tmpl_TwoVectorLongDouble P_hat;
    const long double rcpr_norm = 1.0L / tmpl_2DLDouble_L2_Norm(P);

    P_hat.dat[0] = P->dat[0]*rcpr_norm;
    P_hat.dat[1] = P->dat[1]*rcpr_norm;

    return P_hat;
}
/*  End of tmpl_2DLDouble_Normalize.                                          */
