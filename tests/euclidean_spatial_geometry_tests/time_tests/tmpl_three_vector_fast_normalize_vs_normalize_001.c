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
 ******************************************************************************/

#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

static double rand_real(void)
{
    int n = rand();
    return (double)n / (double)RAND_MAX;
}

int main(void)
{
    tmpl_ThreeVectorDouble *P, *U0, *U1;
    const unsigned int N = 10000000U;
    double rms_err = 0.0;
    double max_err = 0.0;
    double tmp = 0.0;
    double norm0, norm1;
    unsigned int n, bad;
    clock_t t1, t2;

    P = malloc(sizeof(*P) * N);

    if (!P)
    {
        puts("malloc failed and returned NULL for P. Aborting.");
        return -1;
    }

    U0 = malloc(sizeof(*P) * N);

    if (!U0)
    {
        puts("malloc failed and returned NULL for U0. Aborting.");
        free(P);
        return -1;
    }

    U1 = malloc(sizeof(*P) * N);

    if (!U1)
    {
        puts("malloc failed and returned NULL for U1. Aborting.");
        free(P);
        free(U0);
        return -1;
    }

    for (n = 0U; n < N; ++n)
    {
        double x = rand_real();
        double y = rand_real();
        double z = rand_real();
        P[n] = tmpl_3DDouble_Rect(x, y, z);
    }

    t1 = clock();
    for (n = 0U; n < N; ++n)
        U0[n] = tmpl_3DDouble_Normalize(&P[n]);
    t2 = clock();
    printf("Normalize:      %f\n", (double)(t2 - t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = 0U; n < N; ++n)
        U1[n] = tmpl_3DDouble_Fast_Normalize(&P[n]);
    t2 = clock();
    printf("Fast Normalize: %f\n", (double)(t2 - t1)/CLOCKS_PER_SEC);

    bad = 0u;
    for (n = 0U; n < N; ++n)
    {
        norm0 = tmpl_3DDouble_L2_Norm(&U0[n]);
        norm1 = tmpl_3DDouble_L2_Norm(&U1[n]);

        tmp = fabs(norm0 - norm1);
        rms_err += tmp*tmp;

        if (max_err < tmp)
        {
            max_err = tmp;
            bad = n;
        }
    }

    rms_err = sqrt(tmp / (double)N);
    printf("max err: %e\n", max_err);
    printf("rms err: %e\n", rms_err);
    printf("(%f, %f, %f)\n(%f, %f, %f)\n", U0[bad].dat[0], U0[bad].dat[1], U0[bad].dat[2], U1[bad].dat[0], U1[bad].dat[1], U1[bad].dat[2]);
    printf("%f\n%f\n", tmpl_3DDouble_L2_Norm(&U0[bad]), tmpl_3DDouble_L2_Norm(&U1[bad]));

    free(P);
    free(U0);
    free(U1);
    return 0;
}
