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
const float tmpl_Float_Pi_By_Two = TMPL_FLOAT_PI_BY_TWO;
const double tmpl_Double_Pi_By_Two = TMPL_DOUBLE_PI_BY_TWO;
const long double tmpl_LDouble_Pi_By_Two = TMPL_LDOUBLE_PI_BY_TWO;

const float tmpl_Float_Pi_By_Three = TMPL_FLOAT_PI_BY_THREE;
const double tmpl_Double_Pi_By_Three = TMPL_DOUBLE_PI_BY_THREE;
const long double tmpl_LDouble_Pi_By_Three = TMPL_LDOUBLE_PI_BY_THREE;

const float tmpl_Float_Pi_By_Four = TMPL_FLOAT_PI_BY_FOUR;
const double tmpl_Double_Pi_By_Four = TMPL_DOUBLE_PI_BY_FOUR;
const long double tmpl_LDouble_Pi_By_Four = TMPL_LDOUBLE_PI_BY_FOUR;

const float tmpl_Float_Pi_By_Five = TMPL_FLOAT_PI_BY_FIVE;
const double tmpl_Double_Pi_By_Five = TMPL_DOUBLE_PI_BY_FIVE;
const long double tmpl_LDouble_Pi_By_Five = TMPL_LDOUBLE_PI_BY_FIVE;

const float tmpl_Float_Pi_By_Six = TMPL_FLOAT_PI_BY_SIX;
const double tmpl_Double_Pi_By_Six = TMPL_DOUBLE_PI_BY_SIX;
const long double tmpl_LDouble_Pi_By_Six = TMPL_LDOUBLE_PI_BY_SIX;

const float tmpl_Float_Pi_By_Eight = TMPL_FLOAT_PI_BY_EIGHT;
const double tmpl_Double_Pi_By_Eight = TMPL_DOUBLE_PI_BY_EIGHT;
const long double tmpl_LDouble_Pi_By_Eight = TMPL_LDOUBLE_PI_BY_EIGHT;

const float tmpl_Float_Pi_By_Twelve = TMPL_FLOAT_PI_BY_TWELVE;
const double tmpl_Double_Pi_By_Twelve = TMPL_DOUBLE_PI_BY_TWELVE;
const long double tmpl_LDouble_Pi_By_Twelve = TMPL_LDOUBLE_PI_BY_TWELVE;

const float tmpl_Float_Three_Pi_By_Four = TMPL_FLOAT_THREE_PI_BY_FOUR;
const double tmpl_Double_Three_Pi_By_Four = TMPL_DOUBLE_THREE_PI_BY_FOUR;
const long double tmpl_LDouble_Three_Pi_By_Four = TMPL_LDOUBLE_THREE_PI_BY_FOUR;

const float tmpl_Float_Pi_By_Sqrt_Two = TMPL_FLOAT_PI_BY_SQRT_TWO;
const double tmpl_Double_Pi_By_Sqrt_Two = TMPL_DOUBLE_PI_BY_SQRT_TWO;
const long double tmpl_LDouble_Pi_By_Sqrt_Two = TMPL_LDOUBLE_PI_BY_SQRT_TWO;

/******************************************************************************
 *                      Conversions Radians and Degrees                       *
 ******************************************************************************/
const float tmpl_Float_Rad_To_Deg = TMPL_FLOAT_RAD_TO_DEG;
const double tmpl_Double_Rad_To_Deg = TMPL_DOUBLE_RAD_TO_DEG;
const long double tmpl_LDouble_Rad_To_Deg = TMPL_LDOUBLE_RAD_TO_DEG;

const float tmpl_Float_Deg_To_Rad = TMPL_FLOAT_DEG_TO_RAD;
const double tmpl_Double_Deg_To_Rad = TMPL_DOUBLE_DEG_TO_RAD;
const long double tmpl_LDouble_Deg_To_Rad = TMPL_LDOUBLE_DEG_TO_RAD;

/******************************************************************************
 *                            Multiples of 1 / Pi                             *
 ******************************************************************************/
const float tmpl_Float_Rcpr_Pi = TMPL_FLOAT_RCPR_PI;
const double tmpl_Double_Rcpr_Pi = TMPL_DOUBLE_RCPR_PI;
const long double tmpl_LDouble_Rcpr_Pi = TMPL_LDOUBLE_RCPR_PI;

const float tmpl_Float_Two_By_Pi = TMPL_FLOAT_TWO_BY_PI;
const double tmpl_Double_Two_By_Pi = TMPL_DOUBLE_TWO_BY_PI;
const long double tmpl_LDouble_Two_By_Pi = TMPL_LDOUBLE_TWO_BY_PI;

const float tmpl_Float_Rcpr_Two_Pi = TMPL_FLOAT_RCPR_TWO_PI;
const double tmpl_Double_Rcpr_Two_Pi = TMPL_DOUBLE_RCPR_TWO_PI;
const long double tmpl_LDouble_Rcpr_Two_Pi = TMPL_LDOUBLE_RCPR_TWO_PI;

const float tmpl_Float_Rcpr_Four_Pi = TMPL_FLOAT_RCPR_FOUR_PI;
const double tmpl_Double_Rcpr_Four_Pi = TMPL_DOUBLE_RCPR_FOUR_PI;
const long double tmpl_LDouble_Rcpr_Four_Pi = TMPL_LDOUBLE_RCPR_FOUR_PI;

/******************************************************************************
 *                           Multiples of Sqrt(Pi)                            *
 ******************************************************************************/
const float tmpl_Float_Sqrt_Pi = TMPL_FLOAT_SQRT_PI;
const double tmpl_Double_Sqrt_Pi = TMPL_DOUBLE_SQRT_PI;
const long double tmpl_LDouble_Sqrt_Pi = TMPL_LDOUBLE_SQRT_PI;

const float tmpl_Float_Sqrt_Two_Pi = TMPL_FLOAT_SQRT_TWO_PI;
const double tmpl_Double_Sqrt_Two_Pi = TMPL_DOUBLE_SQRT_TWO_PI;
const long double tmpl_LDouble_Sqrt_Two_Pi = TMPL_LDOUBLE_SQRT_TWO_PI;

const float tmpl_Float_Sqrt_Pi_By_Two = TMPL_FLOAT_SQRT_PI_BY_TWO;
const double tmpl_Double_Sqrt_Pi_By_Two = TMPL_DOUBLE_SQRT_PI_BY_TWO;
const long double tmpl_LDouble_Sqrt_Pi_By_Two = TMPL_LDOUBLE_SQRT_PI_BY_TWO;

const float tmpl_Float_Sqrt_Pi_By_Four = TMPL_FLOAT_SQRT_PI_BY_FOUR;
const double tmpl_Double_Sqrt_Pi_By_Four = TMPL_DOUBLE_SQRT_PI_BY_FOUR;
const long double tmpl_LDouble_Sqrt_Pi_By_Four = TMPL_LDOUBLE_SQRT_PI_BY_FOUR;

const float tmpl_Float_Sqrt_Pi_By_Eight = TMPL_FLOAT_SQRT_PI_BY_EIGHT;
const double tmpl_Double_Sqrt_Pi_By_Eight = TMPL_DOUBLE_SQRT_PI_BY_EIGHT;
const long double tmpl_LDouble_Sqrt_Pi_By_Eight = TMPL_LDOUBLE_SQRT_PI_BY_EIGHT;

/******************************************************************************
 *                         Multiples of Sqrt(1 / Pi)                          *
 ******************************************************************************/
const float tmpl_Float_Rcpr_Sqrt_Pi = TMPL_FLOAT_RCPR_SQRT_PI;
const double tmpl_Double_Rcpr_Sqrt_Pi = TMPL_DOUBLE_RCPR_SQRT_PI;
const long double tmpl_LDouble_Rcpr_Sqrt_Pi = TMPL_LDOUBLE_RCPR_SQRT_PI;

const float tmpl_Float_Rcpr_Sqrt_Two_Pi = TMPL_FLOAT_RCPR_SQRT_TWO_PI;
const double tmpl_Double_Rcpr_Sqrt_Two_Pi = TMPL_DOUBLE_RCPR_SQRT_TWO_PI;
const long double tmpl_LDouble_Rcpr_Sqrt_Two_Pi = TMPL_LDOUBLE_RCPR_SQRT_TWO_PI;

const float tmpl_Float_Two_By_Sqrt_Pi = TMPL_FLOAT_TWO_BY_SQRT_PI;
const double tmpl_Double_Two_By_Sqrt_Pi = TMPL_DOUBLE_TWO_BY_SQRT_PI;
const long double tmpl_LDouble_Two_By_Sqrt_Pi = TMPL_LDOUBLE_TWO_BY_SQRT_PI;

const float tmpl_Float_Sqrt_Two_By_Pi = TMPL_FLOAT_SQRT_TWO_BY_PI;
const double tmpl_Double_Sqrt_Two_By_Pi = TMPL_DOUBLE_SQRT_TWO_BY_PI;
const long double tmpl_LDouble_Sqrt_Two_By_Pi = TMPL_LDOUBLE_SQRT_TWO_BY_PI;

/******************************************************************************
 *                            Common Square Roots                             *
 ******************************************************************************/
const float tmpl_Float_Sqrt_Two = TMPL_FLOAT_SQRT_TWO;
const double tmpl_Double_Sqrt_Two = TMPL_DOUBLE_SQRT_TWO;
const long double tmpl_LDouble_Sqrt_Two = TMPL_LDOUBLE_SQRT_TWO;

const float tmpl_Float_Sqrt_Three = TMPL_FLOAT_SQRT_THREE;
const double tmpl_Double_Sqrt_Three = TMPL_DOUBLE_SQRT_THREE;
const long double tmpl_LDouble_Sqrt_Three = TMPL_LDOUBLE_SQRT_THREE;

const float tmpl_Float_Sqrt_Five = TMPL_FLOAT_SQRT_FIVE;
const double tmpl_Double_Sqrt_Five = TMPL_DOUBLE_SQRT_FIVE;
const long double tmpl_LDouble_Sqrt_Five = TMPL_LDOUBLE_SQRT_FIVE;

const float tmpl_Float_Rcpr_Sqrt_Two = TMPL_FLOAT_RCPR_SQRT_TWO;
const double tmpl_Double_Rcpr_Sqrt_Two = TMPL_DOUBLE_RCPR_SQRT_TWO;
const long double tmpl_LDouble_Rcpr_Sqrt_Two = TMPL_LDOUBLE_RCPR_SQRT_TWO;

const float tmpl_Float_Rcpr_Sqrt_Three = TMPL_FLOAT_RCPR_SQRT_THREE;
const double tmpl_Double_Rcpr_Sqrt_Three = TMPL_DOUBLE_RCPR_SQRT_THREE;
const long double tmpl_LDouble_Rcpr_Sqrt_Three = TMPL_LDOUBLE_RCPR_SQRT_THREE;

/******************************************************************************
 *                      Euler's Exponential Constant (e)                      *
 ******************************************************************************/
const float tmpl_Float_Euler_E = TMPL_FLOAT_EULER_E;
const double tmpl_Double_Euler_E = TMPL_DOUBLE_EULER_E;
const long double tmpl_LDouble_Euler_E = TMPL_LDOUBLE_EULER_E;

const float tmpl_Float_Rcpr_Euler_E = TMPL_FLOAT_RCPR_EULER_E;
const double tmpl_Double_Rcpr_Euler_E = TMPL_DOUBLE_RCPR_EULER_E;
const long double tmpl_LDouble_Rcpr_Euler_E = TMPL_LDOUBLE_RCPR_EULER_E;

/******************************************************************************
 *                              Common Logarithms                             *
 ******************************************************************************/
const float tmpl_Float_Log_E_Two = TMPL_FLOAT_LOG_E_TWO;
const double tmpl_Double_Log_E_Two = TMPL_DOUBLE_LOG_E_TWO;
const long double tmpl_LDouble_Log_E_Two = TMPL_LDOUBLE_LOG_E_TWO;

const float tmpl_Float_Log_E_Ten = TMPL_FLOAT_LOG_E_TEN;
const double tmpl_Double_Log_E_Ten = TMPL_DOUBLE_LOG_E_TEN;
const long double tmpl_LDouble_Log_E_Ten = TMPL_LDOUBLE_LOG_E_TEN;

#if TMPL_HAS_IEEE754_FLOAT == 1
const float tmpl_Min_Float_Base_E = -85.1956484408F;
const float tmpl_Max_Float_Base_E = 87.4982335338F;
#else
const float tmpl_Min_Float_Base_E = FLT_MIN_10_EXP * 2.302585093F;
const float tmpl_Max_Float_Base_E = FLT_MAX_10_EXP * 2.302585093F;
#endif

#if TMPL_HAS_IEEE754_DOUBLE == 1
const double tmpl_Min_Double_Base_E = -706.893623549172024993;
const double tmpl_Max_Double_Base_E = 709.196208642166070678;
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
