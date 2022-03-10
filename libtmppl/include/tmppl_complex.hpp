/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                               tmppl_complex                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide the complex sublibrary of libtmpl for C++ users.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2022                                                *
 ******************************************************************************/

/*  libtmpl complex data types and function declarations are here.            */
#include <libtmpl/include/tmpl_complex.h>

namespace tmppl {

    /*  Single precision complex number class.                                */
    class complexf {
        public:
            tmpl_ComplexFloat data;

            /*  Empty constructor.                                            */
            complexf(void);

            /*  Constructor from two reals. Outputs z = real + i*imag.        */
            complexf(float real, float imag);

            /*  Constructor from a tmpl_ComplexFloat struct.                  */
            complexf(tmpl_ComplexFloat z);

            /*  Computes the absolute value of the complex number.            */
            float abs(void) const;

            /*  Computes the square of the absolute value of the number.      */
            float abs_squared(void) const;

            /*  Computes the argument of the complex number.                  */
            float arg(void) const;

            /*  Computes the complex conjugate of the complex number.         */
            complexf conjugate(void) const;

            /*  Computes the Euclidean distance to another complex number.    */
            float dist(const complexf &w) const;

            /*  Computes the square of the distance to another complex number.*/
            float dist_squared(const complexf &w) const;

            /*  Returns the imaginary part of the complex number.             */
            float imag_part(void) const;

            /*  Returns the real part of the complex number.                  */
            float real_part(void) const;

            /*  Computes the reciprocal of the complex number, 1 / z.         */
            complexf reciprocal(void) const;
    };

    /*  Double precision complex number class.                                */
    class complex {
        public:
            tmpl_ComplexDouble data;

            /*  Empty constructor.                                            */
            complex(void);

            /*  Constructor from two reals. Outputs z = real + i*imag.        */
            complex(double real, double imag);

            /*  Constructor from a tmpl_ComplexDouble struct.                 */
            complex(tmpl_ComplexDouble z);

            /*  Computes the absolute value of the complex number.            */
            double abs(void) const;

            /*  Computes the square of the absolute value of the number.      */
            double abs_squared(void) const;

            /*  Computes the argument of the complex number.                  */
            double arg(void) const;

            /*  Computes the complex conjugate of the complex number.         */
            complex conjugate(void) const;

            /*  Computes the Euclidean distance to another complex number.    */
            double dist(const complex &w) const;

            /*  Computes the square of the distance to another complex number.*/
            double dist_squared(const complex &w) const;

            /*  Returns the imaginary part of the complex number.             */
            double imag_part(void) const;

            /*  Returns the real part of the complex number.                  */
            double real_part(void) const;

            /*  Computes the reciprocal of the complex number, 1 / z.         */
            complex reciprocal(void) const;
    };

    /*  Long double precision complex number class.                           */
    class complexl {
        public:
            tmpl_ComplexLongDouble data;

            /*  Empty constructor.                                            */
            complexl(void);

            /*  Constructor from two reals. Outputs z = real + i*imag.        */
            complexl(long double real, long double imag);

            /*  Constructor from a tmpl_ComplexLongDouble struct.             */
            complexl(tmpl_ComplexLongDouble z);

            /*  Computes the absolute value of the complex number.            */
            long double abs(void) const;

            /*  Computes the square of the absolute value of the number.      */
            long double abs_squared(void) const;

            /*  Computes the argument of the complex number.                  */
            long double arg(void) const;

            /*  Computes the complex conjugate of the complex number.         */
            complexl conjugate(void) const;

            /*  Computes the Euclidean distance to another complex number.    */
            long double dist(const complexl &w) const;

            /*  Computes the square of the distance to another complex number.*/
            long double dist_squared(const complexl &w) const;

            /*  Returns the imaginary part of the complex number.             */
            long double imag_part(void) const;

            /*  Returns the real part of the complex number.                  */
            long double real_part(void) const;

            /*  Computes the reciprocal of the complex number, 1 / z.         */
            complexl reciprocal(void) const;
    };

    /*  Basic math functions with complex numbers.                        */
    complex cos(const tmppl::complex &z);
    complexf cos(const tmppl::complexf &z);
    complexl cos(const tmppl::complexl &z);

    complex exp(const tmppl::complex &z);
    complexf exp(const tmppl::complexf &z);
    complexl exp(const tmppl::complexl &z);

    complex sin(const tmppl::complex &z);
    complexf sin(const tmppl::complexf &z);
    complexl sin(const tmppl::complexl &z);
} /* namespace tmppl */

/*  Addition of complex numbers with other complex numbers or real numbers.   */
tmppl::complex operator + (const tmppl::complex &z, const tmppl::complex &w);
tmppl::complex operator + (const tmppl::complex &z, const double &x);
tmppl::complex operator + (const double &x, const tmppl::complex &z);

tmppl::complexf operator + (const tmppl::complexf &z, const tmppl::complexf &w);
tmppl::complexf operator + (const tmppl::complexf &z, const float &x);
tmppl::complexf operator + (const float &x, const tmppl::complexf &z);

tmppl::complexl operator + (const tmppl::complexl &z, const tmppl::complexl &w);
tmppl::complexl operator + (const tmppl::complexl &z, const long double &x);
tmppl::complexl operator + (const long double &x, const tmppl::complexl &z);

/*  Subtraction of complex numbers with other complex numbers or real numbers.*/
tmppl::complex operator - (const tmppl::complex &z, const tmppl::complex &w);
tmppl::complex operator - (const tmppl::complex &z, const double &x);
tmppl::complex operator - (const double &x, const tmppl::complex &z);

tmppl::complexf operator - (const tmppl::complexf &z, const tmppl::complexf &w);
tmppl::complexf operator - (const tmppl::complexf &z, const float &x);
tmppl::complexf operator - (const float &x, const tmppl::complexf &z);

tmppl::complexl operator - (const tmppl::complexl &z, const tmppl::complexl &w);
tmppl::complexl operator - (const tmppl::complexl &z, const long double &x);
tmppl::complexl operator - (const long double &x, const tmppl::complexl &z);

/*  Multiplication of complex numbers with complex numbers or real numbers.   */
tmppl::complex operator * (const tmppl::complex &z, const tmppl::complex &w);
tmppl::complex operator * (const tmppl::complex &z, const double &x);
tmppl::complex operator * (const double &x, const tmppl::complex &z);

tmppl::complexf operator * (const tmppl::complexf &z, const tmppl::complexf &w);
tmppl::complexf operator * (const tmppl::complexf &z, const float &x);
tmppl::complexf operator * (const float &x, const tmppl::complexf &z);

tmppl::complexl operator * (const tmppl::complexl &z, const tmppl::complexl &w);
tmppl::complexl operator * (const tmppl::complexl &z, const long double &x);
tmppl::complexl operator * (const long double &x, const tmppl::complexl &z);

/*  Division of complex numbers with other complex numbers or real numbers.   */
tmppl::complex operator / (const tmppl::complex &z, const tmppl::complex &w);
tmppl::complex operator / (const tmppl::complex &z, const double &x);
tmppl::complex operator / (const double &x, const tmppl::complex &z);

tmppl::complexf operator / (const tmppl::complexf &z, const tmppl::complexf &w);
tmppl::complexf operator / (const tmppl::complexf &z, const float &x);
tmppl::complexf operator / (const float &x, const tmppl::complexf &z);

tmppl::complexl operator / (const tmppl::complexl &z, const tmppl::complexl &w);
tmppl::complexl operator / (const tmppl::complexl &z, const long double &x);
tmppl::complexl operator / (const long double &x, const tmppl::complexl &z);
