#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Add comments.
 *      Add license, "doc-string".
 *      Inline this function.
 */

float tmpl_Float_LambertW_Halley(float x, float x0, float tol)
{
    float exp_x0 = tmpl_Float_Exp(x0);
    float s = x0 + 1.0F;
    float t = x0*exp_x0 - x;
    float dx = t / (exp_x0*s - 0.5F*(s + 1.0F)*t/s);
    unsigned int n;

    for (n = 0U; n < 8U; ++n)
    {
        if (tmpl_Float_Abs(dx) < tol)
            break;

        x0 = x0 - dx;
        exp_x0 = tmpl_Float_Exp(x0);
        s = x0 + 1.0F;
        t = x0*exp_x0 - x;
        dx = t / (exp_x0*s - 0.5F*(s + 1.0F)*t/s);
    }

    return x0 - dx;
}
