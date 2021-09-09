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
 *  Purpose:                                                                  *
 *      Provides an example of using infinity.                                *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 8, 2021                                             *
 ******************************************************************************/

/*  printf is found here.                                                     */
#include <stdio.h>

/*  Function declared here.                                                   */
#include <libtmpl/include/tmpl_math.h>

/*  Function for testing infinity functions.                                  */
int main(void)
{
    /*  Compute infinity at various precisions.                               */
    const float inff = tmpl_Float_Infinity();
    const double inf = tmpl_Double_Infinity();
    const long double infl = tmpl_LDouble_Infinity();

    /*  Print the results.                                                    */
    printf("Float Infinity:       %f\n", (double)inff);
    printf("Double Infinity:      %f\n", inf);
    printf("Long Double Infinity: %Lf\n", infl);
    return 0;
}
/*  End of main.                                                              */
