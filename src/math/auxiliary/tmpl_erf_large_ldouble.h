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
 *                        tmpl_erf_asymptotic_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the error function for large positive values.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Erf_Asymptotic                                           *
 *  Purpose:                                                                  *
 *      Computes the Error function erf(x) for x >= 2.                        *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A positive real number.                                           *
 *  Output:                                                                   *
 *      erf_x (long double):                                                  *
 *          The error function at x.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use two Remez Minimax polynomials. The windows [a, b] and [b, c]      *
 *      where the polynomials are used depend on the type of long double      *
 *      being used. For very large values use the asymptote, which is 1.      *
 *  Notes:                                                                    *
 *      Accurate for x >= 2.                                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2023                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_LARGE_LDOUBLE_H
#define TMPL_ERF_LARGE_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT
#include "tmpl_erf_large_ldouble_64_bit_double.h"
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT
#include "tmpl_erf_large_ldouble_128_bit_quadruple.h"
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE
#include "tmpl_erf_large_ldouble_128_bit_double_double.h"
#else
#include "tmpl_erf_large_ldouble_80_bit_extended.h"
#endif

#endif
/*  End of include guard.                                                     */
