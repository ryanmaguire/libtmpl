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
 *                          tmpl_color_quick_add_rgb                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds to colors by summing over the individual color channels.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RGB_Quick_Add                                                    *
 *  Purpose:                                                                  *
 *      Adds two colors together by summing the color channels.               *
 *  Arguments:                                                                *
 *      c0 (const tmpl_RGB *):                                                *
 *          A color.                                                          *
 *      c1 (const tmpl_RGB *):                                                *
 *          Another color.                                                    *
 *  Output:                                                                   *
 *      sum (tmpl_RGB):                                                       *
 *          The color sum of c0 and c1.                                       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Sum the individual color channels and clip them to ensure the end     *
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

/*  Function for adding together two RGB colors.                              */
tmpl_RGB tmpl_RGB_Quick_Add(const tmpl_RGB *c0, const tmpl_RGB *c1)
{
    /*  Struct for the output. C89 requires declarations at the top.          */
    tmpl_RGB sum;

    /*  Add the colors in each channel and store them in the output.          */
    sum.dat[0] = c0->dat[0] + c1->dat[0];
    sum.dat[1] = c0->dat[1] + c1->dat[1];
    sum.dat[2] = c0->dat[2] + c1->dat[2];

    return sum;
}
/*  End of tmpl_RGB_Quick_Add.                                                */
