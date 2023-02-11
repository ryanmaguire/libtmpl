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
static inline tmpl_ComplexDouble
ahh(const tmpl_ComplexDouble *z0, const tmpl_ComplexDouble *z1)
{
    tmpl_ComplexDouble sum;
    sum.dat[0] = z0->dat[0] + z1->dat[0];
    sum.dat[1] = z0->dat[1] + z1->dat[1];
    return sum;
}

#ifdef _WIN32
TEST2(double, tmpl_ComplexDouble, _Dcomplex, ahh, +, _Cbuild)
#else
static inline complex double complex_double_construct(double real, double imag) { return u0 + (complex double)_Complex_I*u1; }
TEST2(double, tmpl_ComplexDouble, complex double, ahh, +, complex_double_construct)
#endif

#else

#ifdef _WIN32
TEST3(double, tmpl_ComplexDouble, _Dcomplex, tmpl_CDouble_Add, +, _Cbuild)
#else
static inline complex double complex_double_construct(double real, double imag) { return u0 + (complex double)_Complex_I*u1; }
TEST3(double, tmpl_ComplexDouble, complex double, tmpl_CDouble_Add, +, complex_double_construct)
#endif

#endif