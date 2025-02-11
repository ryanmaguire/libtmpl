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
 *                            tmpl_airy_j1_double                             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 11, 2025                                             *
 ******************************************************************************/


/*  Prototype for the function given here.                                    */
#include <libtmpl/include/tmpl_special_functions_real.h>

double tmpl_Double_Airy_J1(double x)
{
    if (x == 0.0)
        return 1.0;

    return 2.0 * tmpl_Double_Bessel_J1(x) / x;
}
