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
 *      Provides an example of using the single precision complex abs         *
 *      squared function.                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 24, 2021                                                  *
 ******************************************************************************/

/*  Complex functions defined here.                                           */
#include <libtmpl/include/tmpl_complex.h>

/*  Real nan and inf found here.                                              */
#include <libtmpl/include/tmpl_math.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*  Routine for computing |z|^2 for a few test values.                        */
int main(void)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat z[7];
    float w[7];
    float re_z, im_z;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z.                                   */
    z[0] = tmpl_CFloat_Zero;
    z[1] = tmpl_CFloat_One;
    z[2] = tmpl_CFloat_Rect(1.0F, 1.0F);
    z[3] = tmpl_CFloat_Rect(TMPL_NANF, 0.0F);
    z[4] = tmpl_CFloat_Rect(TMPL_INFINITYF, 0.0F);
    z[5] = tmpl_CFloat_NaN;
    z[6] = tmpl_CFloat_Infinity;

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 7U; ++n)
    {
        /*  Compute |z|^2 for the nth value.                                  */
        w[n] = tmpl_CFloat_Abs_Squared(z[n]);

        /*  Extract the real and imaginary parts from z[n].                   */
        re_z = tmpl_CFloat_Real_Part(z[n]);
        im_z = tmpl_CFloat_Imag_Part(z[n]);

        /*  And finally, print the result to the screen.                      */
        printf("|%f + i%f|^2 = %f\n", (double)re_z, (double)im_z, (double)w[n]);
    }
    /*  End of for loop computing |z|^2.                                      */

    return 0;
}
/*  End of main.                                                              */

