#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/types/tmpl_cubic_double.h>
#include <stddef.h>

extern void
tmpl_Double_Natural_Cubic_Spline(const double * const x,
                                 const double * const y,
                                 tmpl_CubicDouble * TMPL_RESTRICT p,
                                 const size_t len);

void
tmpl_Double_Natural_Cubic_Spline(const double * const x,
                                 const double * const y,
                                 tmpl_CubicDouble * TMPL_RESTRICT p,
                                 const size_t len)
{
    size_t n;

    /*  The super-diagonal and the sub-diagonal in the matrix for the         *
     *  coefficients of the quadratic terms are given in terms of the         *
     *  difference in the x-values. Compute these.                            */
    double dx_n = x[1] - x[0];
    double dx_n_plus_1 = x[2] - x[1];

    /*  The right-hand side of the matrix equation is given in terms of the   *
     *  ratio dy / dx. Compute the differences in the y-values.               */
    double dy_n = y[1] - y[0];
    double dy_n_plus_1 = y[2] - y[1];

    /*  Compute the ratios dy / dx for n = 0 and n = 1.                       */
    double dy_dx_n = dy_n / dx_n;
    double dy_dx_n_plus_1 = dy_n_plus_1 / dx_n_plus_1;

    /*  The diagonal is 2 * (h_{n+1} - h_{n}), where h_{n} = x_{n+1} - x_{n}. *
     *  A cancellation occurs, giving us x_{n+2} - x_{n}. Compute this.       */
    double diag = 2.0 * (x[2] - x[0]);

    /*  Compute the zeroth component of the vector on the right-hand side of  *
     *  the matrix equation.                                                  */
    double g_n = 3.0 * (dy_n_plus_1 / dx_n_plus_1 - dy_n / dx_n);


    /*  Use the constant coefficients array for scratch work.                 */
    p[0].dat[0] = dx_n_plus_1 / diag;

    /*  The quadratic term is where most of the work is done. The constant,   *
     *  linear, and cubic terms all follow quickly from the quadratic term    *
     *  and the (x, y) values. Quadratic coefficients come from the Thomas    *
     *  algorithm for symmetric tridiagonal matrices.                         */
    p[0].dat[2] = g_n / diag;

    for (n = 1; n < len - 1; ++n)
    {
        /*  Variables for computing the scratch terms.                        */
        double numer, denom;

        /*  Update the differences in x, y, and their ratios.                 */
        dx_n = dx_n_plus_1;
        dy_n = dy_n_plus_1;
        dy_dx_n = dy_dx_n_plus_1;

        /*  Compute these terms for the next bin.                             */
        dx_n_plus_1 = x[n + 1] - x[n];
        dy_n_plus_1 = y[n + 1] - y[n];
        dy_dx_n_plus_1 = dy_n_plus_1 / dx_n_plus_1;

        /*  Compute the new diagonal entry, and the component for the vector  *
         *  on the right-hand side of the matrix equation.                    */
        diag = 2.0 * (x[n + 1] - x[n - 1]);
        g_n = 3.0 * (dy_dx_n_plus_1 - dy_dx_n);

        /*  Common factors for the scratch variables.                         */
        numer = g_n - dx_n * p[n - 1].dat[2];
        denom = diag - dx_n * p[n - 1].dat[0];

        /*  Compute the scratch variables.                                    */
        p[n].dat[0] = dx_n_plus_1 / denom;
        p[n].dat[2] = numer / denom;
    }

    /*  Backwards iterate to compute the quadratic terms.                     */
    for (n = len - 1; n > 0; --n)
        p[n - 1].dat[2] -= p[n - 1].dat[0] * p[n].dat[2];

    /*  The constant, linear, and cubic terms follow very quickly from the    *
     *  quadratic terms. Compute all of them.                                 */
    for (n = 0; n < len - 1; ++n)
    {
        const double dx = x[n + 1] - x[n];
        const double dy = y[n + 1] - y[n];

        const double c_n = p[n].dat[2];
        const double c_n_plus_1 = p[n + 1].dat[2];

        p[n].dat[0] = y[n];
        p[n].dat[1] = dy / dx - dx * (c_n_plus_1 + 2.0 * c_n) / 3.0;
        p[n].dat[3] = (c_n_plus_1 - c_n) / (3.0 * dx);
    }
}
/*  End of tmpl_Double_Natural_Cubic_Spline.                                  */
