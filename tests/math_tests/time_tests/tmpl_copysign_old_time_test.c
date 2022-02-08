/******************************************************************************
 *                                 LICENSE                                    *
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
 *      Provide tests for the accuracy and efficiency of libtmpl              *
 *      copysign function compared to the C99 version.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 11, 2020                                             *
 ******************************************************************************/

/*  The copysign functions are found here.                                    */
#include <libtmpl/include/tmpl_math.h>
#include <math.h>

/*  Library for timing computations.                                          */
#include <time.h>

/*  Needed for printing the outputs.                                          */
#include <stdio.h>

/*  Needed for malloc.                                                        */
#include <stdlib.h>

int main(void)
{
    /*  Declare necessary variables.                                          */
    double temp, x, y;
    unsigned long int m, n;
    clock_t t1, t2;

    /*  We'll do our time test with a square of 1000x1000 points.             */
    const unsigned long int N = 1000L;

    /*  We'll have the variables range from -10 to 10.                        */
    const double start = -10.0;
    const double end = 10.0;

    /*  And we'll increment evenly throughout the region.                     */
    const double dx = (end - start) / (double)N;
    const double dy = dx;

    /*  Set the initial value for max_err to zero.                            */
    double max_err = 0.0;

    /*  Allocate memory for the two pointers we've declared.                  */
    double *z0 = malloc(sizeof(*z0) * N * N);
    double *z1 = malloc(sizeof(*z1) * N * N);


    /*  Set x and y to the starting value and grab the current time.          */
    x = start;
    y = start;
    t1 = clock();

    /*  Perform the calculation with the C99 library function copysign.       */
    for (m=0; m<N; ++m)
    {
        for (n=0; n<N; ++n)
        {
            z0[m + N*n] = copysign(x, y);
            y += dy;
        }
        /*  End of y for-loop.                                                */
        x += dx;
    }
    /*  End of x for-loop.                                                    */

    /*  Grab the current clock time again.                                    */
    t2 = clock();

    /*  t2-t1 is the number of clock cycles that have passed between grabbing *
     *  t1 and t2. To convert this to second, use the macro CLOCKS_PER_SEC    *
     *  provided in time.h.                                                   */
    printf("C99:     %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    /*  Restart the computation for the libtmpl function.                     */
    x = start;
    y = start;

    /*  Reset the clock.                                                      */
    t1 = clock();

    /*  Perform the computation using tmpl_Double_Copysign.                   */
    for (m=0; m<N; ++m)
    {
        for (n=0; n<N; ++n)
        {
            z1[m + N*n] = tmpl_Double_Copysign(x, y);
            y += dy;
        }
        x += dx;
    }

    /*  Grab the time again.                                                  */
    t2 = clock();

    /*  Print out how long it took for libtmpl to compute.                    */
    printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    /*  NOTE:                                                                 *
     *      Without the following comparison of the two pointers y0 and y1,   *
     *      some compilers may see the above computations as redundant with   *
     *      optimization on, and skip them. The resulting times will be close *
     *      to zero for both fabs and tmpl_Double_Abs.                        */

    /*  Compute the maximum absolute error between libtmpl and C99.           */
    for (m=0; m<N; ++m)
    {
        for (n=0; n<N; ++n)
        {
            /*  We'll use the standard library function to check the error.   */
            temp = fabs(z0[m + N*n] - z1[m + N*n]);

            /*  Check if the error got larger and set max_err accordingly.    */
            if (max_err < temp)
                max_err = temp;
        }
    }
    /*  End of for loop computing |y0-y1|.                                    */

    /*  Print out the error to 16 decimals (assumes 64-bit precision).        */
    printf("max error: %.16f\n", max_err);

    /*  Free the pointers we've malloc'd.                                     */
    free(z0);
    free(z1);
    return 0;
}
/*  End of main.                                                              */
