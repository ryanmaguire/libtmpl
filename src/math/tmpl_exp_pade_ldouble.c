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
 *                            tmpl_exp_pade_ldouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Pade approximant of exp(x).                                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Exp_Pade                                                 *
 *  Purpose:                                                                  *
 *      Computes a Pade approximant for exp.                                  *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      exp_x (long double):                                                  *
 *          The Pade approximation of exp(x).                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator.                                                      *
 *                                                                            *
 *                     a0 + a1 x + ... + an x^n                               *
 *          exp(x) ~= -------------------------                               *
 *                     b0 + b1 x + ... + bm x^m                               *
 *                                                                            *
 *      64-bit double:                                                        *
 *          Use the (7, 7) approximant.                                       *
 *      80-bit extended / portable:                                           *
 *          Use the (9, 8) approximant.                                       *
 *      128-bit double-double:                                                *
 *          Use the (12, 12) approximant.                                     *
 *      128-bit quadruple:                                                    *
 *          Use the (14, 12) approximant.                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 9, 2022                                              *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only used if inline support is not requested.                */
#if TMPL_USE_INLINE != 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  64-bit long double. Uses the same number of terms as 64-bit double.       */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                               64-bit double                                *
 ******************************************************************************/

/*  Coefficients for the numerator.                                           */
#define P00 (+1.000000000000000000000000000000000000000E+00L)
#define P01 (+5.000000000000000000000000000000000000000E-01L)
#define P02 (+1.153846153846153846153846153846153846154E-01L)
#define P03 (+1.602564102564102564102564102564102564103E-02L)
#define P04 (+1.456876456876456876456876456876456876457E-03L)
#define P05 (+8.741258741258741258741258741258741258741E-05L)
#define P06 (+3.237503237503237503237503237503237503238E-06L)
#define P07 (+5.781255781255781255781255781255781255781E-08L)

/*  Coefficients for the denominator.                                         */
#define Q00 (+1.000000000000000000000000000000000000000E+00L)
#define Q01 (-5.000000000000000000000000000000000000000E-01L)
#define Q02 (+1.153846153846153846153846153846153846154E-01L)
#define Q03 (-1.602564102564102564102564102564102564103E-02L)
#define Q04 (+1.456876456876456876456876456876456876457E-03L)
#define Q05 (-8.741258741258741258741258741258741258741E-05L)
#define Q06 (+3.237503237503237503237503237503237503238E-06L)
#define Q07 (-5.781255781255781255781255781255781255781E-08L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
P00 + z*(P01 + z*(P02 + z*(P03 + z*(P04 + z*(P05 + z*(P06 + z*P07))))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
Q00 + z*(Q01 + z*(Q02 + z*(Q03 + z*(Q04 + z*(Q05 + z*(Q06 + z*Q07))))))

/*  128-bit double-double. More terms to get ~5 x 10^-32 peak error.          */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *                           128-bit double-double                            *
 ******************************************************************************/

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define P01 (+5.0000000000000000000000000000000000000000000000000E-01L)
#define P02 (+1.1956521739130434782608695652173913043478260869565E-01L)
#define P03 (+1.8115942028985507246376811594202898550724637681159E-02L)
#define P04 (+1.9409937888198757763975155279503105590062111801242E-03L)
#define P05 (+1.5527950310559006211180124223602484472049689440994E-04L)
#define P06 (+9.5347063310450038138825324180015255530129672006102E-06L)
#define P07 (+4.5403363481166684828012059133340597871490320002906E-07L)
#define P08 (+1.6692413044546575304416198210786984511577323530480E-08L)
#define P09 (+4.6367814012629375845600550585519401421048120918000E-10L)
#define P10 (+9.2735628025258751691201101171038802842096241836000E-12L)
#define P11 (+1.2043588055228409310545597554680364005467044394286E-13L)
#define P12 (+7.7202487533515444298369215094104897470942592271063E-16L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define Q01 (-5.0000000000000000000000000000000000000000000000000E-01L)
#define Q02 (+1.1956521739130434782608695652173913043478260869565E-01L)
#define Q03 (-1.8115942028985507246376811594202898550724637681159E-02L)
#define Q04 (+1.9409937888198757763975155279503105590062111801242E-03L)
#define Q05 (-1.5527950310559006211180124223602484472049689440994E-04L)
#define Q06 (+9.5347063310450038138825324180015255530129672006102E-06L)
#define Q07 (-4.5403363481166684828012059133340597871490320002906E-07L)
#define Q08 (+1.6692413044546575304416198210786984511577323530480E-08L)
#define Q09 (-4.6367814012629375845600550585519401421048120918000E-10L)
#define Q10 (+9.2735628025258751691201101171038802842096241836000E-12L)
#define Q11 (-1.2043588055228409310545597554680364005467044394286E-13L)
#define Q12 (+7.7202487533515444298369215094104897470942592271063E-16L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
P00 + z*(\
    P01 + z*(\
        P02 + z*(\
            P03 + z*(\
                P04 + z*(\
                    P05 + z*(\
                        P06 + z*(\
                            P07 + z*(\
                                P08 + z*(\
                                    P09 + z*(\
                                        P10 + z*(\
                                            P11 + z*P12\
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

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
Q00 + z*(\
    Q01 + z*(\
        Q02 + z*(\
            Q03 + z*(\
                Q04 + z*(\
                    Q05 + z*(\
                        Q06 + z*(\
                            Q07 + z*(\
                                Q08 + z*(\
                                    Q09 + z*(\
                                        Q10 + z*(\
                                            Q11 + z*Q12\
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

/*  128-bit quadruple. Even more terms to get ~1 x 10^-34 peak error.         */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN || \
      TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN

/******************************************************************************
 *                             128-bit quadruple                              *
 ******************************************************************************/

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define P01 (+5.3846153846153846153846153846153846153846153846154E-01L)
#define P02 (+1.4000000000000000000000000000000000000000000000000E-01L)
#define P03 (+2.3333333333333333333333333333333333333333333333333E-02L)
#define P04 (+2.7898550724637681159420289855072463768115942028986E-03L)
#define P05 (+2.5362318840579710144927536231884057971014492753623E-04L)
#define P06 (+1.8115942028985507246376811594202898550724637681159E-05L)
#define P07 (+1.0351966873706004140786749482401656314699792960663E-06L)
#define P08 (+4.7673531655225019069412662090007627765064836003051E-08L)
#define P09 (+1.7656863576009266322004689662965788061135124445574E-09L)
#define P10 (+5.1931951694144900947072616655781729591573895428160E-11L)
#define P11 (+1.1802716294123841124334685603586756725357703506400E-12L)
#define P12 (+1.9671193823539735207224476005977927875596172510667E-14L)
#define P13 (+2.1616696509384324403543380226349371291863925835898E-16L)
#define P14 (+1.1877305774386991430518340783708445764760398810933E-18L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define Q01 (-4.6153846153846153846153846153846153846153846153846E-01L)
#define Q02 (+1.0153846153846153846153846153846153846153846153846E-01L)
#define Q03 (-1.4102564102564102564102564102564102564102564102564E-02L)
#define Q04 (+1.3795986622073578595317725752508361204013377926421E-03L)
#define Q05 (-1.0033444816053511705685618729096989966555183946488E-04L)
#define Q06 (+5.5741360089186176142697881828316610925306577480491E-06L)
#define Q07 (-2.3889154323936932632584806497849976110845676063067E-07L)
#define Q08 (+7.8582744486634646817713179269243342469887092312722E-09L)
#define Q09 (-1.9403146786823369584620538091171195671577059830302E-10L)
#define Q10 (+3.4240847270864769855212714278537404126312458524062E-12L)
#define Q11 (-3.8910053716891783926378084407428868325355066504616E-14L)
#define Q12 (+2.1616696509384324403543380226349371291863925835898E-16L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
P00 + z*(\
    P01 + z*(\
        P02 + z*(\
            P03 + z*(\
                P04 + z*(\
                    P05 + z*(\
                        P06 + z*(\
                            P07 + z*(\
                                P08 + z*(\
                                    P09 + z*(\
                                        P10 + z*(\
                                            P11 + z*(\
                                                P12 + z*(\
                                                    P13 + z*P14\
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


/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
Q00 + z*(\
    Q01 + z*(\
        Q02 + z*(\
            Q03 + z*(\
                Q04 + z*(\
                    Q05 + z*(\
                        Q06 + z*(\
                            Q07 + z*(\
                                Q08 + z*(\
                                    Q09 + z*(\
                                        Q10 + z*(\
                                            Q11 + z*Q12\
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

/*  Lastly, portable and 80-bit extended. Peak error ~1 x 10^-19.             */
#else

/******************************************************************************
 *                         80-bit extended / portable                         *
 ******************************************************************************/

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define P01 (+5.2941176470588235294117647058823529411764705882353E-01L)
#define P02 (+1.3235294117647058823529411764705882352941176470588E-01L)
#define P03 (+2.0588235294117647058823529411764705882352941176471E-02L)
#define P04 (+2.2058823529411764705882352941176470588235294117647E-03L)
#define P05 (+1.6968325791855203619909502262443438914027149321267E-04L)
#define P06 (+9.4268476621417797888386123680241327300150829562594E-06L)
#define P07 (+3.6727977904448492683786801433860257389669154375037E-07L)
#define P08 (+9.1819944761121231709467003584650643474172885937592E-09L)
#define P09 (+1.1335795649521139717218148590697610305453442708345E-10L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define Q01 (-4.7058823529411764705882352941176470588235294117647E-01L)
#define Q02 (+1.0294117647058823529411764705882352941176470588235E-01L)
#define Q03 (-1.3725490196078431372549019607843137254901960784314E-02L)
#define Q04 (+1.2254901960784313725490196078431372549019607843137E-03L)
#define Q05 (-7.5414781297134238310708898944193061840120663650075E-05L)
#define Q06 (+3.1422825540472599296128707893413775766716943187531E-06L)
#define Q07 (-8.1617728676552205963970669853022794199264787500082E-08L)
#define Q08 (+1.0202216084569025745496333731627849274908098437510E-09L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
P00 + z*(\
    P01 + z*(\
        P02 + z*(\
            P03 + z*(\
                P04 + z*(\
                    P05 + z*(\
                        P06 + z*(\
                            P07 + z*(\
                                P08 + z*P09\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
Q00 + z*(\
    Q01 + z*(\
        Q02 + z*(\
            Q03 + z*(\
                Q04 + z*(\
                    Q05 + z*(\
                        Q06 + z*(\
                            Q07 + z*Q08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

#endif
/*  End of double vs. extended / portable vs. double-double vs. quadruple.    */

/*  Function for computing a Pade approximant of Exp.                         */
long double tmpl_LDouble_Exp_Pade(long double x)
{
    /*  Compute the numerator (p) and the denominator (q).                    */
    const long double p = TMPL_NUM_EVAL(x);
    const long double q = TMPL_DEN_EVAL(x);

    /*  Return the quotient.                                                  */
    return p / q;
}
/*  End of tmpl_LDouble_Exp_Pade.                                             */

/*  Undefine all macros in case someone wants to #include this file.          */
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
#undef P11
#undef P12
#undef P13
#undef P14
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
#undef Q11
#undef Q12
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
