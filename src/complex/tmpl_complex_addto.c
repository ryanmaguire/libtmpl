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
 *                           tmpl_complex_addto                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_AddTo:                                                    *
 *      tmpl_CDouble_AddTo:                                                   *
 *      tmpl_CLDouble_AddTo:                                                  *
 *  Purpose:                                                                  *
 *      Adds two complex numbers:                                             *
 *                                                                            *
 *          z + w = (a + ib) + (c + id) = (a + c) + i(b + d)                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble *):              *
 *          A pointer to acomplex number. The sum is stored here.             *
 *      w (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the component-wise sum and store it in the first pointer.     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Contains the TMPL_USE_INLINE macro.                               *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 8, 2022                                             *
 ******************************************************************************/

/*  TMPL_USE_INLINE found here.                                               */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if defined(TMPL_USE_INLINE) && TMPL_USE_INLINE != 1

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z0  *
 *  and double _Complex z1, you can just do z0 += z1. With C89 we use structs *
 *  to define complex numbers. Structs cannot be added, so we need a function *
 *  for computing the sum of two complex values.                              */

/*  Single precision complex addition. Equivalent of += operation.            */
void
tmpl_CFloat_AddTo(tmpl_ComplexFloat *z, const tmpl_ComplexFloat *w)
{
    /*  Complex addition is done component-wise.                              */
    z->dat[0] += w->dat[0];
    z->dat[1] += w->dat[1];
}
/*  End of tmpl_CFloat_AddTo.                                                 */

/*  Double precision complex addition. Equivalent of += operation.            */
void
tmpl_CDouble_AddTo(tmpl_ComplexDouble *z, const tmpl_ComplexDouble *w)
{
    /*  Complex addition is done component-wise.                              */
    z->dat[0] += w->dat[0];
    z->dat[1] += w->dat[1];
}
/*  End of tmpl_CDouble_AddTo.                                                */

/*  Long double precision complex addition. Equivalent of += operation.       */
void
tmpl_CLDouble_AddTo(tmpl_ComplexLongDouble *z, const tmpl_ComplexLongDouble *w)
{
    /*  Complex addition is done component-wise.                              */
    z->dat[0] += w->dat[0];
    z->dat[1] += w->dat[1];
}
/*  End of tmpl_CLDouble_AddTo.                                               */

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
