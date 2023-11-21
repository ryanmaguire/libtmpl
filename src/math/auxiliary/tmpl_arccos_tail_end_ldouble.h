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
 *          64-bit double:                                                    *
 *              Order (10, 8) approximant.                                    *
 *          80-bit extended / portable:                                       *
 *              Order (12, 10) approximant.                                   *
 *          128-bit quadruple / 128-bit double-double:                        *
 *              Order (18, 18) approximant.                                   *
 *  Notes:                                                                    *
 *      Accurate for 0.5 <= x < 1.0.                                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2023                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_arccos_tail_end_ldouble.c to include this file. *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_TAIL_END_LDOUBLE_H
#define TMPL_ARCCOS_TAIL_END_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the numerator.                                           */
#define P0 (+1.66666666666666657415E-01L)
#define P1 (-3.25565818622400915405E-01L)
#define P2 (+2.01212532134862925881E-01L)
#define P3 (-4.00555345006794114027E-02L)
#define P4 (+7.91534994289814532176E-04L)
#define P5 (+3.47933107596021167570E-05L)

/*  Coefficients for the denominator.                                         */
#define Q0 (+1.00000000000000000000E+00L)
#define Q1 (-2.40339491173441421878E+00L)
#define Q2 (+2.02094576023350569471E+00L)
#define Q3 (-6.88283971605453293030E-01L)
#define Q4 (+7.70381505559019352791e-02L)

/*  Helper macro for evaluating the numerator of the minimax approximation.   */
#define TMPL_NUM_EVAL(z) P0 + z*(P1 + z*(P2 + z*(P3 + z*(P4 + z*P5))))

/*  Helper macro for evaluating the denominator of the minimax approximation. */
#define TMPL_DEN_EVAL(z) Q0 + z*(Q1 + z*(Q2 + z*(Q3 + z*Q4)))

/*  128-bit quadruple and double-double, a few more terms.                    */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN    || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *                 128-bit Quadruple / 128-bit Double-Double                  *
 ******************************************************************************/

/*  Coefficients for the numerator.                                           */
#define P0 (+1.66666666666666666666666666666700314E-01L)
#define P1 (-7.32816946414566252574527475428622708E-01L)
#define P2 (+1.34215708714992334609030036562143589E+00L)
#define P3 (-1.32483151677116409805070261790752040E+00L)
#define P4 (+7.61206183613632558824485341162121989E-01L)
#define P5 (-2.56165783329023486777386833928147375E-01L)
#define P6 (+4.80718586374448793411019434585413855E-02L)
#define P7 (-4.42523267167024279410230886239774718E-03L)
#define P8 (+1.44551535183911458253205638280410064E-04L)
#define P9 (-2.10558957916600254061591040482706179E-07L)

/*  Coefficients for the denominator.                                         */
#define Q0 (+1.00000000000000000000000000000000000E+00L)
#define Q1 (-4.84690167848739751544716485245697428E+00L)
#define Q2 (+9.96619113536172610135016921140206980E+00L)
#define Q3 (-1.13177895428973036660836798461641458E+01L)
#define Q4 (+7.74004374389488266169304117714658761E+00L)
#define Q5 (-3.25871986053534084709023539900339905E+00L)
#define Q6 (+8.27830318881232209752469022352928864E-01L)
#define Q7 (-1.18768052702942805423330715206348004E-01L)
#define Q8 (+8.32600764660522313269101537926539470E-03L)
#define Q9 (-1.99407384882605586705979504567947007E-04L)

/*  Helper macro for evaluating the numerator of the minimax approximation.   */
#define TMPL_NUM_EVAL(z) \
P0+z*(P1+z*(P2+z*(P3+z*(P4+z*(P5+z*(P6+z*(P7+z*(P8+z*P9))))))))

/*  Helper macro for evaluating the denominator of the minimax approximation. */
#define TMPL_DEN_EVAL(z) \
Q0+z*(Q1+z*(Q2+z*(Q3+z*(Q4+z*(Q5+z*(Q6+z*(Q7+z*(Q8+z*Q9))))))))


/*  Lastly, extended precision and portable versions.                         */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the numerator.                                           */
#define P0 (+1.66666666666666666631E-01L)
#define P1 (-4.16313987993683104320E-01L)
#define P2 (+3.69068046323246813704e-01L)
#define P3 (-1.36213932016738603108E-01L)
#define P4 (+1.78324189708471965733E-02L)
#define P5 (-2.19216428382605211588E-04L)
#define P6 (-7.10526623669075243183E-06L)

/*  Coefficients for the denominator.                                         */
#define Q0 (+1.00000000000000000000E+00L)
#define Q1 (-2.94788392796209867269E+00L)
#define Q2 (+3.27309890266528636716E+00L)
#define Q3 (-1.68285799854822427013E+00L)
#define Q4 (+3.90699412641738801874E-01L)
#define Q5 (-3.14365703596053263322E-02L)

/*  Helper macro for evaluating the numerator of the minimax approximation.   */
#define TMPL_NUM_EVAL(z) P0 + z*(P1 + z*(P2 + z*(P3 + z*(P4 + z*(P5 + z*P6)))))

/*  Helper macro for evaluating the denominator of the minimax approximation. */
#define TMPL_DEN_EVAL(z) Q0 + z*(Q1 + z*(Q2 + z*(Q3 + z*(Q4 + z*Q5))))

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
    const long double s = tmpl_LDouble_Sqrt(z);
    const long double t = r*s;

    /*  We now have asin(sqrt(z)) - sqrt(z). We need 2*asin(sqrt(z)).         */
    return 2.0L*(s + t);
}
/*  End of tmpl_LDouble_Arccos_Tail_End.                                      */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef P9
#undef P8
#undef P7
#undef P6
#undef P5
#undef P4
#undef P3
#undef P2
#undef P1
#undef P0
#undef Q9
#undef Q8
#undef Q7
#undef Q6
#undef Q5
#undef Q4
#undef Q3
#undef Q2
#undef Q1
#undef Q0
#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#endif
/*  End of include guard.                                                     */
