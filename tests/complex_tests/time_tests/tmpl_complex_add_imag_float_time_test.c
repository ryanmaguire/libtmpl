/******************************************************************************
 *                                 LICENSE                                    *
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
static inline _Fcomplex add(float y, _Fcomplex z)
{
    return _FCbuild(crealf(z), cimagf(z) + y);
}
#else
static inline complex float add(float y, complex float z)
{
    return z + _Complex_I*y;
}
#endif
TEST5(float, tmpl_ComplexFloat, NATIVE_COMPLEX_FLOAT, tmpl_CFloat_Add_Imag, add)
