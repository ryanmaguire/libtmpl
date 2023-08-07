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

/*  TODO: Fix this absolute mess of a test.                                   */

#include <libtmpl/include/tmpl_polynomial_integer.h>
#include <boost/math/tools/polynomial.hpp>
#include <cstdlib>
#include <ctime>

using namespace boost::math::tools;

static void rand_poly(int *coeffs, size_t deg)
{
    size_t n;
    for (n = (size_t)0; n <= deg; ++n)
        coeffs[n] = rand() & 20;
}

int main(void)
{
    size_t n, m;
    clock_t t1, t2;
    const size_t deg = (size_t)100;
    const size_t N = (size_t)100000;
    polynomial<int> *P0 = (polynomial<int> *)(std::malloc(sizeof(*P0)*N));
    polynomial<int> *P1 = (polynomial<int> *)(std::malloc(sizeof(*P1)*N));
    polynomial<int> *P2 = (polynomial<int> *)(std::malloc(sizeof(*P2)*N));
    tmpl_IntPolynomial *Q0 = (tmpl_IntPolynomial *)(std::malloc(sizeof(*Q0)*N));
    tmpl_IntPolynomial *Q1 = (tmpl_IntPolynomial *)(std::malloc(sizeof(*Q1)*N));
    tmpl_IntPolynomial *Q2 = (tmpl_IntPolynomial *)(std::malloc(sizeof(*Q2)*N));
    int coeffs0[deg + (size_t)1], coeffs1[deg + (size_t)1];

    for (n = 0; n < N; ++n) {
        rand_poly(coeffs0, deg);
        rand_poly(coeffs1, deg);

        Q0[n].error_occurred = tmpl_False;
        Q0[n].error_message = NULL;
        Q0[n].degree = deg;
        Q0[n].coeffs = (int *)malloc(sizeof(*Q0[n].coeffs) * (deg + 1));

        Q1[n].error_occurred = tmpl_False;
        Q1[n].error_message = NULL;
        Q1[n].degree = deg;
        Q1[n].coeffs = (int *)malloc(sizeof(*Q0[n].coeffs) * (deg + 1));

        for (m = 0; m <= deg; ++m) {
            Q0[n].coeffs[m] = coeffs0[m];
            Q1[n].coeffs[m] = coeffs1[m];
        }

        tmpl_IntPolynomial_Shrink(&Q0[n]);
        tmpl_IntPolynomial_Shrink(&Q1[n]);

        tmpl_IntPolynomial_Init(&Q2[n]);
        P0[n] = polynomial<int>(coeffs0, deg);
        P1[n] = polynomial<int>(coeffs1, deg);
        P2[n] = polynomial<int>();
    }

    t1 = clock();
    for (n = (size_t)0; n < N; ++n)
        tmpl_IntPolynomial_Multiply_Naive(&Q0[n], &Q1[n], &Q2[n]);
    t2 = clock();
    std::printf("libtmpl: %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    t1 = clock();
    for (n = (size_t)0; n < N; ++n)
        P2[n] = P0[n] * P1[n];
    t2 = clock();
    std::printf("boost:   %f\n", (double)(t2-t1)/CLOCKS_PER_SEC);

    for (n = (size_t)0; n < N; ++n)
    {
        for (m = (size_t)0; m <= Q2[n].degree; ++m)
        {
            if (P2[n][m] != Q2[n].coeffs[m])
            {
                puts("FAIL");
                goto END;
            }
        }
    }

END:
    for (n = 0; n < N; ++n)
    {
        tmpl_IntPolynomial_Destroy(&Q0[n]);
        tmpl_IntPolynomial_Destroy(&Q1[n]);
        tmpl_IntPolynomial_Destroy(&Q2[n]);
    }

    std::free(P0);
    std::free(P1);
    std::free(P2);
    std::free(Q0);
    std::free(Q1);
    std::free(Q2);
}
