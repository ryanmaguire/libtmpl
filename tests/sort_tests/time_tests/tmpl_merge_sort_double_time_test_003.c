/******************************************************************************
 *                                  LICENSE                                   *
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
#include <stdlib.h>
#include <libtmpl/include/tmpl_sort.h>
#include <gsl/gsl_sort_double.h>
#include <time.h>

static double rand_real(void)
{
    int n = rand();
    return (double)(n) / (double)(RAND_MAX);
}

int main(void)
{
    const size_t len = (size_t)(1E5);
    double *arrtmpl = (double *)(malloc(sizeof(*arrtmpl)*len));
    double *arrc = (double *)(malloc(sizeof(*arrc)*len));
    size_t n;
    clock_t t1, t2;

    for (n = 0; n < len; ++n)
    {
        double x = rand_real();
        arrtmpl[n] = x;
        arrc[n] = x;
    }

    printf("samples: %e\n", (double)(len));
    t1 = clock();
    tmpl_Double_Merge_Sort(arrtmpl, len);
    t2 = clock();
    printf("libtmpl: %f\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);

    t1 = clock();
    gsl_sort(arrc, 1, n);
    t2 = clock();
    printf("gsl:     %f\n", (double)(t2 - t1)/(double)CLOCKS_PER_SEC);

    free(arrc);
    free(arrtmpl);
    return 0;
}
