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
    double max_abs = 0.0;
    double max_rel = 0.0;
    double rms_abs = 0.0;
    double rms_rel = 0.0;
    double temp, y0, y1;
    unsigned long int n;

    const double start = 1.0E-4;
    const double end = 1.0E4;
    const unsigned long int N = 1000000000UL;
    const double dx = (end - start) / (double)N;
    double x = start;

    printf("Functions: tmpl_Double_Log vs log\n");
    printf("start:     %.16e\n", start);
    printf("end:       %.16e\n", end);
    printf("samples:   %lu\n", N);
    printf("increment: %.16e\n\n", dx);

    for (n = 0UL; n < N; ++n)
    {
        y0 = tmpl_Double_Log(x);
        y1 = log(x);

        temp = fabs(y0 - y1);
        rms_abs += temp*temp;
        if (max_abs < temp)
            max_abs = temp;

        temp = fabs((y0 - y1) / y1);
        rms_rel += temp*temp;
        if (max_rel < temp)
            max_rel = temp;

        x += dx;
    }
    rms_abs = sqrt(rms_abs / (double)N);
    rms_rel = sqrt(rms_rel / (double)N);

    printf("max abs error: %.24e\n", max_abs);
    printf("max rel error: %.24e\n", max_rel);
    printf("rms abs error: %.24e\n", rms_abs);
    printf("rms rel error: %.24e\n", rms_rel);
    return 0;
}
/*  End of main.                                                              */

