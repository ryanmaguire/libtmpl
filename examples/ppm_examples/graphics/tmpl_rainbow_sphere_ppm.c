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
 *  Purpose:                                                                  *
 *      Draw a circle with a rainbow gradient.                                *
 ******************************************************************************/

/*  tmpl_Binary_PPM_From_Data function found here.                            */
#include <libtmpl/include/tmpl_ppm.h>

/*  tmpl_Double_Sqrt found here.                                              */
#include <libtmpl/include/tmpl_math.h>

/*  malloc and free are found here.                                           */
#include <stdlib.h>

/*  The puts function is found here.                                          */
#include <stdio.h>

/*  UCHAR_MAX found here.                                                     */
#include <limits.h>

/*  Function for drawing a circle with a rainbow gradient.                    */
int main(void)
{
    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  The number of pixels in the x axis.                                   */
    const unsigned int width = 1024U;

    /*  The number of pixels in the y axis.                                   */
    const unsigned int height = 1024U;

    /*  The x coordinate of the center of the circle.                         */
    const double midx = 0.5*width;

    /*  The y coordinate of the center of the circle.                         */
    const double midy = 0.5*height;

    /*  Allocate memory for the PPM's data.                                   */
    tmpl_PPM_Color *data = malloc(sizeof(*data) * width * height);

    /*  Malloc returns NULL on failure. Check for this.                       */
    if (data == NULL)
    {
        puts("malloc failed and returned NULL. Aborting.");
        return -1;
    }

    /*  If OpenMP is being used we can get significant boosts in performance  *
     *  by using parallel processing.                                         */
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n = 0U; n < width*height; ++n)
    {
        /*  Compute the x and y coordinates of the current pixel.             */
        double y = (double)(n/width);
        double x = (double)n - y*width;

        /*  Compute the distance of this point to the center of the circle.   */
        double dx = (x - midx)/midx;
        double dy = (y - midy)/midy;
        double dist = tmpl_Double_Sqrt(dx*dx + dy*dy);

        /*  Points outside of the circle are white.                           */
        if (dist > 1.0)
            data[n] = tmpl_PPM_White;

        /*  Points inside the circle are given a radinbow gradient            *
         *  based on the distance of the point to the center of the circle.   */
        else
            data[n] = tmpl_PPM_Linear_Gradient(dist, 0.0, 1.0);
    }
    /*  End of for-loop for n.                                                */

    /*  Create the PPM from the data.                                         */
    tmpl_Binary_PPM_From_Data("tmpl_rainbow_sphere.ppm", data, width, height);

    /*  Free the data and return.                                             */
    free(data);
    return 0;
}
/*  End of main.                                                              */
