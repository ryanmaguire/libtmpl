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
 *                   tmpl_three_vector_cross_product_double                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the Euclidean cross product of vectors    *
 *      in R^3 at double precision.                                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Cross_Product                                           *
 *  Purpose:                                                                  *
 *      Computes the cross product of two vectors at double precision.        *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorDouble *):                                   *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorDouble *):                                   *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      cross (tmpl_ThreeVectorDouble):                                       *
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
 *      The macro tmpl_Cross_Product is an alias for this function.           *
 *                                                                            *
 *      A 73% to 100% increase in performance (pending hardware and compiler  *
 *      used) was found when passing by reference instead of by value.        *
 *                                                                            *
 *      No checks for NULL pointers are performed.                            *
 *                                                                            *
 *  Accuracy and Performance:                                                 *
 *                                                                            *
 *      A time and accuracy test against linasm's 3D library produced the     *
 *      following results:                                                    *
 *                                                                            *
 *          tmpl_3DDouble_Cross_Product vs. Vector3D_VectorProduct_flt64      *
 *          samples: 400000000                                                *
 *          libtmpl: 3.845129 seconds                                         *
 *          linasm:  4.516983 seconds                                         *
 *          x max err: 0.000000e+00                                           *
 *          y max err: 0.000000e+00                                           *
 *          z max err: 0.000000e+00                                           *
 *          x rms err: 0.000000e+00                                           *
 *          y rms err: 0.000000e+00                                           *
 *          z rms err: 0.000000e+00                                           *
 *                                                                            *
 *      These tests were performed with the following specs:                  *
 *                                                                            *
 *          2017 iMac                                                         *
 *          CPU:  Intel Core i5-7500                                          *
 *          MIN:  800.0000 MHz                                                *
 *          MAX:  3800.0000 MHz                                               *
 *          ARCH: x86_64                                                      *
 *          RAM:  OWC 64GB (4x16GB) PC19200 DDR4 2400MHz SO-DIMMs Memory      *
 *          OS:   Ubuntu Budgie 20.04                                         *
 *                                                                            *
 *      Performance will of course vary on different systems.                 *
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
 *  2022/03/18: Ryan Maguire                                                  *
 *      Changed function to pass by reference instead of by value.            *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the cross product of vectors at double precision.  */
tmpl_ThreeVectorDouble
tmpl_3DDouble_Cross_Product(const tmpl_ThreeVectorDouble *P,
                            const tmpl_ThreeVectorDouble *Q)
{
    /*  Declare a variable for the output.                                    */
    tmpl_ThreeVectorDouble cross;

    /*  Compute the components of the cross product PxQ.                      */
    cross.dat[0] = P->dat[1]*Q->dat[2] - P->dat[2]*Q->dat[1];
    cross.dat[1] = P->dat[2]*Q->dat[0] - P->dat[0]*Q->dat[2];
    cross.dat[2] = P->dat[0]*Q->dat[1] - P->dat[1]*Q->dat[0];
    return cross;
}
/*  End of tmpl_3DDouble_Cross_Product.                                       */
