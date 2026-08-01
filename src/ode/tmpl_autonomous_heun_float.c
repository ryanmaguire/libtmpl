#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  ODE routine using Heun's RK2 for autonomous equations, x'(t) = f(x).      */
TMPL_CONST_FUNC
float
tmpl_Float_Autonomous_Heun(const tmpl_FunctionFloat f,
                           const float x,
                           const float h)
TMPL_UNSEQUENCED
{
    /*  The Euler step, the slope at the start of the interval.               */
    const float dx0 = f(x);

    /*  Compute the next point and the slope there.                           */
    const float x1 = x + h * dx0;
    const float dx1 = f(x1);

    /*  Use the average of the two slopes that have been computed.            */
    return x + 0.5F * h * (dx0 + dx1);
}
/*  End of tmpl_Float_Autonomous_Heun.                                        */
