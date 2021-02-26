/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *      Provide functions for comparing the accuracy and efficiency of        *
 *      functions in libtmpl as opposed to other libraries.                   *
 *  NOTE:                                                                     *
 *      libtmpl does not have any dependencies and will compile on any        *
 *      compiler capable of handling C89/C90 or C99 compliant code. The tests *
 *      using these functions use external libraries to compare the results   *
 *      of tmpl with others. To run these tests requires having these         *
 *      libraries available. These tests are NOT required to use libtmpl      *
 *      and are mainly for internal use.                                      *
 *                                                                            *
 *      The code written for these tests is augmented from the code I wrote   *
 *      for rss_ringoccs. rss_ringoccs is released under the GPL3.            *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 26, 2020                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/12/29: Ryan Maguire                                                  *
 *      Created file (rss_ringoccs for Wellesley College).                    *
 *  2021/02/26: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Added comments and license.                                           *
 ******************************************************************************/

/*  Library for timing computations.                                          */
#include <time.h>

/*  Needed for printing the outputs.                                          */
#include <stdio.h>

/*  Needed for malloc.                                                        */
#include <stdlib.h>

/*  Needed for fabs, fabsf, and fabsl.                                        */
#include <math.h>

/*  Prototypes for these functions found here.                                */
#include "tmpl_compare_funcs.h"

/*  Routine for comparing two real valued functions at single precision.      */
void
tmpl_Compare_Float_1in1out(const char *ftmpl_name, float_1in1out ftmpl,
                           const char *fext_name,  float_1in1out fext,
                           const float start, const float end,
                           const unsigned long N, float eps, FILE *fp)
{
    /*  Declare variables for sampling the region [start, end].               */
    float *x, dx;

    /*  Declare variables for computing the maximum difference between the    *
     *  two provided functions fext and ftmpl.                                */
    float max_abs_err = 0.0F;
    float max_rel_err = 0.0F;
    float temp, worst_abs_point, worst_rel_point, worst_rel_ext, worst_rel_tmpl;

    /*  Declare two pointers to represent arrays for fext(x) and ftmpl(x).    */
    float *yext, *ytmpl;

    /*  Declare a dummy variable for indexing.                                */
    unsigned long n;

    /*  Declare variables for computing computation time.                     */
    clock_t t1, t2;

    fprintf(fp, "%s vs. %s\n", ftmpl_name, fext_name);

    /*  Error check to make sure the user provided valid inputs.              */
    if (start >= end)
    {
        puts("\nError Encountered: libtmpl\n"
             "\r\ttmpl_Compare_Float_1in1out\n\n"
             "start is greater than or equal to end.\n"
             "Aborting computation.\n");
        return;
    }
    else if (N == 0)
    {
        puts("\nError Encountered: libtmpl\n"
             "\r\ttmpl_Compare_Float_1in1out\n\n"
             "Input sample size is zero. Aborting computation.\n");
        return;
    }

    /*  We'll increment evenly throughout the region.                         */
    dx = (end - start) / (float)N;

    /*  Allocate memory for the array of test values.                         */
    x = malloc(sizeof(*x) * N);

    /*  Check that malloc didn't fail.                                        */
    if (x == NULL)
    {
        fprintf(fp,
                "\nError Encountered: libtmpl\n"
                "\r\ttmpl_Compare_Float_1in1out\n\n"
                "\rMalloc failed and returned NULL for x. Aborting.\n");
        return;
    }

    /*  Allocate memory for the libtmpl computation.                          */
    ytmpl = malloc(sizeof(*ytmpl) * N);

    /*  Check that malloc didn't fail, free'ing x if it did.                  */
    if (ytmpl == NULL)
    {
        fprintf(fp,
                "\nError Encountered: libtmpl\n"
                "\r\ttmpl_Compare_Float_1in1out\n\n"
                "\rMalloc failed and returned NULL for ytmpl. Aborting.\n");
        free(x);
        return;
    }

    /*  Allocate memory for the external library computation.                 */
    yext = malloc(sizeof(*yext) * N);

    /*  Check that malloc didn't fail, free'ing x and ytmpl if it did.        */
    if (yext == NULL)
    {
        fprintf(fp,
                "\nError Encountered: libtmpl\n"
                "\r\ttmpl_Compare_Float_1in1out\n\n"
                "\rMalloc failed and returned NULL for yext. Aborting.\n");
        free(x);
        free(ytmpl);
        return;
    }

    /*  Compute the x array, which consists of the values we're testing.      */
    x[0] = start;
    for (n = 1UL; n < N; ++n)
        x[n] = x[n-1UL] + dx;

    /*  Grab the current time.                                                */
    t1 = clock();

    /*  Perform the calculation for the f0 function.                          */
    for (n = 0UL; n < N; ++n)
        ytmpl[n] = ftmpl(x[n]);

    /*  Grab the current clock time again.                                    */
    t2 = clock();

    /*  t2-t1 is the number of clock cycles that have passed between grabbing *
     *  t1 and t2. To convert this to seconds, use the macro CLOCKS_PER_SEC   *
     *  provided in time.h.                                                   */
    fprintf(fp, "\t%s:\t%f\n", ftmpl_name, (double)(t2-t1)/CLOCKS_PER_SEC);

    /*  Reset the clock.                                                      */
    t1 = clock();

    /*  Perform the computation using fext instead of ftmpl.                  */
    for (n = 0UL; n < N; ++n)
        yext[n] = fext(x[n]);

    /*  Grab the time again.                                                  */
    t2 = clock();

    /*  Print out how long it took for fext to compute.                       */
    fprintf(fp, "\t%s:\t%f\n", fext_name, (double)(t2-t1)/CLOCKS_PER_SEC);

    /*  NOTE:                                                                 *
     *      Without the following comparison of the two pointers yext and     *
     *      ytmpl, some compilers may see the above computations as redundant *
     *      with optimization on, and skip them. The resulting times will be  *
     *      close to zero for both fext and ftmpl.                            */

    /*  Compute the maximum absolute error between fext and ftmpl.            */
    worst_abs_point = x[0];
    worst_rel_point = x[0];
    worst_rel_ext   = yext[0];
    worst_rel_tmpl  = ytmpl[0];
    for (n = 0UL; n < N; ++n)
    {
        /*  We'll use the standard library function to check the error.       */
        temp = fabsf(yext[n] - ytmpl[n]);

        /*  Check if the absolute error got bigger, and set max_abs_err.      */
        if (max_abs_err < temp)
        {
            max_abs_err = temp;
            worst_abs_point = x[n];
        }

        /*  Also check the relative error.                                    */
        temp = fabsf((yext[n] - ytmpl[n]) / yext[n]);

        /*  Check if the relative error got bigger, and set max_rel_err.      */
        if (max_rel_err < temp)
        {
            max_rel_err = temp;
            worst_rel_point = x[n];
            worst_rel_ext   = yext[n];
            worst_rel_tmpl  = ytmpl[n];
        }
    }
    /*  End of for-loop computing |yext-ytmpl|.                               */

    /*  Print out the error to 8 decimals (assumes 32-bit precision).         */
    fprintf(fp, "\tMax Abs Error:   %.8f\n", (double)max_abs_err);
    fprintf(fp, "\tWorst Abs Point: %.8f\n", (double)worst_abs_point);
    fprintf(fp, "\tMax Rel Error:   %.8f\n", (double)max_rel_err);
    fprintf(fp, "\tWorst Rel Point: %.8f\n", (double)worst_rel_point);
    fprintf(fp, "\t\t%s:\t\t%.16f\n", ftmpl_name, (double)worst_rel_tmpl);
    fprintf(fp, "\t\t%s:\t\t%.16f\n", fext_name,  (double)worst_rel_ext);

    if ((max_rel_err >= eps) && (max_abs_err >= eps))
        fprintf(fp, "FAILED\n\n");
    else
        fprintf(fp, "PASSED\n\n");

    /*  Free the pointers we've malloc'd.                                     */
    free(x);
    free(yext);
    free(ytmpl);
}
/*  End of tmpl_Compare_Float_1in1out.                                        */

