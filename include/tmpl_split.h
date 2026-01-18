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

/*  TMPL_USE_INLINE macro provided here.                                      */
#include <libtmpl/include/tmpl_config.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Even_High_Split                                           *
 *  Purpose:                                                                  *
 *      Splits a double and retreives the higher order bits.                  *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      x_hi (double):                                                        *
 *          The high part of x.                                               *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/

/*  These functions are very small and should be inlined, if possible.        */
#if TMPL_USE_INLINE == 1

/*  Inline versions for each data type found here.                            */
#include <libtmpl/include/inline/split/tmpl_even_high_split_float.h>
#include <libtmpl/include/inline/split/tmpl_even_high_split_double.h>
#include <libtmpl/include/inline/split/tmpl_even_high_split_ldouble.h>

#else
/*  Else for #elif TMPL_USE_INLINE == 1.                                      */

/*  Lacking inline support, use the versions in src/split/.                   */
extern float tmpl_Float_Even_High_Split(const float x);
extern double tmpl_Double_Even_High_Split(const double x);
extern long double tmpl_LDouble_Even_High_Split(const long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_High_Split                                                *
 *  Purpose:                                                                  *
 *      Splits a double and retreives the higher order bits.                  *
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

/*  These functions are very small and should be inlined, if possible.        */
#if TMPL_USE_INLINE == 1

/*  Inline versions for each data type found here.                            */
#include <libtmpl/include/inline/split/tmpl_high_split_float.h>
#include <libtmpl/include/inline/split/tmpl_high_split_double.h>
#include <libtmpl/include/inline/split/tmpl_high_split_ldouble.h>

#else
/*  Else for #elif TMPL_USE_INLINE == 1.                                      */

/*  Lacking inline support, use the versions in src/split/.                   */
extern float tmpl_Float_High_Split(const float x, const float splitter);
extern double tmpl_Double_High_Split(const double x, const double splitter);

/*  Double-Double is split differently than the other implementations. Since  *
 *  double-double is literally two doubles together, the splitting factor is  *
 *  of type "double" instead of "long double."                                */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

extern long double
tmpl_LDouble_High_Split(const long double x, const double splitter);

/*  All other versions are treated in a similar manner to float and double.   */
#else

extern long double
tmpl_LDouble_High_Split(const long double x, const long double splitter);

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE.                */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
