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
 *                         tmpl_vec2_midpoint_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the midpoint of two points in the plane.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DDouble_Midpoint                                                *
 *  Purpose:                                                                  *
 *      Computes the midpoint of two double precision 2D vectors.             *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a point in the Euclidean plane.                      *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another point in the Euclidean plane.                             *
 *  Output:                                                                   *
 *      mid (tmpl_TwoVectorDouble):                                           *
 *          The midpoint of P and Q.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The midpoint is computed by averaging the components. That is, if     *
 *      P = (a, b) and Q = (c, d), then the midpoint is given by:             *
 *                                                                            *
 *                P + Q                                                       *
 *          mid = -----                                                       *
 *                  2                                                         *
 *                                                                            *
 *                (a, b) + (c, d)                                             *
 *              = ---------------                                             *
 *                       2                                                    *
 *                                                                            *
 *                 -               -                                          *
 *                |  a + c   b + d  |                                         *
 *              = |  ----- , -----  |                                         *
 *                |    2       2    |                                         *
 *                 -               -                                          *
 *                                                                            *
 *      In other words:                                                       *
 *                                                                            *
 *          x = (a + c) / 2                                                   *
 *          y = (b + d) / 2                                                   *
 *                                                                            *
 *      We compute these averages and return.                                 *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P and Q are  *
 *          valid pointers to 2D vectors.                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_double.h:                                                   *
 *          The tmpl_TwoVectorDouble typedef is provided here.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 29, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files. Also changed *
 *      function to pass the vector struct by address, rather than value.     *
 *  2025/05/06: Ryan Maguire                                                  *
 *      Inlined the function, added detailed docstring.                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_MIDPOINT_DOUBLE_H
#define TMPL_VEC2_MIDPOINT_DOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  Function for computing the midpoint of two 2D vectors.                    */
TMPL_INLINE_DECL
tmpl_TwoVectorDouble
tmpl_2DDouble_Midpoint(const tmpl_TwoVectorDouble * const P,
                       const tmpl_TwoVectorDouble * const Q)
{
    /*  Output variable for the midpoint of P and Q.                          */
    tmpl_TwoVectorDouble mid;

    /*  The midpoint is computed by averaging the components.                 */
    mid.dat[0] = 0.5 * (P->dat[0] + Q->dat[0]);
    mid.dat[1] = 0.5 * (P->dat[1] + Q->dat[1]);
    return mid;
}
/*  End of tmpl_2DDouble_Midpoint.                                            */

#endif
/*  End of include guard.                                                     */
