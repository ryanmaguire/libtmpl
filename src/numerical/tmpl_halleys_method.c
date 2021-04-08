#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_numerical.h>

float tmpl_Halleys_Method_Float(float x, float (*f)(float),
                                float (*f_prime)(float),
                                float (*f_2prime)(float),
                                unsigned int max_iters, float eps)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float dx, y, y_prime, y_2prime, denom;
    unsigned int n;

    /*  Evaluate the perturbation term, then compute the next iteration.      */
    y = f(x);
    y_prime = f_prime(x);
    y_2prime = f_2prime(x);

    denom = 2.0F*y_prime*y_prime - y*y_2prime;

    /*  Check that the denominator is non-zero.                               */
    if (denom == 0.0F)
        return tmpl_NaN_F;

    /*  Compute the first iteration of Halley's method.                       */
    dx = 2.0F*y*y_prime/denom;
    x -= dx;

    /*  The first iteration has been computed above, so set n to 1.           */
    n = 1;

    /*  Continuing this computation until the error is below the threshold.   */
    while(tmpl_Float_Abs(dx) > eps)
    {
        y = f(x);
        y_prime = f_prime(x);
        y_2prime = f_2prime(x);

        denom = 2*y_prime*y_prime - y*y_2prime;

        if (denom == 0.0F)
            return tmpl_NaN_F;

        dx = 2.0F*y*y_prime/denom;
        x -= dx;
        ++n;

        /*  Break if too many iterations have been run.                       */
        if (n > max_iters)
            break;
    }

    return x;
}

double tmpl_Halleys_Method_Double(double x, double (*f)(double),
                                  double (*f_prime)(double),
                                  double (*f_2prime)(double),
                                  unsigned int max_iters, double eps)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double dx, y, y_prime, y_2prime, denom;
    unsigned int n;

    /*  Evaluate the perturbation term, then compute the next iteration.      */
    y = f(x);
    y_prime = f_prime(x);
    y_2prime = f_2prime(x);

    denom = 2.0*y_prime*y_prime - y*y_2prime;

    /*  Check that the denominator is non-zero.                               */
    if (denom == 0.0)
        return tmpl_NaN;

    /*  Compute the first iteration of Halley's method.                       */
    dx = 2.0*y*y_prime/denom;
    x -= dx;

    /*  The first iteration has been computed above, so set n to 1.           */
    n = 1;

    /*  Continuing this computation until the error is below the threshold.   */
    while(tmpl_Double_Abs(dx) > eps)
    {
        y = f(x);
        y_prime = f_prime(x);
        y_2prime = f_2prime(x);

        denom = 2.0*y_prime*y_prime - y*y_2prime;

        if (denom == 0.0)
            return tmpl_NaN;

        dx = 2.0*y*y_prime/denom;
        x -= dx;
        ++n;

        /*  Break if too many iterations have been run.                       */
        if (n > max_iters)
            break;
    }

    return x;
}

long double
tmpl_Halleys_Method_LDouble(long double x, long double (*f)(long double),
                            long double (*f_prime)(long double),
                            long double (*f_2prime)(long double),
                            unsigned int max_iters, long double eps)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    long double dx, y, y_prime, y_2prime, denom;
    unsigned int n;

    /*  Evaluate the perturbation term, then compute the next iteration.      */
    y = f(x);
    y_prime = f_prime(x);
    y_2prime = f_2prime(x);

    denom = 2.0L*y_prime*y_prime - y*y_2prime;

    /*  Check that the denominator is non-zero.                               */
    if (denom == 0.0L)
        return tmpl_NaN_L;

    /*  Compute the first iteration of Halley's method.                       */
    dx = 2.0L*y*y_prime/denom;
    x -= dx;

    /*  The first iteration has been computed above, so set n to 1.           */
    n = 1;

    /*  Continuing this computation until the error is below the threshold.   */
    while(tmpl_LDouble_Abs(dx) > eps)
    {
        y = f(x);
        y_prime = f_prime(x);
        y_2prime = f_2prime(x);

        denom = 2.0L*y_prime*y_prime - y*y_2prime;

        if (denom == 0.0L)
            return tmpl_NaN_L;

        dx = 2.0L*y*y_prime/denom;
        x -= dx;
        ++n;

        /*  Break if too many iterations have been run.                       */
        if (n > max_iters)
            break;
    }

    return x;
}


