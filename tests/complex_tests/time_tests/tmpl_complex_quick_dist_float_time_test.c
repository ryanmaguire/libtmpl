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
#ifdef _MSC_VER
static float func(_Fcomplex z0, _Fcomplex z1){
    return cabsf(_FCbuild(crealf(z0)-crealf(z1), cimagf(z0)-cimagf(z1)));
}
#else
static float func(complex float z0, complex float z1){return cabsf(z0-z1);}
#endif
TEST8(float, tmpl_ComplexFloat, NATIVE_COMPLEX_FLOAT, tmpl_CFloat_Quick_Dist, func, COMPLEX_FLOAT_CTOR)

