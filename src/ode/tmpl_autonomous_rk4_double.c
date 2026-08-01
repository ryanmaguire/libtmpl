#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  Numerical ODE routine using RK4 for autonomous equations, x'(t) = f(x).   */
TMPL_CONST_FUNC
double
tmpl_Double_Autonomous_RK4(const tmpl_FunctionDouble f,
                           const double x,
                           const double h)
TMPL_UNSEQUENCED
{
    /*  RK4 uses 2 step size, a full step and a half step.                    */
    const double half_h = 0.5 * h;

    /*  Start with the Euler iteration. Compute the rough estimate for the    *
     *  slope, which is given by the differential equation.                   */
    const double dy0 = f(x);

    /*  We diverge from Euler's method now. Instead of stepping forward with  *
     *  step-size h, we move with step-size h / 2. This is the next x value.  *
     *  Compute the slope for this point using the differential equation.     */
    const double x1 = x + half_h * dy0;
    const double dy1 = f(x1);

    /*  Step back to the starting point, increment forward using the slope    *
     *  obtained from the previous step.                                      */
    const double x2 = x + half_h * dy1;
    const double dy2 = f(x2);

    /*  Use the previous slope to step across the entire interval. Compute    *
     *  slope about this new point.                                           */
    const double x3 = x + h * dy2;
    const double dy3 = f(x3);

    /*  The actual slope we use for the starting point is the weighted        *
     *  average of the four slopes we have. We give a higher weight to the    *
     *  midpoint slopes.                                                      */
    const double slope = (dy0 + 2.0 * (dy1 + dy2) + dy3) / 6.0;

    /*  The new point is obtained by incrementing x using this new slope.     */
    return x + h * slope;
}
/*  End of tmpl_Double_Autonomous_RK4.                                        */
