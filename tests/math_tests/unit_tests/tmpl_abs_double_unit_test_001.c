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

/*  tmpl_Double_Abs function found here.                                      */
#include <libtmpl/include/tmpl_math.h>

/*  Function for checking the validity of the absolute value function.        */
int main(void)
{
    /*  Two arrays for inputs and outputs.                                    */
    double in[10];
    double out[10];

    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  And a variable for storing the output of tmpl_Double_Abs.             */
    double output;

    /*  The test values for the input.                                        */
    in[0] = 0.0;
    in[1] = -0.0;
    in[2] = DBL_MIN;
    in[3] = -DBL_MIN;
    in[4] = DBL_MAX;
    in[5] = -DBL_MAX;
    in[6] = TMPL_INFINITY;
    in[7] = -TMPL_INFINITY;
    in[8] = TMPL_NAN;
    in[9] = -TMPL_NAN;

    /*  The values that tmpl_Double_Abs should return.                        */
    out[0] = 0.0;
    out[1] = 0.0;
    out[2] = DBL_MIN;
    out[3] = DBL_MIN;
    out[4] = DBL_MAX;
    out[5] = DBL_MAX;
    out[6] = TMPL_INFINITY;
    out[7] = TMPL_INFINITY;
    out[8] = TMPL_NAN;
    out[9] = TMPL_NAN;

    /*  Loop over the input array and test the tmpl_Double_Abs function.      */
    for (n = 0U; n < sizeof(in)/sizeof(in[0]); ++n)
    {
        /*  Compute tmpl_Double_Abs(in[n]) and compare with the out array.    */
        output = tmpl_Double_Abs(in[n]);

        /*  If the values aren't exactly identical, abort and print "FAIL".   *
         *  The exception is "NAN", which always evaluates false when         *
         *  compared with anything (including another NAN).                   */
        if (tmpl_Double_Is_NaN(output))
        {
            if (!tmpl_Double_Is_NaN(out[n]))
            {
                puts("FAIL");
                return -1;
            }
        }

        /*  For non-NaN's we can just compare the values.                     */
        else if (output != out[n])
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
