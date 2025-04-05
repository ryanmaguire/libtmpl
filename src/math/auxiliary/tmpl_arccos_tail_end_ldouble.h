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
 *                        tmpl_arccos_tail_end_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the acos(x) for 0.5 <= x < 1.0.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arccos_Tail_End                                          *
 *  Purpose:                                                                  *
 *      Computes the inverse cosine for 0.5 <= x < 1.                         *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (long double):                                                 *
 *          The inverse cosine of x.                                          *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_Sqrt:                                                *
 *              Computes the square root of a number.                         *
 *  Method:                                                                   *
 *      Use the following trig identity:                                      *
 *          acos(x) = 2*asin(sqrt((1-x)/2))                                   *
 *      Compute this using a Remez rational minimax approximation.            *
 *      64-bit double:                                                        *
 *          Order (8, 8) approximation.                                       *
 *      80-bit extended / portable:                                           *
 *          Order (10, 10) approximation.                                     *
 *      128-bit double-double:                                                *
 *          Order (18, 16) approximation.                                     *
 *      128-bit quadruple:                                                    *
 *          Order (18, 18) approximation.                                     *
 *  Notes:                                                                    *
 *      Accurate for 0.5 <= x < 1.0.                                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2023                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_arccos_tail_end_ldouble.c to include this file. *
 *  2024/11/08: Ryan Maguire                                                  *
 *      Changed coefficients to match those found in arccos_rat_remez_ldouble.*
 *      This includes adding (18, 16) approximations for double-double, and   *
 *      making the coefficients for each precision match the output of the    *
 *      Python scripts found in libtmpl_data. This is to help create          *
 *      reproducibible results in libtmpl.                                    *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_TAIL_END_LDOUBLE_H
#define TMPL_ARCCOS_TAIL_END_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  The compiler needs to know about the sqrt function.                       */
extern long double tmpl_LDouble_Sqrt(long double x);

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.6666666666666675172610409335401762495970069423667E-01L)
#define A01 (-2.9647442738212244852684254810912673101657174481766E-01L)
#define A02 (+1.6001969221867813049084016184632874497094695883901E-01L)
#define A03 (-2.5510481570872249173776491491771394448907125511346E-02L)
#define A04 (+2.6066097969323856113412749790103952111930280796716E-04L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-2.2288465642924490579275829949790393075345284377974E+00L)
#define B02 (+1.6952419643599424152439428142515867324057155650851E+00L)
#define B03 (-5.0120096652328631713045487959099718175996563925832E-01L)
#define B04 (+4.5088915315077310386265964807853660211534733521946E-02L)

/*  Helper macro for evaluating the numerator of the minimax approximation.   */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))

/*  Helper macro for evaluating the denominator of the minimax approximation. */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  128-bit double-double, a few more terms.                                  */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                       128-Bit Double-Double Version                        *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.6666666666666666666666666666664788350189799631388E-01L)
#define A01 (-6.7953487712343915574629405476556772441017491044686E-01L)
#define A02 (+1.1355619701185383396809502073437485674503112281478E+00L)
#define A03 (-9.9979136861031466933084901065494659727226368799419E-01L)
#define A04 (+4.9542222658058914988889870432900282258468548407047E-01L)
#define A05 (-1.3619497632729465917010549488509051327066923409678E-01L)
#define A06 (+1.8893779497378076181367383073424468319568918871776E-02L)
#define A07 (-1.0127751917585769797088507439230121924663387007820E-03L)
#define A08 (+4.1609143699953575338552391698200117907397110245559E-06L)
#define A09 (+6.4696737362761237061122472460464127042098844745215E-08L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-4.5272092627406349344777643288466317806594588091439E+00L)
#define B02 (+8.5827588460873729014578381443554824724815994789507E+00L)
#define B03 (-8.8306360208337738451441152531141366926804404474047E+00L)
#define B04 (+5.3384058738222081336161251070080734212567758116369E+00L)
#define B05 (-1.9150848930384390299612099877658282688028004983951E+00L)
#define B06 (+3.9045152646266604165940541749287272445233674531396E-01L)
#define B07 (-4.0182950418624211402578721577444719860456633216405E-02L)
#define B08 (+1.5253118366932057306896123733715782641557910872142E-03L)

/*  Helper macro for evaluating the numerator of the minimax approximation.   */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*(A08+z*A09))))))))

/*  Helper macro for evaluating the denominator of the minimax approximation. */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*(B07+z*B08)))))))

/*  128-bit quadruple, one more term than double-double.                      */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                         128-Bit Quadruple Version                          *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.6666666666666666666666666666666694706933946298950E-01L)
#define A01 (-7.3144709334175817512762531348508944088120313226673E-01L)
#define A02 (+1.3368369867017129703977436941625958610948526767792E+00L)
#define A03 (-1.3164457448338078898680515898399898883183856946743E+00L)
#define A04 (+7.5433447772390026447745048361121104864822141175686E-01L)
#define A05 (-2.5305623011757570478996213419242526094866179872734E-01L)
#define A06 (+4.7313332272611269610015425840407483047031537556424E-02L)
#define A07 (-4.3361995096656108677667878009793595389518727216915E-03L)
#define A08 (+1.4087190715202195938465702311593468262447436322608E-04L)
#define A09 (-2.0328626084732569115240530375825287148402561696861E-07L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-4.8386825600505490507657518809063303704994296482532E+00L)
#define B02 (+9.9305719293758820380881933667670676755911673699658E+00L)
#define B03 (-1.1253647818160835284416693673889480035561042302542E+01L)
#define B04 (+7.6779923143729025203841464458693002845067905250317E+00L)
#define B05 (-3.2239304092346372000140864131217032195928519148161E+00L)
#define B06 (+8.1647784902583048535525297530145980584299894277043E-01L)
#define B07 (-1.1672244212330846346297892822136598340504167438939E-01L)
#define B08 (+8.1483736398505318670509521365312690155985702378105E-03L)
#define B09 (-1.9417708181167947671251189418713447040829557241161E-04L)

/*  Helper macro for evaluating the numerator of the minimax approximation.   */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*(A08+z*A09))))))))

/*  Helper macro for evaluating the denominator of the minimax approximation. */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*(B07+z*(B08+z*B09))))))))

/*  Lastly, extended precision and portable versions.                         */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.6666666666666666669358251569645684688643237278511E-01L)
#define A01 (-3.8389959330056732758636509319266298229402893686417E-01L)
#define A02 (+3.0547782594474706446692132238957214674495279745495E-01L)
#define A03 (-9.6693903957891911586190023930102559650735648424735E-02L)
#define A04 (+9.9046992157998326437479057754826461967989551212864E-03L)
#define A05 (-6.0191388460588721027458992349689449409895145475348E-05L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-2.7533975598034038304032842577489084280592940825487E+00L)
#define B02 (+2.8040387147228523924992805747940733605037960201632E+00L)
#define B03 (-1.2867553085195036875472887512990417368983501280050E+00L)
#define B04 (+2.5507476114048228270116995436960640085599958340105E-01L)
#define B05 (-1.6150977641153863432089856687117703962621376999198E-02L)

/*  Helper macro for evaluating the numerator of the minimax approximation.   */
#define TMPL_NUM_EVAL(z) A00+z*(A01+z*(A02+z*(A03+z*(A04+z*A05))))

/*  Helper macro for evaluating the denominator of the minimax approximation. */
#define TMPL_DEN_EVAL(z) B00+z*(B01+z*(B02+z*(B03+z*(B04+z*B05))))

#endif
/*  End of 80-bit extended / portable version.                                */

/*  Function for computing acos(x) for 0.5 <= x < 1.0.                        */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Arccos_Tail_End(long double x)
{
    /*  Rational function is computed in terms of (1 - x)/2.                  */
    const long double z = 0.5L*(1.0L - x);

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const long double p = TMPL_NUM_EVAL(z);
    const long double q = TMPL_DEN_EVAL(z);

    /*  p(z) / q(z) is the rational minimax approximant for                   *
     *  (asin(sqrt(z)) - sqrt(z)) / z^{3/2}. We need to multiply by z^{3/2}.  */
    const long double r = z*p/q;
    const long double sqrt_z = tmpl_LDouble_Sqrt(z);
    const long double t = r * sqrt_z;

    /*  We now have t = asin(sqrt(z)) - sqrt(z). We need 2*asin(sqrt(z)).     */
    return 2.0L*(sqrt_z + t);
}
/*  End of tmpl_LDouble_Arccos_Tail_End.                                      */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
