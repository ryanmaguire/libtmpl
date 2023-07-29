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
#include "tmpl_complex_time_tests.h"
#define ONE_PI (3.141592653589793238462643383279502884197L)
static inline NATIVE_COMPLEX_LDOUBLE func(long double t)
{
    return COMPLEX_LDOUBLE_CTOR(cosl(ONE_PI*t), sinl(ONE_PI*t));
}
TEST9(long double,
      tmpl_ComplexLongDouble,
      NATIVE_COMPLEX_LDOUBLE,
      tmpl_CLDouble_ExpiPi, func)
