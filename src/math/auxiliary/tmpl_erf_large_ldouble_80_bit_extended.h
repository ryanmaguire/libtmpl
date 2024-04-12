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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_LARGE_LDOUBLE_80_BIT_EXTENDED_H
#define TMPL_ERF_LARGE_LDOUBLE_80_BIT_EXTENDED_H

/*  TMPL_LDOUBLE_ENDIANNESS and TMPL_STATIC_INLINE macros provided here.      */
#include <libtmpl/include/tmpl_config.h>

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT || \
    TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_UNKNOWN

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+9.9989937807788036323635832885122809589876532463142E-01L)
#define A01 (+5.8627724709379212521151997617098240278823190111526E-04L)
#define A02 (-1.6122624295079605131779043827977279521826859462200E-03L)
#define A03 (+2.7603887050666346001119241282240159201336902001535E-03L)
#define A04 (-3.2581136596283511965117890635398924470431214963537E-03L)
#define A05 (+2.7558084140724342830912926405148839738704968019889E-03L)
#define A06 (-1.6573274037287921173109161327905504010508614212512E-03L)
#define A07 (+6.4604095669747884549284532138948869722683318865705E-04L)
#define A08 (-8.9011570316959968193077722162748255362813654118975E-05L)
#define A09 (-7.1223115003303988657653747483508977376957685797503E-05L)
#define A10 (+5.4996984964897677939909481418356138019310183751684E-05L)
#define A11 (-1.5843802783368981690606932710737427272822767214297E-05L)
#define A12 (-1.0710950423647716673949539429271238703752108307227E-06L)
#define A13 (+2.6875461229458660229508208746488977613173519522369E-06L)
#define A14 (-9.1470625797851390711631904697835090811081496155858E-07L)
#define A15 (+2.6252179721205560549194843830059334723993239047100E-09L)
#define A16 (+1.0608595445175885442214082072254139334207918098020E-07L)
#define A17 (-3.4567670091037935381619858083427149348537186047186E-08L)
#define A18 (-8.9259248309398096801001006886456486273254683992665E-10L)
#define A19 (+3.6430256361603963515661296803040028481207426454318E-09L)
#define A20 (-6.4717419948608016028278457547752148379679145050239E-10L)
#define A21 (-1.2495917799113807348468967036653329609734182770574E-10L)

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define B00 (+9.9999999814942586268080791999424627365073300324196E-01L)
#define B01 (+1.6143993721484878476502150138218276660937644118822E-08L)
#define B02 (-6.8611973329834335160324534285817221329659694405963E-08L)
#define B03 (+1.8901925958733821400546333047519035680227632861722E-07L)
#define B04 (-3.7879526812035725775915021048092744461195132897912E-07L)
#define B05 (+5.8724618649493181103404725583257078038450250411079E-07L)
#define B06 (-7.3092004129062304117380947027285694139867504381953E-07L)
#define B07 (+7.4772512184216052762841361817311021754368610344585E-07L)
#define B08 (-6.3783205489138669586051094558810701029943738697808E-07L)
#define B09 (+4.5700688555615779914491638055254859560210148230008E-07L)
#define B10 (-2.7506450545984283776665055552875228114420474760813E-07L)
#define B11 (+1.3776263939094284258032088226010188212037580082979E-07L)
#define B12 (-5.5901560260883951209381335136368518776246850202047E-08L)
#define B13 (+1.7134617994755708363010482002480757408362752413017E-08L)
#define B14 (-3.0406686522816531901255791326976586870572672696646E-09L)
#define B15 (-4.1735176035008468245046716234031844411669289270722E-10L)
#define B16 (+5.8956827701154581270011973820457869467598645027570E-10L)
#define B17 (-2.3188206629950464004528258219920470100136568358511E-10L)
#define B18 (+3.7408042527273864592543066056056879362218521835659E-11L)

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define C00 (+9.9999999999999957689593618880168470082118936684967E-01L)
#define C01 (+4.9377125142957475448585183902161330507382375394995E-15L)
#define C02 (-2.8421097017671547241281695076953981103748093010317E-14L)
#define C03 (+1.0726500771264432354425237761169047290476127563768E-13L)
#define C04 (-2.9783312726376697942429925109706498074231127283775E-13L)
#define C05 (+6.5365305789161144940256770559495477006592256635094E-13L)
#define C06 (-1.1886385276562450005617705459775123349486112011927E-12L)
#define C07 (+1.7888908705631124106865466459726489704608795450276E-12L)
#define C08 (-2.2112552729418656329870964998597045284333444727873E-12L)
#define C09 (+2.5220900474514618728719033877741760359372149477406E-12L)
#define C10 (-2.9052364281407988630812637199579783782816875292767E-12L)
#define C11 (+2.4878061504537807226302487412347203368275515585083E-12L)
#define C12 (-1.1121746765195779818878055112181230750436218799058E-12L)
#define C13 (+8.7407930360096652269080431167070638454500059860915E-13L)
#define C14 (-1.4773037930994547065804917753405876081892015198301E-12L)
#define C15 (+7.9786406846682354132513752066875154368253792758206E-13L)

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
                                B16 + z*(\
                                  B17 + z*B18\
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
                    C10 + z*(\
                      C11 + z*(\
                        C12 + z*(\
                          C13 + z*(\
                            C14 + z*C15\
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
long double tmpl_LDouble_Erf_Large(long double x)
{
    /*  For large enough values use the limit, erf(infinity) = 1.             */
    if (x >= 6.5L)
        return 1.0L;

    /*  For values in [2, 4] use the first polynomial.                        */
    else if (x < 3.5L)
    {
        /*  Shift the interval [2, 4] to [-1, 1] for the polynomial.          */
        const long double z = x - 2.75L;
        return TMPL_POLYA_EVAL(z);
    }

    /*  Lastly, use the second Remez polynomial for arguments in [4, 6].      */
    else if (x < 5.0L)
    {
        /*  Shift the interval [4, 6] to [-1, 1] for the polynomial.          */
        const long double z = x - 4.25L;
        return TMPL_POLYB_EVAL(z);
    }
    else
    {
        const long double z = x - 5.75L;
        return TMPL_POLYC_EVAL(z);
    }
}
/*  End of tmpl_LDouble_Erf_Large.                                            */

/*  #undef everything in case someone wants to #include this file.            */
#include "tmpl_math_undef.h"

#endif
/*  End of check for 80-bit extended long double.                             */

#endif
/*  End of include guard.                                                     */
