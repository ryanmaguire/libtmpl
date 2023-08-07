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
 *                          tmpl_arcsin_pade_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Pade approximation for asin(x) at long double precision. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arcsin_Pade                                              *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant for arcsin.                             *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      asin_x (long double):                                                 *
 *          The Pade approximation of asin(x).                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator.                                                      *
 *                                                                            *
 *          asin(x) - x   a0 + a1*x^2 + ... + an*x^2n                         *
 *          ----------- = ---------------------------                         *
 *              x^3        1 + b1*x^2 + ... + bn*x^2n                         *
 *                                                                            *
 *      64-bit double:                                                        *
 *          Order (12, 12) approximant.                                       *
 *      80-bit extended / portable:                                           *
 *          Order (14, 14) approximant.                                       *
 *      128-bit quadruple / 128-bit double-double:                            *
 *          Order (20, 20) approximant.                                       *
 *  Notes:                                                                    *
 *      64-bit double:                                                        *
 *          Accurate to double precision for |x| < 0.5. For |x| < 0.9 the     *
 *          approximation is accurate to 7 decimals.                          *
 *      80-bit extended / portable:                                           *
 *          Accurate to extended precision for |x| < 0.5. For |x| < 0.9 the   *
 *          approximation is accurate to 7 decimals.                          *
 *      128-bit quadruple / 128-bit double-double.                            *
 *          Accurate to quadruple precision for |x| < 0.4. For |x| < 0.9 the  *
 *          approximation is accurate to 10 decimals.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 9, 2023                                                   *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/06/01: Ryan Maguire                                                  *
 *      Changed so that this computes an actual Pade approximant. It was a    *
 *      Remez rational minimax approximation before, improperly labelled.     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCSIN_PADE_LDOUBLE_H
#define TMPL_ARCSIN_PADE_LDOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P00 (+1.6666666666666666666666666666666666666666666666667E-01L)
#define P01 (-4.5183467789315450573566044285447580081757824962844E-01L)
#define P02 (+4.5268338285839953885847747489466534382453836599311E-01L)
#define P03 (-2.0451170074586957459619221134199241262964264122754E-01L)
#define P04 (+4.0161699156136797388526896443437389593682105247059E-02L)
#define P05 (-2.6043612272315037174810668430207303056407157408729E-03L)
#define P06 (+8.5298365158969137130716621168483153368286640425841E-06L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define Q01 (-3.1610080673589270344139626571268548049054694977706E+00L)
#define Q02 (+3.8706967846047715414942909022179338680118343270983E+00L)
#define Q03 (-2.3044768347428901379839394147005695603073114886090E+00L)
#define Q04 (+6.8318346338074073586036792129413385817260793401216E-01L)
#define Q05 (-9.1189047491786682631147583983250333633502470655541E-02L)
#define Q06 (+3.9268447888541310343247866236378900929051188393826E-03L)

/*  Helper macro for evaluating the numerator of the Pade approximant.        */
#define TMPL_NUM_EVAL(z) \
P00 + z*(P01 + z*(P02 + z*(P03 + z*(P04 + z*(P05 + z*P06)))))

/*  Helper macro for evaluating the denominator of the Pade approximant.      */
#define TMPL_DEN_EVAL(z) \
Q00 + z*(Q01 + z*(Q02 + z*(Q03 + z*(Q04 + z*(Q05 + z*Q06)))))

/*  128-bit quadruple and double-double, a few more terms.                    */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN    || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *                 128-bit Quadruple / 128-bit Double-Double                  *
 ******************************************************************************/

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P00 (+1.6666666666666666666666666666666666666666666666667E-01L)
#define P01 (-7.8682500568726055925843694065973326855444485450780E-01L)
#define P02 (+1.5721341786076528353814217938892330715194211561461E+00L)
#define P03 (-1.7303891076558164206396109193149035836590644653198E+00L)
#define P04 (+1.1437428458486714430351653594882968858132473452772E+00L)
#define P05 (-4.6405478105637879335157547564210714507166140979443E-01L)
#define P06 (+1.1329993924503889845020138649231881546511699128038E-01L)
#define P07 (-1.5598729920199485781533686807445522007188051495647E-02L)
#define P08 (+1.0523468584330608894211030919509078554327894950815E-03L)
#define P09 (-2.4836981037464416279136657080479798442829474805605E-05L)
#define P10 (+2.2760364811669201318172963972027670732967992154397E-08L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define Q01 (-5.1709500341235633555506216439583996113266691270468E+00L)
#define Q02 (+1.1491875444144377665143453360259535397070670901190E+01L)
#define Q03 (-1.4350894360469152098153541111469736344268926133662E+01L)
#define Q04 (+1.1050566760189461204736744884894201548326306874065E+01L)
#define Q05 (-5.4179719810735343203956660801549025693235949938006E+00L)
#define Q06 (+1.6859664488220793128678557866152417689475914580501E+00L)
#define Q07 (-3.2163466246421089760770186386008114855796490616118E-01L)
#define Q08 (+3.4858159093987721955956543688516745723391107424080E-02L)
#define Q09 (-1.8419912821038033469525716596748032646541329283969E-03L)
#define Q10 (+3.2935571401685268966454609597775835814483845840333E-05L)

/*  Helper macro for evaluating the numerator of the Pade approximant.        */
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
                                    P09 + z*P10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Helper macro for evaluating the denominator of the Pade approximant.      */
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

/*  Lastly, extended precision and portable versions.                         */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P00 (+1.6666666666666666666666666666666666666666666666667E-01L)
#define P01 (-5.3573326769405420816393341782881509990761203454372E-01L)
#define P02 (+6.6987758889115211750747634491190241241775771566337E-01L)
#define P03 (-4.0975961857187703437256612304838429537335133802760E-01L)
#define P04 (+1.2604458970786184280594914762157680635033223820909E-01L)
#define P05 (-1.7779970446209616665880258200688356097871890998536E-02L)
#define P06 (+8.4937383297103285108739995420852009073640185085804E-04L)
#define P07 (-1.9067288402719086953642842729138569648135874825351E-06L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define Q01 (-3.6643996061643252489836005069728905994456722072623E+00L)
#define Q02 (+5.4003882132637162099446211547520723871142416443911E+00L)
#define Q03 (-4.0894884652725854756851070745133807453995212364344E+00L)
#define Q04 (+1.6837613474905420665264405525852747541955827534249E+00L)
#define Q05 (-3.6565290180353386952194977935294488267885730631395E-01L)
#define Q06 (+3.6937863813830793659677653967692005806636822071947E-02L)
#define Q07 (-1.2264650631348465850650285033738693891166864249171E-03L)

/*  Helper macro for evaluating the numerator of the Pade approximant.        */
#define TMPL_NUM_EVAL(z) \
P00 + z*(P01 + z*(P02 + z*(P03 + z*(P04 + z*(P05 + z*(P06 + z*P07))))))

/*  Helper macro for evaluating the denominator of the Pade approximant.      */
#define TMPL_DEN_EVAL(z) \
Q00 + z*(Q01 + z*(Q02 + z*(Q03 + z*(Q04 + z*(Q05 + z*(Q06 + z*Q07))))))

#endif
/*  End of 80-bit extended / portable version.                                */

/*  Function for computing a Pade approximant for asin(x).                    */
TMPL_INLINE_DECL
long double tmpl_LDouble_Arcsin_Pade(long double x)
{
    /*  The polynomials for the numerator and denominator are in terms of x^2.*/
    const long double x2 = x*x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const long double p = TMPL_NUM_EVAL(x2);
    const long double q = TMPL_DEN_EVAL(x2);
    const long double r = x2*p/q;

    /*  p/q is the Pade approximant for (asin(x) - x) / x^3.                  */
    return x*r + x;
}
/*  End of tmpl_LDouble_Arcsin_Pade.                                          */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef P10
#undef P09
#undef P08
#undef P07
#undef P06
#undef P05
#undef P04
#undef P03
#undef P02
#undef P01
#undef P00
#undef Q10
#undef Q09
#undef Q08
#undef Q07
#undef Q06
#undef Q05
#undef Q04
#undef Q03
#undef Q02
#undef Q01
#undef Q00
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
/*  End of include guard.                                                     */
