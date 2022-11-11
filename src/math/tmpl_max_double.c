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

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Function for finding the maximum of two doubles.                          */
double tmpl_Double_Max(double x, double y)
{
    /*  Special cases, handle NaN's.                                          */
    if (tmpl_Double_Is_NaN(x))
        return y;
    else if (tmpl_Double_Is_NaN(y))
        return x;

    /*  Neither is NaN, compare and return the larger value.                  */
    if (x < y)
        return y;
    else
        return x;
}
/*  End of tmpl_Double_Max.                                                   */
