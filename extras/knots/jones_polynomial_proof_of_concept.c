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

/*  Crossing signs or negative and positive. This assumes the knot has been   *
 *  given an orientation.                                                     */
enum crossing_sign {negative_crossing, positive_crossing};

/*  Crossing type for the Gauss code. Is the current strand over or under.    */
enum crossing_type {under_crossing, over_crossing};

static unsigned char backward = 0x00U;
static unsigned char forward = 0x01U;

/*  Extended Gauss code. This contains crossing number, sign, and type. This  *
 *  allows us to distinguish a knot from it's mirror.                         */
struct knot {
    unsigned int number_of_crossings;
    enum crossing_sign *sign;
    enum crossing_type *type;
    unsigned int *crossing_number;
};

/*  Laurent polynomials, i.e. polynomials with negative exponents allowed.    */
struct laurent_polynomial {
    signed int lowest_degree;
    signed int highest_degree;
    signed int *coeffs;
};

/*  This struct is used for keeping track of which crossing number            *
 *  corresponds to which indices.                                             */
struct CrossingIndices {
    unsigned int under;
    unsigned int over;
};

/*  Returns an array ind where ind[n] is a struct containing the indices of   *
 *  the under and over crossings of the nth crossing.                         */
static struct CrossingIndices *
get_indices(struct knot *K)
{
    unsigned int n;
    struct CrossingIndices *ind;

    /*  Check for invalid inputs.                                             */
    if (!K)
        return NULL;

    /*  If there are no crossings, return an empty array (a NULL pointer).    */
    if (K->number_of_crossings == 0U)
        return NULL;

    /*  Allocate memory for the array.                                        */
    ind = malloc(sizeof(*ind)*K->number_of_crossings);

    /*  Check if malloc failed.                                               */
    if (!ind)
        return NULL;

    /*  Loop through and save the indices.                                    */
    for (n = 0U; n < 2U * K->number_of_crossings; ++n)
    {
        if (K->type[n] == over_crossing)
            ind[K->crossing_number[n]].over = n;
        else
             ind[K->crossing_number[n]].under = n;
    }

    return ind;
}
/*  End of get_indices.                                                       */

static unsigned int
number_of_circles_in_resolution(struct knot *K,
                                struct CrossingIndices *ind,
                                unsigned int resolution,
                                unsigned char *have_visited)
{
    unsigned int number_of_circles, n, k, m;
    unsigned char dir, crossing_resolution;

    /*  The empty knot has zero circles.                                      */
    if (!K)
        return 0U;

    /*  The unknot has 1 circle.                                              */
    if (K->number_of_crossings == 0U)
        return 1U;

    if (!ind)
        return 0U;

    if (!have_visited)
        return 0U;

    number_of_circles = 0U;

    for (n = 0U; n < 2U*K->number_of_crossings; ++n)
    {
        k = 4U*K->crossing_number[n];

        /*  Each crossing has four entrances. Bottom left, bottom right, top  *
         *  left, top right. Check which one's we have visited.               */
        for (m = 0U; m < 3; ++m)
        {
            if (!have_visited[k])
                break;
            else
                ++k;
        }

        if (have_visited[k])
            continue;

        if (m < 2U)
            dir = forward;
        else
            dir = backward;

        m = n;
        while (!have_visited[k])
        {
            crossing_resolution = (resolution >> K->crossing_number[m]) & 0x01U;
            have_visited[k] = 0x01U;

            if (K->sign[m] == positive_crossing)
            {
                if (K->type[m] == over_crossing)
                {
                    if (crossing_resolution == 0x00U)
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 3U;
                        else
                            k = 4U*K->crossing_number[m] + 1U;
                    }
                    else
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 1U;
                        else
                            k = 4U*K->crossing_number[m] + 3U;

                        dir = 0x01U - dir;
                    }
                    m = ind[K->crossing_number[m]].under;
                }
                else
                {
                    if (crossing_resolution == 0x00U)
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 2U;
                        else
                            k = 4U*K->crossing_number[m];
                    }
                    else
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m];
                        else
                            k = 4U*K->crossing_number[m] + 2U;

                        dir = 0x01U - dir;
                    }
                    m = ind[K->crossing_number[m]].over;
                }
            }
            else
            {
                if (K->type[m] == over_crossing)
                {
                    if (crossing_resolution == 0x00U)
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 2U;
                        else
                            k = 4U*K->crossing_number[m];
                    }
                    else
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m];
                        else
                            k = 4U*K->crossing_number[m] + 2U;

                        dir = 0x01U - dir;
                    }

                    m = ind[K->crossing_number[m]].under;
                }
                else
                {
                    if (crossing_resolution == 0x00U)
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 3U;
                        else
                            k = 4U*K->crossing_number[m] + 1U;
                    }
                    else
                    {
                        if (dir == forward)
                            k = 4U*K->crossing_number[m] + 1U;
                        else
                            k = 4U*K->crossing_number[m] + 3U;

                        dir = 0x01U - dir;
                    }
                    m = ind[K->crossing_number[m]].over;
                }
            }

            if (dir == forward)
            {
                if (m == 2U*K->number_of_crossings - 1U)
                    m = 0U;
                else
                    ++m;
            }
            else
            {
                if (m == 0U)
                    m = 2U*K->number_of_crossings - 1U;
                else
                    --m;
            }
            
            have_visited[k] = 0x01U;

            k = 4U*K->crossing_number[m];
            if (K->sign[m] == positive_crossing)
            {
                if (K->type[m] == over_crossing)
                {
                    if (dir == backward)
                        k += 2U;
                }
                else
                {
                    if (dir == forward)
                        k += 1U;
                    else
                        k += 3U;
                }
            }
            else
            {
                if (K->type[m] == over_crossing)
                {
                    if (dir == forward)
                        k += 1U;
                    else
                        k += 3U;
                }
                else
                {
                    if (dir == backward)
                        k += 2U;
                }
            }
        }
        ++number_of_circles;
    }
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
    struct CrossingIndices *ind;
    unsigned char *have_visited;
    unsigned int n, m;
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
    ind = get_indices(&K);
    have_visited = calloc(sizeof(*have_visited), 4U*K.number_of_crossings);
    printf("\n");
    for (n = 0U; n < 1U << K.number_of_crossings; ++n)
    {
        printf("%u : %u\n",
               n, number_of_circles_in_resolution(&K, ind, n, have_visited));

        for (m = 0U; m < 4U*K.number_of_crossings; ++m)
            have_visited[m] = 0x00U;
    }

    free(ind);
    free(have_visited);
    return 0;
}
