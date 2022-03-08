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

/*  PPM tools found here.                                                     */
#include <libtmpl/include/tmpl_ppm.h>

/*  The FILE data type is here.                                               */
#include <stdio.h>

/*  Function for creating a PPM file with a color gradient.                   */
int main(void)
{
    /*  We'll create a 1024x1024 picture. Save this in the variable "size".   */
    const unsigned int size = 1024U;

    /*  The value 255 / (size-1) is used to compute the color gradient. 255   *
     *  is the maximum value allowed in the RGB format, so 255 / (size - 1)   *
     *  can be used to "normalize" the value.                                 */
    const double factor = 255.0 / (double)(size - 1U);

    /*  Variables for the colors being written to the PPM.                    */
    unsigned char red, green, blue;

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

    /*  The preamble of a PPM file is the following:                          *
     *      Pn                                                                *
     *      x_size y_size                                                     *
     *      max_color                                                         *
     *  Pn determines the type of file we're making. There are 6 types:       *
     *      P1: Black and White, text-based.                                  *
     *      P2: Gray-scale, text-based.                                       *
     *      P3: RGB, text-based.                                              *
     *      P4: Black and white, binary.                                      *
     *      P5: Grayscale, binary.                                            *
     *      P6: RGB, binary.                                                  *
     *  The text based options are more human-readable, but larger in file    *
     *  size. For this example we'll use RGB binary, which is P6.             */
    fprintf(fp, "P6\n%u %u\n255\n", size, size);

    /*  Loop over all of the pixels.                                          */
    for (y = 0U; y < size; ++y)
    {
        for (x = 0U; x < size; ++x)
        {
            /*  Compute the RGB value as a gradient based on the where the    *
             *  current pixel lies.                                           */
            red = (unsigned char)((double)x * factor);
            green = (unsigned char)((double)y * factor);
            blue = 64U;

            /*  Write the RGB value to the file.                              */
            tmpl_PPM_Write_Color_From_Values(fp, red, green, blue);
        }
        /*  End of x for-loop.                                                */
    }
    /*  End of y for-loop.                                                    */

    /*  Close the file and return.                                            */
    fclose(fp);
    return 0;
}
/*  End of main.                                                              */
