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
#ifndef TMPL_NUMERICAL_H
#define TMPL_NUMERICAL_H

#include <libtmpl/include/tmpl_complex.h>

TMPL_EXPORT extern tmpl_ComplexDouble
tmpl_Halleys_Method_Complex(tmpl_ComplexDouble z,
                            tmpl_ComplexDouble (*f)(tmpl_ComplexDouble),
                            tmpl_ComplexDouble (*f_prime)(tmpl_ComplexDouble),
                            tmpl_ComplexDouble (*f_2prime)(tmpl_ComplexDouble),
                            unsigned int max_iters, double eps);

TMPL_EXPORT extern tmpl_ComplexDouble
tmpl_Newton_Raphson_Complex(tmpl_ComplexDouble z,
                            tmpl_ComplexDouble (*f)(tmpl_ComplexDouble),
                            tmpl_ComplexDouble (*f_prime)(tmpl_ComplexDouble),
                            unsigned int max_iters, double eps);

TMPL_EXPORT extern tmpl_ComplexDouble
tmpl_Newton_Raphson_CDouble_Poly_Real(tmpl_ComplexDouble z,
                                      double *coeffs, unsigned int degree,
                                      unsigned int max_iters, double eps);

TMPL_EXPORT extern float
tmpl_Newton_Raphson_Float(float x, float (*f)(float), float (*f_prime)(float),
                          unsigned int max_iters, float eps);

TMPL_EXPORT extern double
tmpl_Newton_Raphson_Double(double x, double (*f)(double),
                           double (*f_prime)(double),
                           unsigned int max_iters, double eps);

TMPL_EXPORT extern long double
tmpl_Newton_Raphson_LDouble(long double x, long double (*f)(long double),
                            long double (*f_prime)(long double),
                            unsigned int max_iters, long double eps);

TMPL_EXPORT extern float
tmpl_Halleys_Method_Float(float x, float (*f)(float),
                          float (*f_prime)(float),
                          float (*f_2prime)(float),
                          unsigned int max_iters, float eps);

TMPL_EXPORT extern double
tmpl_Halleys_Method_Double(double x, double (*f)(double),
                           double (*f_prime)(double),
                           double (*f_2prime)(double),
                           unsigned int max_iters, double eps);

TMPL_EXPORT extern long double
tmpl_Halleys_Method_LDouble(long double x, long double (*f)(long double),
                            long double (*f_prime)(long double),
                            long double (*f_2prime)(long double),
                            unsigned int max_iters, long double eps);

TMPL_EXPORT extern float
tmpl_Float_Five_Point_Derivative(float (*f)(float), float x, float h);

TMPL_EXPORT extern double
tmpl_Double_Five_Point_Derivative(double (*f)(double), double x, double h);

TMPL_EXPORT extern long double
tmpl_LDouble_Five_Point_Derivative(long double (*f)(long double),
                                   long double x, long double h);

#endif
/*  End of include guard: #ifndef __TMPL_NUMERICAL_H__                        */
