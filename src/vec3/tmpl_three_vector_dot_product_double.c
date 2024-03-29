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
 *                    tmpl_three_vector_dot_product_double                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the Euclidean dot product at double precision.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Dot_Product                                             *
 *  Purpose:                                                                  *
 *      Computes the dot product of two vectors at double precision.          *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorDouble *):                                   *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorDouble *):                                   *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      dot (double):                                                         *
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
 *      The macro tmpl_3D_Dot_Product is an alias for this function.          *
 *                                                                            *
 *      No checks for Null pointers are performed.                            *
 *                                                                            *
 *  Accuracy and Performance:                                                 *
 *                                                                            *
 *      A time and accuracy test against linasm's 3D library produced the     *
 *      following results:                                                    *
 *                                                                            *
 *          tmpl_3DDouble_Dot_Product vs. Vector3D_ScalarProduct_flt64        *
 *          samples: 400000000                                                *
 *          libtmpl: 1.965377 seconds                                         *
 *          linasm:  1.921617 seconds                                         *
 *          max err: 0.000000e+00                                             *
 *          rms err: 0.000000e+00                                             *
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
 *  2022/03/21: Ryan Maguire                                                  *
 *      Changed function to pass by reference instead of by value.            *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the dot product of 2 three-vectors.                */
double
tmpl_3DDouble_Dot_Product(const tmpl_ThreeVectorDouble *P,
                          const tmpl_ThreeVectorDouble *Q)
{
    /*  Use the Euclidean dot product formula and return.                     */
    return P->dat[0]*Q->dat[0] + P->dat[1]*Q->dat[1] + P->dat[2]*Q->dat[2];
}
/*  End of tmpl_3DDouble_Dot_Product.                                         */
