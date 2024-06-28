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
 *                            tmpl_color_add_rgb48                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds two colors by summing over the individual color channels.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RGB48_Add                                                        *
 *  Purpose:                                                                  *
 *      Adds two colors together by summing the color channels.               *
 *  Arguments:                                                                *
 *      c0 (tmpl_RGB48):                                                      *
 *          A color.                                                          *
 *      c1 (tmpl_RGB48):                                                      *
 *          Another color.                                                    *
 *  Output:                                                                   *
 *      sum (tmpl_RGB48):                                                     *
 *          The color sum of c0 and c1.                                       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Carefully sum the individual channels by checking that the result     *
 *      will not overflow, storing the max value of 65535 if it does.         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_color.h:                                                         *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2024                                               *
 ******************************************************************************/

/*  Color typedef's and function prototypes provided here.                    */
#include <libtmpl/include/tmpl_color.h>

/*  The maximum value for a 16-bit color channel is 65535.                    */
#define PEAK (0xFFFFU)

/*  Function for adding together two colors in 48-bit RGB format.             */
tmpl_RGB48 tmpl_RGB48_Add(tmpl_RGB48 c0, tmpl_RGB48 c1)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_RGB48 sum;

    /*  Avoid overflowing the sums by ensuring the sums of the color channels *
     *  do not exceed 65535.                                                  */
    const unsigned short int r_diff = PEAK - c0.dat[0];
    const unsigned short int g_diff = PEAK - c0.dat[1];
    const unsigned short int b_diff = PEAK - c0.dat[2];

    /*  If a channel will overflow, set the channel to 65535 (max value).     *
     *  Otherwise compute the sum as normal. The "& PEAK" at the end is       *
     *  simply to avoid compiler warnings about conversions to int. As a      *
     *  reminder about ternary syntax, x = (a <= b ? c : d) sets x to "c" if  *
     *  "a <= b" is true, and "d" otherwise.                                  */
    sum.dat[0] = (r_diff <= c1.dat[0] ? PEAK : (c0.dat[0] + c1.dat[0]) & PEAK);
    sum.dat[1] = (g_diff <= c1.dat[1] ? PEAK : (c0.dat[1] + c1.dat[1]) & PEAK);
    sum.dat[2] = (b_diff <= c1.dat[2] ? PEAK : (c0.dat[2] + c1.dat[2]) & PEAK);

    return sum;
}
/*  End of tmpl_RGB48_Add.                                                    */

/*  Undefine everything in case someone wants to #include this file.          */
#undef PEAK
