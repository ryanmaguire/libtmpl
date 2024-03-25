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
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <libtmpl/include/tmpl_array_integer.h>

static signed int * randarr(size_t len)
{
    size_t n;
    signed int * const arr = malloc(sizeof(*arr) * len);
    const double factor = 20.0 / (double)RAND_MAX;

    for (n = 0; n < len; ++n)
    {
        const int val = rand();
        const double x_val = (double)val * factor;
        arr[n] = (int)x_val;
    }

    return arr;
}

int main(void)
{
    const size_t N = (size_t)1E7;
    signed int * const arr = randarr(N);

    const clock_t t0 = clock();
    const double rms0 = tmpl_Int_Array_Double_RMS(arr, N);
    const clock_t t1 = clock();
    const double rms1 = tmpl_Int_Array_Double_Quick_RMS(arr, N);
    const clock_t t2 = clock();

    printf("RMS:       %e\n", (double)(t1 - t0) / CLOCKS_PER_SEC);
    printf("Quick RMS: %e\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
    printf("Error:     %e\n", (rms0 - rms1) / rms0);
    free(arr);
    return 0;
}
