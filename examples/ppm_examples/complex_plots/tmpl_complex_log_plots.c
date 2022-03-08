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
 ******************************************************************************/

/*  This program plots the real and imaginary parts of the complex log        *
 *  function using a color gradient to represent the values.                  */

/*  Complex numbers and functions found here.                                 */
#include <libtmpl/include/tmpl_complex.h>

/*  Plotting routine found here.                                              */
#include <libtmpl/include/tmpl_ppm.h>

/*  Function for plotting complex log.                                        */
int main(void)
{
    /*  The number of pixels in the x and y axes.                             */
    const unsigned int size = 1024U;

    /* Values for the min and max of the x and y axes.                        */
    const double x_min = -4.0;
    const double x_max = 4.0;
    const double y_min = -4.0;
    const double y_max = 4.0;

    /*  Plot the function.                                                    */
    tmpl_PPM_Complex_Plot("complex_log", tmpl_CDouble_Log,
                          size, size, x_min, x_max, y_min, y_max);
    return 0;
}
/*  End of main.                                                              */
