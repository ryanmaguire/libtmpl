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
static double func(_Dcomplex z0, _Dcomplex z1){
    return cabs(_Cbuild(creal(z0)-creal(z1), cimag(z0)-cimag(z1)));
}
#else
static double func(complex double z0, complex double z1){return cabs(z0-z1);}
#endif

TEST8(double, tmpl_ComplexDouble, complex double, tmpl_CDouble_Dist, func, COMPLEX_DOUBLE_CTOR)

