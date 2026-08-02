#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  Central difference method for 2nd order autonomous ODEs, x''(t) = f(x).   */
TMPL_CONST_FUNC
double
tmpl_Double_Autonomous_Second_Order_CD(const tmpl_FunctionDouble f,
                                       const double x0,
                                       const double x1,
                                       const double h)
TMPL_UNSEQUENCED
{
    const double curvature = f(x1);
    return 2.0 * x1 - x0 + h * h * curvature;
}
/*  End of tmpl_Double_Autonomous_Second_Order_CD.                            */
