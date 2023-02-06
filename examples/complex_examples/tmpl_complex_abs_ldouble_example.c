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
 *      Provides an example of using the complex absolute value function.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 03, 2021                                                 *
 ******************************************************************************/

/*  Complex functions defined here.                                           */
#include <libtmpl/include/tmpl_complex.h>

/*  Real nan and inf found here.                                              */
#include <libtmpl/include/tmpl_math.h>

/*  We'll use stdio to print the results.                                     */
#include <stdio.h>

/*  Routine for computing |z| for a few test values.                          */
int main(void)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble z[7];
    long double w[7];
    long double re_z, im_z;

    /*  And declare a variable for indexing.                                  */
    unsigned int n;

    /*  Set the test values in the array z.                                   */
    z[0] = tmpl_CLDouble_Zero;
    z[1] = tmpl_CLDouble_One;
    z[2] = tmpl_CLDouble_Rect(1.0L, 1.0L);
    z[3] = tmpl_CLDouble_Rect(TMPL_NANL, 0.0L);
    z[4] = tmpl_CLDouble_Rect(TMPL_INFINITYL, 0.0L);
    z[5] = TMPL_CNANL;
    z[6] = TMPL_CINFINITYL;

    /*  Loop over the results and print them.                                 */
    for (n = 0U; n < 7U; ++n)
    {
        /*  Compute |z| of the nth value.                                     */
        w[n] = tmpl_CLDouble_Abs(z[n]);

        /*  Extract the real and imaginary parts from z[n].                   */
        re_z = tmpl_CLDouble_Real_Part(z[n]);
        im_z = tmpl_CLDouble_Imag_Part(z[n]);

        /*  And finally, print the result to the screen.                      */
        printf("|%Lf + i%Lf| = %Lf\n", re_z, im_z, w[n]);
    }
    /*  End of for loop computing |z|.                                        */

    return 0;
}
/*  End of main.                                                              */

