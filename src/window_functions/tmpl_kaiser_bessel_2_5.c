/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_window_functions.h>

/* Taylor Expansion of Kaiser-Bessel Function, alpha = 2.5 Pi                 */
#define KAISER_BESSEL_2_5_A00   2.68081686402441505171337754074e-3
#define KAISER_BESSEL_2_5_A01   4.13415654995155304033725418114e-2
#define KAISER_BESSEL_2_5_A02   1.59384725313258776340026287383e-1
#define KAISER_BESSEL_2_5_A03   2.73101421253152312766441954607e-1
#define KAISER_BESSEL_2_5_A04   2.63222948158581149121867402070e-1
#define KAISER_BESSEL_2_5_A05   1.62369147975853037148863339646e-1
#define KAISER_BESSEL_2_5_A06   6.95537872163024505198825271932e-2
#define KAISER_BESSEL_2_5_A07   2.18899350900016401453595086695e-2
#define KAISER_BESSEL_2_5_A08   5.27453612558204524028021710190e-3
#define KAISER_BESSEL_2_5_A09   1.00419724071661588837240301149e-3
#define KAISER_BESSEL_2_5_A10   1.54859836039664097565228705845e-4
#define KAISER_BESSEL_2_5_A11   1.97366389376168033180903245885e-5
#define KAISER_BESSEL_2_5_A12   2.11363735374798616835586093526e-6

float tmpl_Float_Kaiser_Bessel_2_5(float x, float W)
{
    float bessel_x, arg;
    arg = 2.0F * x/W;
    arg = 1.0F - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0.0F)
    {
        bessel_x = (float)KAISER_BESSEL_2_5_A12;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A11;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A10;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A09;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A08;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A07;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A06;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A05;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A04;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A03;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A02;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A01;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_5_A00;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0F;

    return bessel_x;
}

double tmpl_Double_Kaiser_Bessel_2_5(double x, double W)
{
    double bessel_x, arg;
    arg = 2.0*x/W;
    arg = 1.0 - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0)
    {
        bessel_x = KAISER_BESSEL_2_5_A12;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A11;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A10;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A09;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A08;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A07;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A06;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A05;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A04;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A03;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A02;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A01;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_5_A00;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0;

    return bessel_x;
}

long double
tmpl_LDouble_Kaiser_Bessel_2_5(long double x, long double W)
{
    long double bessel_x, arg;
    arg = 2.0L*x/W;
    arg = 1.0L - arg*arg;

    if (arg > 0)
    {
        bessel_x = (long double)KAISER_BESSEL_2_5_A12;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A11;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A10;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A09;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A08;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A07;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A06;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A05;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A04;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A03;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A02;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A01;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_5_A00;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0L;

    return bessel_x;
}
