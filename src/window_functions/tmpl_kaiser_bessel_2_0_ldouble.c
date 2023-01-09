#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_window_functions.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/*  (9, 9) Pade approximant.                                                  *
 *      Max Relative Error: 2E-18                                             *
 *      RMS Relative Error: 7E-19                                             *
 *          Actual error for 64-bit long double is less than 1 ULP.           */

/*  Coefficients of the numerator.                                            */
#define P00 (+1.147993453795864792123256251730288859461E-02)
#define P01 (+1.089790128371111321554374900397660538008E-01)
#define P02 (+2.377105794800031186134565326466905228847E-01)
#define P03 (+2.092636283774886203212152441457477172325E-01)
#define P04 (+9.257515648344964470757412174676463620137E-02)
#define P05 (+2.287912862416715797377369389546066335607E-02)
#define P06 (+3.309532224917444846997983825846377306060E-03)
#define P07 (+2.797860700165350538361382529918277822222E-04)
#define P08 (+1.290527907066360424942306464948584998564E-05)
#define P09 (+2.537011972925611522691331552438283809594E-07)

/*  Coefficients of the denominator.                                          */
#define Q00 (+1.000000000000000000000000000000000000000E+00)
#define Q01 (-3.766049003718496129020039336140441103214E-01)
#define Q02 (+7.128316873877182778240295206238813275886E-02)
#define Q03 (-8.963795068655300298779633628452570816671E-03)
#define Q04 (+8.318633930931961266076848105490873301205E-04)
#define Q05 (-5.961413170047543637842885985788132655307E-05)
#define Q06 (+3.332692590401286361374502373956321918915E-06)
#define Q07 (-1.417912095440724499980310056000438703332E-07)
#define Q08 (+4.222465742471958776777040882707095535238E-09)
#define Q09 (-6.812597858597641118443266860521373937274E-11)

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
                                A##08 + x*A##09\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  128-bit quadruple and 128-bit double-double. (14, 14) Pade approximant.   */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN    || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/*  (14, 14) Pade approximant.                                                *
 *      Max Relative Error: 1E-35                                             *
 *      RMS Relative Error: 5E-36                                             *
 *          Actual error for 128-bit quadruple is less than 1 ULP (~2E-34).   *
 *          Error for 128-bit double-double is roughly 2**-104 ~= 5E-32.      */

/*  Coefficients of the numerator.                                            */
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

/*  Coefficients of the denominator.                                          */
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

/*  80-bit and portable method. (10, 10) Pade approximant.                    */
#else

/*  (10, 10) Pade approximant.                                                *
 *      Max Relative Error: 7E-22                                             *
 *      RMS Relative Error: 2E-22                                             *
 *          Actual error for 80-bit long double is less than 1 ULP (~1E-19).  */

/*  Coefficients of the numerator.                                            */
#define P00 (+1.147993453795864792123256251730288859461E-02L)
#define P01 (+1.093970397537675388725484282860995214402E-01L)
#define P02 (+2.416858436077829524121716207096858143407E-01L)
#define P03 (+2.179850698735958472737011382153802805463E-01L)
#define P04 (+1.003358531250250675578947613439528440930E-01L)
#define P05 (+2.637013607516716014574176237088974114730E-02L)
#define P06 (+4.193021844618576132354365338846592278944E-03L)
#define P07 (+4.117381334535173988129294188477195546511E-04L)
#define P08 (+2.453423464988086942571685441005499298312E-05L)
#define P09 (+8.191872420781051053794685047347515701636E-07L)
#define P10 (+1.187528023028491674211132314950508868693E-08L)

/*  Coefficients of the denominator.                                          */
#define Q00 (+1.000000000000000000000000000000000000000E+00L)
#define Q01 (-3.401911982488808957271341639681001268467E-01L)
#define Q02 (+5.817367163071483807676519770830423213322E-02L)
#define Q03 (-6.622871483653638911102751745617244660588E-03L)
#define Q04 (+5.594346393036180272355591624054772718633E-04L)
#define Q05 (-3.689508161824235540076974574043483314974E-05L)
#define Q06 (+1.939177985664448966279799090866941677681E-06L)
#define Q07 (-8.091944028043149923802541058994831491357E-08L)
#define Q08 (+2.591618071434932244380621811665968697136E-09L)
#define Q09 (-5.819266537361917929946685087213711075394E-11L)
#define Q10 (+7.050277852983463994127995931411667942785E-13L)

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

#endif
/*  End of 80-bit extended and portable method.                               */

/*  Checking the sign bit is a bit faster than the portable method. We can    *
 *  get a slight performance boost this way.                                  */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  Long double precision Kaiser-Bessel window with alpha = 2 pi.             */
long double tmpl_LDouble_Kaiser_Bessel_2_0(long double x, long double W)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;
    long double numer, denom;

    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2))/I_0(2pi) for values      *
     *  inside the window. To determine if x falls in the window we need to   *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    const long double c = 2.0L*x/W;

    /*  Set the long double part to 1 - (2x/W)^2 and check the sign.          */
    w.r = 1.0L - c*c;

    /*  Negative means the input falls outside of the window. Return 0.       */
    if (TMPL_LDOUBLE_IS_NEGATIVE(w))
        return 0.0L;

    /*  Otherwise x falls inside the window. Compute via the Pade approximant.*/
    numer = TMPL_PADE_HELPER(w.r, P);
    denom = TMPL_PADE_HELPER(w.r, Q);
    return numer / denom;
}
/*  End of tmpl_LDouble_Kaiser_Bessel_2_0.                                    */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/*  long double precision Kaiser-Bessel window with alpha = 2 pi.             */
long double tmpl_LDouble_Kaiser_Bessel_2_0(long double x, long double W)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    long double numer, denom;

    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2)) for values inside the    *
     *  window. To determine if x falls inside the window we just need to     *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    const long double c = 2.0L*x/W;
    const long double arg = 1.0L - c*c;

    /*  Negative means the input falls outside of the window. Return 0.       */
    if (arg < 0.0L)
        return 0.0L;

    /*  Otherwise x falls inside the window. Compute via the Pade approximant.*/
    numer = TMPL_PADE_HELPER(arg, P);
    denom = TMPL_PADE_HELPER(arg, Q);
    return numer / denom;
}
/*  End of tmpl_LDouble_Kaiser_Bessel_2_0.                                    */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

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
#undef Q11
#undef Q12
#undef Q13
#undef Q14
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
#undef P11
#undef P12
#undef P13
#undef P14
