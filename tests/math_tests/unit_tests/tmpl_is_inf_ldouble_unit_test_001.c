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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 5, 2022                                             *
 ******************************************************************************/

/*  puts function found here.                                                 */
#include <stdio.h>

/*  DBL_MIN and DBL_MAX found here.                                           */
#include <float.h>

/*  tmpl_Bool defined here.                                                   */
#include <libtmpl/include/tmpl_bool.h>

/*  tmpl_LDouble_Is_Inf function found here.                                  */
#include <libtmpl/include/tmpl_math.h>

/*  Function for checking the validity of the isinf function.                 */
int main(void)
{
    /*  Two arrays for inputs and outputs.                                    */
    long double in[10];
    tmpl_Bool out[10];

    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  And a variable for storing the output of tmpl_LDouble_Is_Inf.         */
    tmpl_Bool output;

    /*  The test values for the input.                                        */
    in[0] = 0.0L;
    in[1] = -0.0L;
    in[2] = LDBL_MIN;
    in[3] = -LDBL_MIN;
    in[4] = LDBL_MAX;
    in[5] = -LDBL_MAX;
    in[6] = TMPL_INFINITYL;
    in[7] = -TMPL_INFINITYL;
    in[8] = TMPL_NANL;
    in[9] = -TMPL_NANL;

    /*  The values that tmpl_LDouble_Is_Inf should return.                    */
    out[0] = tmpl_False;
    out[1] = tmpl_False;
    out[2] = tmpl_False;
    out[3] = tmpl_False;
    out[4] = tmpl_False;
    out[5] = tmpl_False;
    out[6] = tmpl_True;
    out[7] = tmpl_True;
    out[8] = tmpl_False;
    out[9] = tmpl_False;

    /*  Loop over the input array and test the tmpl_LDouble_Is_Inf function.  */
    for (n = 0U; n < sizeof(in)/sizeof(in[0]); ++n)
    {
        /*  Compute tmpl_LDouble_Is_Inf(in[n]) and compare with the out array.*/
        output = tmpl_LDouble_Is_Inf(in[n]);

        /*  Check if the function works as expected.                          */
        if (output != out[n])
        {
            puts("FAIL");
            return -1;
        }
    }

    /*  All results are identical, print "PASS" and return.                   */
    puts("PASS");
    return 0;
}
/*  End of main.                                                              */
