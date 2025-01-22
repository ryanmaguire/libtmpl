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
#ifndef TMPL_ERF_LARGE_LDOUBLE_64_BIT_DOUBLE_H
#define TMPL_ERF_LARGE_LDOUBLE_64_BIT_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  With IEEE-754 support we can use a switch-trick to double the performance.*/
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  Coefficients for the Remez polynomial for Erf on [2, 2.5].                */
#define A00 (+9.9853728341331885122917049163048561164071612143256E-01L)
#define A01 (+7.1423190220182551212639592571545453534409310185057E-03L)
#define A02 (-1.6070217799544499375749681878385412130461324864096E-02L)
#define A03 (+2.1724553691848123484559446741931650749320609820280E-02L)
#define A04 (-1.9083383636029665626388678675899106786912669285060E-02L)
#define A05 (+1.0657679181541277097330847349642305238766047557653E-02L)
#define A06 (-2.9043571515295761913149210463157628004300500688630E-03L)
#define A07 (-6.7045684210182447361233109790249938460067974648627E-04L)
#define A08 (+9.9949708347555551712978749627502335336796459803359E-04L)
#define A09 (-3.6935727415108647200579303917701509950420786490064E-04L)
#define A10 (-1.1539736718627222791947754786629603849538237347908E-05L)
#define A11 (+6.4844129322404749029706341545510470582290000286178E-05L)
#define A12 (-2.1894411428366273657419057866807365805957172479599E-05L)

/*  Coefficients for the Remez polynomial for Erf on [2.5, 3].                */
#define B00 (+9.9989937807788039773943230740580948402586993282533E-01L)
#define B01 (+5.8627724709288510487639134704333605218589654673250E-04L)
#define B02 (-1.6122624295482425426304601750093559507647212938844E-03L)
#define B03 (+2.7603887054235208922187015740027856748423601087818E-03L)
#define B04 (-3.2581136520601992659920616155360778326984288841911E-03L)
#define B05 (+2.7558083732457483020077876686722456228005898633149E-03L)
#define B06 (-1.6573279206213689173398469279229336075066504603200E-03L)
#define B07 (+6.4604298582199359342942355389533824474815088559908E-04L)
#define B08 (-8.8995738552911916607140022002464813003860492032919E-05L)
#define B09 (-7.1272678135500073303826809202164960992348502289215E-05L)
#define B10 (+5.4777156882263340978770021622040500192003276479264E-05L)
#define B11 (-1.5257484938233752477773286853489458461321735575630E-05L)

/*  Coefficients for the Remez polynomial for Erf on [3, 3.5].                */
#define C00 (+9.9999569722053626957864703926955653072792111165044E-01L)
#define C01 (+2.9189025383770338707620156424961017118408025567378E-05L)
#define C02 (-9.4864332432900072999698943062667595423041150635053E-05L)
#define C03 (+1.9580971187473420429638691406381813188079734919573E-04L)
#define C04 (-2.8656934965381843365066550677883507768250335956211E-04L)
#define C05 (+3.1379723382979700033926833020726486185166480414035E-04L)
#define C06 (-2.6352769128894339114442472765483397006883506067932E-04L)
#define C07 (+1.6999100251263728824659988597178758000620848570200E-04L)
#define C08 (-8.1672723600307529679031004533150304918005203217527E-05L)
#define C09 (+2.5923868424212381256693135633307154628060970739941E-05L)
#define C10 (-1.9718785781558686676798501526036408892028792767577E-06L)
#define C11 (-2.9827176694095196134711117250213384965033235972170E-06L)

/*  Coefficients for the Remez polynomial for Erf on [3.5, 4].                */
#define D00 (+9.9999988627274343253356551538774082813127489225062E-01L)
#define D01 (+8.8143219125234271870080846925274230542344460932361E-07L)
#define D02 (-3.3053707198253979852183694651385735847848482549661E-06L)
#define D03 (+7.9696160543435196502233058816783242848520522699009E-06L)
#define D04 (-1.3841239368803963902660192649649020716989763531639E-05L)
#define D05 (+1.8370975914818732032856067262807646176858974326086E-05L)
#define D06 (-1.9272756518979244337015225778661174725653000107335E-05L)
#define D07 (+1.6275257365804144889354146983604872664066753515367E-05L)
#define D08 (-1.1127131642251367709095658594427019516626727283995E-05L)
#define D09 (+6.1099830497210315365686437232690420729350622645852E-06L)
#define D10 (-2.6192389213319816747876472629098661358128134237123E-06L)
#define D11 (+7.6243896060223080058526708385726241059551019298625E-07L)

/*  Coefficients for the Remez polynomial for Erf on [4, 4.5].                */
#define E00 (+9.9999999814942586593606361611445131768218026025321E-01L)
#define E01 (+1.6143995161114304743062572768179453264188622455552E-08L)
#define E02 (-6.8611976549508848991288015161583412291090846635137E-08L)
#define E03 (+1.8901879873542089635602398005957728736134968033244E-07L)
#define E04 (-3.7879474275583309329909055096105158877575975708691E-07L)
#define E05 (+5.8728744824523232944682260689708461419316158739311E-07L)
#define E06 (-7.3095191364207481457314542475848939638520417630463E-07L)
#define E07 (+7.4621894285100202841578132616109155463598772225848E-07L)
#define E08 (-6.3694616784748210497593872699946034632487684702494E-07L)
#define E09 (+4.8100430292123512706733557636000623587835436930718E-07L)
#define E10 (-2.8652969948032422896948003854371567993509710279951E-07L)

/*  Coefficients for the Remez polynomial for Erf on [4.5, 5].                */
#define F00 (+9.9999999998151492923599855833197345269503530222873E-01L)
#define F01 (+1.7934371855502848735974345710054251774935331607893E-10L)
#define F02 (-8.5186356004089592622887530601694252323961998368097E-10L)
#define F03 (+2.6378047978654265486494933007797128532518319659139E-09L)
#define F04 (-5.9832688099679586312292522487056289582798553473565E-09L)
#define F05 (+1.0575533835256321140407182840892048536696801380740E-08L)
#define F06 (-1.5040140473477141962910120232547198488669786549004E-08L)
#define F07 (+1.7934642740598449624250135951332135318651467897185E-08L)
#define F08 (-2.0062670512208084629162182356873884123115858869315E-08L)
#define F09 (+1.7130931819877410358405197183616916743129781348922E-08L)

/*  Coefficients for the Remez polynomial for Erf on [5, 5.5].                */
#define G00 (+9.9999999999988693380861989837696532177328737896535E-01L)
#define G01 (+1.2081133405529725316352314517408122004343280361457E-12L)
#define G02 (-6.3629344845528682696353532035754542281562253402972E-12L)
#define G03 (+2.1853072284687390840090703649707145333163449785406E-11L)
#define G04 (-5.3628357483333772603925260714769551826237400310448E-11L)
#define G05 (+1.0668983967979651399045356137204522355231743941992E-10L)
#define G06 (-2.1354533241912177833879484470727804205014376820730E-10L)
#define G07 (+2.8474369150597829596454084804722261286134811281892E-10L)

/*  Coefficients for the Remez polynomial for Erf on [5.5, 6].                */
#define H00 (+9.9999999999999955387850795076520886363002512443239E-01L)
#define H01 (+3.9340427279773976530011305330744974291684882874340E-15L)
#define H02 (-2.3763600089489119124602536211619222230546842706339E-14L)
#define H03 (+1.6823275229079022610382212627661663901978300514574E-13L)
#define H04 (-4.5019575287861106347929033568853260439899192451307E-13L)

/*  Helper macro for evaluating the zeroth polynomial via Horner's method.    */
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
                                            A11 + z*A12\
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
                                        B10 + z*B11\
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
#define TMPL_POLYC_EVAL(z) \
C00 + z*(\
    C01 + z*(\
        C02 + z*(\
            C03 + z*(\
                C04 + z*(\
                    C05 + z*(\
                        C06 + z*(\
                            C07 + z*(\
                                C08 + z*(\
                                    C09 + z*(\
                                        C10 + z*C11\
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
#define TMPL_POLYD_EVAL(z) \
D00 + z*(\
    D01 + z*(\
        D02 + z*(\
            D03 + z*(\
                D04 + z*(\
                    D05 + z*(\
                        D06 + z*(\
                            D07 + z*(\
                                D08 + z*(\
                                    D09 + z*(\
                                        D10 + z*D11\
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
#define TMPL_POLYE_EVAL(z) E00 + \
z*(E01+z*(E02+z*(E03+z*(E04+z*(E05+z*(E06+z*(E07+z*(E08+z*(E09+z*E10)))))))))

/*  Helper macro for evaluating the fifth polynomial via Horner's method.     */
#define TMPL_POLYF_EVAL(z) \
F00+z*(F01+z*(F02+z*(F03+z*(F04+z*(F05+z*(F06+z*(F07+z*(F08+z*F09))))))))

/*  Helper macro for evaluating the sixth polynomial via Horner's method.     */
#define TMPL_POLYG_EVAL(z) \
G00 + z*(G01 + z*(G02 + z*(G03 + z*(G04 + z*(G05 + z*(G06 + z*G07))))))

/*  Helper macro for evaluating the seventh polynomial via Horner's method.   */
#define TMPL_POLYH_EVAL(z) H00 + z*(H01 + z*(H02 + z*(H03 + z*H04)))

/*  Function for computing Erf(x) for x >= 2 at double precision.             */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Erf_Large(long double x)
{
    /*  64-bit word used for type punning.                                    */
    tmpl_IEEE754_LDouble w;

    /*  Integer used as a switch for the range of x.                          */
    unsigned int n;

    /*  Input variable for the polynomial approximations.                     */
    long double z;

    /*  Set the word to the input double.                                     */
    w.r = x;

    /*  For x > 8 we have |erf(x) - 1| < 2^-96, way beyond double precision.  *
     *  We can safely return 1 for this range.                                */
    if (w.bits.expo > TMPL_LDOUBLE_UBIAS + 2U)
        return 1.0L;

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
    w.r += 549755813886.0L;

    /*  The integer and halves place are now the 13th and 14th bits. Shift by *
     *  12 to obtain them.                                                    */
    n = w.bits.man3 >> 12;

    /*  We can now use this integer to select the correct window.             */
    switch(n)
    {
        /*  Remez polynomial on the interval [2, 2.5].                        */
        case 0:
            z = x - 2.25L;
            return TMPL_POLYA_EVAL(z);

        /*  Remez polynomial on the interval [2.5, 3].                        */
        case 1:
            z = x - 2.75L;
            return TMPL_POLYB_EVAL(z);

        /*  Remez polynomial on the interval [3, 3.5].                        */
        case 2:
            z = x - 3.25L;
            return TMPL_POLYC_EVAL(z);

        /*  Remez polynomial on the interval [3.5, 4].                        */
        case 3:
            z = x - 3.75L;
            return TMPL_POLYD_EVAL(z);

        /*  Remez polynomial on the interval [4, 4.5].                        */
        case 4:
            z = x - 4.25L;
            return TMPL_POLYE_EVAL(z);

        /*  Remez polynomial on the interval [4.5, 5].                        */
        case 5:
            z = x - 4.75L;
            return TMPL_POLYF_EVAL(z);

        /*  Remez polynomial on the interval [5, 5.5].                        */
        case 6:
            z = x - 5.25L;
            return TMPL_POLYG_EVAL(z);

        /*  Remez polynomial on the interval [5, 5.5].                        */
        case 7:
            z = x - 5.75L;
            return TMPL_POLYH_EVAL(z);

        /*  For the remaining values, which fall between 6 and 8, we have     *
         *  |erf(x) - 1| < 2^-52 and can safely return 1.                     */
        default:
            return 1.0L;
    }
    /*  End of switch for "n".                                                */
}
/*  End of tmpl_LDouble_Erf_Large.                                            */

/*  Undefine everything in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

#endif
/*  End of include guard.                                                     */
