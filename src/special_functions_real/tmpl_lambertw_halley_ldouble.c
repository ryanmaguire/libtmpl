#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Add comments.
 *      Add license, "doc-string".
 *      Inline this function.
 */

long double
tmpl_LDouble_LambertW_Halley(long double x, long double x0, long double tol)
{
    long double exp_x0 = tmpl_LDouble_Exp(x0);
    long double s = x0 + 1.0L;
    long double t = x0*exp_x0 - x;
    long double dx = t / (exp_x0*s - 0.5L*(s + 1.0L)*t/s);
    unsigned int n;

    for (n = 0U; n < 14U; ++n)
    {
        if (tmpl_LDouble_Abs(dx) < tol)
            break;

        x0 = x0 - dx;
        exp_x0 = tmpl_LDouble_Exp(x0);
        s = x0 + 1.0L;
        t = x0*exp_x0 - x;
        dx = t / (exp_x0*s - 0.5L*(s + 1.0L)*t/s);
    }

    return x0 - dx;
}
