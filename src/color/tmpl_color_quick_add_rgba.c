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
 *                             tmpl_color_add_rgba                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds to colors by summing over the individual color channels.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RGBA_Add                                                         *
 *  Purpose:                                                                  *
 *      Adds two colors together by summing the color channels.               *
 *  Arguments:                                                                *
 *      c0 (const tmpl_RGBA *):                                               *
 *          A color.                                                          *
 *      c1 (const tmpl_RGBA *):                                               *
 *          Another color.                                                    *
 *  Output:                                                                   *
 *      sum (tmpl_RGBA):                                                      *
 *          The color sum of c0 and c1.                                       *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Unit_Clamp:                                           *
 *              Clips a real valued input to fall between zero and one.       *
 *  Method:                                                                   *
 *      Sum the individual color channels and clip them to ensure the end     *
 *      results lie between 0 and 1. The alpha parameter will also be added   *
 *      and clamped to fall within this region.                               *
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
tmpl_RGBA tmpl_RGBA_Quick_Add(const tmpl_RGBA *c0, const tmpl_RGBA *c1)
{
    /*  Struct for the output. C89 requires declarations at the top.          */
    tmpl_RGBA sum;

    /*  Add the colors in each channel and store them in the output.          */
    sum.dat[0] = c0->dat[0] + c1->dat[0];
    sum.dat[1] = c0->dat[1] + c1->dat[1];
    sum.dat[2] = c0->dat[2] + c1->dat[2];

    /*  Similarly, sum the alpha parameters together.                         */
    sum.dat[3] = c0->dat[3] + c1->dat[3];

    return sum;
}
/*  End of tmpl_RGBA_Quick_Add.                                               */
