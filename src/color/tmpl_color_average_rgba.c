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
 *                           tmpl_color_average_rgba                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds to colors by averaging over the color channels.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RGBA_Average                                                     *
 *  Purpose:                                                                  *
 *      Adds two colors together by averaging the color channels.             *
 *  Arguments:                                                                *
 *      c0 (const tmpl_RGBA *):                                               *
 *          A color.                                                          *
 *      c1 (const tmpl_RGBA *):                                               *
 *          Another color.                                                    *
 *  Output:                                                                   *
 *      sum (tmpl_RGBA):                                                      *
 *          The color average of c0 and c1.                                   *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Unit_Clamp:                                           *
 *              Clips a real valued input to fall between zero and one.       *
 *  Method:                                                                   *
 *      Average the individual color channels and clip them to ensure the end *
 *      results lie between 0 and 1.                                          *
 *  Notes:                                                                    *
 *      Colors channels will be "clipped" into the interval [0, 1].           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_color.h:                                                         *
 *          Header file containing the function prototype.                    *
 *  2.) tmpl_math.h:                                                          *
 *          Unit clamp function provided here.                                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2024                                               *
 ******************************************************************************/

/*  Color typedef's and the function prototype provided here.                 */
#include <libtmpl/include/tmpl_color.h>

/*  Unit clamp function found here.                                           */
#include <libtmpl/include/tmpl_math.h>

/*  Function for adding together two RGB colors.                              */
tmpl_RGBA tmpl_RGBA_Average(const tmpl_RGBA *c0, const tmpl_RGBA *c1)
{
    /*  Struct for the output. C89 requires declarations at the top.          */
    tmpl_RGBA average;

    /*  Average the individual color channels. We'll clip these in a moment.  */
    const double red = 0.5 * (c0->dat[0] + c1->dat[0]);
    const double green = 0.5 * (c0->dat[1] + c1->dat[1]);
    const double blue = 0.5 * (c0->dat[2] + c1->dat[2]);

    /*  Average the alpha channels as well.                                   */
    const double alpha = 0.5 * (c0->dat[3] + c1->dat[2]);

    /*  Ensure the color values lie between 0 and 1 by clipping.              */
    average.dat[0] = tmpl_Double_Unit_Clamp(red);
    average.dat[1] = tmpl_Double_Unit_Clamp(green);
    average.dat[2] = tmpl_Double_Unit_Clamp(blue);

    /*  Clip the alpha parameter as well.                                     */
    average.dat[3] = tmpl_Double_Unit_Clamp(alpha);

    return average;
}
/*  End of tmpl_RGB_Average.                                                  */
