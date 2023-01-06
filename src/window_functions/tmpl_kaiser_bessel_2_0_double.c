#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_window_functions.h>

#ifndef TMPL_KAISER_BESSEL_2_0_DOUBLE_METHOD
#define TMPL_KAISER_BESSEL_2_0_DOUBLE_METHOD 0
#endif

/*  (10, 10) Pade approximant.                                                *
 *      Max Relative Error: 1E-18                                             *
 *      RMS Relative Error: 3E-19                                             *
 *          Actual error for 64-bit double is less than 1 ULP.                *
 *  Default method.                                                           */
#if TMPL_KAISER_BESSEL_2_0_DOUBLE_METHOD == 0

/*  Coefficients of the numerator.                                            */
#define P00 (+1.147993453795864792123256251730288859461E-02)
#define P01 (+1.093970397537675388725484282860995214402E-01)
#define P02 (+2.416858436077829524121716207096858143407E-01)
#define P03 (+2.179850698735958472737011382153802805463E-01)
#define P04 (+1.003358531250250675578947613439528440930E-01)
#define P05 (+2.637013607516716014574176237088974114730E-02)
#define P06 (+4.193021844618576132354365338846592278944E-03)
#define P07 (+4.117381334535173988129294188477195546511E-04)
#define P08 (+2.453423464988086942571685441005499298312E-05)
#define P09 (+8.191872420781051053794685047347515701636E-07)
#define P10 (+1.187528023028491674211132314950508868693E-08)

/*  Coefficients of the denominator.                                          */
#define Q00 (+1.000000000000000000000000000000000000000E+00)
#define Q01 (-3.401911982488808957271341639681001268467E-01)
#define Q02 (+5.817367163071483807676519770830423213322E-02)
#define Q03 (-6.622871483653638911102751745617244660588E-03)
#define Q04 (+5.594346393036180272355591624054772718633E-04)
#define Q05 (-3.689508161824235540076974574043483314974E-05)
#define Q06 (+1.939177985664448966279799090866941677681E-06)
#define Q07 (-8.091944028043149923802541058994831491357E-08)
#define Q08 (+2.591618071434932244380621811665968697136E-09)
#define Q09 (-5.819266537361917929946685087213711075394E-11)
#define Q10 (+7.050277852983463994127995931411667942785E-13)

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
                                    A##09 + x*A##10\
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
double tmpl_Double_Kaiser_Bessel_2_0(double x, double W)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;
    double numer, denom;

    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2)) for values inside the    *
     *  window. To determine if x falls inside the window we just need to     *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    const double c = 2.0*x/W;

    /*  Set the union part of the word to 1 - (2x/W)^2 and check the sign.    */
    w.r = 1.0 - c*c;

    /*  Negative means the input falls outside of the window. Return 0.       */
    if (w.bits.sign)
        return 0.0;

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

/*  (8, 8) Pade approximant.                                                  *
 *      Max Relative Error: 3E-15                                             *
 *      RMS Relative Error: 1E-15                                             */
#else

/*  Coefficients of the numerator.                                            */
#define P0 (+1.14799345379586479212325625173E-02)
#define P1 (+1.08460957320536773036375456606E-01)
#define P2 (+2.32805011457736410816092872215E-01)
#define P3 (+1.98654102911356976882372573366E-01)
#define P4 (+8.33924574747798099715396990518E-02)
#define P5 (+1.89374146455274903062254800825E-02)
#define P6 (+2.38528881140176091721254727362E-03)
#define P7 (+1.58185689589546216155616576405E-04)
#define P8 (+4.36543773687157959376385892914E-06)

/*  Coefficients of the denominator.                                          */
#define Q0 (+1.00000000000000000000000000000E+00)
#define Q1 (-4.21731944856415054085193094988E-01)
#define Q2 (+8.93525212632413657127079762661E-02)
#define Q3 (-1.25350222898161735099188621406E-02)
#define Q4 (+1.28667499707303873183193073396E-03)
#define Q5 (-1.00125398262872993854148570995E-04)
#define Q6 (+5.84738134193771654036450053602E-06)
#define Q7 (-2.38084238875396710793297721666E-07)
#define Q8 (+5.27370330232818833752452109393E-09)

/*  Helper macro for the Pade approximant. This uses Horner's method.         */
#define TMPL_PADE_HELPER(x, A) \
A##0 + x*(\
    A##1 + x*(\
        A##2 + x*(\
            A##3 + x*(\
                A##4 + x*(\
                    A##5 + x*(\
                        A##6 + x*(\
                            A##7 + x*A##8\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Double precision Kaiser-Bessel window with alpha = 2.0.                   */
double tmpl_Double_Kaiser_Bessel_2_0(double x, double W)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;
    double numer, denom;

    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2)) for values inside the    *
     *  window. To determine if x falls inside the window we just need to     *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    const double c = 2.0*x/W;

    /*  Set the union part of the word to 1 - (2x/W)^2 and check the sign.    */
    w.r = 1.0 - c*c;

    /*  Negative means the input falls outside of the window. Return 0.       */
    if (w.bits.sign)
        return 0.0;

    /*  Otherwise x falls inside the window. Compute via the Pade approximant.*/
    numer = TMPL_PADE_HELPER(w.r, P);
    denom = TMPL_PADE_HELPER(w.r, Q);
    return numer / denom;
}
/*  End of tmpl_Double_Kaiser_Bessel_2_0.                                     */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_PADE_HELPER
#undef P0
#undef P1
#undef P2
#undef P3
#undef P4
#undef P5
#undef P6
#undef P7
#undef P8
#undef Q0
#undef Q1
#undef Q2
#undef Q3
#undef Q4
#undef Q5
#undef Q6
#undef Q7
#undef Q8

#endif
