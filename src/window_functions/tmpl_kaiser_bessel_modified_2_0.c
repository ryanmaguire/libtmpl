/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_window_functions.h>

/* Taylor Expansion of Modified Kaiser-Bessel Function, alpha = 2.0 Pi        */
#define MODIFIED_KAISER_BESSEL_2_0_A01 1.14618222126928749645196222695e-1
#define MODIFIED_KAISER_BESSEL_2_0_A02 2.82809127387243423533545769115e-1
#define MODIFIED_KAISER_BESSEL_2_0_A03 3.10134912036597639686900220959e-1
#define MODIFIED_KAISER_BESSEL_2_0_A04 1.91306805797991572819499337886e-1
#define MODIFIED_KAISER_BESSEL_2_0_A05 7.55248996984881942399995746237e-2
#define MODIFIED_KAISER_BESSEL_2_0_A06 2.07055800682230959900642506315e-2
#define MODIFIED_KAISER_BESSEL_2_0_A07 4.17052824833556674429483596109e-3
#define MODIFIED_KAISER_BESSEL_2_0_A08 6.43147874291253173568797655869e-4
#define MODIFIED_KAISER_BESSEL_2_0_A09 7.83656184031631837458373758816e-5
#define MODIFIED_KAISER_BESSEL_2_0_A10 7.73437652285948594043705662616e-6
#define MODIFIED_KAISER_BESSEL_2_0_A11 6.30869723716497460710444914139e-7
#define MODIFIED_KAISER_BESSEL_2_0_A12 4.32391291785164657063120476020e-8

float tmpl_Float_Modified_Kaiser_Bessel_2_0(float x, float W)
{
    float bessel_x, arg;
    arg = 2.0F*x/W;
    arg = 1.0F - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0.0F)
    {
        bessel_x = (float)MODIFIED_KAISER_BESSEL_2_0_A12;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_0_A11;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_0_A10;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_0_A09;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_0_A08;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_0_A07;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_0_A06;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_0_A05;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_0_A04;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_0_A03;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_0_A02;
        bessel_x = arg*bessel_x + (float)MODIFIED_KAISER_BESSEL_2_0_A01;
        bessel_x = arg*bessel_x;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0F;

    return bessel_x;
}

double tmpl_Double_Modified_Kaiser_Bessel_2_0(double x, double W)
{
    double bessel_x, arg;
    arg = 2.0*x/W;
    arg = 1.0 - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0.0)
    {
        bessel_x = MODIFIED_KAISER_BESSEL_2_0_A12;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_0_A11;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_0_A10;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_0_A09;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_0_A08;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_0_A07;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_0_A06;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_0_A05;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_0_A04;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_0_A03;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_0_A02;
        bessel_x = arg*bessel_x + MODIFIED_KAISER_BESSEL_2_0_A01;
        bessel_x = arg*bessel_x;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0;

    return bessel_x;
}

long double
tmpl_LDouble_Modified_Kaiser_Bessel_2_0(long double x, long double W)
{
    long double bessel_x, arg;
    arg = 2.0L*x/W;
    arg = 1.0L - arg*arg;

    if (arg > 0.0L)
    {
        bessel_x = (long double)MODIFIED_KAISER_BESSEL_2_0_A12;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_0_A11;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_0_A10;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_0_A09;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_0_A08;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_0_A07;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_0_A06;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_0_A05;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_0_A04;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_0_A03;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_0_A02;
        bessel_x = arg*bessel_x + (long double)MODIFIED_KAISER_BESSEL_2_0_A01;
        bessel_x = arg*bessel_x;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0L;

    return bessel_x;
}
