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
 *      Provides an example of using is_nan_or_inf function.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 3, 2022                                              *
 ******************************************************************************/

/*  printf is here.                                                           */
#include <stdio.h>

/*  DBL_MAX is found here.                                                    */
#include <float.h>

/*  Booleans are here.                                                        */
#include <libtmpl/include/tmpl_bool.h>

/*  is_nan_or_inf function found here.                                        */
#include <libtmpl/include/tmpl_math.h>

/*  Function for showing use of is_nan_or_inf function.                       */
int main(void)
{
    /*  Array for a few test values.                                          */
    double x[11];

    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Boolean for the output of the function.                               */
    tmpl_Bool is_nan_or_inf;

    /*  Set the values of the array.                                          */
    x[0] = 0.0;
    x[1] = -TMPL_INFINITY;
    x[2] = TMPL_INFINITY;
    x[3] = DBL_MAX;
    x[4] = -DBL_MAX;
    x[5] = DBL_MIN;
    x[6] = -DBL_MIN;
    x[7] = TMPL_NAN;
    x[8] = -TMPL_NAN;
    x[9] = 3.1415926;
    x[10] = -1.414;

    /*  Run is_nan_or_inf on the test values.                                 */
    for (n = 0U; n < 11U; ++n)
    {
        is_nan_or_inf = tmpl_Double_Is_NaN_Or_Inf(x[n]);

        if (is_nan_or_inf)
            printf("is_nan_or_inf(%.8e) = True\n", x[n]);
        else
            printf("is_nan_or_inf(%.8e) = False\n", x[n]);
    }
}
/*  End of main.                                                              */
