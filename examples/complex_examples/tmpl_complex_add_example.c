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
 *          gcc tmpl_complex_add_example.c -o test -ltmpl                     *
 *                                                                            *
 *      If libtmpl is not in /usr/local/lib/ (this is the default location it *
 *      is placed in when built via make.sh), change the -L option to the     *
 *      correct location. If /usr/local/include/ is not in your path, add the *
 *      -I option as follows:                                                 *
 *                                                                            *
 *          gcc -I/usr/local/include/ -L/usr/local/lib/                       *
 *              tmpl_complex_add_example.c -o test -ltmpl                     *
 *                                                                            *
 *      Note, this should all be one line. This outputs an executable "test". *
 *      Running the executable with ./test, this outputs:                     *
 *          (0.0000 + i0.0000) + (1.0000 + i1.0000) = 1.0000 + i1.0000        *
 *          (1.0000 + i0.0000) + (2.0000 + i0.0000) = 3.0000 + i0.0000        *
 *          (1.0000 + i1.0000) + (1.0000 + i3.0000) = 2.0000 + i4.0000        *
 *          (-nan + i0.0000) + (1.0000 + i4.0000) = -nan + i4.0000            *
 *          (inf + i0.0000) + (1.0000 + i0.0000) = inf + i0.0000              *
 *          (nan + inan) + (1.0000 + i8.0000) = nan + inan                    *
 *          (inf + iinf) + (1.0000 + i1.0000) = inf + iinf                    *
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
    tmpl_ComplexDouble z0[7], z1[7], w[7];
    double re_z0, im_z0, re_z1, im_z1, re_w, im_w;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z0.                                  */
    z0[0] = tmpl_CDouble_Zero;
    z0[1] = tmpl_CDouble_One;
    z0[2] = tmpl_CDouble_Rect(1.0, 1.0);
    z0[3] = tmpl_CDouble_Rect(TMPL_NAN, 0.0);
    z0[4] = tmpl_CDouble_Rect(TMPL_INFINITY, 0.0);
    z0[5] = tmpl_Complex_NaN;
    z0[6] = tmpl_Complex_Infinity;

    /*  Set the test values for the array z1.                                 */
    z1[0] = tmpl_CDouble_Rect(1.0, 1.0);
    z1[1] = tmpl_CDouble_Rect(2.0, 0.0);
    z1[2] = tmpl_CDouble_Rect(1.0, 3.0);
    z1[3] = tmpl_CDouble_Rect(1.0, 4.0);
    z1[4] = tmpl_CDouble_Rect(1.0, 0.0);
    z1[5] = tmpl_CDouble_Rect(1.0, 8.0);
    z1[6] = tmpl_CDouble_Rect(1.0, 1.0);

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 7U; ++n)
    {
        /*  Compute z0 + z1 of the nth value.                                 */
        w[n] = tmpl_CDouble_Add(z0[n], z1[n]);

        /*  Extract the real and imaginary parts from z0[n].                  */
        re_z0 = tmpl_CDouble_Real_Part(z0[n]);
        im_z0 = tmpl_CDouble_Imag_Part(z0[n]);

        /*  Extract the real and imaginary parts from z1[n].                  */
        re_z1 = tmpl_CDouble_Real_Part(z1[n]);
        im_z1 = tmpl_CDouble_Imag_Part(z1[n]);

        /*  Extract the real and imaginary parts from w[n].                   */
        re_w = tmpl_CDouble_Real_Part(w[n]);
        im_w = tmpl_CDouble_Imag_Part(w[n]);

        /*  And finally, print the result to the screen.                      */
        printf("(%.4f + i%.4f) + (%.4f + i%.4f) = %.4f + i%.4f\n",
               re_z0, im_z0, re_z1, im_z1, re_w, im_w);
    }
    /*  End of for loop z0 + z1.                                              */

    return 0;
}
/*  End of main.                                                              */
