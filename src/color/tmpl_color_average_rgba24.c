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
 *                          tmpl_color_average_rgb24                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Adds to colors by averaging over the individual color channels.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RGB24_Average                                                    *
 *  Purpose:                                                                  *
 *      Adds two colors together by summing the color channels.               *
 *  Arguments:                                                                *
 *      c0 (tmpl_RGB24):                                                      *
 *          A color.                                                          *
 *      c1 (tmpl_RGB24):                                                      *
 *          Another color.                                                    *
 *  Output:                                                                   *
 *      sum (tmpl_RGB24):                                                     *
 *          The color sum of c0 and c1.                                       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Carefully sum the individual channels by checking that the result     *
 *      will not overflow, storing the max value of 255 if it does.           *
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

#include <libtmpl/include/tmpl_math.h>

#define PEAK (0xFFU)

/*  Function for adding together two colors in 24-bit RGB format.             */
tmpl_RGBA24 tmpl_RGBA24_Average(tmpl_RGBA24 c0, tmpl_RGBA24 c1)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_RGBA24 sum;

    /*  Average over the alpha channels.                                      */
    const double alpha = 0.5 * (c0.alpha + c1.alpha);

    /*  Unsigned short is required to be at least 16 bits wide, which is      *
     *  large enough to fit 8-bit arithmetic and avoid overflow. Cast the     *
     *  color channels to safely average them.                                */
    unsigned short int r = (unsigned short int)c0.dat[0];
    unsigned short int g = (unsigned short int)c0.dat[1];
    unsigned short int b = (unsigned short int)c0.dat[2];

    /*  We can safely add the channels from the other color without overflow. */
    r += (unsigned short int)c1.dat[0];
    g += (unsigned short int)c1.dat[1];
    b += (unsigned short int)c1.dat[2];

    /*  Lastly, divide the channels by two to get the average.                */
    r >>= 1U;
    g >>= 1U;
    b >>= 1U;

    /*  If the value is larger than the max allowed for 8-bit integers, clip  *
     *  the average.                                                          */
    sum.dat[0] = (r > PEAK ? PEAK : (unsigned char)r);
    sum.dat[1] = (g > PEAK ? PEAK : (unsigned char)g);
    sum.dat[2] = (b > PEAK ? PEAK : (unsigned char)b);

    /*  Clip the alpha parameter as well.                                     */
    sum.alpha = tmpl_Double_Unit_Clamp(alpha);

    return sum;
}
/*  End of tmpl_RGB24_Average.                                                */

/*  Undefine everything in case someone wants to #include this file.          */
#undef PEAK
