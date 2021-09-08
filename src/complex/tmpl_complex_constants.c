/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                          tmpl_complex_constants                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Define 0, 1, i, and complex infinity.                                 *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file where infinity is defined.                            *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *  2020/12/01: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/12/02: Ryan Maguire                                                  *
 *      Frozen for v1.3.                                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2021/06/26: Ryan Maguire                                                  *
 *      Changed NaN variables to compile with TinyC Compiler. Still works     *
 *      with PCC, GCC, anc LLVM's clang.                                      *
 ******************************************************************************/

/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Previously this code followed the style of Python setting infinity to     *
 *  HUGE_VAL and NaN to 0 * HUGE_VAL. This worked on PCC, clang, and GCC, but *
 *  TCC yields a compiler error. Using 0.0 / 0.0 works on all 4 compilers, so *
 *  for the sake of greater portability this is used instead.                 */

/*  Single precision constants.                                               */
const tmpl_ComplexFloat tmpl_CFloat_I = {{0.0F, 1.0F}};
const tmpl_ComplexFloat tmpl_CFloat_Zero = {{0.0F, 0.0F}};
const tmpl_ComplexFloat tmpl_CFloat_One = {{1.0F, 0.0F}};

/*  Double precision constants.                                               */
const tmpl_ComplexDouble tmpl_CDouble_I = {{0.0, 1.0}};
const tmpl_ComplexDouble tmpl_CDouble_Zero = {{0.0, 0.0}};
const tmpl_ComplexDouble tmpl_CDouble_One = {{1.0, 0.0}};

/*  Long double precision constants.                                          */
const tmpl_ComplexLongDouble tmpl_CLDouble_I = {{0.0L, 1.0L}};
const tmpl_ComplexLongDouble tmpl_CLDouble_Zero = {{0.0L, 0.0L}};
const tmpl_ComplexLongDouble tmpl_CLDouble_One = {{1.0L, 0.0L}};

tmpl_ComplexFloat tmpl_CFloat_Infinity(void)
{
    return tmpl_CFloat_Rect(TMPL_INFINITYF, TMPL_INFINITYF);
}

tmpl_ComplexDouble tmpl_CDouble_Infinity(void)
{
    return tmpl_CDouble_Rect(TMPL_INFINITY, TMPL_INFINITY);
}

tmpl_ComplexLongDouble tmpl_CLDouble_Infinity(void)
{
    return tmpl_CLDouble_Rect(TMPL_INFINITYL, TMPL_INFINITYL);
}

tmpl_ComplexFloat tmpl_CFloat_NaN(void)
{
    return tmpl_CFloat_Rect(TMPL_NANF, TMPL_NANF);
}

tmpl_ComplexDouble tmpl_CDouble_NaN(void)
{
    return tmpl_CDouble_Rect(TMPL_NAN, TMPL_NAN);
}

tmpl_ComplexLongDouble tmpl_CLDouble_NaN(void)
{
    return tmpl_CLDouble_Rect(TMPL_NANL, TMPL_NANL);
}
