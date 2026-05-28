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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SPLIT_H
#define TMPL_SPLIT_H

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Even_High_Split                                           *
 *  Purpose:                                                                  *
 *      Splits a double and retrieves the higher order bits.                  *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      x_hi (double):                                                        *
 *          The high part of x.                                               *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
#include <libtmpl/include/split/tmpl_even_high_split_float.h>
#include <libtmpl/include/split/tmpl_even_high_split_double.h>
#include <libtmpl/include/split/tmpl_even_high_split_ldouble.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_High_Split                                                *
 *  Purpose:                                                                  *
 *      Splits a double and retrieves the higher order bits.                  *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      splitter (const double):                                              *
 *          The splitting factor. This should be 2^n + 1 if you want the      *
 *          higher 53 - n bits, assuming double has a 52-bit mantissa.        *
 *  Output:                                                                   *
 *      x_hi (double):                                                        *
 *          The high part of x.                                               *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
#include <libtmpl/include/split/tmpl_high_split_float.h>
#include <libtmpl/include/split/tmpl_high_split_double.h>
#include <libtmpl/include/split/tmpl_high_split_ldouble.h>

#endif
/*  End of include guard.                                                     */
