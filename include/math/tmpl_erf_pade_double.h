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
 *                            tmpl_erf_pade_double                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (11, 10) Pade approximant of erf(x) at double precision. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Erf_Pade                                                  *
 *  Purpose:                                                                  *
 *      Computes the (11, 10) Pade approximant of erf(x) for small values x.  *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      erf_x (double):                                                       *
 *          The error function erf(x).                                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator and *
 *      denominator and return the rational function.                         *
 *  Notes:                                                                    *
 *      Only accurate for small values. For |x| < 2.0 this is accurate to     *
 *      double precision.                                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2023                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_PADE_DOUBLE_H
#define TMPL_ERF_PADE_DOUBLE_H

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only use this if inline support is requested.                             */
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P00 (+1.1283791670955125738961589031215451716881012586580E+00)
#define P01 (+1.3653604987966495586759211697688576442102221718998E-01)
#define P02 (+5.1749133386331750867416850723259001188283157239959E-02)
#define P03 (+2.4316284696759906599288677259840268557633830749782E-03)
#define P04 (+4.6724898712633391616817912325854332677568125784928E-04)
#define P05 (+8.2748907784525578542265891799668747374356153949248E-06)
#define P06 (+1.2993768166544340284101444199351220440258275251957E-06)
#define P07 (+9.5146727147910885118295044945368149310190099334500E-10)
#define P08 (+1.1653924592589693265755658699861476701051666158678E-09)
#define P09 (-1.0592917112358296163564609423396699252176257453128E-11)
#define P10 (+2.6225647239024354498309699672857904473355453412759E-13)
#define P11 (-1.8721668968551161430076646564833193258373167964434E-15)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q01 (+4.5433525703165321793713952696915566055766450963636E-01)
#define Q02 (+9.7306561053031198753533806640862178828014980510042E-02)
#define Q03 (+1.2966493079893235539347383946872136482829045221529E-02)
#define Q04 (+1.1934733781148156515473334093334593461697728881847E-03)
#define Q05 (+7.9503254446977902246140071403945252033553190881098E-05)
#define Q06 (+3.8937469301963061308939118212122507616535952301508E-06)
#define Q07 (+1.3891904295612107743984285323591842884545912726076E-07)
#define Q08 (+3.4688006200049841307862289443809148909455195966759E-09)
#define Q09 (+5.4982384616278628969068662342409107278264509429937E-11)
#define Q10 (+4.2222830653999861528042975603679694167280283946607E-13)

/*  Helper macros for evaluating the polynomials via Horner's method.         */
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
                                        P10 + z*P11\
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
                                    Q09 + z*Q10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Function for computing the (11, 10) Pade approximant of erf(x).           */
TMPL_INLINE_DECL
double tmpl_Double_Erf_Pade(double x)
{
    /*  Both polynomials are even. Computing x^2 and work with that.          */
    const double x2 = x*x;

    /*  Compute the two polynomials using Horner's method.                    */
    const double num = TMPL_NUM_EVAL(x2);
    const double den = TMPL_DEN_EVAL(x2);

    /*  The rational function approximates erf(x)/x. Return x*num/den.        */
    return x*num/den;
}
/*  End of tmpl_Double_Erf_Pade.                                              */

/*  #undef everything in case someone wants to #include this file.            */
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
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of TMPL_ERF_PADE_DOUBLE_H.                                            */
