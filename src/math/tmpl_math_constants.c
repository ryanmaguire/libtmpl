/******************************************************************************
 *                                 LICENSE                                    *
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
 *                           tmpl_math_constants                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides definitions for various constants that are declared in       *
 *      tmpl_math.h. Float, double, and long double precisions are provided.  *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *      Header file where all of these constants are declared.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 7, 2021                                                   *
 ******************************************************************************/

/*  All constants are declared in this header file.                           */
#include <libtmpl/include/tmpl_math.h>

#include <libtmpl/include/constants/tmpl_math_constants.h>

#if TMPL_HAS_IEEE754_FLOAT == 0  || \
    TMPL_HAS_IEEE754_DOUBLE == 0 || \
    TMPL_HAS_IEEE754_LDOUBLE == 0
#include <float.h>
#endif

/******************************************************************************
 *                              Multiples of Pi                               *
 ******************************************************************************/
const float tmpl_float_pi = TMPL_FLOAT_PI;
const double tmpl_double_pi = TMPL_DOUBLE_PI;
const long double tmpl_ldouble_pi = TMPL_LDOUBLE_PI;

const float tmpl_float_two_pi = TMPL_FLOAT_TWO_PI;
const double tmpl_double_two_pi = TMPL_DOUBLE_TWO_PI;
const long double tmpl_ldouble_two_pi = TMPL_LDOUBLE_TWO_PI;

const float tmpl_float_four_pi = TMPL_FLOAT_FOUR_PI;
const double tmpl_double_four_pi = TMPL_DOUBLE_FOUR_PI;
const long double tmpl_ldouble_four_pi = TMPL_LDOUBLE_FOUR_PI;

const float tmpl_float_eight_pi = TMPL_FLOAT_EIGHT_PI;
const double tmpl_double_eight_pi = TMPL_DOUBLE_EIGHT_PI;
const long double tmpl_ldouble_eight_pi = TMPL_LDOUBLE_EIGHT_PI;

/******************************************************************************
 *                          Fractional Values of Pi                           *
 ******************************************************************************/
const float tmpl_float_pi_by_two = TMPL_FLOAT_PI_BY_TWO;
const double tmpl_double_pi_by_two = TMPL_DOUBLE_PI_BY_TWO;
const long double tmpl_ldouble_pi_by_two = TMPL_LDOUBLE_PI_BY_TWO;

const float tmpl_float_pi_by_three = TMPL_FLOAT_PI_BY_THREE;
const double tmpl_double_pi_by_three = TMPL_DOUBLE_PI_BY_THREE;
const long double tmpl_ldouble_pi_by_three = TMPL_LDOUBLE_PI_BY_THREE;

const float tmpl_float_pi_by_four = TMPL_FLOAT_PI_BY_FOUR;
const double tmpl_double_pi_by_four = TMPL_DOUBLE_PI_BY_FOUR;
const long double tmpl_ldouble_pi_by_four = TMPL_LDOUBLE_PI_BY_FOUR;

const float tmpl_float_pi_by_five = TMPL_FLOAT_PI_BY_FIVE;
const double tmpl_double_pi_by_five = TMPL_DOUBLE_PI_BY_FIVE;
const long double tmpl_ldouble_pi_by_five = TMPL_LDOUBLE_PI_BY_FIVE;

const float tmpl_float_pi_by_six = TMPL_FLOAT_PI_BY_SIX;
const double tmpl_double_pi_by_six = TMPL_DOUBLE_PI_BY_SIX;
const long double tmpl_ldouble_pi_by_six = TMPL_LDOUBLE_PI_BY_SIX;

const float tmpl_float_pi_by_eight = TMPL_FLOAT_PI_BY_EIGHT;
const double tmpl_double_pi_by_eight = TMPL_DOUBLE_PI_BY_EIGHT;
const long double tmpl_ldouble_pi_by_eight = TMPL_LDOUBLE_PI_BY_EIGHT;

const float tmpl_float_pi_by_twelve = TMPL_FLOAT_PI_BY_TWELVE;
const double tmpl_double_pi_by_twelve = TMPL_DOUBLE_PI_BY_TWELVE;
const long double tmpl_ldouble_pi_by_twelve = TMPL_LDOUBLE_PI_BY_TWELVE;

const float tmpl_float_three_pi_by_four = TMPL_FLOAT_THREE_PI_BY_FOUR;
const double tmpl_double_three_pi_by_four = TMPL_DOUBLE_THREE_PI_BY_FOUR;
const long double tmpl_ldouble_three_pi_by_four = TMPL_LDOUBLE_THREE_PI_BY_FOUR;

const float tmpl_float_pi_by_sqrt_two = TMPL_FLOAT_PI_BY_SQRT_TWO;
const double tmpl_double_pi_by_sqrt_two = TMPL_DOUBLE_PI_BY_SQRT_TWO;
const long double tmpl_ldouble_pi_by_sqrt_two = TMPL_LDOUBLE_PI_BY_SQRT_TWO;

/******************************************************************************
 *                      Conversions Radians and Degrees                       *
 ******************************************************************************/
const float tmpl_float_rad_to_deg = TMPL_FLOAT_RAD_TO_DEG;
const double tmpl_double_rad_to_deg = TMPL_DOUBLE_RAD_TO_DEG;
const long double tmpl_ldouble_rad_to_deg = TMPL_LDOUBLE_RAD_TO_DEG;

const float tmpl_float_deg_to_rad = TMPL_FLOAT_DEG_TO_RAD;
const double tmpl_double_deg_to_rad = TMPL_DOUBLE_DEG_TO_RAD;
const long double tmpl_ldouble_deg_to_rad = TMPL_LDOUBLE_DEG_TO_RAD;

/******************************************************************************
 *                            Multiples of 1 / Pi                             *
 ******************************************************************************/
const float tmpl_float_rcpr_pi = TMPL_FLOAT_RCPR_PI;
const double tmpl_double_rcpr_pi = TMPL_DOUBLE_RCPR_PI;
const long double tmpl_ldouble_rcpr_pi = TMPL_LDOUBLE_RCPR_PI;

const float tmpl_float_two_by_pi = TMPL_FLOAT_TWO_BY_PI;
const double tmpl_double_two_by_pi = TMPL_DOUBLE_TWO_BY_PI;
const long double tmpl_ldouble_two_by_pi = TMPL_LDOUBLE_TWO_BY_PI;

const float tmpl_float_rcpr_two_pi = TMPL_FLOAT_RCPR_TWO_PI;
const double tmpl_double_rcpr_two_pi = TMPL_DOUBLE_RCPR_TWO_PI;
const long double tmpl_ldouble_rcpr_two_pi = TMPL_LDOUBLE_RCPR_TWO_PI;

const float tmpl_float_rcpr_four_pi = TMPL_FLOAT_RCPR_FOUR_PI;
const double tmpl_double_rcpr_four_pi = TMPL_DOUBLE_RCPR_FOUR_PI;
const long double tmpl_ldouble_rcpr_four_pi = TMPL_LDOUBLE_RCPR_FOUR_PI;

/******************************************************************************
 *                           Multiples of Sqrt(Pi)                            *
 ******************************************************************************/
const float tmpl_float_sqrt_pi = TMPL_FLOAT_SQRT_PI;
const double tmpl_double_sqrt_pi = TMPL_DOUBLE_SQRT_PI;
const long double tmpl_ldouble_sqrt_pi = TMPL_LDOUBLE_SQRT_PI;

const float tmpl_float_sqrt_two_pi = TMPL_FLOAT_SQRT_TWO_PI;
const double tmpl_double_sqrt_two_pi = TMPL_DOUBLE_SQRT_TWO_PI;
const long double tmpl_ldouble_sqrt_two_pi = TMPL_LDOUBLE_SQRT_TWO_PI;

const float tmpl_float_sqrt_pi_by_two = TMPL_FLOAT_SQRT_PI_BY_TWO;
const double tmpl_double_sqrt_pi_by_two = TMPL_DOUBLE_SQRT_PI_BY_TWO;
const long double tmpl_ldouble_sqrt_pi_by_two = TMPL_LDOUBLE_SQRT_PI_BY_TWO;

const float tmpl_float_sqrt_pi_by_four = TMPL_FLOAT_SQRT_PI_BY_FOUR;
const double tmpl_double_sqrt_pi_by_four = TMPL_DOUBLE_SQRT_PI_BY_FOUR;
const long double tmpl_ldouble_sqrt_pi_by_four = TMPL_LDOUBLE_SQRT_PI_BY_FOUR;

const float tmpl_float_sqrt_pi_by_eight = TMPL_FLOAT_SQRT_PI_BY_EIGHT;
const double tmpl_double_sqrt_pi_by_eight = TMPL_DOUBLE_SQRT_PI_BY_EIGHT;
const long double tmpl_ldouble_sqrt_pi_by_eight = TMPL_LDOUBLE_SQRT_PI_BY_EIGHT;

/******************************************************************************
 *                         Multiples of Sqrt(1 / Pi)                          *
 ******************************************************************************/
const float tmpl_float_rcpr_sqrt_pi = TMPL_FLOAT_RCPR_SQRT_PI;
const double tmpl_double_rcpr_sqrt_pi = TMPL_DOUBLE_RCPR_SQRT_PI;
const long double tmpl_ldouble_rcpr_sqrt_pi = TMPL_LDOUBLE_RCPR_SQRT_PI;

const float tmpl_float_rcpr_sqrt_two_pi = TMPL_FLOAT_RCPR_SQRT_TWO_PI;
const double tmpl_double_rcpr_sqrt_two_pi = TMPL_DOUBLE_RCPR_SQRT_TWO_PI;
const long double tmpl_ldouble_rcpr_sqrt_two_pi = TMPL_LDOUBLE_RCPR_SQRT_TWO_PI;

const float tmpl_float_two_by_sqrt_pi = TMPL_FLOAT_TWO_BY_SQRT_PI;
const double tmpl_double_two_by_sqrt_pi = TMPL_DOUBLE_TWO_BY_SQRT_PI;
const long double tmpl_ldouble_two_by_sqrt_pi = TMPL_LDOUBLE_TWO_BY_SQRT_PI;

const float tmpl_float_sqrt_two_by_pi = TMPL_FLOAT_SQRT_TWO_BY_PI;
const double tmpl_double_sqrt_two_by_pi = TMPL_DOUBLE_SQRT_TWO_BY_PI;
const long double tmpl_ldouble_sqrt_two_by_pi = TMPL_LDOUBLE_SQRT_TWO_BY_PI;

/******************************************************************************
 *                            Common Square Roots                             *
 ******************************************************************************/
const float tmpl_float_sqrt_two = TMPL_FLOAT_SQRT_TWO;
const double tmpl_double_sqrt_two = TMPL_DOUBLE_SQRT_TWO;
const long double tmpl_ldouble_sqrt_two = TMPL_LDOUBLE_SQRT_TWO;

const float tmpl_float_sqrt_three = TMPL_FLOAT_SQRT_THREE;
const double tmpl_double_sqrt_three = TMPL_DOUBLE_SQRT_THREE;
const long double tmpl_ldouble_sqrt_three = TMPL_LDOUBLE_SQRT_THREE;

const float tmpl_float_sqrt_five = TMPL_FLOAT_SQRT_FIVE;
const double tmpl_double_sqrt_five = TMPL_DOUBLE_SQRT_FIVE;
const long double tmpl_ldouble_sqrt_five = TMPL_LDOUBLE_SQRT_FIVE;

const float tmpl_float_rcpr_sqrt_two = TMPL_FLOAT_RCPR_SQRT_TWO;
const double tmpl_double_rcpr_sqrt_two = TMPL_DOUBLE_RCPR_SQRT_TWO;
const long double tmpl_ldouble_rcpr_sqrt_two = TMPL_LDOUBLE_RCPR_SQRT_TWO;

const float tmpl_float_rcpr_sqrt_three = TMPL_FLOAT_RCPR_SQRT_THREE;
const double tmpl_double_rcpr_sqrt_three = TMPL_DOUBLE_RCPR_SQRT_THREE;
const long double tmpl_ldouble_rcpr_sqrt_three = TMPL_LDOUBLE_RCPR_SQRT_THREE;

/******************************************************************************
 *                      Euler's Exponential Constant (e)                      *
 ******************************************************************************/
const float tmpl_float_euler_e = TMPL_FLOAT_EULER_E;
const double tmpl_double_euler_e = TMPL_DOUBLE_EULER_E;
const long double tmpl_ldouble_euler_e = TMPL_LDOUBLE_EULER_E;

const float tmpl_float_rcpr_euler_e = TMPL_FLOAT_RCPR_EULER_E;
const double tmpl_double_rcpr_euler_e = TMPL_DOUBLE_RCPR_EULER_E;
const long double tmpl_ldouble_rcpr_euler_e = TMPL_LDOUBLE_RCPR_EULER_E;

/******************************************************************************
 *                              Common Logarithms                             *
 ******************************************************************************/
const float tmpl_float_log_e_of_two = TMPL_FLOAT_LOG_E_OF_TWO;
const double tmpl_double_log_e_of_two = TMPL_DOUBLE_LOG_E_OF_TWO;
const long double tmpl_ldouble_log_e_of_two = TMPL_LDOUBLE_LOG_E_OF_TWO;

const float tmpl_float_log_e_of_ten = TMPL_FLOAT_LOG_E_OF_TEN;
const double tmpl_double_log_e_of_ten = TMPL_DOUBLE_LOG_E_OF_TEN;
const long double tmpl_ldouble_log_e_of_ten = TMPL_LDOUBLE_LOG_E_OF_TEN;

const float tmpl_float_rcpr_log_e_of_two = TMPL_FLOAT_RCPR_LOG_E_OF_TWO;
const double tmpl_double_rcpr_log_e_of_two = TMPL_DOUBLE_RCPR_LOG_E_OF_TWO;
const long double
tmpl_ldouble_rcpr_log_e_of_two = TMPL_LDOUBLE_RCPR_LOG_E_OF_TWO;

#if TMPL_HAS_IEEE754_FLOAT == 1
const float tmpl_Min_Float_Base_E = -85.1956484408F;
const float tmpl_Max_Float_Base_E = 87.4982335338F;
#else
const float tmpl_Min_Float_Base_E = FLT_MIN_10_EXP * 2.302585093F;
const float tmpl_Max_Float_Base_E = FLT_MAX_10_EXP * 2.302585093F;
#endif

#if TMPL_HAS_IEEE754_DOUBLE == 1
const double tmpl_Min_Double_Base_E = -745.1332191019411;
const double tmpl_Max_Double_Base_E = 709.782712893384;
#else
const double tmpl_Min_Double_Base_E = DBL_MIN_10_EXP * 2.30258509299404568;
const double tmpl_Max_Double_Base_E = DBL_MAX_10_EXP * 2.30258509299404568;
#endif

#if !defined(TMPL_LDOUBLE_ENDIANNESS) || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_UNKNOWN
const long double tmpl_Max_LDouble_Base_E
    = LDBL_MAX_10_EXP*2.30258509299404568401799145468436421L;
const long double tmpl_Min_LDouble_Base_E
    = LDBL_MIN_10_EXP*2.30258509299404568401799145468436421L;

#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN    || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN     || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN  || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN      || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN
const long double tmpl_Min_LDouble_Base_E
    = -11354.04709355363926789271586304859990768L;
const long double tmpl_Max_LDouble_Base_E
    = 11356.34967864663331357673385450328427189L;
#else
const long double tmpl_Min_LDouble_Base_E
    = -706.89362354917202499352337658809981173L;
const long double tmpl_Max_LDouble_Base_E
    = 709.19620864216607067754136804278417594L;
#endif

const float
tmpl_float_pi_hi = 3.1415927410125732421875F;

const float
tmpl_float_pi_lo = -8.74227800037248566167204971158028306006E-08F;

const double
tmpl_double_pi_hi = 3.141592653589793115997963468544185161590576171875;

const double
tmpl_double_pi_lo = 1.2246467991473531772260659322750010582097494459230782E-16;

const float
tmpl_float_pi_by_two_hi = 1.57079637050628662109375F;

const float
tmpl_float_pi_by_two_lo = -4.371139000186242830836024855790141530031244709E-08F;

const double
tmpl_double_pi_by_two_hi = 1.5707963267948965579989817342720925807952880859375;

const double
tmpl_double_pi_by_two_lo = 6.1232339957367658861303296613750052910487472296E-17;

const float
tmpl_float_pi_by_four_hi = 7.85398185253143310546875E-01F;

const float
tmpl_float_pi_by_four_lo = -2.18556950009312141541801242789507076501562235E-08F;

const double
tmpl_double_pi_by_four_hi = 7.853981633974482789994908671360462903976440430E-01;

const double
tmpl_double_pi_by_four_lo = 3.061616997868382943065164830687502645524373615E-17;

const float
tmpl_float_ln_2_hi = 6.93115234375E-01F;

const float
tmpl_float_ln_2_lo = 3.194618494530941723212145817656807550013436E-05F;

const double
tmpl_double_ln_2_hi = 6.93147182464599609375E-01;

const double
tmpl_double_ln_2_lo = -1.90465429995776787854182343192449986563974474587932E-09;

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT
const long double
tmpl_ldouble_pi_hi = 3.141592653589793115997963468544185161590576171875L;

const long double
tmpl_ldouble_pi_lo = 1.22464679914735317722606593227500105820974944592308E-16L;

const long double
tmpl_ldouble_pi_by_two_hi = 1.570796326794896557998981734272092580795288085938L;

const long double
tmpl_ldouble_pi_by_two_lo = 1.2323399573676588613032966137500529104874723E-17L;

const long double
tmpl_ldouble_pi_by_four_hi = 7.8539816339744827899949086713604629039764404E-01L;

const long double
tmpl_ldouble_pi_by_four_lo = 3.0616169978683829430651648306875026455243736E-17L;

const long double
tmpl_ldouble_ln_2_hi = 6.93147182464599609375E-01L;

const long double
tmpl_ldouble_ln_2_lo = -1.904654299957767878541823431924499865639744745879E-09L;
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE
const long double
tmpl_ldouble_pi_hi = 3.1415926535897932384626433832794812270636909610957413460L;

const long double
tmpl_ldouble_pi_lo = 2.165713347843827936447492339721161948731436169347863E-32L;

const long double
tmpl_ldouble_pi_by_two_hi = 1.570796326794896619231321691639740613531845480548L;

const long double
tmpl_ldouble_pi_by_two_lo = 1.08285667392191396822374616986058097436571808E-32L;

const long double
tmpl_ldouble_pi_by_four_hi = 7.8539816339744830961566084581987030676592274E-01L;

const long double
tmpl_ldouble_pi_by_four_lo = 5.4142833696095698411187308493029048718285904E-33L;

const long double
tmpl_ldouble_ln_2_hi = 6.9314718055994528622676398299518041312694549560547E-01L;

const long double
tmpl_ldouble_ln_2_lo = 2.3190468138462996154948554638754786504120680009493E-17L;
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT
const long double
tmpl_ldouble_pi_hi = 3.1415926535897932384626433832795027974790680981372955730L;

const long double
tmpl_ldouble_pi_lo = 8.6718101301237810247970440260433519687623233458628035E-35;

const long double
tmpl_ldouble_pi_by_two_hi = 1.570796326794896619231321691639751398739534049069L;

const long double
tmpl_ldouble_pi_by_two_lo = 4.335905065061890512398522013021675984381161673E-35;

const long double
tmpl_ldouble_pi_by_four_hi = 7.8539816339744830961566084581987569936976702E-01L;

const long double
tmpl_ldouble_pi_by_four_lo = 2.1679525325309452561992610065108379921905808E-35L;

const long double
tmpl_ldouble_ln_2_hi = 6.9314718055994530704344569471686554607003927230835E-01L;

const long double
tmpl_ldouble_ln_2_lo = 2.3737864267413110220054608620519056447456800094934E-18L;
#else
const long double
tmpl_ldouble_pi_hi = 3.1415926535897932385128089594061862044327426701784133911L;

const long double
tmpl_ldouble_pi_lo = -5.01655761266833202355732708033075701383366576921836E-20L;

const long double
tmpl_ldouble_pi_by_two_hi = 1.570796326794896619256404479703093102216371335089L;

const long double
tmpl_ldouble_pi_by_two_lo = -2.5082788063341660117786635401653785069168329E-20L;

const long double
tmpl_ldouble_pi_by_four_hi = 7.8539816339744830962820223985154655110818567E-01L;

const long double
tmpl_ldouble_pi_by_four_lo = -1.254139403167083005889331770082689253458416E-20L;

const long double
tmpl_ldouble_ln_2_hi = 6.9314718060195446014404296875E-01L;

const long double
tmpl_ldouble_ln_2_lo = -4.200915072681084729182343192449986563974474587932E-11L;
#endif
