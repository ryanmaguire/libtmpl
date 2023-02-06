/******************************************************************************
 *                                  LICENSE                                   *
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
 *      Provides an example of using the complex argument function.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 26, 2021                                                 *
 ******************************************************************************/

/*  Complex functions defined here.                                           */
#include <libtmpl/include/tmpl_complex.h>

/*  Real nan and inf found here.                                              */
#include <libtmpl/include/tmpl_math.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*  Routine for computing arg(z) for several test values.                     */
int main(void)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat z[9];
    float w[9], re_z, im_z;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z.                                   */
    z[0] = tmpl_CFloat_Zero;
    z[1] = tmpl_CFloat_One;
    z[2] = tmpl_CFloat_Rect(1.0F, 1.0F);
    z[3] = tmpl_CFloat_I;
    z[4] = tmpl_CFloat_Rect(-1.0F, 1.0F);
    z[5] = tmpl_CFloat_Rect(-1.0F, 0.0F);
    z[6] = tmpl_CFloat_Rect(-1.0F, -1.0F);
    z[7] = tmpl_CFloat_Rect(0.0F, -1.0F);
    z[8] = tmpl_CFloat_Rect(1.0F, -1.0F);

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 9U; ++n)
    {
        /*  Compute arg(z) of the nth value.                                  */
        w[n] = tmpl_CFloat_Argument(z[n]);

        /*  Extract the real and imaginary parts from z[n].                   */
        re_z = tmpl_CFloat_Real_Part(z[n]);
        im_z = tmpl_CFloat_Imag_Part(z[n]);

        /*  And finally, print the result to the screen.                      */
        printf("arg(%f + i%f) = %f\n",
               (double)re_z, (double)im_z, (double)w[n]);
    }
    /*  End of for loop computing arg(z).                                     */

    return 0;
}
/*  End of main.                                                              */
