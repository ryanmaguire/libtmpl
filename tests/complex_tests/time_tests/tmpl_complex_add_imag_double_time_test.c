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
static inline _Dcomplex add(double y, _Dcomplex z)
{
    return _Cbuild(creal(z), cimag(z) + y);
}
#else
static inline complex double add(double y, complex double z)
{
    return z + (complex double)_Complex_I*y;
}
#endif
TEST5(double, tmpl_ComplexDouble, NATIVE_COMPLEX_DOUBLE, tmpl_CDouble_Add_Imag, add, COMPLEX_DOUBLE_CTOR)
