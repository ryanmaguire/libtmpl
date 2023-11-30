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
/*  End of include guard.                                                     */
