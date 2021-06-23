/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_window_functions.h>

/*  Taylor Expansion of Modified Kaiser-Bessel Function, alpha = 3.5 Pi       */
#define MODIFIED_KAISER_BESSEL_3_5_A01  4.16514995414684968723698450860e-3
#define MODIFIED_KAISER_BESSEL_3_5_A02  3.14736052127124923141946151611e-2
#define MODIFIED_KAISER_BESSEL_3_5_A03  1.05701177734383843513797151295e-1
#define MODIFIED_KAISER_BESSEL_3_5_A04  1.99680514216455319565277233641e-1
#define MODIFIED_KAISER_BESSEL_3_5_A05  2.41419041035507923786083460554e-1
#define MODIFIED_KAISER_BESSEL_3_5_A06  2.02695852544496965664760985660e-1
#define MODIFIED_KAISER_BESSEL_3_5_A07  1.25032992397232932630182925731e-1
#define MODIFIED_KAISER_BESSEL_3_5_A08  5.90500804982519735481437039452e-2
#define MODIFIED_KAISER_BESSEL_3_5_A09  2.20349118704793214846304905263e-2
#define MODIFIED_KAISER_BESSEL_3_5_A10  6.66019830971902766697459162007e-3
#define MODIFIED_KAISER_BESSEL_3_5_A11  1.66371002321116235031980438335e-3
#define MODIFIED_KAISER_BESSEL_3_5_A12  3.49213467271634973449651728719e-4

float tmpl_Float_Modified_Kaiser_Bessel_3_5(float x, float W)
{
    float bessel_x, arg;
    arg = 2.0F*x/W;
    arg = 1.0F - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0.0F)
    {
        bessel_x = (float)MODIFIED_KAISER_BESSEL_3_5_A12;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_3_5_A11;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_3_5_A10;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_3_5_A09;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_3_5_A08;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_3_5_A07;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_3_5_A06;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_3_5_A05;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_3_5_A04;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_3_5_A03;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_3_5_A02;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_3_5_A01;
        bessel_x = arg*bessel_x;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0F;

    return bessel_x;
}

double tmpl_Double_Modified_Kaiser_Bessel_3_5(double x, double W)
{
    double bessel_x, arg;
    arg = 2.0*x/W;
    arg = 1.0 - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0)
    {
        bessel_x = MODIFIED_KAISER_BESSEL_3_5_A12;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_3_5_A11;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_3_5_A10;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_3_5_A09;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_3_5_A08;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_3_5_A07;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_3_5_A06;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_3_5_A05;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_3_5_A04;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_3_5_A03;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_3_5_A02;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_3_5_A01;
        bessel_x = arg*bessel_x;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0;

    return bessel_x;
}

long double
tmpl_LDouble_Modified_Kaiser_Bessel_3_5(long double x, long double W)
{
    long double bessel_x, arg;
    arg = 2.0L*x/W;
    arg = 1.0L - arg*arg;

    if (arg > 0.0L)
    {
        bessel_x = (long double)MODIFIED_KAISER_BESSEL_3_5_A12;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_3_5_A11;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_3_5_A10;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_3_5_A09;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_3_5_A08;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_3_5_A07;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_3_5_A06;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_3_5_A05;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_3_5_A04;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_3_5_A03;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_3_5_A02;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_3_5_A01;
        bessel_x = arg*bessel_x;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0L;

    return bessel_x;
}
