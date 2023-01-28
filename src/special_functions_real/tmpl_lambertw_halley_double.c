#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Add comments.
 *      Add license, "doc-string".
 *      Inline this function.
 */

double tmpl_Double_LambertW_Halley(double x, double x0, double tol)
{
    double exp_x0 = tmpl_Double_Exp(x0);
    double s = x0 + 1.0;
    double t = x0*exp_x0 - x;
    double dx = t / (exp_x0*s - 0.5*(s + 1.0)*t/s);
    unsigned int n;

    for (n = 0U; n < 10U; ++n)
    {
        if (tmpl_Double_Abs(dx) < tol)
            break;

        x0 = x0 - dx;
        exp_x0 = tmpl_Double_Exp(x0);
        s = x0 + 1.0;
        t = x0*exp_x0 - x;
        dx = t / (exp_x0*s - 0.5*(s + 1.0)*t/s);
    }

    return x0 - dx;
}
