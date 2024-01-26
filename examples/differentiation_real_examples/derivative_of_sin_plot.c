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
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_differentiation_real.h>

static void write_val(FILE *fp, double x, double y)
{
    fwrite(&x, sizeof(x), 1, fp);
    fwrite(&y, sizeof(y), 1, fp);
}

int main(void)
{
    const double start = -20;
    const double end =  20;
    const size_t zero = (size_t)0;
    const size_t n_elements = (size_t)(1E3);
    const double dx = (end - start) / (double)n_elements;
    size_t n;

    FILE * const sin_fp = fopen("sin_binary", "w");
    FILE * const cos_fp = fopen("cos_binary", "w");
    FILE * const diff_fp = fopen("diff_binary", "w");

    double x = start;

    for (n = zero; n < n_elements; ++n)
    {
        const double y = tmpl_Double_Sin(x);
        const double dy = tmpl_Double_Derivative(tmpl_Double_Sin, x);
        const double z = tmpl_Double_Cos(x);
        const double diff = tmpl_Double_Abs(z - dy);

        write_val(sin_fp, x, y);
        write_val(cos_fp, x, dy);
        write_val(diff_fp, x, diff);

        x += dx;
    }

    fclose(sin_fp);
    fclose(cos_fp);
    fclose(diff_fp);

    system("graph -T ps -I d "
           "sin_binary -L \"Sin Plot\" "
           "--reposition 0.0 -0.8 1.0 cos_binary -L \"Derivative Plot\" "
           "--reposition 0.0 -1.6 1.0 diff_binary -L \"Difference Plot\" "
           "> sin_derivative.ps");
    system("rm -f sin_binary cos_binary diff_binary");
    return 0;
}
