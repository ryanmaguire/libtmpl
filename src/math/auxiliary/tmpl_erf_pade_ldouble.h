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
 *                           tmpl_erf_pade_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (12, 12) Pade approximant of erf(x).                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Erf_Pade                                                 *
 *  Purpose:                                                                  *
 *      Computes the (12, 12) Pade approximant of erf(x) for small values x.  *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      erf_x (long double):                                                  *
 *          The error function erf(x).                                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator and *
 *      denominator and return the rational function.                         *
 *  Notes:                                                                    *
 *      Only accurate for small values.                                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 27, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_PADE_LDOUBLE_H
#define TMPL_ERF_PADE_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P00 (+1.1283791670955125738961589031215451716881012586580E+00L)
#define P01 (+1.6589927860831881745295128899660099252749208955960E-01L)
#define P02 (+5.6463156917715860078254897500432845771669096012972E-02L)
#define P03 (+3.9289711546131419638119038912791801652075485138083E-03L)
#define P04 (+5.8460125960947762569846264702268242114998471063106E-04L)
#define P05 (+2.3352720665193956361352780797976002834961601465771E-05L)
#define P06 (+1.9990991478914900893746992665695764284975151655562E-06L)
#define P07 (+4.6586611149336123416340145934047327429003051039399E-08L)
#define P08 (+2.4527375988661917340113832201295649047561848268120E-09L)
#define P09 (+2.9466263811762561507392546461820906873692213975174E-11L)
#define P10 (+8.9190519793909352192030226556697365160970216632138E-13L)
#define P11 (+3.2448599594752976622498686177568075617273170400713E-15L)
#define P12 (+3.0191117500857256422613963146944917621778483499540E-17L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define Q01 (+4.8035774094921422619281704391562167390543583239488E-01L)
#define Q02 (+1.1015841693961536020224266628283974203301342752788E-01L)
#define Q03 (+1.5975182054352884514766719613379881772480911569859E-02L)
#define Q04 (+1.6347678083320324884824812255207977775765288829726E-03L)
#define Q05 (+1.2461698537667184258878426702330400974230634458334E-04L)
#define Q06 (+7.2724489210934821839418014967049133121462601175666E-06L)
#define Q07 (+3.2819221478373822988356333716101029369631237194112E-07L)
#define Q08 (+1.1398272938001464366315589569114241898101802752792E-08L)
#define Q09 (+2.9802895219121814306328628528522433267788914709566E-10L)
#define Q10 (+5.5878948648770099869289895682284695762957412106586E-12L)
#define Q11 (+6.7718516451867134345777284893008145736615741503498E-14L)
#define Q12 (+4.0291980440236012355280280177971662778638655035154E-16L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
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

/*  Function for computing the (12, 12) Pade approximant of erf(x).           */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Erf_Pade(long double x)
{
    /*  Both polynomials are even. Computing x^2 and work with that.          */
    const long double x2 = x*x;

    /*  Compute the two polynomials using Horner's method.                    */
    const long double num = TMPL_NUM_EVAL(x2);
    const long double den = TMPL_DEN_EVAL(x2);

    /*  The rational function approximates erf(x)/x. Return x*num/den.        */
    return x*num/den;
}
/*  End of tmpl_LDouble_Erf_Pade.                                             */

/*  #undef everything in case someone wants to #include this file.            */
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL
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
#undef Q12
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

#endif
/*  End of include guard.                                                     */
