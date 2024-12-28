/*  The C standard library header math.h is included here, as are aliases for *
 *  various functions, the macros INFINITY and NAN, as well as the max legal  *
 *  values for the exponential function which don't return INFINITY.          */
#include <libtmpl/include/tmpl_math.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_window_functions.h>

float tmpl_Float_Coss_Window(float x, float W)
{
    /*  Declare necessary variables. C89 requires declaring these at the top. */
    float abs_x, coss_x, arg;

    /*  Get the absolute value of x.                                          */
    abs_x = tmpl_Float_Abs(x);

    /*  Compute the cosine squared window function.                           */
    if (abs_x <= W/2.0F)
    {
        arg    = abs_x * tmpl_Float_Pi / W;
        coss_x = tmpl_Float_Cos(arg);
        coss_x *= coss_x;
    }
    else
        coss_x = 0.0F;

    return coss_x;
}

double tmpl_Double_Coss_Window(double x, double W)
{
    /*  Declare necessary variables. C89 requires declaring these at the top. */
    double abs_x, coss_x, arg;

    /*  Get the absolute value of x.                                          */
    abs_x = tmpl_Double_Abs(x);

    /*  Compute the cosine squared window function.                           */
    if (abs_x <= W/2.0)
    {
        arg    = abs_x * tmpl_Double_Pi/W;
        coss_x = tmpl_Double_Cos(arg);
        coss_x *= coss_x;
    }
    else
        coss_x = 0.0;

    return coss_x;
}

long double tmpl_LDouble_Coss_Window(long double x, long double W)
{
    /*  Declare necessary variables. C89 requires declaring these at the top. */
    long double abs_x, coss_x, arg;

    /*  Get the absolute value of x.                                          */
    abs_x = tmpl_LDouble_Abs(x);

    /*  Compute the cosine squared window function.                           */
    if (abs_x <= W/2.0L)
    {
        arg    = abs_x * tmpl_LDouble_Pi/W;
        coss_x = tmpl_LDouble_Cos(arg);
        coss_x *= coss_x;
    }
    else
        coss_x = 0.0L;

    return coss_x;
}
