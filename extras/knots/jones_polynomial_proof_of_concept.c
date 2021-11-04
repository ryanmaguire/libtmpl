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
#include <limits.h>

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

unsigned int hamming_weight(unsigned int val)
{
    unsigned int result = 0U;
    unsigned int n;

    for (n = 0; n < sizeof(val) * CHAR_BIT; ++n)
    {
        result += val & 1U;
        val = val >> 1U;
    }

    return result;
}

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

    if (P.coeffs[0] == 1)
        printf("q^%d", P.lowest_degree);
    else if (P.coeffs[0] == -1)
        printf("-q^%d", P.lowest_degree);
    else
        printf("%dq^%d", P.coeffs[n], P.lowest_degree);

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

    if (sum->coeffs != NULL)
        free(sum->coeffs);

    N = (unsigned int)(sum->highest_degree - sum->lowest_degree) + 1U;
    sum->coeffs = calloc(sizeof(*sum->coeffs), N);

    for (n = Pstart; n < Pend; ++n)
        sum->coeffs[n] += P.coeffs[n - Pstart];

    for (n = Qstart; n < Qend; ++n)
        sum->coeffs[n] += Q.coeffs[n - Qstart];
}

static void
poly_shift(struct laurent_polynomial P,
           signed int shift,
           struct laurent_polynomial *out)
{
    if (!out)
        return;

    *out = P;
    out->lowest_degree += shift;
    out->highest_degree += shift;
}

static void
poly_scale(struct laurent_polynomial P,
           signed int scale,
           struct laurent_polynomial *out)
{
    unsigned int n;
    unsigned int N = (unsigned int)(P.highest_degree - P.lowest_degree + 1);
    if (!out)
        return;

    *out = P;

    for (n = 0U; n < N; ++n)
        out->coeffs[n] *= scale;
}

/*  Function for multiplying two polynomials.                                 */
void
poly_multiply(struct laurent_polynomial *P,
              struct laurent_polynomial *Q,
              struct laurent_polynomial *prod)
{
    /*  Declare variables for indexing.                                       */
    signed int n, k;

    /*  Two polynomial pointers for ordering the inputs in terms of degree.   */
    struct laurent_polynomial *first, *second;
    signed long int *first_coeffs, *second_coeffs;
    unsigned long int first_deg, second_deg;

    /*  Temporary variable used in case realloc is needed.                    */
    signed long int *tmp;

    /*  If prod is NULL, nothing can be done.                                 */
    if (prod == NULL)
        return;

    /*  If either P or Q are NULL, nothing can be done. Store an error        *
     *  message in prod.                                                      */
    if ((P == NULL) || (Q == NULL))
        return;

    /*  If either P or Q has a NULL coeffs pointer, nothing can be done.      */
    if ((P->coeffs == NULL) || (Q->coeffs == NULL))
        return;

    /*  Order the polynomials by degree.                                      */
    if (P->degree <= Q->degree)
    {
        first = P;
        second = Q;
    }
    else
    {
        first = Q;
        second = P;
    }

    /*  Copy the data from first and second, rather than using them directly. *
     *  If either P or Q are also the same as the prod pointer, their coeffs  *
     *  pointers will be changed as the Cauchy sum is performed. This will    *
     *  result in the wrong values for the product polynomial. To prevent P   *
     *  and Q from being changed in transit, make copies of their data and    *
     *  work with that.                                                       */
    first_deg = first->degree;
    first_coeffs = malloc(sizeof(*first_coeffs) * (first_deg + 1UL));

    /*  Check if malloc failed.                                               */
    if (first_coeffs == NULL)
        return;

    /*  If malloc was successful, copy the data from first.                   */
    for (n = 0UL; n <= first->degree; ++n)
        first_coeffs[n] = first->coeffs[n];

    /*  Do the same thing with the second pointer.                            */
    second_deg = second->degree;
    second_coeffs = malloc(sizeof(*second_coeffs) * (second_deg + 1UL));

    /*  Check if malloc failed.                                               */
    if (second_coeffs == NULL)
    {
        /*  Free the memory allocated to first_coeffs, since malloc was       *
         *  successful for that one.                                          */
        free(first_coeffs);
        return;
    }

    /*  Otherwise, copy the data.                                             */
    for (n = 0; n <= second->highest_degree; ++n)
        second_coeffs[n] = second->coeffs[n];

    /*  If the prod coeffs pointer is NULL, allocate memory for it.           */
    if (prod->coeffs == NULL)
    {
        /*  The degree of a product is the sum of the degrees.                */
        prod->degree = first_deg + second_deg;
        prod->coeffs = malloc(sizeof(*prod->coeffs) * (prod->degree + 1UL));

        /*  Check if malloc failed.                                           */
        if (prod->coeffs == NULL)
        {
            free(first_coeffs);
            free(second_coeffs);
            return;  
        }
    }

    /*  If prod does not have the correct size for it's degree, reallocate    *
     *  the coeffs pointer to be the sum of the two others.                   */
    else if (prod->degree != (first_deg + second_deg))
    {
        /*  The degree of a product is the sum of the degrees.                */
        prod->degree = first_deg + second_deg;
        tmp = realloc(prod->coeffs, sizeof(*prod->coeffs)*(prod->degree + 1UL));

        /*  Check if realloc failed.                                          */
        if (tmp == NULL)
        {
            free(first_coeffs);
            free(second_coeffs);
            return;
        }

        /*  If realloc was successful, set prod->coeffs to the result.        */
        prod->coeffs = tmp;
    }

    /*  Perform the first part of the Cauchy product. We arrange coefficients *
     *  P_m, Q_n in a rectangular array. Suppose P->degree = 5 and            *
     *  Q->degree = 3, we get the following:                                  *
     *      P0*Q0 P0*Q1 P0*Q2 P0*Q3                                           *
     *      P1*Q0 P1*Q1 P1*Q2 P1*Q3                                           *
     *      P2*Q0 P2*Q1 P2*Q2 P2*Q3                                           *
     *      P3*Q0 P3*Q1 P3*Q2 P3*Q3                                           *
     *      P4*Q0 P4*Q1 P4*Q2 P4*Q3                                           *
     *      P5*Q0 P5*Q1 P5*Q2 P5*Q3                                           *
     *  The Cauchy product for infinite sums is defined by:                   *
     *      /  infty     \ /  infty     \     infty                           *
     *      |  -----     | |  -----     |     -----                           *
     *      |  \         | |  \         |     \                               *
     *      |  /     a_m | |  /     b_n |  =  /     c_n                       *
     *      |  -----     | |  -----     |     -----                           *
     *      \  m = 0     / \   n = 0    /     n = 0                           *
     *  Where:                                                                *
     *              n                                                         *
     *            -----                                                       *
     *            \                                                           *
     *      c_n = /    a_k * b_{n-k}                                          *
     *            -----                                                       *
     *            k = 0                                                       *
     *  To make this well defined for finite sums we need to limit the range  *
     *  of the sum for c_n. The first leg of this is going to be:             *
     *        00   01   02   03                                               *
     *                                                                        *
     *        10   11   12   13                                               *
     *      -----                                                             *
     *      | 20 | 21   22   23                                               *
     *      |     ----                                                        *
     *      | 30   31 | 32   33                                               *
     *      |          ----                                                   *
     *      | 40   41   42 | 43                                               *
     *      |               ----                                              *
     *      | 50   51   52   53 |                                             *
     *      --------------------                                              *
     *  Perform this part of the sum.                                         */
    for (n = 0UL; n < first_deg; ++n)
    {
        prod->coeffs[n] = first_coeffs[n] * second_coeffs[0];
        for (k = 1UL; k <= n; ++k)
            prod->coeffs[n] += first_coeffs[n-k] * second_coeffs[k];
    }

    /*  In the next part, the sum can't start at zero since Q does not have   *
     *  a fifth coefficient. We can pretend it does by adding 0 x^4, or we    *
     *  start the sum at 1, and then the next one starts at 2, and so on.     *
     *  This leg of the sum is the following:                                 *
     *       ----                                                             *
     *      | 00 | 01   02   03                                               *
     *      |     ----                                                        *
     *      | 10   11 | 12   13                                               *
     *      -----      ----                                                   *
     *        20 | 21   22 | 23                                               *
     *            ----      ----                                              *
     *        30   31 | 32   33 |                                             *
     *                 ----     |                                             *
     *        40   41   42 | 43 |                                             *
     *                      ----                                              *
     *        50   51   52   53                                               *
     *  Perform this part of the sum.                                         */
    for (n = first_deg; n < second_deg; ++n)
    {
        prod->coeffs[n] = 0UL;
        for (k = n - first_deg; k <= n; ++k)
            prod->coeffs[n] += first_coeffs[n-k] * second_coeffs[k];
    }

    /*  In the last part, the sum can't go too high since P may not have the  *
     *  corresponding coefficient. Here we compute the following portion:     *
     *          --------------                                                *
     *      00 | 01   02   03 |                                               *
     *          ----          |                                               *
     *      10   11 | 12   13 |                                               *
     *               ----     |                                               *
     *      20   21   22 | 23 |                                               *
     *                    ----                                                *
     *      30   31   32   33                                                 *
     *                                                                        *
     *      40   41   42   43                                                 *
     *                                                                        *
     *      50   51   52   53                                                 *
     *  Perform this part of the sum.                                         */
    for (n = second_deg; n <= prod->degree; ++n)
    {
        prod->coeffs[n] = 0UL;
        for (k = n - first_deg; k <= second_deg; ++k)
            prod->coeffs[n] += first_coeffs[n-k] * second_coeffs[k];
    }

    /*  Free the memory allocated to first and second.                        */
    free(first_coeffs);
    free(second_coeffs);
    return;
}
/*  End of tmpl_Create_Zero_PolynomialZ.                                      */

static struct laurent_polynomial
kaufmann_bracket(struct knot *K)
{
    struct laurent_polynomial out;
    return out;
}

int main(void)
{
    struct laurent_polynomial P, Q, sum = {0, 0, NULL};
    struct knot K;
    struct CrossingIndices *ind;
    unsigned char *have_visited;
    unsigned int n, m;
    signed int Pcoeffs[7] = {1, 0, 0, 0, 0, 0, 1};
    signed int Qcoeffs[6] = {1, 0, 0, 0, 0, 1};
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
    poly_multiply(P, Q, &sum);
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
