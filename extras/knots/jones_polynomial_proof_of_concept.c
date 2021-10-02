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
 *  Attempt of a proof of concept of computing the Jones' polynomial from     *
 *  the Gauss code of a knot.                                                 *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2021/09/30                                                        *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

enum crossing_sign {negative_crossing, positive_crossing};
enum crossing_type {under_crossing, over_crossing};

struct knot {
    unsigned int number_of_crossings;
    enum crossing_sign *sign;
    enum crossing_type *type;
    unsigned int *crossing_number;
};

struct laurent_polynomial {
    signed int lowest_degree;
    signed int highest_degree;
    signed int *coeffs;
};

struct CrossingIndices {
    unsigned long int under;
    unsigned long int over;
};

static struct CrossingIndices *
get_indices(struct knot *K)
{
    unsigned int n;
    struct CrossingIndices *ind;

    if (!K)
        return NULL;

    if (K->number_of_crossings == 0U)
        return NULL;

    ind = malloc(sizeof(*ind)*K->number_of_crossings);

    if (!ind)
        return NULL;

    for (n = 0U; n < 2U * K->number_of_crossings; ++n)
    {
        if (K->type[n] == over_crossing)
            ind[K->crossing_number[n]].over = n;
        else
             ind[K->crossing_number[n]].under = n;
    }

    return ind;
}

static unsigned int
number_of_circles_in_resolution(struct knot *K,
                                unsigned int resolution)
{
    unsigned int number_of_circles, crossing_resolution, n;
    struct CrossingIndices *ind;

    /*  The empty knot has zero circles.                                      */
    if (!K)
        return 0U;

    /*  The unknot has 1 circle.                                              */
    if (K->number_of_crossings == 0U)
        return 1U;

    ind = get_indices(K);

    if (!ind)
        return 0;

    number_of_circles = 0U;

    for (n = 0U; n < K->number_of_crossings; ++n)
    {
        crossing_resolution = resolution & 1U;
        number_of_circles += crossing_resolution;
        resolution >>= 1U;
    }

    free(ind);
    return number_of_circles;
}

static void
print_poly(struct laurent_polynomial P)
{
    signed int n, N;

    if (!P.coeffs)
    {
        puts("0");
        return;
    }

    N = P.highest_degree - P.lowest_degree + 1;

    printf("%dq^%d", P.coeffs[0], P.lowest_degree);

    for (n = 1; n < N; ++n)
    {
        if (P.coeffs[n] == 0)
            continue;
        else if (P.coeffs[n] == 1)
            printf(" + q^%d", P.lowest_degree + n);
        else if (P.coeffs[n] == -1)
            printf(" - q^%d", P.lowest_degree + n);
        else if (P.coeffs[n] > 1)
            printf(" + %dq^%d", P.coeffs[n], P.lowest_degree + n);
        else 
            printf(" - %dq^%d", -P.coeffs[n], P.lowest_degree + n);
    }

    printf("\n");
}

static void
poly_add(struct laurent_polynomial P,
         struct laurent_polynomial Q,
         struct laurent_polynomial *sum)
{
    unsigned int n, N, Pstart, Pend, Qstart, Qend;

    if (!sum)
        return;

    if (P.lowest_degree < Q.lowest_degree)
    {
        sum->lowest_degree = P.lowest_degree;
        Pstart = 0U;
        Qstart = (unsigned int)(Q.lowest_degree - P.lowest_degree);
    }
    else
    {
        sum->lowest_degree = Q.lowest_degree;
        Qstart = 0U;
        Pstart = (unsigned int)(P.lowest_degree - Q.lowest_degree);
    }

    if (P.highest_degree < Q.highest_degree)
    {
        sum->highest_degree = Q.highest_degree;
        Pend = (unsigned int)(P.highest_degree - sum->lowest_degree) + 1U;
        Qend = (unsigned int)(sum->highest_degree - sum->lowest_degree) + 1U;
    }
    else
    {
        sum->highest_degree = P.highest_degree;
        Qend = (unsigned int)(Q.highest_degree - sum->lowest_degree) + 1U;
        Pend = (unsigned int)(sum->highest_degree - sum->lowest_degree) + 1U;
    }

    if (!P.coeffs || !Q.coeffs)
        return;

    if (!sum->coeffs)
        free(sum->coeffs);

    N = (unsigned int)(sum->highest_degree - sum->lowest_degree) + 1U;
    sum->coeffs = calloc(sizeof(*sum->coeffs), N);

    for (n = Pstart; n < Pend; ++n)
        sum->coeffs[n] += P.coeffs[n - Pstart];

    for (n = Qstart; n < Qend; ++n)
        sum->coeffs[n] += Q.coeffs[n - Qstart];
}

int main(void)
{
    struct laurent_polynomial P, Q, sum;
    struct knot K;
    signed int Pcoeffs[7] = {3, 2, 1, 0, -1, -2, -3};
    signed int Qcoeffs[6] = {-3, 2, -1, 7, 3, 1};
    enum crossing_sign s[6] = {
        positive_crossing, positive_crossing, positive_crossing,
        positive_crossing, positive_crossing, positive_crossing
    };
    unsigned int c[6] = {0U, 1U, 2U, 0U, 1U, 2U};

    enum crossing_type t[6] = {
        over_crossing, under_crossing, over_crossing,
        under_crossing, over_crossing, under_crossing
    };

    P.lowest_degree = -3;
    P.highest_degree = 3;
    P.coeffs = Pcoeffs;

    Q.lowest_degree = -1;
    Q.highest_degree = 4;
    Q.coeffs = Qcoeffs;

    poly_add(P, Q, &sum);

    print_poly(P);
    print_poly(Q);
    print_poly(sum);

    K.number_of_crossings = 3;
    K.sign = s;
    K.type = t;
    K.crossing_number = c;

    number_of_circles_in_resolution(&K, 0x00);


    return 0;
}
