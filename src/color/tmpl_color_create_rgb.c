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
 *                           tmpl_color_create_rgb                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates a real-valued RGB color from three real numbers.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RGB_Create                                                       *
 *  Purpose:                                                                  *
 *      Creates a color from the values of the color channels.                *
 *  Arguments:                                                                *
 *      red (double):                                                         *
 *          The amount of red in the color.                                   *
 *      green (double):                                                       *
 *          The amount of green in the color.                                 *
 *      blue (double):                                                        *
 *          The amount of blue in the color.                                  *
 *  Output:                                                                   *
 *      c (tmpl_RGB):                                                         *
 *          The color (red, green, blue) in RGB format.                       *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Unit_Clamp:                                           *
 *              Clips a real valued input to fall between zero and one.       *
 *  Method:                                                                   *
 *      Clip each input to make it lie in the unit interval and store the     *
 *      result in an RGB struct.                                              *
 *  Notes:                                                                    *
 *      Colors channels will be "clipped" into the interval [0, 1]. So        *
 *      negative values will correspond to zero, and values greater than one  *
 *      will be reset to one. This includes infinite values as well. NaN will *
 *      be set to NaN. An input of NaN's will give an undefined color.        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_color.h:                                                         *
 *          Header file containing the function prototype.                    *
 *  2.) tmpl_math.h:                                                          *
 *          Unit clamp function provided here.                                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 19, 2023                                             *
 ******************************************************************************/

/*  Color typedef's and the function prototype provided here.                 */
#include <libtmpl/include/tmpl_color.h>

/*  Unit clamp function found here.                                           */
#include <libtmpl/include/tmpl_math.h>

/*  Function for creating an RGB struct from the given color values.          */
tmpl_RGB tmpl_RGB_Create(double red, double green, double blue)
{
    /*  Struct for the output color in real RGB format.                       */
    tmpl_RGB c;

    /*  Ensure the inputs fall between zero and one by clamping. Note that if *
     *  an input is NaN, the unit clamp function will return NaN and the      *
     *  color channel will not be defined.                                    */
    c.dat[0] = tmpl_Double_Unit_Clamp(red);
    c.dat[1] = tmpl_Double_Unit_Clamp(green);
    c.dat[2] = tmpl_Double_Unit_Clamp(blue);

    return c;
}
/*  End of tmpl_RGB_Create.                                                   */
