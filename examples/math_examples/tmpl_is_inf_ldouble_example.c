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

/*  LDBL_MAX is found here.                                                   */
#include <float.h>

/*  Booleans are here.                                                        */
#include <libtmpl/include/tmpl_bool.h>

/*  is_inf function found here.                                               */
#include <libtmpl/include/tmpl_math.h>

/*  Function for showing use of is_inf function.                              */
int main(void)
{
    /*  Array for a few test values.                                          */
    long double x[11];

    /*  Variable for indexing.                                                */
    unsigned int n;

    /*  Boolean for the output of the function.                               */
    tmpl_Bool is_inf;

    /*  Set the values of the array.                                          */
    x[0] = 0.0L;
    x[1] = -TMPL_INFINITYL;
    x[2] = TMPL_INFINITYL;
    x[3] = LDBL_MAX;
    x[4] = -LDBL_MAX;
    x[5] = LDBL_MIN;
    x[6] = -LDBL_MIN;
    x[7] = TMPL_NANL;
    x[8] = -TMPL_NANL;
    x[9] = 3.1415926L;
    x[10] = -1.414L;

    /*  Run is_inf on the test values.                                        */
    for (n = 0U; n < 11U; ++n)
    {
        is_inf = tmpl_LDouble_Is_Inf(x[n]);

        if (is_inf)
            printf("is_inf(%.8Le) = True\n", x[n]);
        else
            printf("is_inf(%.8Le) = False\n", x[n]);
    }
}
/*  End of main.                                                              */
