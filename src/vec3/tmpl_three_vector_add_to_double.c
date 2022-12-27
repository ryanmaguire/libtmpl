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
 *                       tmpl_three_vector_add_to_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for performing vector addition at double precision.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_AddTo                                                   *
 *  Purpose:                                                                  *
 *      Computes the vector sum of two vectors at double precision.           *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorDouble *):                                    *
 *          A pointer to a vector in R^3. The sum will be stored here.        *
 *      source (const tmpl_ThreeVectorDouble *):                              *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of vector addition. If P = (Px, Py, Pz) and        *
 *      Q = (Qx, Qy, Qz), then the vector sum P+Q has coordinates:            *
 *          x = Px + Qx                                                       *
 *          y = Py + Qy                                                       *
 *          z = Pz + Qz                                                       *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *                                                                            *
 *      The macro tmpl_3D_AddTo is an alias for this function.                *
 *                                                                            *
 *      If tmpl_3DDouble_Add is the equivalent of the "+" operator for the    *
 *      tmpl_ThreeVectorDouble struct, this is the equivalent of "+=". It is  *
 *      about 3x faster to do tmpl_3DDouble_AddTo(&P, &Q) instead of doing    *
 *      P = tmpl_3DDouble_Add(&P, &Q).                                        *
 *                                                                            *
 *      No checks for Null pointers are performed.                            *
 *                                                                            *
 *  Accuracy and Performance:                                                 *
 *                                                                            *
 *      A time and accuracy test against linasm's 3D library produced the     *
 *      following results:                                                    *
 *                                                                            *
 *          tmpl_3DDouble_AddTo vs. Vector3D_Add_flt64                        *
 *          samples: 400000000                                                *
 *          libtmpl: 1.166377 seconds                                         *
 *          linasm:  1.170419 seconds                                         *
 *          x max err: 0.000000e+00                                           *
 *          y max err: 0.000000e+00                                           *
 *          z max err: 0.000000e+00                                           *
 *          x rms err: 0.000000e+00                                           *
 *          y rms err: 0.000000e+00                                           *
 *          z rms err: 0.000000e+00                                           *
 *                                                                            *
 *      This test was performed with the following specs:                     *
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
 *  Date:       March 15, 2022                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/17: Ryan Maguire                                                  *
 *      Added doc-string and comments.                                        *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for performing vector addition in R^3.                           */
void tmpl_3DDouble_AddTo(tmpl_ThreeVectorDouble *target,
                         const tmpl_ThreeVectorDouble *source)
{
    target->dat[0] += source->dat[0];
    target->dat[1] += source->dat[1];
    target->dat[2] += source->dat[2];
}
/*  End of tmpl_3DDouble_AddTo.                                               */
