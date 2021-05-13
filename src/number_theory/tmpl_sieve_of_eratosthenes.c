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
 *  This file contains he Sieve of Eratosthenes, which is an algorithm for    *
 *  computing all prime numbers up to some fixed number N.                    *
 ******************************************************************************
 *  Author: Ryan Maguire, Dartmouth College                                   *
 *  Date:   2021/04/19                                                        *
 ******************************************************************************/

#include <libtmpl/include/tmpl_vector.h>
#include <libtmpl/include/tmpl_number_theory.h>
#include <libtmpl/include/tmpl_bool.h>
#include <stdlib.h>

tmpl_ULongVector *tmpl_Sieve_of_Eratosthenes(unsigned long N)
{
    tmpl_ULongVector *sieve = malloc(sizeof(*sieve));
    tmpl_Bool *is_prime, *has_been_visited;
    unsigned long n, k, factor;

    if (sieve == NULL)
        return NULL;

    if (N < 2)
    {
        sieve->data = NULL;
        sieve->length = 0UL;
        return sieve;
    }

    is_prime = malloc(sizeof(*is_prime) * N);
    if (is_prime == NULL)
    {
        free(sieve);
        return NULL;
    }

    has_been_visited = calloc(sizeof(*has_been_visited), N);
    if (has_been_visited == NULL)
    {
        free(sieve);
        return NULL;
    }

    n = 2UL;
    sieve->length = 0UL;
    factor = 1UL;
    while (n < N)
    {
        if (!has_been_visited[n])
        {
            is_prime[n] = tmpl_True;
            sieve->length++;
            k = n + factor*n;
            while(k < N)
            {
                is_prime[k] = tmpl_False;
                has_been_visited[k] = tmpl_True;
                k += factor*n;
            }
        }
        factor = n;
        ++n;
    }

    sieve->data = malloc(sizeof(*sieve->data) * sieve->length);
    k = 0U;
    for (n=0U; n<sieve->length; ++n)
    {
        while (!is_prime[k])
            ++k;
        sieve->data[n] = k;
        ++k;
    }

    return sieve;
}

