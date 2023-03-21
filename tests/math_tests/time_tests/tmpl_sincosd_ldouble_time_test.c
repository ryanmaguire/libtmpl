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
#include "tmpl_math_time_tests.h"
static const long double d2r = 0.01745329251994329576923690768488612713443L;
static void func(long double t, long double *s, long double *c)
{
    const long double arg = fmodl(t, 360.0L)*d2r;
    *s = sinl(arg);
    *c = cosl(arg);
}
TEST4(long double, -1.0E6L, 1.0E6L, tmpl_LDouble_SinCosd, func)
