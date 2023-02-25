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

static double complex_abs_squared(NATIVE_COMPLEX_DOUBLE z)
{
    double x = creal(z);
    double y = cimag(z);
    return x*x + y*y;
}

#ifdef _WIN32
TEST1(double, tmpl_ComplexDouble, NATIVE_COMPLEX_DOUBLE, tmpl_CDouble_Abs_Squared, complex_abs_squared, _Cbuild)
#else
static inline complex double complex_double_construct(double real, double imag) { return real + (complex double)_Complex_I*imag; }
TEST1(double, tmpl_ComplexDouble, NATIVE_COMPLEX_DOUBLE, tmpl_CDouble_Abs_Squared, complex_abs_squared, complex_double_construct)
#endif