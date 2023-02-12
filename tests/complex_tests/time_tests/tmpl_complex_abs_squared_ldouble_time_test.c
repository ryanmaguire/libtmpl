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

#ifdef _WIN32
static long double complex_abs_squared(_Lcomplex z)
{
    long double x = creall(z);
    long double y = cimagl(z);
    return x*x + y*y;
}
TEST1(long double,
      tmpl_ComplexLongDouble,
      _Lcomplex,
      tmpl_CLDouble_Abs_Squared,
      complex_abs_squared,
      _LCbuild)
#else
static long double complex_abs_squared(complex long double z)
{
    long double x = creall(z);
    long double y = cimagl(z);
    return x*x + y*y;
}
static inline complex long double complex_long_double_construct(long double real, long double imag) { return real + (complex long double)_Complex_I*imag; }
TEST1(long double,
      tmpl_ComplexLongDouble,
      complex long double,
      tmpl_CLDouble_Abs_Squared,
      complex_abs_squared,
      complex_long_double_construct)
#endif