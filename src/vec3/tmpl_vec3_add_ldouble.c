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
 *                           tmpl_vec3_add_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs vector addition at long double precision.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DLDouble_Add                                                    *
 *  Purpose:                                                                  *
 *      Computes the vector sum of two vectors at long double precision.      *
 *  Arguments:                                                                *
 *      p (const tmpl_ThreeVectorLongDouble * const):                         *
 *          A pointer to a vector in R^3.                                     *
 *      q (const tmpl_ThreeVectorLongDouble * const):                         *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      sum (tmpl_ThreeVectorLongDouble):                                     *
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
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_ALWAYS_INLINE macro.                         *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides C23 attributes for optimization.                         *
 *  3.) tmpl_vec3.h:                                                          *
 *          tmpl_ThreeVectorLongDouble and function prototype provided here.  *
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

/*  The TMPL_ALWAYS_INLINE macro is provided here.                            */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Three-vector typedef and function prototype found here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for adding 2 three-dimensional vectors.                          */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Add(const tmpl_ThreeVectorLongDouble * const p,
                   const tmpl_ThreeVectorLongDouble * const q)
TMPL_UNSEQUENCED
{
    /*  Variable for the sum of the two inputs.                               */
    tmpl_ThreeVectorLongDouble sum;

    /*  The sum of two vectors simply adds their components together.         */
    sum.dat[0] = p->dat[0] + q->dat[0];
    sum.dat[1] = p->dat[1] + q->dat[1];
    sum.dat[2] = p->dat[2] + q->dat[2];

    return sum;
}
/*  End of tmpl_3DLDouble_Add.                                                */
