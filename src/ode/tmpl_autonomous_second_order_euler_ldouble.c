#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  Euler's method for 2nd order autonomous ODEs, x''(t) = f(x).              */
TMPL_CONST_FUNC
long double
tmpl_LDouble_Autonomous_Second_Order_Euler(const tmpl_FunctionLongDouble f,
                                           const long double x,
                                           long double * const v,
                                           const long double h)
TMPL_UNSEQUENCED
{
    const long double curvature = f(x);
    *v += h * curvature;
    return x + h * (*v);
}
/*  End of tmpl_LDouble_Autonomous_Second_Order_Euler.                        */
