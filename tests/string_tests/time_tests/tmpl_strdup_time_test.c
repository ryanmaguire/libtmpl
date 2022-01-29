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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 12, 2021                                               *
 ******************************************************************************/

/*  printf is here.                                                           */
#include <stdio.h>

/*  clock_t data type and clock() function found here.                        */
#include <time.h>

/*  strdup found here.                                                        */
#include <string.h>

/*  malloc and free are here.                                                 */
#include <stdlib.h>

/*  tmpl_strdup is here.                                                      */
#include <libtmpl/include/tmpl_string.h>

/*  Function for comparing tmpl_strdup and strdup for speed.                  */
int main(void)
{
    /*  Two char pointers for running the test.                               */
    char *test1, *test2;

    /*  Variable for saving the results of the rand function.                 */
    int random;

    /*  Variable for indexing.                                                */
    unsigned long int n;

    /*  Number of elements in the str array. 3*10^8 bytes should fit fine     *
     *  with 2GB of RAM, taking up 15% of the total memory. Modern computers  *
     *  with 4GB or more will have no trouble running this test.              */
    unsigned long int N = 1E8;

    /*  Variables for computing clock time later.                             */
    clock_t t1, t2;
    double time1, time2;

    /*  Allocate memory for the test pointer.                                 */
    char *str = malloc(N+1UL);

    /*  Check if malloc failed.                                               */
    if (!str)
    {
        puts("malloc failed and returned NULL. Aborting.");
        return -1;
    }

    /*  Compute a bunch of random char's for the str array.                   */
    for (n = 0; n < N; ++n)
    {
        random = rand() % 255;

        /*  Ignore NULL terminators.                                          */
        while (random == '\0')
        {
            random = rand() % 255;
        }

        str[n] = (char)random;
    }

    /*  Add the NULL terminator.                                              */
    str[N] = '\0';

    /*  Run a speed test with tmpl_strdup.                                    */
    t1 = clock();
    test1 = tmpl_strdup(str);

    /*  Check if malloc failed and returned NULL.                             */
    if (!test1)
    {
        puts("malloc failed and returned NULL. Aborting.");
        free(str);
        return -1;
    }

    t2 = clock();
    time1 = (double)(t2-t1)/CLOCKS_PER_SEC;

    /*  Run a speed test with tmpl_Lower_Case.                                */
    t1 = clock();
    test2 = strdup(str);

    /*  Check if malloc failed and returned NULL.                             */
    if (!test2)
    {
        puts("malloc failed and returned NULL. Aborting.");
        free(str);
        free(test1);
        return -1;
    }

    t2 = clock();
    time2 = (double)(t2-t1)/CLOCKS_PER_SEC;

    printf("tmpl_strdup: %f\n", time1);
    printf("strdup:      %f\n", time2);

    /*  The results should all be the same. Check that this is true.          */
    for (n = 0U; n <= N; ++n)
    {
        if (test1[n] != str[n])
        {
            puts("FAILED");

            /*  Free everything.                                              */
            free(str);
            free(test1);
            free(test2);
            return -1;
        }
    }

    /*  If we get here, all tests passed. Free all pointers and return.       */
    puts("PASSED");
    free(str);
    free(test1);
    free(test2);
    return 0;
}
/*  End of main.                                                              */

