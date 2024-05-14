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
 ******************************************************************************
 *                tmpl_complex_newtons_method_explicit_double                 *
 ******************************************************************************/
#include <libtmpl/include/tmpl_root_finding_complex.h>
#include <libtmpl/include/tmpl_float.h>

tmpl_ComplexDouble
tmpl_CDouble_Newtons_Method_Explicit(
    tmpl_ComplexDouble z,
    tmpl_ComplexDouble (*f)(tmpl_ComplexDouble),
    tmpl_ComplexDouble (*f_prime)(tmpl_ComplexDouble)
)
{
    const double eps = TMPL_SQRT_DBL_EPS;
    const unsigned int toler = 32U;
    return tmpl_CDouble_Newtons_Method_Explicit_With_Vars(
        z, f, f_prime, toler, eps
    );
}
