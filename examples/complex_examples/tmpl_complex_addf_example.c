/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *      Provides an example of using complex addition.                        *
 *      We can compile this with:                                             *
 *                                                                            *
 *          gcc tmpl_complex_addf_example.c -o test -ltmpl                    *
 *                                                                            *
 *      If libtmpl is not in /usr/local/lib/ (this is the default location it *
 *      is placed in when built via make.sh), change the -L option to the     *
 *      correct location. If /usr/local/include/ is not in your path, add the *
 *      -I option as follows:                                                 *
 *                                                                            *
 *          gcc -I/usr/local/include/ -L/usr/local/lib/                       *
 *              tmpl_complex_addf_example.c -o test -ltmpl                    *
 *                                                                            *
 *      Note, this should all be one line. This outputs an executable "test". *
 *      Running the executable with ./test, this outputs:                     *
 *      (0.000000 + i0.000000) + (1.000000 + i1.000000) = 1.000000 +i1.000000 *
 *      (1.000000 + i0.000000) + (2.000000 + i0.000000) = 3.000000 +i0.000000 *
 *      (1.000000 + i1.000000) + (1.000000 + i3.000000) = 2.000000 +i4.000000 *
 *      (nan + i0.000000) + (1.000000 + i4.000000) = nan +i4.000000           *
 *      (inf + i0.000000) + (1.000000 + i0.000000) = inf +i0.000000           *
 *      (nan + inan) + (1.000000 + i8.000000) = nan +inan                     *
 *      (inf + iinf) + (1.000000 + i1.000000) = inf +iinf                     *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       June 3, 2021                                                  *
 ******************************************************************************/

/*  Complex functions defined here.                                           */
#include <libtmpl/include/tmpl_complex.h>

/*  Real nan and inf found here.                                              */
#include <libtmpl/include/tmpl_math.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*  Routine for adding two complex numbers.                                   */
int main(void)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat z0[7], z1[7], w[7];
    float re_z0, im_z0, re_z1, im_z1, re_w, im_w;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z0.                                  */
    z0[0] = tmpl_CFloat_Zero;
    z0[1] = tmpl_CFloat_One;
    z0[2] = tmpl_CFloat_Rect(1.0F, 1.0F);
    z0[3] = tmpl_CFloat_Rect(tmpl_NaN_F, 0.0F);
    z0[4] = tmpl_CFloat_Rect(tmpl_Infinity_F, 0.0F);
    z0[5] = tmpl_CFloat_NaN;
    z0[6] = tmpl_CFloat_Infinity;

    /*  Set the test values for the array z1.                                 */
    z1[0] = tmpl_CFloat_Rect(1.0F, 1.0F);
    z1[1] = tmpl_CFloat_Rect(2.0F, 0.0F);
    z1[2] = tmpl_CFloat_Rect(1.0F, 3.0F);
    z1[3] = tmpl_CFloat_Rect(1.0F, 4.0F);
    z1[4] = tmpl_CFloat_Rect(1.0F, 0.0F);
    z1[5] = tmpl_CFloat_Rect(1.0F, 8.0F);
    z1[6] = tmpl_CFloat_Rect(1.0F, 1.0F);

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 7U; ++n)
    {
        /*  Compute z0 + z1 of the nth value.                                 */
        w[n] = tmpl_CFloat_Add(z0[n], z1[n]);

        /*  Extract the real and imaginary parts from z0[n].                  */
        re_z0 = tmpl_CFloat_Real_Part(z0[n]);
        im_z0 = tmpl_CFloat_Imag_Part(z0[n]);

        /*  Extract the real and imaginary parts from z1[n].                  */
        re_z1 = tmpl_CFloat_Real_Part(z1[n]);
        im_z1 = tmpl_CFloat_Imag_Part(z1[n]);

        /*  Extract the real and imaginary parts from w[n].                   */
        re_w = tmpl_CFloat_Real_Part(w[n]);
        im_w = tmpl_CFloat_Imag_Part(w[n]);

        /*  And finally, print the result to the screen.                      */
        printf("(%f + i%f) + (%f + i%f) = %f +i%f\n",
               (double)re_z0, (double)im_z0, (double)re_z1,
               (double)im_z1, (double)re_w, (double)im_w);
    }
    /*  End of for loop z0 + z1.                                              */

    return 0;
}
/*  End of main.                                                              */

