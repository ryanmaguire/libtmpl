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
 *                        tmpl_arcsin_aux_remez_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Remez polynomial for (asin(x) - x) / x at long double      *
 *      precision.                                                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arcsin_Aux_Remez                                         *
 *  Purpose:                                                                  *
 *      Computes a Remez polynomial for (asin(x) - x) / x with |x| < 1/8.     *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number in the interval [-1/8, 1/8].                        *
 *  Output:                                                                   *
 *      asin_aux_x (double):                                                  *
 *          (asin(x) - x) / x to long double precision.                       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The function                                                          *
 *                                                                            *
 *                 asin(x) - x                                                *
 *          f(x) = -----------                                                *
 *                       3                                                    *
 *                      x                                                     *
 *                                                                            *
 *      is even, so the degree 2N Remez polynomial for f(x) on [-1/8, 1/8]    *
 *      only requires N + 1 non-zero terms. The value for N depends on how    *
 *      long double is represented:                                           *
 *                                                                            *
 *          long double           |  N                                        *
 *          --------------------------                                        *
 *          64-bit double         |  5                                        *
 *          80-bit extended       |  6                                        *
 *          128-bit double-double | 11                                        *
 *          128-bit quadruple     | 12                                        *
 *                                                                            *
 *      The polynomial is evaluated using Horner's method and then x^2 * p(x) *
 *      is returned, where p is the Remez polynomial.                         *
 *  Notes:                                                                    *
 *      1.) Accurate to long double precision for |x| < 1/8. There are no     *
 *          checks that the input falls within this interval.                 *
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

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.6666666666666656293481345275688480130071045466573E-01L)
#define A01 (+7.5000000000477049774617709946013607390518865927319E-02L)
#define A02 (+4.4642856787430947600823955193235375582518886056675E-02L)
#define A03 (+3.0382041227401833288830911184935457270396756757083E-02L)
#define A04 (+2.2360264850884186132567530659511508895783907274177E-02L)
#define A05 (+1.8023799292951331941625122396560343869425939766530E-02L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z * (A01 + z * (A02 + z * (A03 + z * (A04 + z * A05))))

/*  128-bit double-double, about twice as many terms.                         */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                       128-Bit Double-Double Version                        *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.6666666666666666666666666666650801563459296797261E-01L)
#define A01 (+7.5000000000000000000000002921078288357563018705190E-02L)
#define A02 (+4.4642857142857142857133955806498456536566136984720E-02L)
#define A03 (+3.0381944444444444455065952526682092320737033792116E-02L)
#define A04 (+2.2372159090909084362783089309970878384551781540477E-02L)
#define A05 (+1.7352764423079302836761646229527055203624389802329E-02L)
#define A06 (+1.3964843749451814072348041215769837733622409013824E-02L)
#define A07 (+1.1551800979214711052592002771784718265428063029493E-02L)
#define A08 (+9.7616011386005259792014789854672168510509277972823E-03L)
#define A09 (+8.3908946609919742021824322724392283153903674759310E-03L)
#define A10 (+7.2889955719919267899350671384505919317466682959182E-03L)
#define A11 (+7.0118676554865279118455669446994902081183104820556E-03L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * (\
                        A06 + z * (\
                            A07 + z * (\
                                A08 + z * (\
                                    A09 + z * (\
                                        A10 + z * A11\
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

/*  128-bit quadruple, one more term than double-double.                      */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                         128-Bit Quadruple Version                          *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.6666666666666666666666666666666722739440103912923E-01L)
#define A01 (+7.4999999999999999999999999987882605605509077824030E-02L)
#define A02 (+4.4642857142857142857142900526846026309606521614400E-02L)
#define A03 (+3.0381944444444444444383426387688183587186043396336E-02L)
#define A04 (+2.2372159090909090953667834829714223495796450001725E-02L)
#define A05 (+1.7352764423076903703505742042575216575489518753208E-02L)
#define A06 (+1.3964843750005401729905623217200458625820707752116E-02L)
#define A07 (+1.1551800895131180242694569600834589747547449316008E-02L)
#define A08 (+9.7616096579528186187780592268255893528440091865881E-03L)
#define A09 (+8.3903245389259487526662069662823174312663048391020E-03L)
#define A10 (+7.3131905709624049288776573912037613865795964638348E-03L)
#define A11 (+6.4220142312067902125688806299949018463509663783968E-03L)
#define A12 (+6.2913919218900638347386961861062007121310121591162E-03L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * (\
                        A06 + z * (\
                            A07 + z * (\
                                A08 + z * (\
                                    A09 + z * (\
                                        A10 + z * (\
                                            A11 + z * A12\
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

/*  Lastly, extended precision and portable versions.                         */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.6666666666666666700442162815180844395382956632851E-01L)
#define A01 (+7.4999999999997885286068802318564357188466359014323E-02L)
#define A02 (+4.4642857145018588779832262641102930143966755506640E-02L)
#define A03 (+3.0381943616315804443776120608313159279642645662858E-02L)
#define A04 (+2.2372310052653463519084497450088352248052177701291E-02L)
#define A05 (+1.7338663457635806212815287046141048197931957569644E-02L)
#define A06 (+1.4614928569071617091374277717995964893248209045187E-02L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z * (A01 + z * (A02 + z * (A03 + z * (A04 + z * (A05 + z * A06)))))

#endif
/*  End of 80-bit extended / portable version.                                */

/*  Computes a Remez polynomial for (asin(x) - x) / x.                        */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
long double
tmpl_LDouble_Arcsin_Aux_Remez(const long double x)
TMPL_UNSEQUENCED
{
    /*  The Remez polynomial for (asin(x) - x) / x^3 is even. Compute x^2.    */
    const long double x2 = x * x;

    /*  Evaluate the Remez polynomial using Horner's method.                  */
    const long double poly = TMPL_POLY_EVAL(x2);

    /*  (asin(x) - x) / x is given by scaling the polynomial by x^2.          */
    return x2 * poly;
}
/*  End of tmpl_LDouble_Arcsin_Aux_Remez.                                     */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>
