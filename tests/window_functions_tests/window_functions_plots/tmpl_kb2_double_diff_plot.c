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
#include "tmpl_math_plots.h"
#include <libtmpl/include/tmpl_window_functions.h>
#include <gsl/gsl_specfunc.h>
#include <math.h>
static double func(double x, double W)
{
    const double c = 2.0*x/W;
    const double arg = 1.0 - c*c;
    const double alpha = 2.0*tmpl_One_Pi;

    if (arg < 0.0)
        return 0.0;
    else
    {
        const double numer = gsl_sf_bessel_I0(alpha*sqrt(arg));
        const double denom = gsl_sf_bessel_I0(alpha);
        return numer / denom;
    }
}
static inline double f0(double x){return tmpl_Double_Kaiser_Bessel_2_0(x, 1.0);}
static inline double f1(double x){return func(x, 1.0);}

PLOT_DIFF(f0, f1, double, 0.40, 0.49, 1E4, "tmpl_kb2_diff_plot.ps")
