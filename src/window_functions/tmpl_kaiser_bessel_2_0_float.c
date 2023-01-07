#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_window_functions.h>

/*  Degree 11 Taylor series.                                                  *
 *      Max Relative Error: 4E-8                                              *
 *      RMS Relative Error: 2E-8                                              *
 *          Actual error for 32-bit float is less than 1 ULP.                 */
#define T00 (1.14799345379586479212325625173E-2F)
#define T01 (1.13302412440054404174028755736E-1F)
#define T02 (2.79562497118100660800421522589E-1F)
#define T03 (3.06574583548481935246360365287E-1F)
#define T04 (1.89110616190764661645757930810E-1F)
#define T05 (7.46578787939636569441597855450E-2F)
#define T06 (2.04678813644694334928965293809E-2F)
#define T07 (4.12265085705596709062582845471E-3F)
#define T08 (6.35764578796162329491799908822E-4F)
#define T09 (7.74659862338682228855283637288E-5F)
#define T10 (7.64558638668513481381569815368E-6F)
#define T11 (6.23627380586252011565352895678E-7F)
/* Not needed. #define T12 (4.27427468060687589919240887794E-8).              */

#define TMPL_TAYLOR_HELPER(x, A) \
A##00 + x*(\
    A##01 + x*(\
        A##02 + x*(\
            A##03 + x*(\
                A##04 + x*(\
                    A##05 + x*(\
                        A##06 + x*(\
                            A##07 + x*(\
                                A##08 + x*(\
                                    A##09 + x*(\
                                        A##10 + x*A##11\
                                    )\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Single precision Kaiser-Bessel window with alpha = 2.0.                   */
float tmpl_Float_Kaiser_Bessel_2_0(float x, float W)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w;

    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2)) for values inside the    *
     *  window. To determine if x falls inside the window we just need to     *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    const float c = 2.0F*x/W;

    /*  Set the union part of the word to 1 - (2x/W)^2 and check the sign.    */
    w.r = 1.0F - c*c;

    /*  Negative means the input falls outside of the window. Return 0.       */
    if (w.bits.sign)
        return 0.0F;

    /*  Otherwise use the Taylor series to compute the window function.       */
    else
        return TMPL_TAYLOR_HELPER(w.r, T);
}

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_TAYLOR_HELPER
#undef T00
#undef T01
#undef T02
#undef T03
#undef T04
#undef T05
#undef T06
#undef T07
#undef T08
#undef T09
#undef T10
#undef T11
#undef T12
