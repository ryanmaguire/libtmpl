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
static long double func(NATIVE_COMPLEX_LDOUBLE z0, NATIVE_COMPLEX_LDOUBLE z1) {
    const long double dx = creall(z0) - creall(z1);
    const long double dy = cimagl(z0) - cimagl(z1);
    return dx*dx + dy*dy;
}
TEST8(long double,
      tmpl_ComplexLongDouble,
      NATIVE_COMPLEX_LDOUBLE,
      tmpl_CLDouble_Dist_Squared, func, COMPLEX_LDOUBLE_CTOR)

