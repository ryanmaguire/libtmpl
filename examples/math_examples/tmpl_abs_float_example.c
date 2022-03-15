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
 *      Provides an example of using tmpl_Float_Abs function.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 15, 2022                                                *
 ******************************************************************************/

/*  printf is here.                                                           */
#include <stdio.h>

/*  FLT_MAX is found here.                                                    */
#include <float.h>

/*  tmpl_Float_Abs function found here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  Function for showing use of tmpl_Float_Abs function.                      */
int main(void)
{
    /*  Array for a few test values.                                          */
    float x[11];

    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Variable for the output.                                              */
    float out;

    /*  Set the values of the array.                                          */
    x[0] = 0.0F;
    x[1] = -TMPL_INFINITYF;
    x[2] = TMPL_INFINITYF;
    x[3] = FLT_MAX;
    x[4] = -FLT_MAX;
    x[5] = FLT_MIN;
    x[6] = -FLT_MIN;
    x[7] = TMPL_NANF;
    x[8] = -TMPL_NANF;
    x[9] = 3.1415926F;
    x[10] = -1.414F;

    /*  Run tmpl_Float_Abs on the test values.                                */
    for (n = 0U; n < sizeof(x)/sizeof(x[0]); ++n)
    {
        out = tmpl_Float_Abs(x[n]);
        printf("|%.8e| = %.8e\n", (double)x[n], (double)out);
    }

    return 0;
}
/*  End of main.                                                              */
