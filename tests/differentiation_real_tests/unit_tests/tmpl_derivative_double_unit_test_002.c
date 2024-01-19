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
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_differentiation_real.h>
#include <stdio.h>

int main(void)
{
    const double x0 = 1.0;
    const double tol = 1.0E-6;
    const double y0 = tmpl_Double_Derivative(tmpl_Double_Exp, x0);
    const double ans = tmpl_Euler_E;
    const double err = tmpl_Double_Abs(y0 - ans);

    if (err > tol)
        puts("FAIL");
    else
        puts("PASS");

    return 0;
}
