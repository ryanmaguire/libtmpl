/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EXP_REMEZ_LDOUBLE_H
#define TMPL_EXP_REMEZ_LDOUBLE_H

/*  TMPL_USE_INLINE found here                                                */
#include <libtmpl/include/tmpl_config.h>

/*  Only use this if inline support is requested.                             */
#if TMPL_USE_INLINE == 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Quadruple precision, degree 18 polynomial needed.                         */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN

/*  Coefficients for the numerator of the Remez polynomial.                   */
#define A00 (+9.9999999999999999999999999999999999868849386092390E-01L)
#define A01 (+1.0000000000000000000000000000000086685697149341608E+00L)
#define A02 (+5.0000000000000000000000000000000380030915600840191E-01L)
#define A03 (+1.6666666666666666666666666665834403474008130116099E-01L)
#define A04 (+4.1666666666666666666666666664827886322571356134050E-02L)
#define A05 (+8.3333333333333333333333356772076306441426109448022E-03L)
#define A06 (+1.3888888888888888888888892374942819275457122018355E-03L)
#define A07 (+1.9841269841269841269811265518547928820794649065081E-04L)
#define A08 (+2.4801587301587301587267731157133410708309374359698E-05L)
#define A09 (+2.7557319223985890860605207405982456235594197166903E-06L)
#define A10 (+2.7557319223985890842859392870041655579861441391222E-07L)
#define A11 (+2.5052108385440871386418610170675812085330239974488E-08L)
#define A12 (+2.0876756987867443389349290373345976373205115580230E-09L)
#define A13 (+1.6059043838907628969669125371971810824023489639807E-10L)
#define A14 (+1.1470745599135941848313611002606890813376439765698E-11L)
#define A15 (+7.6471606801654702422671617516672873377277699008062E-13L)
#define A16 (+4.7794754998284789128713986912613186334005182452969E-14L)
#define A17 (+2.8138985011864086532272191512191663692824756446880E-15L)
#define A18 (+1.5632492304954196039852719020242720044725438377851E-16L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*(\
                                A08 + z*(\
                                    A09 + z*(\
                                        A10 + z*(\
                                            A11 + z*(\
                                                A12 + z*(\
                                                    A13 + z*(\
                                                        A14 + z*(\
                                                            A15 + z*(\
                                                                A16 + z*(\
                                                                    A17 + z*A18\
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
                )\
            )\
        )\
    )\
)

/*  Double-double precision. Degree 17 polynomial needed.                     */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/*  Coefficients for the numerator of the Remez polynomial.                   */
#define A00 (+1.0000000000000000000000000000000173369134497438089E+00L)
#define A01 (+1.0000000000000000000000000000000151750210079099247E+00L)
#define A02 (+4.9999999999999999999999999995505809672498704832771E-01L)
#define A03 (+1.6666666666666666666666666665345335269216821031469E-01L)
#define A04 (+4.1666666666666666666666685843792082538761805409314E-02L)
#define A05 (+8.3333333333333333333333367489267110093801595846620E-03L)
#define A06 (+1.3888888888888888888857384233064273346024343175878E-03L)
#define A07 (+1.9841269841269841269800726333192100502919067942989E-04L)
#define A08 (+2.4801587301587301846563485295724858910393367965626E-05L)
#define A09 (+2.7557319223985890915538229903170582765704332837934E-06L)
#define A10 (+2.7557319223984692187376935202596927759360442030304E-07L)
#define A11 (+2.5052108385440709049804007755645522828465392463082E-08L)
#define A12 (+2.0876756991122335380503946124630578718402148669067E-09L)
#define A13 (+1.6059043839180694042044828881686239916114730177547E-10L)
#define A14 (+1.1470740447966829139279959537194957254830680054602E-11L)
#define A15 (+7.6471604365902252885210236629795004640368847212391E-13L)
#define A16 (+4.7838716512081484784088754484685088724097376252253E-14L)
#define A17 (+2.8139879090984274933284818617769640742216104448431E-15L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*(\
                                A08 + z*(\
                                    A09 + z*(\
                                        A10 + z*(\
                                            A11 + z*(\
                                                A12 + z*(\
                                                    A13 + z*(\
                                                        A14 + z*(\
                                                            A15 + z*(\
                                                                A16 + z*A17\
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
            )\
        )\
    )\
)

/*  Double precision, 10 terms needed.                                        */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN || \
      TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN

/*  Coefficients for the numerator of the Remez polynomial.                   */
#define A00 (+9.9999999999999999988430264938382617864875775206464E-01L)
#define A01 (+1.0000000000000002567155499064945764299110332942888E+00L)
#define A02 (+5.0000000000000011303128565037818364883412745825979E-01L)
#define A03 (+1.6666666666658450641538834111096804338714833792536E-01L)
#define A04 (+4.1666666666648208299845851261960139340509395965848E-02L)
#define A05 (+8.3333333406957231917106078391264123789847252849529E-03L)
#define A06 (+1.3888888900173203766146657738825963558824828302470E-03L)
#define A07 (+1.9841242914202268899999786488562084101590255844480E-04L)
#define A08 (+2.4801555544629532354737090416957032661760944182686E-05L)
#define A09 (+2.7600400233476040774827464572558357184830459675937E-06L)
#define A10 (+2.7599120100813904758992842016718714757809673113599E-07L)

/*  Helper macro for evaluating the polynomial via Horner's method.           */
#define TMPL_POLY_HELPER(z) \
A00 + x*(\
    A01 + x*(\
        A02 + x*(\
            A03 + x*(\
                A04 + x*(\
                    A05 + x*(\
                        A06 + x*(\
                            A07 + x*(\
                                A08 + x*(\
                                    A09 + x*A10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Lastly, extended precision and portable. 11 degree polynomial used.       */
#else

/*  Coefficients for the numerator of the Remez polynomial.                   */
#define A00 (+9.9999999999999999993920367738695082919354056255325E-01L)
#define A01 (+9.9999999999999999994534063680501661238470536228375E-01L)
#define A02 (+5.0000000000000007004118329780582433831808957458304E-01L)
#define A03 (+1.6666666666666668797182608870038372788124260838280E-01L)
#define A04 (+4.1666666666653591768899367566223269175264058197314E-02L)
#define A05 (+8.3333333333309083035568304537039880951695803197881E-03L)
#define A06 (+1.3888888897814860033632954284984357774990859811499E-03L)
#define A07 (+1.9841269853300970089116999397099545752789319875931E-04L)
#define A08 (+2.4801559759254460349914793449686278224752779679557E-05L)
#define A09 (+2.7557289814747593675619298528608142392024798269836E-06L)
#define A10 (+2.7596485342096270864781635128680294512610172204021E-07L)
#define A11 (+2.5086995810396568966660042977322370705119942180205E-08L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*(\
                                A08 + z*(\
                                    A09 + z*(\
                                        A10 + z*A11\
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

#endif
/*  End of quadruple vs. double-double vs. double vs. extended / portable.    */

/*  Function for computing exp(x) for -1/4 < x < 1/4 using minimax polynomial.*/
TMPL_INLINE_DECL
long double tmpl_LDouble_Exp_Remez(long double x)
{
    return TMPL_POLY_EVAL(x);
}
/*  End of tmpl_LDouble_Exp_Remez.                                            */

/*  Undefine everything in case someone wants to #include this file.          */
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef A09
#undef A10
#undef A11
#undef A12
#undef A13
#undef A14
#undef A15
#undef A16
#undef A17
#undef A18
#undef TMPL_POLY_EVAL

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
