#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  Numerical ODE routine using RK4 for autonomous equations, x'(t) = f(x).   */
TMPL_CONST_FUNC
long double
tmpl_LDouble_Autonomous_RK4(const tmpl_FunctionLongDouble f,
                            const long double x,
                            const long double h)
TMPL_UNSEQUENCED
{
    /*  RK4 uses 2 step size, a full step and a half step.                    */
    const long double half_h = 0.5L * h;

    /*  Start with the Euler iteration. Compute the rough estimate for the    *
     *  slope, which is given by the differential equation.                   */
    const long double dy0 = f(x);

    /*  We diverge from Euler's method now. Instead of stepping forward with  *
     *  step-size h, we move with step-size h / 2. This is the next x value.  *
     *  Compute the slope for this point using the differential equation.     */
    const long double x1 = x + half_h * dy0;
    const long double dy1 = f(x1);

    /*  Step back to the starting point, increment forward using the slope    *
     *  obtained from the previous step.                                      */
    const long double x2 = x + half_h * dy1;
    const long double dy2 = f(x2);

    /*  Use the previous slope to step across the entire interval. Compute    *
     *  slope about this new point.                                           */
    const long double x3 = x + h * dy2;
    const long double dy3 = f(x3);

    /*  The actual slope we use for the starting point is the weighted        *
     *  average of the four slopes we have. We give a higher weight to the    *
     *  midpoint slopes.                                                      */
    const long double slope = (dy0 + 2.0L * (dy1 + dy2) + dy3) / 6.0L;

    /*  The new point is obtained by incrementing x using this new slope.     */
    return x + h * slope;
}
/*  End of tmpl_LDouble_Autonomous_RK4.                                       */
