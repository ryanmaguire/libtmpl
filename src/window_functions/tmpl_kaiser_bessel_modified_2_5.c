/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_window_functions.h>

/*  Taylor Expansion of Modified Kaiser-Bessel Function, alpha = 2.5 Pi       */
#define MODIFIED_KAISER_BESSEL_2_5_A01  4.14526925768347286292556360856e-2
#define MODIFIED_KAISER_BESSEL_2_5_A02  1.59813155114582899876788606369e-1
#define MODIFIED_KAISER_BESSEL_2_5_A03  2.73835524144247175471513296242e-1
#define MODIFIED_KAISER_BESSEL_2_5_A04  2.63930497487175121688556222589e-1
#define MODIFIED_KAISER_BESSEL_2_5_A05  1.62805599973820467924927444509e-1
#define MODIFIED_KAISER_BESSEL_2_5_A06  6.97407493933859400420106113296e-2
#define MODIFIED_KAISER_BESSEL_2_5_A07  2.19487757381451495909574422227e-2
#define MODIFIED_KAISER_BESSEL_2_5_A08  5.28871419979786875646449115789e-3
#define MODIFIED_KAISER_BESSEL_2_5_A09  1.00689654595734627672697987971e-3
#define MODIFIED_KAISER_BESSEL_2_5_A10  1.55276102834723413370648946123e-4
#define MODIFIED_KAISER_BESSEL_2_5_A11  1.97896914762602018893080108449e-5
#define MODIFIED_KAISER_BESSEL_2_5_A12  2.11931885948674321924199402729e-6

float tmpl_Float_Modified_Kaiser_Bessel_2_5(float x, float W)
{
    float bessel_x, arg;
    arg = 2.0F*x/W;
    arg = 1.0F - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0.0F)
    {
        bessel_x = (float)MODIFIED_KAISER_BESSEL_2_5_A12;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_5_A11;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_5_A10;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_5_A09;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_5_A08;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_5_A07;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_5_A06;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_5_A05;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_5_A04;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_5_A03;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_5_A02;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_5_A01;
        bessel_x = arg*bessel_x;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0F;

    return bessel_x;
}

double tmpl_Double_Modified_Kaiser_Bessel_2_5(double x, double W)
{
    double bessel_x, arg;
    arg = 2.0*x/W;
    arg = 1.0 - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0)
    {
        bessel_x = MODIFIED_KAISER_BESSEL_2_5_A12;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_5_A11;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_5_A10;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_5_A09;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_5_A08;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_5_A07;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_5_A06;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_5_A05;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_5_A04;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_5_A03;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_5_A02;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_5_A01;
        bessel_x = arg*bessel_x;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0;

    return bessel_x;
}

long double
tmpl_LDouble_Modified_Kaiser_Bessel_2_5(long double x, long double W)
{
    long double bessel_x, arg;
    arg = 2.0L*x/W;
    arg = 1.0L - arg*arg;

    if (arg > 0.0L)
    {
        bessel_x = (long double)MODIFIED_KAISER_BESSEL_2_5_A12;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_5_A11;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_5_A10;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_5_A09;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_5_A08;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_5_A07;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_5_A06;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_5_A05;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_5_A04;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_5_A03;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_5_A02;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_5_A01;
        bessel_x = arg*bessel_x;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0L;

    return bessel_x;
}
