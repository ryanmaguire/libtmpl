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
    const long double asin_three_eigths_hi = ASIN_3_8_HI;
    const long double asin_three_eigths_lo = ASIN_3_8_LO;
    const long double x_shift = x - 0.625L;
    const long double p = TMPL_NUM_EVAL(x_shift);
    const long double q = TMPL_DEN_EVAL(x_shift);
    const long double rat = p / q;
    const long double low_bits = asin_three_eigths_lo + x_shift * rat;
    return asin_three_eigths_hi + low_bits;
}
/*  End of tmpl_LDouble_Arcsin_Aux_Shifted_Rat_Remez.                         */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>

#undef ASIN_3_8_HI
#undef ASIN_3_8_LO
