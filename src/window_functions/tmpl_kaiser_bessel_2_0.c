/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_window_functions.h>

/* Taylor Expansion of Kaiser-Bessel Function, alpha = 2.0 Pi                 */
#define KAISER_BESSEL_2_0_A00 1.14799345379586479212325625173E-2
#define KAISER_BESSEL_2_0_A01 1.13302412440054404174028755736E-1
#define KAISER_BESSEL_2_0_A02 2.79562497118100660800421522589E-1
#define KAISER_BESSEL_2_0_A03 3.06574583548481935246360365287E-1
#define KAISER_BESSEL_2_0_A04 1.89110616190764661645757930810E-1
#define KAISER_BESSEL_2_0_A05 7.46578787939636569441597855450E-2
#define KAISER_BESSEL_2_0_A06 2.04678813644694334928965293809E-2
#define KAISER_BESSEL_2_0_A07 4.12265085705596709062582845471E-3
#define KAISER_BESSEL_2_0_A08 6.35764578796162329491799908822E-4
#define KAISER_BESSEL_2_0_A09 7.74659862338682228855283637288E-5
#define KAISER_BESSEL_2_0_A10 7.64558638668513481381569815368E-6
#define KAISER_BESSEL_2_0_A11 6.23627380586252011565352895678E-7
#define KAISER_BESSEL_2_0_A12 4.27427468060687589919240887794E-8

float tmpl_Float_Kaiser_Bessel_2_0(float x, float W)
{
    float bessel_x, arg;
    arg = 2.0F * x/W;
    arg = 1.0F - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0.0F)
    {
        bessel_x = (float)KAISER_BESSEL_2_0_A12;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A11;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A10;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A09;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A08;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A07;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A06;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A05;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A04;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A03;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A02;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A01;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_2_0_A00;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0F;

    return bessel_x;
}

double tmpl_Double_Kaiser_Bessel_2_0(double x, double W)
{
    double bessel_x, arg;
    arg = 2.0*x/W;
    arg = 1.0 - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0)
    {
        bessel_x = KAISER_BESSEL_2_0_A12;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A11;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A10;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A09;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A08;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A07;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A06;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A05;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A04;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A03;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A02;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A01;
        bessel_x = arg*bessel_x + KAISER_BESSEL_2_0_A00;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0;

    return bessel_x;
}

long double
tmpl_LDouble_Kaiser_Bessel_2_0(long double x, long double W)
{
    long double bessel_x, arg;
    arg = 2.0L*x/W;
    arg = 1.0L - arg*arg;

    if (arg > 0)
    {
        bessel_x = (long double)KAISER_BESSEL_2_0_A12;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A11;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A10;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A09;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A08;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A07;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A06;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A05;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A04;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A03;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A02;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A01;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_2_0_A00;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0L;

    return bessel_x;
}
