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
#include <libtmpl/include/tmpl_math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>

static double rand_real(void)
{
    int n = rand();
    return ((double)n / (double)RAND_MAX);
}

static void minmax(double *arr, unsigned int size)
{
    double min = TMPL_INFINITY;
    double max = -TMPL_INFINITY;
    unsigned int n;

    for (n = 0U; n < size; ++n)
    {
        if (max < arr[n])
            max = arr[n];
        if (min > arr[n])
            min = arr[n];
    }

    printf("min(x): %e\nmax(x): %e\n", min, max);
}

int main(void)
{
    double *x, *y0, *y1;
    int *n0, *n1;
    const unsigned int N = 10000000U;
    unsigned int n;
    clock_t t1, t2;
    double mant_rms_rel = 0.0;
    double mant_rms_abs = 0.0;
    double mant_max_rel = 0.0;
    double mant_max_abs = 0.0;
    double expo_rms_rel = 0.0;
    double expo_rms_abs = 0.0;
    double expo_max_rel = 0.0;
    double expo_max_abs = 0.0;
    double tmp;
    int n_tmp;

    x = malloc(sizeof(*x) * N);
    y0 = malloc(sizeof(*y0) * N);
    y1 = malloc(sizeof(*y1) * N);
    n0 = malloc(sizeof(*n0) * N);
    n1 = malloc(sizeof(*n1) * N);

    for (n = 0U; n < N; ++n)
        x[n] = rand_real();

    t1 = clock();
    for (n = 0U; n < N; ++n)
        tmpl_Double_Base2_Mant_and_Exp(x[n], &y0[n], &n0[n]);
    t2 = clock();
    printf("libtmpl: %f\n", (double)(t2 - t1)/CLOCKS_PER_SEC);


    t1 = clock();
    for (n = 0U; n < N; ++n)
    {
        y1[n] = 2.0*frexp(x[n], &n1[n]);
        n1[n] -= 1;
    }
    t2 = clock();
    printf("C:       %f\n", (double)(t2 - t1)/CLOCKS_PER_SEC);

    for (n = 0U; n < N; ++n)
    {
        tmp = fabs(y0[n] - y1[n]);
        mant_rms_abs += tmp*tmp;

        if (mant_max_abs < tmp)
            mant_max_abs = tmp;

        tmp = fabs((y0[n] - y1[n])/y1[n]);
        mant_rms_rel += tmp*tmp;

        if (mant_max_rel < tmp)
            mant_max_rel = tmp;

        n_tmp = abs(n0[n] - n1[n]);
        tmp = (double)n_tmp;
        expo_rms_abs += tmp*tmp;

        if (expo_max_abs < tmp)
            expo_max_abs = tmp;

        n_tmp = abs(n1[n]);
        tmp = tmp / (double)n_tmp;
        expo_rms_rel += tmp*tmp;

        if (expo_max_rel < tmp)
            expo_max_rel = tmp;

    }

    mant_rms_abs = sqrt(mant_rms_abs / (double)N);
    mant_rms_rel = sqrt(mant_rms_rel / (double)N);
    expo_rms_abs = sqrt(expo_rms_abs / (double)N);
    expo_rms_rel = sqrt(expo_rms_rel / (double)N);

    printf("mant max abs err: %e\n", mant_max_abs);
    printf("mant max rel err: %e\n", mant_max_rel);
    printf("mant rms abs err: %e\n", mant_rms_abs);
    printf("mant rms rel err: %e\n", mant_rms_rel);
    printf("expo max abs err: %e\n", expo_max_abs);
    printf("expo max rel err: %e\n", expo_max_rel);
    printf("expo rms abs err: %e\n", expo_rms_abs);
    printf("expo rms rel err: %e\n", expo_rms_rel);

    minmax(x, N);

    free(x);
    free(y0);
    free(y1);
    free(n0);
    free(n1);
    return 0;
}
