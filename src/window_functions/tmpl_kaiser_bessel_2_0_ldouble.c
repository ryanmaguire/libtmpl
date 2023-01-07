#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_window_functions.h>

/*  (14, 14) Pade approximant.                                                *
 *      Max Relative Error: 2E-20                                             *
 *      RMS Relative Error: 1E-20                                             *
 *          Actual error for 80-bit long double is less than 1 ULP.           */
#define P00 (+1.147993453795864792123256251730288859461E-02L)
#define P01 (+1.104865906135079079729524515869751553303E-01L)
#define P02 (+2.521185114911010178594291764281183422939E-01L)
#define P03 (+2.413997121169689182817195989724438217834E-01L)
#define P04 (+1.220848714470749000576816551923431272427E-01L)
#define P05 (+3.686227805266718824539623925499900003586E-02L)
#define P06 (+7.151815788837974816730611488552758559880E-03L)
#define P07 (+9.335721983280385498948187789166204750327E-04L)
#define P08 (+8.430410938971608034064652499339364627040E-05L)
#define P09 (+5.337596679755038259394935406052827153313E-06L)
#define P10 (+2.368157451389426401389436587010364780472E-07L)
#define P11 (+7.234153894019955034562982982680724461938E-09L)
#define P12 (+1.455279682303659771195665540676806741830E-10L)
#define P13 (+1.744399873274392896325063774928690745931E-12L)
#define P14 (+9.496434664115067018765183657252014285123E-15L)

#define Q00 (+1.000000000000000000000000000000000000000E+00L)
#define Q01 (-2.452820455757758366709940747664624188793E-01L)
#define Q02 (+3.023204216187514843589547473006422208825E-02L)
#define Q03 (-2.489002175819260252854650091172991760449E-03L)
#define Q04 (+1.533965157211072579429033375324208050348E-04L)
#define Q05 (-7.511298404802196393699462332966962784712E-06L)
#define Q06 (+3.024504672206494175634710579970458121995E-07L)
#define Q07 (-1.021333561154653655314394439687332752973E-08L)
#define Q08 (+2.918843461427138144629491015774025005863E-10L)
#define Q09 (-7.057880268463933247620522236821123421864E-12L)
#define Q10 (+1.428611401979141543022706671523509884631E-13L)
#define Q11 (-2.360373330947802732300190642477778227170E-15L)
#define Q12 (+3.027739551978848860500402034687625708519E-17L)
#define Q13 (-2.717499797609068370103775414837628467992E-19L)
#define Q14 (+1.297462600381044644477731797459655307931E-21L)

/*  Helper macro for the Pade approximant. This uses Horner's method.         */
#define TMPL_PADE_HELPER(x, A) \
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
                                        A##10 + x*(\
                                            A##11 + x*(\
                                                A##12 + x*(\
                                                    A##13 + x*A##14\
                                                )\
                                            )\
                                        )\
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

/*  Double precision Kaiser-Bessel window with alpha = 2.0.                   */
long double tmpl_LDouble_Kaiser_Bessel_2_0(long double x, long double W)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;
    long double numer, denom;

    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2)) for values inside the    *
     *  window. To determine if x falls inside the window we just need to     *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    const long double c = 2.0L*x/W;

    /*  Set the union part of the word to 1 - (2x/W)^2 and check the sign.    */
    w.r = 1.0L - c*c;

    /*  Negative means the input falls outside of the window. Return 0.       */
    if (TMPL_LDOUBLE_IS_NEGATIVE(w))
        return 0.0L;

    /*  Otherwise x falls inside the window. Compute via the Pade approximant.*/
    numer = TMPL_PADE_HELPER(w.r, P);
    denom = TMPL_PADE_HELPER(w.r, Q);
    return numer / denom;
}
/*  End of tmpl_Double_Kaiser_Bessel_2_0.                                     */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_PADE_HELPER
#undef P00
#undef P01
#undef P02
#undef P03
#undef P04
#undef P05
#undef P06
#undef P07
#undef P08
#undef P09
#undef P10
#undef P11
#undef P12
#undef P13
#undef P14
#undef Q00
#undef Q01
#undef Q02
#undef Q03
#undef Q04
#undef Q05
#undef Q06
#undef Q07
#undef Q08
#undef Q09
#undef Q10
#undef Q11
#undef Q12
#undef Q13
#undef Q14
