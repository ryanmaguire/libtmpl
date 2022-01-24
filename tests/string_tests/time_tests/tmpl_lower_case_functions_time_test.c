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
 ******************************************************************************/

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <libtmpl/include/tmpl_string.h>

int main(void)
{
    char *str, *test1, *test2, *test3;
    int random;
    unsigned long int n;
    unsigned long int N = 1E6;
    clock_t t1, t2;

    str = malloc(N);
    test1 = malloc(N);
    test2 = malloc(N);
    test3 = malloc(N);

    for (n = 0; n < N; ++n)
    {
        random = rand() % 255;
        str[n] = (char)random;
    }

    t1 = clock();
    for (n = 0; n < N; ++n)
        test1[n] = tmpl_ASCII_Lower_Case(str[n]);
    t2 = clock();
    printf("tmpl_ASCII_Lower_Case: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0; n < N; ++n)
        test2[n] = tmpl_Lower_Case(str[n]);
    t2 = clock();
    printf("tmpl_Lower_Case:       %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0; n < N; ++n)
        test3[n] = tolower(str[n]);
    t2 = clock();
    printf("tolower:               %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    for (n = 0U; n < N; ++n)
    {
        if ((test1[n] != test3[n]) || (test2[n] != test3[n]))
        {
            puts("FAILED");
            free(test1);
            free(test2);
            free(test3);
            return -1;
        }
    }

    puts("PASSED");
    free(test1);
    free(test2);
    free(test3);
    return 0;
}

