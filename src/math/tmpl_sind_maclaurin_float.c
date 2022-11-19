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
 *                         tmpl_sind_maclaurin_float                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of sine in degrees.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Sind_Maclaurin                                             *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of sine in degrees for small values x.  *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sind_x (float):                                                       *
 *          The Maclaurin series of sine in degrees.                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \         (-1)^n pi^{2n+1}                          *
 *          sind(x)   =   /        ------------------ * x^{2n}                *
 *                        -----    (2n+1)! 180^{2n+1}                         *
 *                        n = 0                                               *
 *                                                                            *
 *      Use the first 3 terms (0 <= n <= 2) and compute.                      *
 *  Notes:                                                                    *
 *      Only accurate for values near 0.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 25, 2022                                              *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the Maclaurin series at single precision.                */
#define A0 (1.7453292519943295769236907684886127134429E-02F)
#define A1 (-8.8609615570129801598869213154725066307228E-07F)
#define A2 (1.3496016231632550105929914052816816969112E-11F)

/*  Maclaurin series for sine in degrees, single precision, to 3 terms.       */
float tmpl_Float_Sind_Maclaurin(float x)
{
    /*  Declare necessary variables.                                          */
    const float x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0 + x2*(A1 + x2*A2));
}
/*  End of tmpl_Float_Sind_Maclaurin.                                         */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
