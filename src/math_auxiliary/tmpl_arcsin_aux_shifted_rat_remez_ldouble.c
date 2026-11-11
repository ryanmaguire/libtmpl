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
 *                  tmpl_arcsin_aux_shifted_rat_remez_ldouble                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a degree (6, 6) rational Remez approximation for asin(x)     *
 *      centered about 5/8 on the interval [1/2, 3/4].                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arcsin_Aux_Shifted_Rat_Remez                             *
 *  Purpose:                                                                  *
 *      Computes a degree (6, 6) rational Remez approximation for asin(x)     *
 *      on the interval [1/2, 3/4] by shifting the input by 5/8.              *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number in the interval [1/2, 3/4].                         *
 *  Output:                                                                   *
 *      asin_x (long double):                                                 *
 *          asin(x) to long double precision.                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the degree (M, N) rational Remez approximation   *
 *      on the interval [-1/8, 1/8] for the function                          *
 *                                                                            *
 *                 asin(x + 5/8) - asin(5/8)                                  *
 *          f(x) = -------------------------                                  *
 *                             x                                              *
 *                                                                            *
 *      have been pre-computed. asin(x) is computed using                     *
 *                                                                            *
 *          asin(x) = asin(5/8) + (x - 5/8) * r(x - 5/8)                      *
 *                                                                            *
 *      where r is the rational Remez approximation. The degree of the        *
 *      approximation depends on how long double is implemented:              *
 *                                                                            *
 *                                                                            *
 *          long double           |  M |  N                                   *
 *          --------------------------------                                  *
 *          64-bit double         |  6 |  6                                   *
 *          80-bit extended       |  8 |  7                                   *
 *          128-bit double-double | 18 | 16                                   *
 *          128-bit quadruple     | 18 | 18                                   *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) Accurate to long double precision for 1/2 <= x <= 3/4. There are  *
 *          no checks that the input falls within this interval.              *
 *  References:                                                               *
 *      1.) Maguire, Ryan (2024)                                              *
 *          tmpld                                                             *
 *          https://github.com/ryanmaguire/libtmpl_data                       *
 *                                                                            *
 *          Python library providing an implementation of the rational        *
 *          Remez exchange algorithm. The coefficients for the                *
 *          approximation used by this function were computed using this.     *
 *                                                                            *
 *      2.) Tasissa, Abiy (2019)                                              *
 *          Function Approximation and the Remez Exchange Algorithm.          *
 *          https://sites.tufts.edu/atasissa/files/2019/09/remez.pdf          *
 *                                                                            *
 *          Survey of the Remez polynomial and Remez exchange algorithm.      *
 *          The implementation in tmpld is based on these notes.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_ALWAYS_INLINE macro.              *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  3.) tmpl_math_auxiliary.h:                                                *
 *          Contains the function prototype / forward declaration.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 6, 2026                                               *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.2810252304406972486120109535816568934847264625400E+00L)
#define A01 (-4.0484052648574630462581331912608769396074592922513E+00L)
#define A02 (-4.7972532776743966087173847292196857298797697019924E+00L)
#define A03 (+2.4424574932939250732516808901118164990997677343368E+01L)
#define A04 (-1.6804320822570014076769180928327851026907536501678E+01L)
#define A05 (-3.3311938222189006681631968216993613706183079115091E+00L)
#define A06 (+2.3300469518272892996538826310339664734701331835423E+00L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-3.6731058597880585471659357686838038961868829899774E+00L)
#define B02 (-2.6606846391928424735802870740486381412339686695071E+00L)
#define B03 (+2.2061950193310168293427078933270091574344541746879E+01L)
#define B04 (-1.9974282302319488739647035513096559624368403266214E+01L)
#define B05 (-2.4025119038699931555070688372327351814284720795078E+00L)
#define B06 (+4.5414368669168018480544500989011482168218305220203E+00L)

#define TMPL_NUM_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * A06\
                )\
            )\
        )\
    )\
)

#define TMPL_DEN_EVAL(z) \
B00 + z * (\
    B01 + z * (\
        B02 + z * (\
            B03 + z * (\
                B04 + z * (\
                    B05 + z * B06\
                )\
            )\
        )\
    )\
)

#define ASIN_3_8_HI (+6.75131532937031653140991238615243E-01L)
#define ASIN_3_8_LO (-5.93193497332085475014956678498079E-18L)

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.2810252304406970678660293581414949721954738552302E+00L)
#define A01 (-1.6446511602263547056580732787129037513978488937560E+01L)
#define A02 (+8.7246868137883278229413629756799464009259834176069E+01L)
#define A03 (-2.4275601447693312040160682304635573036441709692938E+02L)
#define A04 (+3.6225756240019720606650475906568149533732146867953E+02L)
#define A05 (-2.3198379151844696521638970407098172351826646389175E+02L)
#define A06 (-6.3604349596072997403929484937766400512327055544376E+01L)
#define A07 (+1.6797618585440389811625215527687421434726658424315E+02L)
#define A08 (-5.0778787007005649998189687906892420088542460701053E+01L)
#define A09 (-2.4339871566847151163786550129620867769205565595368E+01L)
#define A10 (+1.0774471246089696651660467371544751146974432801945E+01L)
#define A11 (+7.3581034597684212518898932142207938300199763213783E-01L)
#define A12 (-2.8142694968214863114427248490835876273101897908257E-01L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-1.3351374517416998364451242713405287773814915831621E+01L)
#define B02 (+7.4154449307588507998310369528173172285774773799913E+01L)
#define B03 (-2.1816068249960041298721203388816558387806852648503E+02L)
#define B04 (+3.5034501841610623133951712964910946535442331858218E+02L)
#define B05 (-2.5517471190703173465521670545001880731350008003059E+02L)
#define B06 (-4.1339018566443821950587608067342286375275390161404E+01L)
#define B07 (+1.8663764618311706175119886488720860979673169537312E+02L)
#define B08 (-7.4428752995534950446344734176813316831102275837097E+01L)
#define B09 (-2.8101896126508094051880562197081422523248981640197E+01L)
#define B10 (+1.8527473223069977919277953800277313370842455139422E+01L)
#define B11 (+7.7708647817530778315546659321074794562871437252517E-01L)
#define B12 (-8.9875487772395844450361707026702182143436217442913E-01L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_NUM_EVAL(z) \
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

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_DEN_EVAL(z) \
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
                                            B11 + z*B12\
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

#define ASIN_3_8_HI (+6.75131532937031647209056265294393919000292301254667E-01L)
#define ASIN_3_8_LO (-5.90479610695000498778262158015095439734389108052690E-33L)

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.2810252304406970678660293581414963207630120407826E+00L)
#define A01 (-1.6984784334390135412195651298540459629067728643089E+01L)
#define A02 (+9.3434835209206066476984684578525856418826726329648E+01L)
#define A03 (-2.7092909367689293540455078053637118158355213247773E+02L)
#define A04 (+4.2387274574400947860421119195581353504608317669207E+02L)
#define A05 (-2.8652997736400513462958153877650251222443736928871E+02L)
#define A06 (-8.4657947976589525668675686640617483175783955637427E+01L)
#define A07 (+2.4023823000610663284067271194484140322033246469154E+02L)
#define A08 (-7.9550740511351541353324917227692560295639400123987E+01L)
#define A09 (-4.3632354594489623252066294471346735541804855098328E+01L)
#define A10 (+2.2507894997413924448620265229376546866858568602856E+01L)
#define A11 (+2.0182978361656420786262187373356055266426072916683E+00L)
#define A12 (-1.0697285481947587560116257675805746079138185169471E+00L)
#define A13 (-5.6335011900915620319065172199899262974897543112198E-03L)
#define A14 (-1.1283629814769454439998576620070212159666692048726E-02L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-1.3771563534257371046216344747202750514237385846197E+01L)
#define B02 (+7.9200411101506886364214392728363425650166816044164E+01L)
#define B03 (-2.4240502790923159821302061358376207417499363488958E+02L)
#define B04 (+4.0739078773210375534398202635547057235664549809630E+02L)
#define B05 (-3.1317801957633773796254297214002706802598931990678E+02L)
#define B06 (-5.2349068201284408305349688796659023726230694416600E+01L)
#define B07 (+2.5980661587194726201420345144619705544772836667289E+02L)
#define B08 (-1.1369865953312206999298289957772422831701578532466E+02L)
#define B09 (-4.6880926295406198485004755924510242367908206650576E+01L)
#define B10 (+3.5780611214975790881527467161882821819939466824847E+01L)
#define B11 (+1.6907682607183046898945256873150310948986812350610E+00L)
#define B12 (-2.6596547166864037479008498460184389077191652710650E+00L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_NUM_EVAL(z) \
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
                                                    A13 + z*A14\
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

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_DEN_EVAL(z) \
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
                                            B11 + z*B12\
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

#define ASIN_3_8_HI (+6.75131532937031647209056265294388044913961920185316E-01L)
#define ASIN_3_8_LO (-3.07097765689356367826215801509544226398766044411917E-35L)

#else

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.2810252304406970678703134587305014004581816729834E+00L)
#define A01 (-9.4186690966310483213232293834412376717830951022783E+00L)
#define A02 (+2.4444634751175273480401825311426550022759772414151E+01L)
#define A03 (-2.4398868200429887511953959882563220555135316214985E+01L)
#define A04 (+2.5879553359947942118108612579866689581355262013355E+00L)
#define A05 (+7.4948111274275029308402344077492344891558993135052E+00L)
#define A06 (-1.5257813034505386068614102140330180417863732006427E+00L)
#define A07 (-2.7274061791882367192924666219734695367117114850071E-01L)
#define A08 (-5.8521468741917925903098813613855000925693699069866E-02L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-7.8652667198252310924289624129469234663069385401157E+00L)
#define B02 (+2.2316082969071315456070108791748024781507920813045E+01L)
#define B03 (-2.5507912922300471942397024794334733511124146638258E+01L)
#define B04 (+5.0631315049956610539534555597093970351902237374344E+00L)
#define B05 (+8.9662868565424796510850279786956310749994330106653E+00L)
#define B06 (-3.0921944537622137406315161150277490648579367474712E+00L)
#define B07 (-6.3586602493502437191238627801095870887821963487038E-01L)

#define TMPL_NUM_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * (\
                        A06 + z * (\
                            A07 + z * A08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)


#define TMPL_DEN_EVAL(z) \
B00 + z * (\
    B01 + z * (\
        B02 + z * (\
            B03 + z * (\
                B04 + z * (\
                    B05 + z * (\
                        B06 + z * B07\
                    )\
                )\
            )\
        )\
    )\
)

#define ASIN_3_8_HI (+6.75131532937031647232089398569243599013134371489286E-01L)
#define ASIN_3_8_LO (-2.30331332748555848089490202396072053510723384544148E-20L)

#endif

/*  Computes a degree (10, 8) Remez approximation for (asin(x) - x) / x.      */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
long double
tmpl_LDouble_Arcsin_Aux_Shifted_Rat_Remez(const long double x)
TMPL_UNSEQUENCED
{
    /*  asin(5/8) to extra precision using two long doubles.                  */
    const long double asin_three_eigths_hi = ASIN_3_8_HI;
    const long double asin_three_eigths_lo = ASIN_3_8_LO;

    /*  The Remez approximation is evaluated on the interval [-1/8, +1/8].    *
     *  The input lies in the interval [1/2, 3/4], shift by 5/8.              */
    const long double x_shift = x - 0.625L;

    /*  Evaluate the rational Remez approximation using Horner's method.      */
    const long double p = TMPL_NUM_EVAL(x_shift);
    const long double q = TMPL_DEN_EVAL(x_shift);
    const long double rat = p / q;

    /*  The approximation is for (asin(x) - asin(5/8)) / (x - 5/8). Compute   *
     *  asin(x) from this.                                                    */
    const long double low_bits = asin_three_eigths_lo + x_shift * rat;
    return asin_three_eigths_hi + low_bits;
}
/*  End of tmpl_LDouble_Arcsin_Aux_Shifted_Rat_Remez.                         */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>

#undef ASIN_3_8_HI
#undef ASIN_3_8_LO
