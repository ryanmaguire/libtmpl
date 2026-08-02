#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  Euler's method for 2nd order autonomous ODEs, x''(t) = f(x).              */
TMPL_CONST_FUNC
float
tmpl_Float_Autonomous_Second_Order_Euler(const tmpl_FunctionFloat f,
                                         const float x,
                                         float * const v,
                                         const float h)
TMPL_UNSEQUENCED
{
    const float curvature = f(x);
    *v += h * curvature;
    return x + h * (*v);
}
/*  End of tmpl_Float_Autonomous_Second_Order_Euler.                          */
