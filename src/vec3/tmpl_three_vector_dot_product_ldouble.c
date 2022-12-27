/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                    tmpl_three_vector_dot_product_ldouble                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the Euclidean dot product at long double precision. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Dot_Product                                            *
 *  Purpose:                                                                  *
 *      Computes the dot product of two vectors at long double precision.     *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorLongDouble *):                               *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorLongDouble *):                               *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      dot (long double):                                                    *
 *          The dot product P . Q.                                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of the dot product. If P = (Px, Py, Pz) and        *
 *      Q = (Qx, Qy, Qz), then the dot product is:                            *
 *          dot = PxQx + PyQy + PzQz                                          *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *                                                                            *
 *      The macro tmpl_3D_Dot_Productl is an alias for this function.         *
 *                                                                            *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/02: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 *  2022/03/21: Ryan Maguire                                                  *
 *      Changed function to pass by reference instead of by value.            *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the dot product of 2 three-vectors.                */
long double
tmpl_3DLDouble_Dot_Product(const tmpl_ThreeVectorLongDouble *P,
                           const tmpl_ThreeVectorLongDouble *Q)
{
    /*  Use the Euclidean dot product formula and return.                     */
    return P->dat[0]*Q->dat[0] + P->dat[1]*Q->dat[1] + P->dat[2]*Q->dat[2];
}
/*  End of tmpl_3DLDouble_Dot_Product.                                        */
