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

#if 0
static inline tmpl_ComplexLongDouble
ahh(const tmpl_ComplexLongDouble *z0, const tmpl_ComplexLongDouble *z1)
{
    tmpl_ComplexLongDouble sum;
    sum.dat[0] = z0->dat[0] + z1->dat[0];
    sum.dat[1] = z0->dat[1] + z1->dat[1];
    return sum;
}

TEST2(long double, tmpl_ComplexLongDouble, NATIVE_COMPLEX_LDOUBLE, ahh, +, COMPLEX_LDOUBLE_CTOR)
#else
TEST3(long double,
      tmpl_ComplexLongDouble,
      NATIVE_COMPLEX_LDOUBLE,
      tmpl_CLDouble_Add, +, COMPLEX_LDOUBLE_CTOR)
#endif
