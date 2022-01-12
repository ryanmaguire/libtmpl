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
 ******************************************************************************/

/*  tmpl_Double_Arctan function is here.                                      */
#include <libtmpl/include/tmpl_math.h>

/*  printf here.                                                              */
#include <stdio.h>

/*  atan found here.                                                          */
#include <math.h>

/*  DBL_MAX found here.                                                       */
#include <float.h>

/*  Function for testing the speed and accuracy of tmpl_Double_Arctan.        */
int main(void)
{
    double max_abs, max_rel, temp, x, y0, y1;
    unsigned long int n;

    const double start = -0.1*DBL_MAX;
    const double end = 0.1*DBL_MAX;
    const unsigned long int N = 1E8;
    const double dx = (end - start) / (double)N;

    printf("Functions: tmpl_Double_Arctan vs atan\n\n");
    printf("Start:     %.16e\n", start);
    printf("End:       %.16e\n", end);
    printf("Number:    %lu\n", N);
    printf("Increment: %.16e\n\n", dx);

    max_abs = 0.0;
    max_rel = 0.0;
    x = start;
    for (n = 0UL; n < N; ++n)
    {
        y0 = tmpl_Double_Arctan(x);
        y1 = atan(x);

        temp = fabs(y0 - y1);
        if (max_abs < temp)
            max_abs = temp;

        temp = fabs((y0 - y1) / y1);
        if (max_rel < temp)
            max_rel = temp;

        x += dx;
    }

    printf("Max Abs Error: %.24e\n", max_abs);
    printf("Max Rel Error: %.24e\n", max_rel);
    return 0;
}
/*  End of main.                                                              */
