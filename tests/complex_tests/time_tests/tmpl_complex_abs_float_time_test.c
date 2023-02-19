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
TEST1(float, tmpl_ComplexFloat, NATIVE_COMPLEX_FLOAT, tmpl_CFloat_Abs, cabsf, _FCbuild)
#else
static inline complex float complex_float_construct(float real, float imag) { return real + (complex float)_Complex_I*imag; }
TEST1(float, tmpl_ComplexFloat, NATIVE_COMPLEX_FLOAT, tmpl_CFloat_Abs, cabsf, complex_float_construct)
#endif