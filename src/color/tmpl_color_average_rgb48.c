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

#include <libtmpl/include/tmpl_limits.h>

#define PEAK (0xFFFFU)

/*  Function for adding together two colors in 24-bit RGB format.             */
tmpl_RGB48 tmpl_RGB48_Average(tmpl_RGB48 c0, tmpl_RGB48 c1)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_RGB48 sum;

    /*  Unsigned long is required to be at least 32 bits. On many systems it  *
     *  is 64-bits, and int is 32-bits (though int is only required to be     *
     *  at least 16-bits). Because of this it may be more efficient to use    *
     *  "int" to perform the computation. If int is not big enough, use long. *
     *  To avoid overflow with 16-bit integer arithmetic, int needs to be     *
     *  at least 17-bits wide. Check for this.                                */
#if TMPL_UINT_BIT >= 17
    unsigned int r = (unsigned int)c0.dat[0];
    unsigned int g = (unsigned int)c0.dat[1];
    unsigned int b = (unsigned int)c0.dat[2];

    /*  We can safely add the channels from the other color without overflow. */
    r += (unsigned int)c1.dat[0];
    g += (unsigned int)c1.dat[1];
    b += (unsigned int)c1.dat[2];

#else
/*  Else for #if TMPL_UINT_BIT >= 17.                                         */

    /*  If int is not large enough, long int is required to be at least 32    *
     *  bits wide. This is more than enough to safely compute with.           */
    unsigned long int r = (unsigned long int)c0.dat[0];
    unsigned long int g = (unsigned long int)c0.dat[1];
    unsigned long int b = (unsigned long int)c0.dat[2];

    /*  We can safely add the channels from the other color without overflow. */
    r += (unsigned long int)c1.dat[0];
    g += (unsigned long int)c1.dat[1];
    b += (unsigned long int)c1.dat[2];

#endif
/*  End of #if TMPL_UINT_BIT >= 17.                                           */

    /*  Lastly, divide the channels by two to get the average.                */
    r >>= 1U;
    g >>= 1U;
    b >>= 1U;

    /*  If the value is larger than the max allowed for 8-bit integers, clip  *
     *  the average.                                                          */
    sum.dat[0] = (r > PEAK ? PEAK : (unsigned char)r);
    sum.dat[1] = (g > PEAK ? PEAK : (unsigned char)g);
    sum.dat[2] = (b > PEAK ? PEAK : (unsigned char)b);

    return sum;
}
/*  End of tmpl_RGB48_Average.                                                */

/*  Undefine everything in case someone wants to #include this file.          */
#undef PEAK
