#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_root_finding_real.h>

float tmpl_Newton_Raphson_Float(float x, float (*f)(float),
                                float (*f_prime)(float),
                                unsigned int max_iters, float eps)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float dx, y, y_prime;
    unsigned int n;

    /*  Evaluate the perturbation term, then compute the next iteration.      */
    y = (*f)(x);
    y_prime = (*f_prime)(x);

    /*  If the derivative is zero at your initial guess, Newton-Raphson       *
     *  fails. Return Not-a-Number in this case.                              */
    if (y_prime == 0.0F)
        return TMPL_NANF;

    /*  Compute the first iteration of Newton-Raphson.                        */
    dx = y/y_prime;
    x -= dx;

    /*  The first iteration has been computed above, so set n to 1.           */
    n = 1;

    /*  Continuing this computation until the error is below the threshold.   */
    while(tmpl_Float_Abs(dx) > eps)
    {
        y = (*f)(x);
        y_prime = (*f_prime)(x);

        if (y_prime == 0.0F)
            return TMPL_NANF;

        dx = y/y_prime;
        x -= dx;
        ++n;

        /*  Break if too many iterations have been run.                      */
        if (n > max_iters)
            break;
    }

    return x;
}

double tmpl_Newton_Raphson_Double(double x, double (*f)(double),
                                  double (*f_prime)(double),
                                  unsigned int max_iters, double eps)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double dx, y, y_prime;
    unsigned int n;

    /*  Evaluate the perturbation term, then compute the next iteration.      */
    y = (*f)(x);
    y_prime = (*f_prime)(x);

    /*  If the derivative is zero at your initial guess, Newton-Raphson       *
     *  fails. Return Not-a-Number in this case.                              */
    if (y_prime == 0.0)
        return TMPL_NAN;

    /*  Compute the first iteration of Newton-Raphson.                        */
    dx = y/y_prime;
    x -= dx;

    /*  The first iteration has been computed above, so set n to 1.           */
    n = 1;

    /*  Continuing this computation until the error is below the threshold.   */
    while(tmpl_Double_Abs(dx) > eps)
    {
        y = (*f)(x);
        y_prime = (*f_prime)(x);

        if (y_prime == 0.0)
            return TMPL_NAN;

        dx = y/y_prime;
        x -= dx;
        ++n;

        /*  Break if too many iterations have been run.                      */
        if (n > max_iters)
            break;
    }

    return x;
}

