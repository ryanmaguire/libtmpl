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
 *      Provides an example of using is_inf function.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 8, 2021                                             *
 ******************************************************************************/

/*  printf is here.                                                           */
#include <stdio.h>

/*  FLT_MAX is found here.                                                    */
#include <float.h>

/*  Booleans are here.                                                        */
#include <libtmpl/include/tmpl_bool.h>

/*  is_inf function found here.                                               */
#include <libtmpl/include/tmpl_math.h>

/*  Function for showing use of is_inf function.                              */
int main(void)
{
    /*  Array for a few test values.                                          */
    float x[11];

    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Boolean for the output of the function.                               */
    tmpl_Bool is_inf;

    /*  Set the values of the array.                                          */
    x[0] = 0.0;
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

    /*  Run is_inf on the test values.                                        */
    for (n = 0U; n < 11U; ++n)
    {
        is_inf = tmpl_Float_Is_Inf(x[n]);

        if (is_inf)
            printf("is_inf(%.8e) = True\n", (double)x[n]);
        else
            printf("is_inf(%.8e) = False\n", (double)x[n]);
    }
}
/*  End of main.                                                              */
