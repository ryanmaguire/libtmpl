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
 *                           tmpl_color_average_rgb                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Blends two colors by averaging over their individual color channels.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RGB_Average                                                      *
 *  Purpose:                                                                  *
 *      Blends two colors together by averaging their color channels.         *
 *  Arguments:                                                                *
 *      c0 (const tmpl_RGB * const):                                          *
 *          A color.                                                          *
 *      c1 (const tmpl_RGB * const):                                          *
 *          Another color.                                                    *
 *  Output:                                                                   *
 *      average (tmpl_RGB):                                                   *
 *          The color average of c0 and c1.                                   *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Unit_Clamp:                                           *
 *              Clips a real-valued input to fall between zero and one.       *
 *  Method:                                                                   *
 *      Average the individual color channels and clip them to ensure the end *
 *      results lie between 0 and 1.                                          *
 *  Notes:                                                                    *
 *      Color channels will be "clipped" into the interval [0, 1].            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_attributes.h:                                                    *
 *          Provides (optional) C23 attributes for optimization.              *
 *  2.) tmpl_color.h:                                                         *
 *          Header file containing the function prototype.                    *
 *  3.) tmpl_math.h:                                                          *
 *          Unit clamp function provided here.                                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2024                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/06/28: Ryan Maguire                                                  *
 *      Added C23 attributes, cleaned up docstring.                           *
 ******************************************************************************/

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  Color typedefs and the function prototype provided here.                  */
#include <libtmpl/include/tmpl_color.h>

/*  Unit clamp function found here.                                           */
#include <libtmpl/include/tmpl_math.h>

/*  Function for averaging together two RGB colors.                           */
TMPL_PURE_FUNC
tmpl_RGB tmpl_RGB_Average(const tmpl_RGB * const c0, const tmpl_RGB * const c1)
TMPL_UNSEQUENCED
{
    /*  Struct for the output. C89 requires declarations at the top.          */
    tmpl_RGB average;

    /*  Average the individual color channels. We'll clip these in a moment.  */
    const double red = 0.5 * (c0->dat[0] + c1->dat[0]);
    const double green = 0.5 * (c0->dat[1] + c1->dat[1]);
    const double blue = 0.5 * (c0->dat[2] + c1->dat[2]);

    /*  Ensure the color values lie between 0 and 1 by clipping.              */
    average.dat[0] = tmpl_Double_Unit_Clamp(red);
    average.dat[1] = tmpl_Double_Unit_Clamp(green);
    average.dat[2] = tmpl_Double_Unit_Clamp(blue);

    return average;
}
/*  End of tmpl_RGB_Average.                                                  */
