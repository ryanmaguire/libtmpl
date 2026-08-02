#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  Euler's method for 2nd order autonomous ODEs, x''(t) = f(x).              */
TMPL_CONST_FUNC
double
tmpl_Double_Autonomous_Second_Order_Euler(const tmpl_FunctionDouble f,
                                          const double x,
                                          double * const v,
                                          const double h)
TMPL_UNSEQUENCED
{
    const double curvature = f(x);
    *v += h * curvature;
    return x + h * (*v);
}
/*  End of tmpl_Double_Autonomous_Second_Order_Euler.                         */
