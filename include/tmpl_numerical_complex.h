/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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

/*  Include guard for this file to prevent including this twice.              */
#ifndef TMPL_NUMERICAL_COMPLEX_H
#define TMPL_NUMERICAL_COMPLEX_H

#include <libtmpl/include/tmpl_complex.h>

extern tmpl_ComplexDouble
tmpl_Halleys_Method_Complex(tmpl_ComplexDouble z,
                            tmpl_ComplexDouble (*f)(tmpl_ComplexDouble),
                            tmpl_ComplexDouble (*f_prime)(tmpl_ComplexDouble),
                            tmpl_ComplexDouble (*f_2prime)(tmpl_ComplexDouble),
                            unsigned int max_iters, double eps);

extern tmpl_ComplexDouble
tmpl_Newton_Raphson_Complex(tmpl_ComplexDouble z,
                            tmpl_ComplexDouble (*f)(tmpl_ComplexDouble),
                            tmpl_ComplexDouble (*f_prime)(tmpl_ComplexDouble),
                            unsigned int max_iters, double eps);

extern tmpl_ComplexDouble
tmpl_Newton_Raphson_CDouble_Poly_Real(tmpl_ComplexDouble z,
                                      double *coeffs, unsigned int degree,
                                      unsigned int max_iters, double eps);

#endif
