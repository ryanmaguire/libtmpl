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
#include <cstdio>
#include <cstdlib>
#include <libtmpl/include/tmpl_sort.h>
#include <algorithm>

static double rand_real(void)
{
    int n = std::rand();
    return static_cast<double>(n) / static_cast<double>(RAND_MAX);
}

int main(void)
{
    const size_t len = static_cast<size_t>(1E5);
    double *arrtmpl = static_cast<double *>(std::malloc(sizeof(*arrtmpl)*len));
    double *arrcpp = static_cast<double *>(std::malloc(sizeof(*arrcpp)*len));
    size_t n;

    for (n = 0; n < len; ++n)
    {
        double x = rand_real();
        arrtmpl[n] = x;
        arrcpp[n] = x;
    }

    tmpl_Double_Merge_Sort(arrtmpl, len);
    std::sort(arrcpp, arrcpp + n);

    for (n = 0; n < len; ++n)
    {
        if (arrtmpl[n] != arrcpp[n])
        {
            std::puts("FAIL");
            return -1;
        }
    }
    std::puts("PASS");
    return 0;
}
