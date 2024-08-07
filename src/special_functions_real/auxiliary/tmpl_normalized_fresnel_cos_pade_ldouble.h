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
 *                   tmpl_normalized_fresnel_cos_pade_double                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for small values.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Cos_Pade                               *
 *  Purpose:                                                                  *
 *      Computes C(x) for |x| < 1.                                            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      C_x (double):                                                         *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the (20, 16) Pade approximant for C(x). The polynomials are   *
 *      in terms of x^4, so only 5 terms are needed for the numerator and     *
 *      4 terms required for the denominator.                                 *
 *  Notes:                                                                    *
 *      This function assumes the input is bounded by 1.                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 8, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_COS_PADE_LDOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_PADE_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/*  Coefficients for the numerator of the Pade approximant.                   */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (-2.1090942541681899242845079918511663967216358911725E-01L)
#define A02 (+1.9952947354822570927809856437132718931800178922439E-02L)
#define A03 (-7.3911123111933377948080176313020983341150763045957E-04L)
#define A04 (+1.2274218310026533331254617912315044753062117420452E-05L)
#define A05 (-7.8097325185845863146674684390301377301045873738860E-08L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+3.5830684610414973042411475811787138710678896063772E-02L)
#define B02 (+6.0831354005325641202296672843869017418765178894320E-04L)
#define B03 (+5.9614617845960804718215100801144490827271427390733E-06L)
#define B04 (+2.9455885172523367699202977882571957391522644286406E-08L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  Coefficients for the numerator of the Pade approximant.                   */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (-2.2242168870723570212459612975558566524889861817498E-01L)
#define A02 (+2.2477639779047854264940540859976178786976225978075E-02L)
#define A03 (-9.8934273076167159232321568568869495336532464352628E-04L)
#define A04 (+2.2739925159640304325217023750696135959925000087140E-05L)
#define A05 (-2.9333531444941221764566377540567331477704682310378E-07L)
#define A06 (+2.1605673805638163881475363491805913318046467166869E-09L)
#define A07 (-8.5935282363994030663932918251534721847093679341694E-12L)
#define A08 (+1.4576339158219923447883122439039163094673675753626E-14L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+2.4318421319998263346266145241318113133943867006044E-02L)
#define B02 (+2.9246885333863427194600171976932423221834889241059E-04L)
#define B03 (+2.2773164693647748278415112483670267333268453414960E-06L)
#define B04 (+1.2539801156590031596649667605920127193736376904900E-08L)
#define B05 (+4.9469800216310852539186073587172355615512134871716E-11L)
#define B06 (+1.3145002931141456750070994381113153596557507807035E-13L)
#define B07 (+1.8479249917982223216632512453430463652839053850679E-16L)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*B07))))))

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/*  Coefficients for the numerator of the Pade approximant.                   */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (-2.2138969766845593920689379290841421109911505796467E-01L)
#define A02 (+2.2252565345351153993004280321809417882564763442197E-02L)
#define A03 (-9.6712543843132170507133551592379548055061971720012E-04L)
#define A04 (+2.1816316774912461440244311216042139533087562368583E-05L)
#define A05 (-2.7398799246476266761835830823882529500627652514367E-07L)
#define A06 (+1.9464355467871577128296684361249610899791871852484E-09L)
#define A07 (-7.3822064308747040602136305739822721627228639342470E-12L)
#define A08 (+1.1775529088770925227925548523210738121586732462919E-14L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+2.5350412358778026263968482088489567283727427216353E-02L)
#define B02 (+3.2202800209757217641390407683596155412549356987671E-04L)
#define B03 (+2.7008520873003973375423550805316632190576262959071E-06L)
#define B04 (+1.6520242375648225781599895997678357696971588640757E-08L)
#define B05 (+7.6320579325316275529830352674564911482765702020227E-11L)
#define B06 (+2.6346982948863799493141703634051325629868290698336E-13L)
#define B07 (+6.3091044165684645011757564493960132052011533561803E-16L)
#define B08 (+8.1693280494942424540721423476412837204960866837068E-19L)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*(B07+z*B08)))))))

#else

/*  Coefficients for the numerator of the Pade approximant.                   */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (-2.1573519443393282604486913993246584317067546216367E-01L)
#define A02 (+2.1001783020025247278319719142929700729493133863364E-02L)
#define A03 (-8.4174813280572968187927819325138931522481449106707E-04L)
#define A04 (+1.6417497758326320814340142144367945838085480003060E-05L)
#define A05 (-1.5612961846073306742920907422940173828862344035308E-07L)
#define A06 (+5.9777056867430469311336869705123121578330044115658E-10L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+3.1004915593301139425993135064437935212167023017352E-02L)
#define B02 (+4.6643842700724874671363510848409479472599983593593E-04L)
#define B03 (+4.3349959634786923548919961521913665842923180358596E-06L)
#define B04 (+2.5446789051616733895140913601812071676764911536022E-08L)
#define B05 (+7.7559028457313867649205421286943025194624400668790E-11L)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*A06)))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) B00+z*(B01+z*(B02+z*(B03+z*(B04+z*B05))))

#endif

/*  Computes the normalized Fresnel cosine function using a Pade approximant. */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Cos_Pade(long double x)
{
    /*  The Pade approximant is in terms of x^4.                              */
    const long double x2 = x*x;
    const long double x4 = x2*x2;

    /*  Compute the Pade approximant.                                         */
    const long double num = TMPL_NUM_EVAL(x4);
    const long double den = TMPL_DEN_EVAL(x4);
    return x * num / den;
}
/*  End of tmpl_Double_Normalized_Fresnel_Cos_Pade.                           */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
