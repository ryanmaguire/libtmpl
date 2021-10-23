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
 *      Provides an example of using NaN.                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       October 20, 2021                                              *
 ******************************************************************************/

/*  printf is found here.                                                     */
#include <stdio.h>

/*  Function declared here.                                                   */
#include <libtmpl/include/tmpl_math.h>

/*  Function for testing NaN functions.                                       */
int main(void)
{
    /*  Compute NaN at various precisions.                                    */
    const float nanf = tmpl_Float_NaN();
    const double nan = tmpl_Double_NaN();
    const long double nanl = tmpl_LDouble_NaN();

    /*  Print the results.                                                    */
    printf("Float NaN:       %f\n", (double)nanf);
    printf("Double NaN:      %f\n", nan);
    printf("Long Double NaN: %Lf\n", nanl);
    return 0;
}
/*  End of main.                                                              */
