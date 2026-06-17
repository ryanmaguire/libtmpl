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
 *                            tmpl_vec3_add_double                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs vector addition at double precision.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Add                                                     *
 *  Purpose:                                                                  *
 *      Computes the vector sum of two vectors at double precision.           *
 *  Arguments:                                                                *
 *      p (const tmpl_ThreeVectorDouble * const):                             *
 *          A pointer to a vector in R^3.                                     *
 *      q (const tmpl_ThreeVectorDouble * const):                             *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      sum (tmpl_ThreeVectorDouble):                                         *
 *          The vector sum p + q.                                             *
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
 *      3.) Performance tests indicate that it is faster to pass by address   *
 *          instead of passing by value.                                      *
 *                                                                            *
 *      4.) Modern compilers with link-time optimization can inline this      *
 *          function across translation units.                                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_attributes.h:                                                    *
 *          Provides C23 attributes for optimization.                         *
 *  2.) tmpl_vec3_double.h:                                                   *
 *          The tmpl_ThreeVectorDouble typedef is provided here.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/02: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 *  2022/03/17: Ryan Maguire                                                  *
 *      Changed function to pass by reference instead of by value.            *
 *  2024/06/06: Ryan Maguire                                                  *
 *      Inlined the function.                                                 *
 *  2026/06/17: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added C23 attributes.          *
 ******************************************************************************/

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Three-vector typedef provided here.                                       */
#include <libtmpl/include/types/tmpl_vec3_double.h>

/*  Function prototype / forward declaration.                                 */
extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Add(const tmpl_ThreeVectorDouble * const p,
                  const tmpl_ThreeVectorDouble * const q);

/*  Function for adding 2 three-dimensional vectors.                          */
TMPL_PURE_FUNC
tmpl_ThreeVectorDouble
tmpl_3DDouble_Add(const tmpl_ThreeVectorDouble * const p,
                  const tmpl_ThreeVectorDouble * const q)
TMPL_UNSEQUENCED
{
    /*  Variable for the sum of the two inputs.                               */
    tmpl_ThreeVectorDouble sum;

    /*  The sum of two vectors simply adds their components together.         */
    sum.dat[0] = p->dat[0] + q->dat[0];
    sum.dat[1] = p->dat[1] + q->dat[1];
    sum.dat[2] = p->dat[2] + q->dat[2];

    return sum;
}
/*  End of tmpl_3DDouble_Add.                                                 */
