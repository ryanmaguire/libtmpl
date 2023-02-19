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
 *  Purpose:                                                                  *
 *      Provides an example of using complex addition.                        *
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

/*  Routine for adding a real number to a complex one.                        */
int main(void)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble z[7], w[7];
    double x[7], re_z, im_z, re_w, im_w;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z.                                   */
    z[0] = tmpl_CDouble_Zero;
    z[1] = tmpl_CDouble_One;
    z[2] = tmpl_CDouble_Rect(1.0, 1.0);
    z[3] = tmpl_CDouble_Rect(TMPL_NAN, 0.0);
    z[4] = tmpl_CDouble_Rect(TMPL_INFINITY, 0.0);
    z[5] = TMPL_CNAN;
    z[6] = TMPL_CINFINITY;

    /*  Set the test values for the array x.                                  */
    x[0] = TMPL_INFINITY;
    x[1] = TMPL_NAN;
    x[2] = -4.0;
    x[3] = 1.0;
    x[4] = 2.0;
    x[5] = 1.0;
    x[6] = -TMPL_INFINITY;

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 7U; ++n)
    {
        /*  Compute z + x of the nth value.                                   */
        w[n] = tmpl_CDouble_Add_Real(x[n], z[n]);

        /*  Extract the real and imaginary parts from z[n].                   */
        re_z = tmpl_CDouble_Real_Part(z[n]);
        im_z = tmpl_CDouble_Imag_Part(z[n]);

        /*  Extract the real and imaginary parts from w[n].                   */
        re_w = tmpl_CDouble_Real_Part(w[n]);
        im_w = tmpl_CDouble_Imag_Part(w[n]);

        /*  And finally, print the result to the screen.                      */
        printf("(%f + i%f) + %f = %f + i%f\n", re_z, im_z, x[n], re_w, im_w);
    }
    /*  End of for loop z + x.                                                */

    return 0;
}
/*  End of main.                                                              */
