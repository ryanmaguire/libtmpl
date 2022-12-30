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
 *                  tmpl_three_vector_cross_product_ldouble                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the Euclidean cross product of vectors    *
 *      in R^3 at long double precision.                                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Cross_Product                                          *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vectors at long double precision.   *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorLongDouble *):                               *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorLongDouble *):                               *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      cross (tmpl_ThreeVectorLongDouble):                                   *
 *          The cross product PxQ.                                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of the cross product. If P = (Px, Py, Pz) and      *
 *      Q = (Qx, Qy, Qz), then the cross product PxQ has coordinates:         *
 *          x = PyQz - PzQy                                                   *
 *          y = PzQx - PxQz                                                   *
 *          z = PxQy - PyQx                                                   *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *                                                                            *
 *      The cross product is not commutative, but anti-commutative. That is,  *
 *      PxQ = -QxP. The order of P and Q matters for this function.           *
 *                                                                            *
 *      The macro tmpl_Cross_Productl is an alias for this function.          *
 *                                                                            *
 *      A 73% to 100% increase in performance (pending hardware and compiler  *
 *      used) was found when passing by reference instead of by value.        *
 *                                                                            *
 *      No checks for NULL pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *                             A NOTE ON COMMENTS                             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/02: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 *  2022/03/18: Ryan Maguire                                                  *
 *      Changed function to pass by reference instead of by value.            *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the cross product at long double precision.        */
tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Cross_Product(const tmpl_ThreeVectorLongDouble *P,
                             const tmpl_ThreeVectorLongDouble *Q)
{
    /*  Declare a variable for the output.                                    */
    tmpl_ThreeVectorLongDouble cross;

    /*  Compute the components of the cross product PxQ.                      */
    cross.dat[0] = P->dat[1]*Q->dat[2] - P->dat[2]*Q->dat[1];
    cross.dat[1] = P->dat[2]*Q->dat[0] - P->dat[0]*Q->dat[2];
    cross.dat[2] = P->dat[0]*Q->dat[1] - P->dat[1]*Q->dat[0];
    return cross;
}
/*  End of tmpl_3DLDouble_Cross_Product.                                       */
