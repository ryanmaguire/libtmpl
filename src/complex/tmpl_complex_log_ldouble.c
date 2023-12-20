/******************************************************************************
 *                                  LICENSE                                   *
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

/*  Header file providing logarithmic and trigonometric functions.            */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Long double precision complex log (clogl equivalent (C99)).               */
tmpl_ComplexLongDouble tmpl_CLDouble_Log(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble ln_z;

    /*  Get the polar representation of the complex number z.                 */
    const long double r = tmpl_CLDouble_Abs(z);
    const long double theta = tmpl_LDouble_Arctan2(z.dat[1], z.dat[0]);

    /*  The real part is just ln(r), and the imaginary part is theta.         */
    const long double real = tmpl_LDouble_Log(r);

    /*  Using rectangular coordinates, create the output complex number.      */
    ln_z.dat[0] = real;
    ln_z.dat[1] = theta;
    return ln_z;
}
/*  End of tmpl_CLDouble_Log.                                                 */
