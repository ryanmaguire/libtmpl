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
#include <math.h>
#include <libtmpl/include/tmpl_math.h>

/*  Macro for plotting libtmpl functions using GNU Plot Utils.                */
#define PLOT_FUNC(func, type, begin, finish, samples, filename)                \
int main(void)                                                                 \
{                                                                              \
    const type start = begin;                                                  \
    const type end = finish;                                                   \
    const size_t N = (size_t)samples;                                          \
    const type dx = (end - start) / (type)N;                                   \
    type x = start;                                                            \
    FILE *fp = fopen("data.txt", "w");                                         \
                                                                               \
    if (!fp)                                                                   \
    {                                                                          \
        puts("fopen failed and returned NULL. Aborting.");                     \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    while (x <= end)                                                           \
    {                                                                          \
        type y = func(x);                                                      \
        fprintf(fp, "%f %f\n", (double)x, (double)y);                          \
        x += dx;                                                               \
    }                                                                          \
                                                                               \
    fclose(fp);                                                                \
    system("graph -T ps data.txt > " filename);                                \
    system("rm -f data.txt");                                                  \
    return 0;                                                                  \
}
/*  End of PLOT_FUNC macro.                                                   */

/*  Macro for plotting libtmpl functions using GNU Plot Utils.                */
#define PLOT_DIFF(f0, f1, type, begin, finish, samples, filename)              \
int main(void)                                                                 \
{                                                                              \
    const type start = begin;                                                  \
    const type end = finish;                                                   \
    const size_t N = (size_t)samples;                                          \
    const type dx = (end - start) / (type)N;                                   \
    type x = start;                                                            \
    FILE *fp = fopen("data.txt", "w");                                         \
                                                                               \
    if (!fp)                                                                   \
    {                                                                          \
        puts("fopen failed and returned NULL. Aborting.");                     \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    while (x <= end)                                                           \
    {                                                                          \
        type y0 = f0(x);                                                       \
        type y1 = f1(x);                                                       \
        type diff = (y1 - y0)/y1;                                              \
                                                                               \
        fprintf(fp, "%e %e\n", (double)x, (double)diff);                       \
        x += dx;                                                               \
    }                                                                          \
                                                                               \
    fclose(fp);                                                                \
    system("graph -T ps data.txt > " filename);                                \
    system("rm -f data.txt");                                                  \
    return 0;                                                                  \
}
/*  End of PLOT_FUNC macro.                                                   */

/*  Macro for plotting libtmpl functions using GNU Plot Utils.                */
#define PLOT_LOGDIFF(f0, f1, type, begin, finish, samples, filename)           \
int main(void)                                                                 \
{                                                                              \
    const type start = begin;                                                  \
    const type end = finish;                                                   \
    const size_t N = (size_t)samples;                                          \
    const type dx = (end - start) / (type)N;                                   \
    type x = start;                                                            \
    FILE *fp = fopen("data.txt", "w");                                         \
                                                                               \
    if (!fp)                                                                   \
    {                                                                          \
        puts("fopen failed and returned NULL. Aborting.");                     \
        return -1;                                                             \
    }                                                                          \
                                                                               \
    while (x <= end)                                                           \
    {                                                                          \
        type y0 = f0(x);                                                       \
        type y1 = f1(x);                                                       \
        double diff = fabs((double)((y1 - y0)/y1));                            \
                                                                               \
        if (diff == 0.0)                                                       \
            diff = -18.0;                                                      \
        else                                                                   \
            diff = log10(diff);                                                \
                                                                               \
        fprintf(fp, "%e %e\n", (double)x, diff);                               \
        x += dx;                                                               \
    }                                                                          \
                                                                               \
    fclose(fp);                                                                \
    system("graph -T ps data.txt > " filename);                                \
    system("rm -f data.txt");                                                  \
    return 0;                                                                  \
}
/*  End of PLOT_FUNC macro.                                                   */
