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
 *                          tmpl_color_average_rgb48                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Blends two colors by averaging over their individual color channels.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RGB48_Average                                                    *
 *  Purpose:                                                                  *
 *      Blends two colors together by averaging their color channels.         *
 *  Arguments:                                                                *
 *      c0 (const tmpl_RGB48):                                                *
 *          A color.                                                          *
 *      c1 (const tmpl_RGB48):                                                *
 *          Another color.                                                    *
 *  Output:                                                                   *
 *      average (tmpl_RGB48):                                                 *
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

/*  Function for averaging together two colors in 48-bit RGB format.          */
TMPL_CONST_FUNC
tmpl_RGB48 tmpl_RGB48_Average(const tmpl_RGB48 c0, const tmpl_RGB48 c1)
TMPL_UNSEQUENCED
{
    /*  Struct for the output. C89 requires declarations at the top.          */
    tmpl_RGB48 average;

    /*  The averaging function safely avoids overflow. Use it to average the  *
     *  individual channels of the two colors.                                */
    average.dat[0] = tmpl_UShort_Average(c0.dat[0], c1.dat[0]);
    average.dat[1] = tmpl_UShort_Average(c0.dat[1], c1.dat[1]);
    average.dat[2] = tmpl_UShort_Average(c0.dat[2], c1.dat[2]);

    return average;
}
/*  End of tmpl_RGB48_Average.                                                */

