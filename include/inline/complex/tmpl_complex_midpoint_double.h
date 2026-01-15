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
 *                        tmpl_complex_midpoint_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the midpoint of two points in the complex plane.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Midpoint                                                 *
 *  Purpose:                                                                  *
 *      Computes the midpoint of two double precision complex numbers.        *
 *  Arguments:                                                                *
 *      z (const tmpl_ComplexDouble):                                         *
 *          A point in the complex plane.                                     *
 *      w (const tmpl_ComplexDouble):                                         *
 *          Another point in the complex plane.                               *
 *  Output:                                                                   *
 *      mid (tmpl_ComplexDouble):                                             *
 *          The midpoint of z and w.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The midpoint is computed by averaging the components. That is, if     *
 *      z = (a, b) and w = (c, d), then the midpoint is given by:             *
 *                                                                            *
 *                z + w                                                       *
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
 *      1.) There are no checks for NaN or infinity.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_complex_double.h:                                                *
 *          The tmpl_ComplexDouble typedef is provided here.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 25, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_MIDPOINT_DOUBLE_H
#define TMPL_COMPLEX_MIDPOINT_DOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  complex typedef found here.                                               */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  Function for computing the midpoint of two complex numbers.               */
TMPL_INLINE_DECL
tmpl_ComplexDouble
tmpl_CDouble_Midpoint(const tmpl_ComplexDouble z, const tmpl_ComplexDouble w)
{
    /*  Output variable for the midpoint of z and w.                          */
    tmpl_ComplexDouble mid;

    /*  The midpoint is computed by averaging the components.                 */
    mid.dat[0] = 0.5 * (z.dat[0] + w.dat[0]);
    mid.dat[1] = 0.5 * (z.dat[1] + w.dat[1]);
    return mid;
}
/*  End of tmpl_CDouble_Midpoint.                                             */

#endif
/*  End of include guard.                                                     */
