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
 ******************************************************************************
 *                     tmpl_sorted_cubic_interp1d_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for cubic interpolation of sorted data.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Sorted_Cubic_Interp1d                                     *
 *  Purpose:                                                                  *
 *      Interpolates a sorted data set against another data set using splines.*
 *  Arguments:                                                                *
 *      x (const double * const):                                             *
 *          A sorted array of real numbers that are monotonically increasing. *
 *      y (const double * const):                                             *
 *          The data points corresponding to x.                               *
 *      p (const tmpl_CubicDouble * TMPL_RESTRICT const):                     *
 *          The user-provided splining polynomials. There are "len - 1" total.*
 *      len (const size_t):                                                   *
 *          The number of elements of x and y.                                *
 *      x_new (const double * const):                                         *
 *          The new data points. Assumed sorted in increasing order.          *
 *      y_new (double * const):                                               *
 *          The interpolated data corresponding to x_new, to be computed.     *
 *      len_new (const size_t):                                               *
 *          The number of elements of x_new and y_new.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      src/interpolate/                                                      *
 *          tmpl_Double_Sorted_Linear_Interp1d:                               *
 *              Linearly interpolates one data set against another.           *
 *  Method:                                                                   *
 *      For values x <= x[0] or x >= x[len - 1], extrapolate using the first  *
 *      and last splining polynomials, respectively. A linear extrapolation   *
 *      is performed using the slopes of these two splines.                   *
 *                                                                            *
 *      For points with x[0] < x < x[len - 1], find the index m such that     *
 *      x[m] <= x < x[m + 1] and then interpolate using the mth spline:       *
 *                                                                            *
 *          y_new[n] = POLY_EVAL(p[m], x_new[n] - x[m])                       *
 *                                                                            *
 *      Since the data is sorted, we repeat this, incrementing m and n along  *
 *      the way.                                                              *
 *  Notes:                                                                    *
 *      1.) Both x and x_new are assumed to be sorted in increasing order.    *
 *                                                                            *
 *      2.) For values outside of (min(x), max(x)), we use the cubic splining *
 *          polynomials to extrapolate.                                       *
 *                                                                            *
 *      3.) The user may provide any splining polynomial they wish. Natural   *
 *          splines, Hermite cubics, and more are all possible.               *
 *                                                                            *
 *      4.) If any of the inputs are NULL, or if len_new = 0, nothing is done.*
 *                                                                            *
 *      5.) If len < 3, then we use a linear interpolation.                   *
 *                                                                            *
 *      6.) The polynomial "p" is declared with TMPL_RESTRICT, which expands  *
 *          to "restrict" if C99 support is available. To properly use this   *
 *          function, none of the other arguments (x, y, x_new, y_new) should *
 *          point to p.                                                       *
 *                                                                            *
 *      7.) It is assumed that the coefficients for the nth splining          *
 *          polynomial are for the function:                                  *
 *                                                                            *
 *                                                 2            3             *
 *              p (x) = a + b (x - x ) + c (x - x ) + d (x - x )              *
 *               n                  n            n            n               *
 *                                                                            *
 *          where x_n is the nth element of the "x" array. That is the        *
 *          parameter for the nth spline is x - x_n.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard library header file where size_t is given.               *
 *  2.) tmpl_cubic_double.h:                                                  *
 *          Header providing cubic polynomials and helper macros.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 14, 2026                                             *
 ******************************************************************************/

/*  size_t data type found here.                                              */
#include <stddef.h>

/*  Location of the TMPL_RESTRICT macro.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Cubic polynomial typedef and helper macros provided here.                 */
#include <libtmpl/include/types/tmpl_cubic_double.h>

/*  Function for performing a linear interpolation across a data set.         */
extern void
tmpl_Double_Sorted_Linear_Interp1d(const double * const x,
                                   const double * const y,
                                   const size_t len,
                                   const double * const x_new,
                                   double * const y_new,
                                   const size_t len_new);

/*  Function prototype / forward declaration.                                 */
extern void
tmpl_Double_Sorted_Cubic_Interp1d(
    const double * const x,
    const double * const y,
    const tmpl_CubicDouble * TMPL_RESTRICT const p,
    const size_t len,
    const double * const x_new,
    double * const y_new,
    const size_t len_new
);

/*  Double precision cubic interpolation of sorted data.                      */
extern void
tmpl_Double_Sorted_Cubic_Interp1d(
    const double * const x,
    const double * const y,
    const tmpl_CubicDouble * TMPL_RESTRICT const p,
    const size_t len,
    const double * const x_new,
    double * const y_new,
    const size_t len_new
)
{
    /*  Declare two variables for indexing the interpolated and raw data.     */
    size_t m;
    size_t n = 0;

    /*  Check for NULL pointers, aborting if there is one.                    */
    if (!x || !y || !p || !x_new || !y_new || len_new == 0)
        return;

    /*  The input data set needs at least three points to perform splines.    */
    if (len < 3)
    {
        /*  Lacking enough points, use a linear interpolation.                */
        tmpl_Double_Sorted_Linear_Interp1d(x, y, len, x_new, y_new, len_new);
        return;
    }

    /*  Loop over the entries of the interpolating arrays and compute.        */
    for (m = 0; m < len_new; ++m)
    {
        /*  For values with x-values less than x[0], use a backwards linear   *
         *  extrapolation using the zeroth splining polynomial.               */
        if (x_new[m] <= x[0])
        {
            /*  The spline is centered at x[0], meaning the slope and         *
             *  y-intercept for the extrapolation can be read directly from p.*/
            const double a = y[0];
            const double b = TMPL_CUBIC_DOUBLE_LINEAR_TERM(p[0]);

            /*  The argument for the linear extrapolation.                    */
            const double dx = x_new[m] - x[0];

            /*  Compute the extrapolated point.                               */
            y_new[m] = a + b * dx;
        }

        /*  Similarly for x-values above x[len-1], use a forwards linear      *
         *  extrapolation using the last splining polynomial.                 */
        else if (x_new[m] >= x[len - 1])
        {
            /*  The last spline is centered about x[len - 2], not x[len - 1]. *
             *  The y-intercept is the last y-value in the data set, and the  *
             *  slope can be obtained by evaluating the derivative of the     *
             *  final spline at the final x-value.                            */
            const double diff = x[len - 1] - x[len - 2];
            const double a = y[len - 1];
            const double b = TMPL_CUBIC_DOUBLE_DERIV_EVAL(p[len - 2], diff);

            /*  The argument for the linear extrapolation.                    */
            const double dx = x_new[m] - x[len - 1];

            /*  Compute the extrapolated point.                               */
            y_new[m] = a + b * dx;
        }

        /*  And finally, handle the general case.                             */
        else
        {
            /*  Find the largest index n such that x[n] <= x_new[m].          */
            while (x[n + 1] < x_new[m])
                ++n;

            /*  Use this index to compute the linear interpolation.           */
            y_new[m] = TMPL_CUBIC_DOUBLE_EVAL(p[n], x_new[m] - x[n]);
        }
    }
    /*  End of for loop computing y_new[m].                                   */
}
/*  End of tmpl_Double_Sorted_Cubic_Interp1d.                                 */
