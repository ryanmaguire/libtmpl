#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  Central difference method for 2nd order autonomous ODEs, x''(t) = f(x).   */
TMPL_CONST_FUNC
float
tmpl_Float_Autonomous_Second_Order_CD(const tmpl_FunctionFloat f,
                                      const float x0,
                                      const float x1,
                                      const float h)
TMPL_UNSEQUENCED
{
    const float curvature = f(x1);
    return 2.0F * x1 - x0 + h * h * curvature;
}
/*  End of tmpl_Float_Autonomous_Second_Order_CD.                             */
