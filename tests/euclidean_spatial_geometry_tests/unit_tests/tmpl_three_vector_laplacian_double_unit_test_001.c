/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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

#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>
#include <math.h>
#include <stdio.h>

static double test_func(tmpl_ThreeVectorDouble v)
{
    return v.dat[0]*v.dat[0] + v.dat[1]*v.dat[1] + v.dat[2]*v.dat[2];
}

int main(void)
{
    tmpl_3DDouble_Functional f = test_func;
    const double start = -10.0;
    const double end = 10.0;
    const unsigned int N = 100U;

    const double ds = (end - start) / (double)N;
    double x = start;
    double y = start;
    double z = start;
    double max_err = 0.0;
    double rms_err = 0.0;
    double tmp;
    tmpl_ThreeVectorDouble P;

    while (x < end)
    {
        while (y < end)
        {
            while (z < end)
            {
                P = tmpl_ThreeVector_Rect(x, y, z);
                tmp = fabs(6.0 - tmpl_3DDouble_Laplacian(f, P));

                rms_err += tmp*tmp;

                if (max_err < tmp)
                    max_err = tmp;

                z += ds;
            }
            z = start;
            y += ds;
        }
        y = start;
        x += ds;
    }
    rms_err = sqrt(rms_err / (double)N) / (double)N;

    P = tmpl_ThreeVector_Rect(0.01, 0.01, 0.01);
    printf("max err: %e\n", max_err);
    printf("rms err: %e\n", rms_err);
    return 0;
}
