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
 *                          tmpl_vec3_add_to_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs vector addition at long double precision.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_AddTo                                                  *
 *  Purpose:                                                                  *
 *      Computes the vector sum of two vectors at long double precision.      *
 *  Arguments:                                                                *
 *      target (tmpl_ThreeVectorLongDouble * const):                          *
 *          A pointer to a vector in R^3. The sum will be stored here.        *
 *      source (const tmpl_ThreeVectorLongDouble * const):                    *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of vector addition. If p = (px, py, pz) and        *
 *      q = (qx, qy, qz), then the vector sum p + q has coordinates:          *
 *                                                                            *
 *          x = px + qx                                                       *
 *          y = py + qy                                                       *
 *          z = pz + qz                                                       *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *                                                                            *
 *      2.) No checks for Null pointers are performed.                        *
 *                                                                            *
 *      3.) This function acts as a += operator for vectors. It is much       *
 *          faster to do tmpl_3DLDouble_AddTo(&p, &q) instead of              *
 *          p = tmpl_3DLDouble_Add(&p, &q).                                   *
 *                                                                            *
 *      4.) Modern compilers with link-time optimization can inline this      *
 *          function across translation units.                                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_vec3.h:                                                          *
 *          tmpl_ThreeVectorLongDouble and function prototype provided here.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/17: Ryan Maguire                                                  *
 *      Added doc-string and comments.                                        *
 *  2024/06/06: Ryan Maguire                                                  *
 *      Inlined the function.                                                 *
 *  2026/06/17: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions.                                *
 ******************************************************************************/

/*  Three-vector typedef and function prototype found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for performing vector addition in R^3.                           */
void
tmpl_3DLDouble_AddTo(tmpl_ThreeVectorLongDouble * const target,
                     const tmpl_ThreeVectorLongDouble * const source)
{
    /*  The sum of two vectors simply adds their components together.         */
    target->dat[0] += source->dat[0];
    target->dat[1] += source->dat[1];
    target->dat[2] += source->dat[2];
}
/*  End of tmpl_3DLDouble_AddTo.                                              */

