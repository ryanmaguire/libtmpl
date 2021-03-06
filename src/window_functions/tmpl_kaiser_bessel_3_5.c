/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_window_functions.h>

/* Taylor Expansion of Kaiser-Bessel Function, alpha = 3.5 Pi                 */
#define KAISER_BESSEL_3_5_A00   1.37782784195108944072394913183e-4
#define KAISER_BESSEL_3_5_A01   4.16457606818957720393279069168e-3
#define KAISER_BESSEL_3_5_A02   3.14692686917576270929327830656e-2
#define KAISER_BESSEL_3_5_A03   1.05686613931822898050138235809e-1
#define KAISER_BESSEL_3_5_A04   1.99653001679257065318455314636e-1
#define KAISER_BESSEL_3_5_A05   2.41385777647876338247314746026e-1
#define KAISER_BESSEL_3_5_A06   2.02667924545588583615194331816e-1
#define KAISER_BESSEL_3_5_A07   1.25015765003424195987707818786e-1
#define KAISER_BESSEL_3_5_A08   5.90419444137539790852413424858e-2
#define KAISER_BESSEL_3_5_A09   2.20318758389723129879141296234e-2
#define KAISER_BESSEL_3_5_A10   6.65928064905262302082534080707e-3
#define KAISER_BESSEL_3_5_A11   1.66348079261207100704542994789e-3
#define KAISER_BESSEL_3_5_A12   3.49165351667835860027922841080e-4

float tmpl_Float_Kaiser_Bessel_3_5(float x, float W)
{
    float bessel_x, arg;
    arg = 2.0F * x/W;
    arg = 1.0F - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0.0F)
    {
        bessel_x = (float)KAISER_BESSEL_3_5_A12;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A11;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A10;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A09;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A08;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A07;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A06;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A05;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A04;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A03;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A02;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A01;
        bessel_x = arg*bessel_x + (float)KAISER_BESSEL_3_5_A00;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0F;

    return bessel_x;
}

double tmpl_Double_Kaiser_Bessel_3_5(double x, double W)
{
    double bessel_x, arg;
    arg = 2.0 * x/W;
    arg = 1.0 - arg*arg;

    /*  arg > 0 means x is within the window. We use a Taylor series for the  *
     *  modified Kaiser-Bessel function.                                      */
    if (arg > 0.0)
    {
        bessel_x = KAISER_BESSEL_3_5_A12;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A11;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A10;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A09;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A08;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A07;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A06;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A05;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A04;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A03;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A02;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A01;
        bessel_x = arg*bessel_x + KAISER_BESSEL_3_5_A00;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0;

    return bessel_x;
}

long double
tmpl_LDouble_Kaiser_Bessel_3_5(long double x, long double W)
{
    long double bessel_x, arg;
    arg = 2.0L*x/W;
    arg = 1.0L - arg*arg;

    if (arg > 0)
    {
        bessel_x = (long double)KAISER_BESSEL_3_5_A12;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A11;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A10;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A09;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A08;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A07;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A06;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A05;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A04;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A03;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A02;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A01;
        bessel_x = arg*bessel_x + (long double)KAISER_BESSEL_3_5_A00;
    }

    /*  For values outside of the window, we return 0.                        */
    else
        bessel_x = 0.0L;

    return bessel_x;
}
