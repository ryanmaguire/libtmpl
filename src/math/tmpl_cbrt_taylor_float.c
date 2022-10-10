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
 ******************************************************************************/

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  Only compile this file if inline support is not requested.                */
#if TMPL_USE_INLINE != 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the Taylor series at x = 1.                              */
#define A0 (1.0000000000000000000000000000E+00F)
#define A1 (3.3333333333333333333333333333E-01F)
#define A2 (-1.111111111111111111111111111E-01F)
#define A3 (6.1728395061728395061728395061E-02F)

/*  Function for computing the Taylor series of cbrt(x) at x = 1 to 5 terms.  */
float tmpl_Float_Cbrt_Taylor(float x)
{
    /*  The series is computed at x = 1. Shift the input.                     */
    const float xs = x - 1.0F;

    /*  Use Horner's method to evaluate the polynomial.                       */
    return A0 + xs*(A1 + xs*(A2 + xs*A3));
}
/*  End of tmpl_Float_Cbrt_Taylor.                                            */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
