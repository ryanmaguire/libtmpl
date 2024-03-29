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
static float func(NATIVE_COMPLEX_FLOAT z0, NATIVE_COMPLEX_FLOAT z1) {
    const float dx = crealf(z0) - crealf(z1);
    const float dy = cimagf(z0) - cimagf(z1);
    return dx*dx + dy*dy;
}
TEST8(float,
      tmpl_ComplexFloat,
      NATIVE_COMPLEX_FLOAT,
      tmpl_CFloat_Dist_Squared, func, COMPLEX_FLOAT_CTOR)

