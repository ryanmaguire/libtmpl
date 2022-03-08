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

/*  The absolute value function is found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Plotting routines defined here.                                           */
#include <libtmpl/include/tmpl_ppm.h>

/*  Routine for plotting the absolute value function y = |x|.                 */
int main(void)
{
    /* Values for the min and max of the x and y axes.                        */
    double x_min = -1.0;
    double x_max =  1.0;

    /*  The number of pixels in the x axes.                                   */
    const unsigned int x_size = 1024;

    /*  The number of pixels in the y axes.                                   */
    const unsigned int y_size = 1024;

    /*  Plot the figure using the rss_ringoccs ppm_plot routines.             */
    tmpl_PPM_Plot("absolute_value.pgm", tmpl_Double_Abs,
                  x_size, y_size, x_min, x_max);

    return 0;
}
/*  End of main.                                                              */
