/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                         tmpl_erf_asymptotic_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the error function for larger values at double precision.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Erf_Asymptotic                                            *
 *  Purpose:                                                                  *
 *      Computes the Error function erf(x) for x >= 2.                        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A positive real number.                                           *
 *  Output:                                                                   *
 *      erf_x (double):                                                       *
 *          The error function at x.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method (Current):                                                         *
 *      Use two Remez Minimax polynomials, one on [2, 4], and the other on    *
 *      [4, 6]. For x > 6, return 1 since |1 - Erf(x)| < 2^-52.               *
 *      The coefficients for the minimax polynomials were precomputed using   *
 *      the Remez exchange algorithm.                                         *
 *  Method (Alternative):                                                     *
 *      Use two rational minimax functions, one on [2, 4] and the other on    *
 *      [4, 6]. The orders are (9, 8) and (7, 6), respectively. This is about *
 *      twice as fast as the minimax polynomials. Theoretical error is below  *
 *      double precision (less than 10^-16) but floating point roundoff       *
 *      errors in the computation yield max errors of 10^-15 on [2, 4] and    *
 *      10^-13 on [4, 6]. RMS error is much better, ~4x10^-16. Nevertheless   *
 *      if extremely accurate computations are needed do not use this method. *
 *  Method (Old):                                                             *
 *      For arguments greater than 6 we can return erf(x) = 1. Otherwise      *
 *      compute using a Chebyshev approximation on the interval [2, 6].       *
 *      The function:                                                         *
 *                                                                            *
 *              x - 4                                                         *
 *          y = ------                                                        *
 *                2                                                           *
 *                                                                            *
 *      Transforms the interval [2, 6] to [-1, 1]. We then compute the        *
 *      Chebyshev coefficients for the function:                              *
 *                                                                            *
 *          f(x) = erf(y)                                                     *
 *                                                                            *
 *      We can accurately compute f(x) using a degree 28 Chebyshev expansion: *
 *                                                                            *
 *                  28                                                        *
 *                 -----                                                      *
 *                 \                                                          *
 *          f(x) = /     c_n T_n(x)                                           *
 *                 -----                                                      *
 *                 n = 0                                                      *
 *                                                                            *
 *      where c_n are the coefficients and T_n is the nth Chebyshev           *
 *      polynomial. We further simplify this into a proper polynomial form    *
 *      by expanding the Chebyshev polynomials.                               *
 *                                                                            *
 *                             --                   --                        *
 *                  28        |    n                  |                       *
 *                 -----      |  -----                |                       *
 *                 \          |  \                    |                       *
 *          f(x) = /      c_n |  /      t_{k, n} x^k  |                       *
 *                 -----      |  -----                |                       *
 *                 n = 0      |  k = 0                |                       *
 *                             --                   --                        *
 *                                                                            *
 *      where t_{k, n} is the kth coefficients of the nth Chebyshev           *
 *      polynomial. By collecting all of the terms together we get:           *
 *                                                                            *
 *                  28                                                        *
 *                 -----                                                      *
 *                 \                                                          *
 *          f(x) = /     a_n x^n                                              *
 *                 -----                                                      *
 *                 n = 0                                                      *
 *                                                                            *
 *      where the a_n are computed from c_n and t_{k, n} via a Cauchy product.*
 *      This is evaluated by Horner's method, which is faster than Clenshaw's *
 *      algorithm for Chebyshev polynomials in their usual form.              *
 *  Notes:                                                                    *
 *      Accurate for x >= 2.                                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2023                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_ASYMPTOTIC_DOUBLE_H
#define TMPL_ERF_ASYMPTOTIC_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

#include <libtmpl/include/tmpl_math.h>

/*  With IEEE-754 support we can use a switch-trick to double the performance.*/
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Coefficients for the Remez polynomial for Erf on [2, 2.5].                */
#define P000 (+9.9853728341331885122917049163048561164071612143256E-01)
#define P001 (+7.1423190220182551212639592571545453534409310185057E-03)
#define P002 (-1.6070217799544499375749681878385412130461324864096E-02)
#define P003 (+2.1724553691848123484559446741931650749320609820280E-02)
#define P004 (-1.9083383636029665626388678675899106786912669285060E-02)
#define P005 (+1.0657679181541277097330847349642305238766047557653E-02)
#define P006 (-2.9043571515295761913149210463157628004300500688630E-03)
#define P007 (-6.7045684210182447361233109790249938460067974648627E-04)
#define P008 (+9.9949708347555551712978749627502335336796459803359E-04)
#define P009 (-3.6935727415108647200579303917701509950420786490064E-04)
#define P010 (-1.1539736718627222791947754786629603849538237347908E-05)
#define P011 (+6.4844129322404749029706341545510470582290000286178E-05)
#define P012 (-2.1894411428366273657419057866807365805957172479599E-05)

/*  Coefficients for the Remez polynomial for Erf on [2.5, 3].                */
#define P100 (+9.9989937807788039773943230740580948402586993282533E-01)
#define P101 (+5.8627724709288510487639134704333605218589654673250E-04)
#define P102 (-1.6122624295482425426304601750093559507647212938844E-03)
#define P103 (+2.7603887054235208922187015740027856748423601087818E-03)
#define P104 (-3.2581136520601992659920616155360778326984288841911E-03)
#define P105 (+2.7558083732457483020077876686722456228005898633149E-03)
#define P106 (-1.6573279206213689173398469279229336075066504603200E-03)
#define P107 (+6.4604298582199359342942355389533824474815088559908E-04)
#define P108 (-8.8995738552911916607140022002464813003860492032919E-05)
#define P109 (-7.1272678135500073303826809202164960992348502289215E-05)
#define P110 (+5.4777156882263340978770021622040500192003276479264E-05)
#define P111 (-1.5257484938233752477773286853489458461321735575630E-05)

/*  Coefficients for the Remez polynomial for Erf on [3, 3.5].                */
#define P200 (+9.9999569722053626957864703926955653072792111165044E-01)
#define P201 (+2.9189025383770338707620156424961017118408025567378E-05)
#define P202 (-9.4864332432900072999698943062667595423041150635053E-05)
#define P203 (+1.9580971187473420429638691406381813188079734919573E-04)
#define P204 (-2.8656934965381843365066550677883507768250335956211E-04)
#define P205 (+3.1379723382979700033926833020726486185166480414035E-04)
#define P206 (-2.6352769128894339114442472765483397006883506067932E-04)
#define P207 (+1.6999100251263728824659988597178758000620848570200E-04)
#define P208 (-8.1672723600307529679031004533150304918005203217527E-05)
#define P209 (+2.5923868424212381256693135633307154628060970739941E-05)
#define P210 (-1.9718785781558686676798501526036408892028792767577E-06)
#define P211 (-2.9827176694095196134711117250213384965033235972170E-06)

/*  Coefficients for the Remez polynomial for Erf on [3.5, 4].                */
#define P300 (+9.9999988627274343253356551538774082813127489225062E-01)
#define P301 (+8.8143219125234271870080846925274230542344460932361E-07)
#define P302 (-3.3053707198253979852183694651385735847848482549661E-06)
#define P303 (+7.9696160543435196502233058816783242848520522699009E-06)
#define P304 (-1.3841239368803963902660192649649020716989763531639E-05)
#define P305 (+1.8370975914818732032856067262807646176858974326086E-05)
#define P306 (-1.9272756518979244337015225778661174725653000107335E-05)
#define P307 (+1.6275257365804144889354146983604872664066753515367E-05)
#define P308 (-1.1127131642251367709095658594427019516626727283995E-05)
#define P309 (+6.1099830497210315365686437232690420729350622645852E-06)
#define P310 (-2.6192389213319816747876472629098661358128134237123E-06)
#define P311 (+7.6243896060223080058526708385726241059551019298625E-07)

/*  Coefficients for the Remez polynomial for Erf on [4, 4.5].                */
#define P400 (+9.9999999814942586593606361611445131768218026025321E-01)
#define P401 (+1.6143995161114304743062572768179453264188622455552E-08)
#define P402 (-6.8611976549508848991288015161583412291090846635137E-08)
#define P403 (+1.8901879873542089635602398005957728736134968033244E-07)
#define P404 (-3.7879474275583309329909055096105158877575975708691E-07)
#define P405 (+5.8728744824523232944682260689708461419316158739311E-07)
#define P406 (-7.3095191364207481457314542475848939638520417630463E-07)
#define P407 (+7.4621894285100202841578132616109155463598772225848E-07)
#define P408 (-6.3694616784748210497593872699946034632487684702494E-07)
#define P409 (+4.8100430292123512706733557636000623587835436930718E-07)
#define P410 (-2.8652969948032422896948003854371567993509710279951E-07)

/*  Coefficients for the Remez polynomial for Erf on [4.5, 5].                */
#define P500 (+9.9999999998151492923599855833197345269503530222873E-01)
#define P501 (+1.7934371855502848735974345710054251774935331607893E-10)
#define P502 (-8.5186356004089592622887530601694252323961998368097E-10)
#define P503 (+2.6378047978654265486494933007797128532518319659139E-09)
#define P504 (-5.9832688099679586312292522487056289582798553473565E-09)
#define P505 (+1.0575533835256321140407182840892048536696801380740E-08)
#define P506 (-1.5040140473477141962910120232547198488669786549004E-08)
#define P507 (+1.7934642740598449624250135951332135318651467897185E-08)
#define P508 (-2.0062670512208084629162182356873884123115858869315E-08)
#define P509 (+1.7130931819877410358405197183616916743129781348922E-08)

/*  Coefficients for the Remez polynomial for Erf on [5, 5.5].                */
#define P600 (+9.9999999999988693380861989837696532177328737896535E-01)
#define P601 (+1.2081133405529725316352314517408122004343280361457E-12)
#define P602 (-6.3629344845528682696353532035754542281562253402972E-12)
#define P603 (+2.1853072284687390840090703649707145333163449785406E-11)
#define P604 (-5.3628357483333772603925260714769551826237400310448E-11)
#define P605 (+1.0668983967979651399045356137204522355231743941992E-10)
#define P606 (-2.1354533241912177833879484470727804205014376820730E-10)
#define P607 (+2.8474369150597829596454084804722261286134811281892E-10)

/*  Coefficients for the Remez polynomial for Erf on [5.5, 6].                */
#define P700 (+9.9999999999999955387850795076520886363002512443239E-01)
#define P701 (+3.9340427279773976530011305330744974291684882874340E-15)
#define P702 (-2.3763600089489119124602536211619222230546842706339E-14)
#define P703 (+1.6823275229079022610382212627661663901978300514574E-13)
#define P704 (-4.5019575287861106347929033568853260439899192451307E-13)

/*  Helper macro for evaluating the zeroth polynomial via Horner's method.    */
#define TMPL_POLY0_EVAL(z) \
P000 + z*(\
    P001 + z*(\
        P002 + z*(\
            P003 + z*(\
                P004 + z*(\
                    P005 + z*(\
                        P006 + z*(\
                            P007 + z*(\
                                P008 + z*(\
                                    P009 + z*(\
                                        P010 + z*(\
                                            P011 + z*P012\
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

/*  Helper macro for evaluating the first polynomial via Horner's method.     */
#define TMPL_POLY1_EVAL(z) \
P100 + z*(\
    P101 + z*(\
        P102 + z*(\
            P103 + z*(\
                P104 + z*(\
                    P105 + z*(\
                        P106 + z*(\
                            P107 + z*(\
                                P108 + z*(\
                                    P109 + z*(\
                                        P110 + z*P111\
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

/*  Helper macro for evaluating the second polynomial via Horner's method.    */
#define TMPL_POLY2_EVAL(z) \
P200 + z*(\
    P201 + z*(\
        P202 + z*(\
            P203 + z*(\
                P204 + z*(\
                    P205 + z*(\
                        P206 + z*(\
                            P207 + z*(\
                                P208 + z*(\
                                    P209 + z*(\
                                        P210 + z*P211\
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

/*  Helper macro for evaluating the third polynomial via Horner's method.     */
#define TMPL_POLY3_EVAL(z) \
P300 + z*(\
    P301 + z*(\
        P302 + z*(\
            P303 + z*(\
                P304 + z*(\
                    P305 + z*(\
                        P306 + z*(\
                            P307 + z*(\
                                P308 + z*(\
                                    P309 + z*(\
                                        P310 + z*P311\
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

/*  Helper macro for evaluating the fourth polynomial via Horner's method.    */
#define TMPL_POLY4_EVAL(z) \
P400 + z*(\
    P401 + z*(\
        P402 + z*(\
            P403 + z*(\
                P404 + z*(\
                    P405 + z*(\
                        P406 + z*(\
                            P407 + z*(\
                                P408 + z*(\
                                    P409 + z*P410\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Helper macro for evaluating the fifth polynomial via Horner's method.     */
#define TMPL_POLY5_EVAL(z) P500 + \
z*(P501+z*(P502+z*(P503+z*(P504+z*(P505+z*(P506+z*(P507+z*(P508+z*P509))))))))

/*  Helper macro for evaluating the sixth polynomial via Horner's method.     */
#define TMPL_POLY6_EVAL(z) \
P600 + z*(P601 + z*(P602 + z*(P603 + z*(P604 + z*(P605 + z*(P606 + z*P607))))))

/*  Helper macro for evaluating the seventh polynomial via Horner's method.   */
#define TMPL_POLY7_EVAL(z) P700 + z*(P701 + z*(P702 + z*(P703 + z*P704)))

/*  Function for computing Erf(x) for x >= 2 at double precision.             */
TMPL_STATIC_INLINE
double tmpl_Double_Erf_Asymptotic(double x)
{
    /*  64-bit word used for type punning.                                    */
    tmpl_IEEE754_Double w;

    /*  Integer used as a switch for the range of x.                          */
    unsigned int n;

    /*  Input variable for the polynomial approximations.                     */
    double z;

    /*  Set the word to the input double.                                     */
    w.r = x;

    /*  For x > 8 we have |erf(x) - 1| < 2^-96, way beyond double precision.  *
     *  We can safely return 1 for this range.                                */
    if (w.bits.expo > TMPL_DOUBLE_UBIAS + 2U)
        return 1.0;

    /*  The polynomials are in intervals of 0.5. That is, the first window is *
     *  2 <= x < 2.5, the second is 2.5 <= x < 3, and so on up to x = 6. We   *
     *  can determine the appropriate window by examining the largest bit     *
     *  past the binary point and the integer part. To get this we shift by   *
     *  549755813886, which is 2^39 - 2 = 2^(51 - 12) - 2. By adding this     *
     *  number and then bit-shifting by twelve, the resulting integer can be  *
     *  used as a switch for the correct window. Rounding in this sum may     *
     *  cause values that are roughly 2^-12 away from the border of these     *
     *  windows (i.e., 2.5, 3.0, etc.) to recieve a switch that is off by     *
     *  1. To account for this the Remez polynomials are computed with ranges *
     *  that overlap slightly, meaning we will still correctly compute the    *
     *  error function for these values.                                      */
    w.r += 549755813886.0;

    /*  The integer and halves place are now the 13th and 14th bits. Shift by *
     *  12 to obtain them.                                                    */
    n = w.bits.man3 >> 12;

    /*  We can now use this integer to select the correct window.             */
    switch(n)
    {
        /*  Remez polynomial on the interval [2, 2.5].                        */
        case 0:
            z = x - 2.25;
            return TMPL_POLY0_EVAL(z);

        /*  Remez polynomial on the interval [2.5, 3].                        */
        case 1:
            z = x - 2.75;
            return TMPL_POLY1_EVAL(z);

        /*  Remez polynomial on the interval [3, 3.5].                        */
        case 2:
            z = x - 3.25;
            return TMPL_POLY2_EVAL(z);

        /*  Remez polynomial on the interval [3.5, 4].                        */
        case 3:
            z = x - 3.75;
            return TMPL_POLY3_EVAL(z);

        /*  Remez polynomial on the interval [4, 4.5].                        */
        case 4:
            z = x - 4.25;
            return TMPL_POLY4_EVAL(z);

        /*  Remez polynomial on the interval [4.5, 5].                        */
        case 5:
            z = x - 4.75;
            return TMPL_POLY5_EVAL(z);

        /*  Remez polynomial on the interval [5, 5.5].                        */
        case 6:
            z = x - 5.25;
            return TMPL_POLY6_EVAL(z);

        /*  Remez polynomial on the interval [5, 5.5].                        */
        case 7:
            z = x - 5.75;
            return TMPL_POLY7_EVAL(z);

        /*  For the remaining values, which fall between 6 and 8, we have     *
         *  |erf(x) - 1| < 2^-52 and can safely return 1.                     */
        default:
            return 1.0;
    }
    /*  End of switch for "n".                                                */
}
/*  End of tmpl_Double_Erf_Asymptotic.                                        */

/*  Undefine everything in case someone wants to #include this file.          */
#undef P000
#undef P001
#undef P002
#undef P003
#undef P004
#undef P005
#undef P006
#undef P007
#undef P008
#undef P009
#undef P010
#undef P011
#undef P012
#undef P100
#undef P101
#undef P102
#undef P103
#undef P104
#undef P105
#undef P106
#undef P107
#undef P108
#undef P109
#undef P110
#undef P111
#undef P200
#undef P201
#undef P202
#undef P203
#undef P204
#undef P205
#undef P206
#undef P207
#undef P208
#undef P209
#undef P210
#undef P211
#undef P300
#undef P301
#undef P302
#undef P303
#undef P304
#undef P305
#undef P306
#undef P307
#undef P308
#undef P309
#undef P310
#undef P311
#undef P400
#undef P401
#undef P402
#undef P403
#undef P404
#undef P405
#undef P406
#undef P407
#undef P408
#undef P409
#undef P410
#undef P500
#undef P501
#undef P502
#undef P503
#undef P504
#undef P505
#undef P506
#undef P507
#undef P508
#undef P509
#undef P600
#undef P601
#undef P602
#undef P603
#undef P604
#undef P605
#undef P606
#undef P607
#undef P700
#undef P701
#undef P702
#undef P703
#undef P704
#undef TMPL_POLY0_EVAL
#undef TMPL_POLY1_EVAL
#undef TMPL_POLY2_EVAL
#undef TMPL_POLY3_EVAL
#undef TMPL_POLY4_EVAL
#undef TMPL_POLY5_EVAL
#undef TMPL_POLY6_EVAL
#undef TMPL_POLY7_EVAL

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *  Three implementations provided for larger inputs (2 <= x < infty).        *
 *      Method 0                                                              *
 *          Two rational Remez approximations on [2, 4] and [4, 6].           *
 *      Method 1                                                              *
 *          Two Remez polynomials on [2, 4] and [4, 6].                       *
 *      Method 2                                                              *
 *          One Chebyshev expansion on [2, 6].                                *
 *  All methods return 1 for x >= 6 since to double precision Erf(x) = 1.     *
 *  Method 0 is faster than method 1 which is faster than method 2. Method 0  *
 *  has floating point roundoff problems that cause the peak relative error   *
 *  to be 2x10^-15 (rms relative error is 2x10^-16) on [2, 4] and 2x10^-13 on *
 *  [4, 6] (rms relative error 5x10^-16). Method 1, the Remez polynomial,     *
 *  does not suffer from such problems but is slower. Method 2 is accurate,   *
 *  but very slow. It should be avoided.                                      *
 ******************************************************************************/
#ifndef TMPL_ERF_IMPLEMENTATION

/*  Default implementation is Remez polynomial. Fast and accurate.            */
#define TMPL_ERF_IMPLEMENTATION 1
#endif

/*  Fastest method, use rational Remez approximations.                        */
#if TMPL_ERF_IMPLEMENTATION == 0

/******************************************************************************
 *  Order (9, 8) rational Remez approximation for Erf(x + 3) on the interval  *
 *  [-1, 1]. Max theoretical error is ~2 x 10^-16. Floating point roundoff    *
 *  causes max rel error to be ~2x10^-15 and rms rel error to be ~3x10^-16.   *
 *                                                                            *
 *  Evaluation is 2x faster than the Remez polynomial provided below.         *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+9.9997790950300169390152237217075747091064215681192E-01)
#define A01 (+1.7234800569210478799713938740116442220025728190736E+00)
#define A02 (+1.6571262106630805739284908883503957932178261795696E+00)
#define A03 (+1.0611869960214990335604167233665094115325112772575E+00)
#define A04 (+4.8806545626286922731045426616367239533990998352380E-01)
#define A05 (+1.6268299758105545838363230973036563492617716692450E-01)
#define A06 (+3.7952659706696277584080960343545345763817333308860E-02)
#define A07 (+5.6748733825276711037533989251955170958449685299198E-03)
#define A08 (+4.0768676489485271290111775890624532067677979875267E-04)
#define A09 (+2.7293766510316760485071859880275192918130563678553E-07)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+1.7233788741649484765705923559579218588657314457128E+00)
#define B02 (+1.6573405955285319991774924881409973310426686159853E+00)
#define B03 (+1.0609104990016522014236956648888133636057243445752E+00)
#define B04 (+4.8830535589108475438405439801471184465252734249320E-01)
#define B05 (+1.6253733264945687666150457216286895715074169045606E-01)
#define B06 (+3.8014762648461803562598720981877677025203850014829E-02)
#define B07 (+5.6568846094112022427885434860640397915217150799567E-03)
#define B08 (+4.1090985964304809709526192219722212708060633515958E-04)

/******************************************************************************
 *  Order (7, 6) rational Remez approximation for Erf(x + 5) on the interval  *
 *  [-1, 1]. Max theoretical error is ~1.2 x 10^-16. Floating point roundoff  *
 *  causes max rel error to be ~2x10^-13 and rms rel error to be ~5x10^-16.   *
 *                                                                            *
 *  Evaluation is 2x faster than the Remez polynomial provided below.         *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define C00 (+9.9999999999846245843490813330267815315827054559597E-01)
#define C01 (+3.4872176345954420572057191295826138028833080897642E+00)
#define C02 (+5.4474082276580598104238260423325675822385551693589E+00)
#define C03 (+4.8532656988750981998795007760926308089883113538506E+00)
#define C04 (+2.5864866905062084726007117044876386581512674936172E+00)
#define C05 (+7.7724608649724151872063265312066900065031942673881E-01)
#define C06 (+1.0227741279265197848826482600801971915526292908129E-01)
#define C07 (+7.5407643928860718504587877942281862217448235394393E-12)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define D01 (+3.4872176345851319136524776147629056313426834006256E+00)
#define D02 (+5.4474082276901317756438332688381554415929177412466E+00)
#define D03 (+4.8532656988144795807430549549595277954781072205889E+00)
#define D04 (+2.5864866905822989611040119062264342279370416615467E+00)
#define D05 (+7.7724608643354065261206413654496098927187275137234E-01)
#define D06 (+1.0227741282512070731986948900216375850892657569066E-01)

/*  Horner's method for the numerator of the first rational Remez function.   */
#define TMPL_NUM_A_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*(\
                                A08 + z*A09\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Horner's method for the denominator of the first rational Remez function. */
#define TMPL_DEN_A_EVAL(z) \
B00 + z*(\
    B01 + z*(\
        B02 + z*(\
            B03 + z*(\
                B04 + z*(\
                    B05 + z*(\
                        B06 + z*(\
                            B07 + z*B08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Horner's method for the numerator of the second rational Remez function.  */
#define TMPL_NUM_B_EVAL(z) \
C00 + z*(\
    C01 + z*(\
        C02 + z*(\
            C03 + z*(\
                C04 + z*(\
                    C05 + z*(\
                        C06 + z*C07\
                    )\
                )\
            )\
        )\
    )\
)

/*  Horner's method for the denominator of the second rational Remez function.*/
#define TMPL_DEN_B_EVAL(z) \
D00 + z*(\
    D01 + z*(\
        D02 + z*(\
            D03 + z*(\
                D04 + z*(\
                    D05 + z*D06\
                )\
            )\
        )\
    )\
)

/*  Function for computing erf(x) for x >= 2.                                 */
TMPL_STATIC_INLINE
double tmpl_Double_Erf_Asymptotic(double x)
{
    /*  For x >= 6 we have |1 - erf(x)| < 2^-52, double epsilon. Return 1.    */
    if (x >= 6.0)
        return 1.0;

    /*  For values in [2, 4] use the first rational function.                 */
    else if (x < 4.0)
    {
        /*  Shift the interval [2, 4] to [-1, 1] for the rational function.   */
        const double z = x - 3.0;
        const double num = TMPL_NUM_A_EVAL(z);
        const double den = TMPL_DEN_A_EVAL(z);
        return num / den;
    }

    /*  Lastly, use the second Minimax function for arguments in [4, 6].      */
    else
    {
        /*  Shift the interval [4, 6] to [-1, 1] for the rational function.   */
        const double z = x - 5.0;
        const double num = TMPL_NUM_B_EVAL(z);
        const double den = TMPL_DEN_B_EVAL(z);
        return num / den;
    }
}
/*  End of tmpl_Double_Erf_Asymptotic.                                        */

/*  Undefine coefficients for the numerator of the first function.            */
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

/*  Undefine coefficients for the denominator of the first function.          */
#undef B00
#undef B01
#undef B02
#undef B03
#undef B04
#undef B05
#undef B06
#undef B07
#undef B08

/*  Undefine coefficients for the numerator of the second function.           */
#undef C00
#undef C01
#undef C02
#undef C03
#undef C04
#undef C05
#undef C06
#undef C07

/*  Undefine coefficients for the denominator of the second function.         */
#undef D00
#undef D01
#undef D02
#undef D03
#undef D04
#undef D05
#undef D06

/*  Lastly, undefine the polynomial helper functions.                         */
#undef TMPL_NUM_A_EVAL
#undef TMPL_DEN_A_EVAL
#undef TMPL_NUM_B_EVAL
#undef TMPL_DEN_B_EVAL

/*  Second method. Higher precision for 64-bit double, but slower.            */
#elif TMPL_ERF_IMPLEMENTATION == 1

/*  Coefficients for the Remez polynomial on [2, 4].                          */
#define A00 (+9.9997790950300142278863355722471061050296451720368E-01)
#define A01 (+1.3925305194477978730091759557886507181169650303288E-04)
#define A02 (-4.1775915584207907505222445864222490037050981433966E-04)
#define A03 (+7.8910062784410584553246307831070049442409725578151E-04)
#define A04 (-1.0443978895327628690880939985809113179018372962513E-03)
#define A05 (+1.0165472760251672627243542892882602250136363898749E-03)
#define A06 (-7.3804117629715295141754417612504429566347271247447E-04)
#define A07 (+3.9057168717017588025084699611985071354171021176972E-04)
#define A08 (-1.3477705374397264294968082173818833018477350223250E-04)
#define A09 (+1.3906709036090407091477497759100032047956244447314E-05)
#define A10 (+1.5616203922585888663540870481575411491315014701930E-05)
#define A11 (-1.0793030925416155155118496283437255220094175737574E-05)
#define A12 (+3.0307961131322541818630402774496836693087589462673E-06)
#define A13 (+1.2215287848578559299889106663173461753007805591752E-07)
#define A14 (-4.5267407595312274124698016023302783433887188558728E-07)
#define A15 (+1.6738764602973046014420230239829010634044316939035E-07)
#define A16 (-9.2100271357752928721700846567656218283477300552198E-09)
#define A17 (-1.6356949876238991597057015261353570360825712700624E-08)
#define A18 (+5.8849980272257660299305851500710617296276568007381E-09)
#define A19 (+2.7722504490166683723484100155202778056570970412414E-10)
#define A20 (-4.2766869676693656764337765033494236327562251157342E-10)
#define A21 (-9.3585224180218124838580975657053993780830761255308E-17)

/*  Coefficients for the Remez polynomial on [4, 6].                          */
#define B00 (+9.9999999999846253878003766209229860153027413505968E-01)
#define B01 (+1.5669414601047508105034356488856799019723219194232E-11)
#define B02 (-7.8354120572362028855259218050569644495176661941769E-11)
#define B03 (+2.5602789237298586068228569174150574163643806687536E-10)
#define B04 (-6.1378118432240642108701556179142980815344222593979E-10)
#define B05 (+1.1497675468731696554242475220206601206941271508726E-09)
#define B06 (-1.7542063096402679204007895889148974890443044386928E-09)
#define B07 (+2.2384442509863376661386954823407723418439390834336E-09)
#define B08 (-2.4145584534091353910479795903445084586094588093661E-09)
#define B09 (+2.2269869488637954043246869826785887322129003452326E-09)
#define B10 (-1.8180869221228204197072724793592631382302212363175E-09)
#define B11 (+1.3273056965393187548377885707715818863521483014437E-09)
#define B12 (-7.9840602204922956108616064844948911059243536529766E-10)
#define B13 (+3.8510168290197499805134022322023742472984779136291E-10)
#define B14 (-1.9964116110595372426997271310974766471990044036930E-10)
#define B15 (+1.0932541980472673355111017027104272274202791021403E-10)
#define B16 (-3.0057327905735070477046851950492000985362338758821E-11)
#define B17 (-8.4988789396205286436910679623143481902548138695499E-17)

/*  Helper macro for evaluating the polynomial on [2, 4] via Horner's method. */
#define TMPL_POLYA_EVAL(z) \
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
                                  A17 + z*(\
                                    A18 + z*(\
                                      A19 + z*(\
                                        A20 + z*A21\
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
      )\
    )\
  )\
)

/*  Helper macro for evaluating the polynomial on [4, 6] via Horner's method. */
#define TMPL_POLYB_EVAL(z) \
B00 + z*(\
  B01 + z*(\
    B02 + z*(\
      B03 + z*(\
        B04 + z*(\
          B05 + z*(\
            B06 + z*(\
              B07 + z*(\
                B08 + z*(\
                  B09 + z*(\
                    B10 + z*(\
                      B11 + z*(\
                        B12 + z*(\
                          B13 + z*(\
                            B14 + z*(\
                              B15 + z*(\
                                B16 + z*B17\
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

/*  Function for computing erf(x) for x >= 2.                                 */
TMPL_STATIC_INLINE
double tmpl_Double_Erf_Asymptotic(double x)
{
    /*  For x >= 6 we have |1 - erf(x)| < 2^-52, double epsilon. Return 1.    */
    if (x >= 6.0)
        return 1.0;

    /*  For values in [2, 4] use the first polynomial.                        */
    else if (x < 4.0)
    {
        /*  Shift the interval [2, 4] to [-1, 1] for the polynomial.          */
        const double z = x - 3.0;
        return TMPL_POLYA_EVAL(z);
    }

    /*  Lastly, use the second Remez polynomial for arguments in [4, 6].      */
    else
    {
        /*  Shift the interval [4, 6] to [-1, 1] for the polynomial.          */
        const double z = x - 5.0;
        return TMPL_POLYB_EVAL(z);
    }
}
/*  End of tmpl_Double_Erf_Asymptotic.                                        */

/*  #undef everything in case someone wants to #include this file.            */
#undef TMPL_POLYA_EVAL
#undef TMPL_POLYB_EVAL
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
#undef A10
#undef A11
#undef A12
#undef A13
#undef A14
#undef A15
#undef A16
#undef A17
#undef A18
#undef A19
#undef A20
#undef A21
#undef B00
#undef B01
#undef B02
#undef B03
#undef B04
#undef B05
#undef B06
#undef B07
#undef B08
#undef B09
#undef B10
#undef B11
#undef B12
#undef B13
#undef B14
#undef B15
#undef B16
#undef B17

/*  Previously a single Chebyshev expansion on [2, 6] was used. It is much    *
 *  faster to use two Remez minimax polynomials on [2, 4] and then [4, 6]     *
 *  instead. The old Chebyshev coefficients are kept here for later study.    */
#else

/*  Coefficients for the polynomial.                                          */
#define A00 (+9.9999998458274208175762223432456249549502926125902E-01)
#define A01 (+2.5396469525474072315862812598955621859919646326548E-07)
#define A02 (-2.0317175394844726792687825258483860217780185054774E-06)
#define A03 (+1.0497207069080116271795993263702674395391427601173E-05)
#define A04 (-3.9279873177333922332504582408292863721138592106915E-05)
#define A05 (+1.1309895453180181019695864439888849555213331820018E-04)
#define A06 (-2.5969863460533195402065003140932652966375366791973E-04)
#define A07 (+4.8588341847909702467484668684320352857808118756892E-04)
#define A08 (-7.4916869570307642471241000326288407502585539013626E-04)
#define A09 (+9.5394799730152875257183607105413033610653843788256E-04)
#define A10 (-9.9356840621075477417401777813978245219270495985029E-04)
#define A11 (+8.2077528526549566750423593640687943522778182310869E-04)
#define A12 (-4.9224095874765589683524100421085379296630966396968E-04)
#define A13 (+1.4289232555329850569658571761403619851382390125881E-04)
#define A14 (+9.6486156696501415073601843161908176802061454681505E-05)
#define A15 (-1.7387132048917405833406069947674234470948247832292E-04)
#define A16 (+1.2842036683237362577907948087598827419660540901807E-04)
#define A17 (-4.3736670033750639293565686279690644772836500156280E-05)
#define A18 (-1.3968592680472564591301820887056412312450355889885E-05)
#define A19 (+2.8477740952087858732556725910687380969690523319095E-05)
#define A20 (-1.8784109116878038541530774069664042408599979607120E-05)
#define A21 (+4.7769180412788485349581455781508742561230050421662E-06)
#define A22 (+4.4055944252548251721699015960894969923081057719191E-06)
#define A23 (-5.2584269297611801936006586952343815902797544183977E-06)
#define A24 (+1.0842314956315554309365139272279286619655706290006E-06)
#define A25 (+1.2336068166571108768589898358888108462984792853852E-06)
#define A26 (-5.8142324105960777505247152292366581743257402006747E-07)
#define A27 (-1.0351072922623697344366646442050567968311005346654E-07)
#define A28 (+7.3988306580553170372966300684171750570874673426603E-08)

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
                                  A17 + z*(\
                                    A18 + z*(\
                                      A19 + z*(\
                                        A20 + z*(\
                                          A21 + z*(\
                                            A22 + z*(\
                                              A23 + z*(\
                                                A24 + z*(\
                                                  A25 + z*(\
                                                    A26 + z*(\
                                                      A27 + z*A28\
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

/*  Function for computing erf(x) for x >= 2.                                 */
TMPL_STATIC_INLINE
double tmpl_Double_Erf_Asymptotic(double x)
{
    /*  For x >= 6 we have |1 - erf(x)| < 2^-52, double epsilon. Return 1.    */
    if (x >= 6.0)
        return 1.0;

    /*  For other values use the Chebyshev expansion from above.              */
    else
    {
        /*  Shift the interval [2, 6] to [-1, 1] for the polynomial.          */
        const double z = 0.5*(x - 4.0);

        /*  Evaluate the polynomial using Horner's method.                    */
        return TMPL_POLY_EVAL(z);
    }
}
/*  End of tmpl_Double_Erf_Asymptotic.                                        */

/*  #undef everything in case someone wants to #include this file.            */
#undef TMPL_POLY_EVAL
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
#undef A19
#undef A20
#undef A21
#undef A22
#undef A23
#undef A24
#undef A25
#undef A26
#undef A27
#undef A28

#endif
/*  End of #if TMPL_ERF_IMPLEMENTATION == 0.                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of include guard.                                                     */
