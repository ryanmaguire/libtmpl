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
 *                          tmpl_complex_abs_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex modulus (absolute value).        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Abs:                                                      *
 *  Purpose:                                                                  *
 *      Computes the absolute value, or modulus, of a complex number:         *
 *                                                                            *
 *          |z| = |x + iy| = sqrt(x^2 + y^2)                                  *
 *                                                                            *
 *  Method:                                                                   *
 *      Pass the real and imaginary parts to tmpl_Float_Hypot.                *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat):                                                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      abs_z (float):                                                        *
 *          The absolute value of z.                                          *
 *  Called Functions:                                                         *
 *      tmpl_Float_Hypot (tmpl_math.h):                                       *
 *          Function for computing the magnitude of the vector (x, y).        *
 *  Error:                                                                    *
 *      Based on 134,217,728 random samples:                                  *
 *          Max Relative Error: 2.220446E-16                                  *
 *          RMS Relative Error: 3.751642e-17                                  *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          TMPL_USE_INLINE macro found here.                                 *
 *  2.) tmpl_math.h:                                                          *
 *          Header file containing basic math functions.                      *
 *  3.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved main algorithm to tmpl_hypot_float.c Function now passes the    *
 *      the real and imaginary parts to tmpl_Float_Hypot.                     *
 ******************************************************************************/

/*  The TMPL_USE_INLINE macro is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if TMPL_USE_INLINE != 1

/*  Header file containing basic math functions.                              */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are given and where complex types are defined.       */
#include <libtmpl/include/tmpl_complex.h>

/*  Function for computing the magnitude, or modulus, of a complex number.    */
float tmpl_CFloat_Abs(tmpl_ComplexFloat z)
{
    return tmpl_Float_Hypot(z.dat[0], z.dat[1]);
}
/*  End of tmpl_CFloat_Abs.                                                   */

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
