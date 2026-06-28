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
 *                          tmpl_color_average_rgb30                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Blends two colors by averaging over their individual color channels.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RGB30_Average                                                    *
 *  Purpose:                                                                  *
 *      Blends two colors together by averaging their color channels.         *
 *  Arguments:                                                                *
 *      c0 (const tmpl_RGB30):                                                *
 *          A color.                                                          *
 *      c1 (const tmpl_RGB30):                                                *
 *          Another color.                                                    *
 *  Output:                                                                   *
 *      average (tmpl_RGB30):                                                 *
 *          The color average of c0 and c1.                                   *
 *  Called Functions:                                                         *
 *      src/integer/                                                          *
 *          tmpl_UShort_Average:                                              *
 *              Averages two integers without overflow.                       *
 *  Method:                                                                   *
 *      Compute the average of each color channel and store it in the result. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_attributes.h:                                                    *
 *          Provides (optional) C23 attributes for optimization.              *
 *  2.) tmpl_color.h:                                                         *
 *          Header file containing the function prototype.                    *
 *  3.) tmpl_integer.h:                                                       *
 *          Integer average function provided here.                           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2024                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/06/28: Ryan Maguire                                                  *
 *      Added C23 attributes, switched to using the new averaging function.   *
 ******************************************************************************/

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  Color typedefs and function prototypes provided here.                     */
#include <libtmpl/include/tmpl_color.h>

/*  Averaging function found here.                                            */
#include <libtmpl/include/tmpl_integer.h>

/*  Function for averaging together two colors in 30-bit RGB format.          */
TMPL_CONST_FUNC
tmpl_RGB30 tmpl_RGB30_Average(const tmpl_RGB30 c0, const tmpl_RGB30 c1)
TMPL_UNSEQUENCED
{
    /*  Struct for the output. C89 requires declarations at the top.          */
    tmpl_RGB30 average;

    /*  The color channels use 10-bit bit fields to store the data. Unsigned  *
     *  short is required to be at least 16 bits wide, meaning we can safely  *
     *  compute the average using the ushort average function.                */
    const unsigned short int red = tmpl_UShort_Average(c0.red, c1.red);
    const unsigned short int green = tmpl_UShort_Average(c0.green, c1.green);
    const unsigned short int blue = tmpl_UShort_Average(c0.blue, c1.blue);

    /*  The average of two 10-bit values cannot exceed the maximum of 10-bit  *
     *  integers, so there is no need to check for overflow. The bit-wise AND *
     *  with 0x3FFU (2^10 - 1) is simply to prevent compilers from warning    *
     *  about converting short int (usually 16 bits) to a 10-bit integer.     */
    average.red = red & 0x3FFU;
    average.green = green & 0x3FFU;
    average.blue = blue & 0x3FFU;

    return average;
}
/*  End of tmpl_RGB30_Average.                                                */

