#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  Central difference method for 2nd order autonomous ODEs, x''(t) = f(x).   */
TMPL_CONST_FUNC
long double
tmpl_LDouble_Autonomous_Second_Order_CD(const tmpl_FunctionLongDouble f,
                                        const long double x0,
                                        const long double x1,
                                        const long double h)
TMPL_UNSEQUENCED
{
    const long double curvature = f(x1);
    return 2.0L * x1 - x0 + h * h * curvature;
}
/*  End of tmpl_LDouble_Autonomous_Second_Order_CD.                           */
