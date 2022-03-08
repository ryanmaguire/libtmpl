/******************************************************************************
 *                                 LICENSE                                    *
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
 *  Author:     Ryan Maguire,                                                 *
 *  Date:       March 8, 2021                                                 *
 ******************************************************************************/

/*  Disable silly warnings for Windows users about using standard library     *
 *  functions such as fopen.                                                  */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

/*  Math tools found here.                                                    */
#include <libtmpl/include/tmpl_math.h>

/*  PPM tools found here.                                                     */
#include <libtmpl/include/tmpl_ppm.h>

/*  The FILE data type is here.                                               */
#include <stdio.h>

/*  Function for creating a PPM file with a grayscale gradient.               */
int main(void)
{
    /*  We'll create a 1024x1024 picture. Save this in the variable "size".   */
    const unsigned int size = 1024U;

    /*  Struct for the color white.                                           */
    const tmpl_PPM_Color white = {0xFFU, 0xFFU, 0xFFU};

    /*  Factor for scaling the color white. The color of a given pixel is     *
     *  given by the Euclidean distance to the center of the image, computed  *
     *  using the Pythagorean formula. This factor ensures the maximum value  *
     *  possible for a given color is 255, which is the max value allowed for *
     *  RGB colors.                                                           */
    const double factor = 2.0 / (double)(size - 1U) / tmpl_Sqrt_Two;

    /*  Parameters for scaling.                                               */
    double t, u, v;

    /*  Color struct for the writing colors to the PPM file.                  */
    tmpl_PPM_Color color;

    /*  And declare two variables for indexing.                               */
    unsigned int x, y;

    /*  We'll write the output to a .ppm file. Open this with fopen.          */
    FILE *fp = fopen("tmpl_basic_ppm.ppm", "w");

    /*  fopen returns NULL on failure. Check that this didn't happen.         */
    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Windows seems to have better luck using text-based. This is much      *
     *  larger than binary format, so use binary for non-Windows users.       */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    fprintf(fp, "P3\n%u %u\n255\n", size, size);
#else
/*  Everyone else (GNU, Linux, FreeBSD, macOS, etc.)                          */
    fprintf(fp, "P6\n%u %u\n255\n", size, size);
#endif

    /*  Loop over all of the pixels.                                          */
    for (y = 0U; y < size; ++y)
    {
        /*  Compute the y-distance to the center of the image.                */
        v = 0.5*size - (double)y;
        for (x = 0U; x < size; ++x)
        {
            /*  Compute the x-distance to the center of the image.            */
            u = 0.5*size - (double)x;

            /*  The scale factor is given by the distance to the center of    *
             *  the image, given by the Pythagorean formula.                  */
            t = factor*tmpl_Double_Sqrt(u*u + v*v);

            /*  Scale the color white to give a black-to-white gradient.      */
            color = tmpl_PPM_Scale_Color(white, t);

            /*  Write the RGB value to the file.                              */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
            tmpl_PPM_Print_Color(fp, color);
#else
            tmpl_PPM_Write_Color(fp, color);
#endif
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */
