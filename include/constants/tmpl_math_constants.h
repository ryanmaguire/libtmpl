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
 *                            tmpl_math_constants                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides common constants in math as macros at various precisions.    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 23, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_CONSTANTS_H
#define TMPL_MATH_CONSTANTS_H

/******************************************************************************
 *                              Multiples of Pi                               *
 ******************************************************************************/
#define TMPL_DOUBLE_PI (+3.141592653589793238462643383279502884197E+00)
#define TMPL_FLOAT_PI (+3.141592653589793238462643383279502884197E+00F)
#define TMPL_LDOUBLE_PI (+3.141592653589793238462643383279502884197E+00L)

#define TMPL_DOUBLE_TWO_PI (+6.283185307179586476925286766559005768394E+00)
#define TMPL_FLOAT_TWO_PI (+6.283185307179586476925286766559005768394E+00F)
#define TMPL_LDOUBLE_TWO_PI (+6.283185307179586476925286766559005768394E+00L)

#define TMPL_DOUBLE_FOUR_PI (+12.56637061435917295385057353311801153679E+00)
#define TMPL_FLOAT_FOUR_PI (+12.56637061435917295385057353311801153679E+00F)
#define TMPL_LDOUBLE_FOUR_PI (+12.56637061435917295385057353311801153679E+00L)

#define TMPL_DOUBLE_EIGHT_PI (+2.513274122871834590770114706623602307358E+01)
#define TMPL_FLOAT_EIGHT_PI (+2.513274122871834590770114706623602307358E+01F)
#define TMPL_LDOUBLE_EIGHT_PI (+2.513274122871834590770114706623602307358E+01L)

#define TMPL_DOUBLE_PI_BY_TWO (+1.570796326794896619231321691639751442099E+00)
#define TMPL_FLOAT_PI_BY_TWO (+1.570796326794896619231321691639751442099E+00F)
#define TMPL_LDOUBLE_PI_BY_TWO (+1.570796326794896619231321691639751442099E+00L)

#define TMPL_DOUBLE_PI_BY_THREE (+1.0471975511965977461542144610931676281E+00)
#define TMPL_FLOAT_PI_BY_THREE (+1.0471975511965977461542144610931676281E+00F)
#define TMPL_LDOUBLE_PI_BY_THREE (+1.0471975511965977461542144610931676281E+00L)

#define TMPL_DOUBLE_PI_BY_FOUR (+7.85398163397448309615660845819875721049E-01)
#define TMPL_FLOAT_PI_BY_FOUR (+7.85398163397448309615660845819875721049E-01F)
#define TMPL_LDOUBLE_PI_BY_FOUR (+7.85398163397448309615660845819875721049E-01L)

#define TMPL_DOUBLE_PI_BY_FIVE (+6.28318530717958647692528676655900576839E-01)
#define TMPL_FLOAT_PI_BY_FIVE (+6.28318530717958647692528676655900576839E-01F)
#define TMPL_LDOUBLE_PI_BY_FIVE (+6.28318530717958647692528676655900576839E-01L)

#define TMPL_DOUBLE_PI_BY_SIX (+5.235987755982988730771072305465838140329E-01)
#define TMPL_FLOAT_PI_BY_SIX (+5.235987755982988730771072305465838140329E-01F)
#define TMPL_LDOUBLE_PI_BY_SIX (+5.235987755982988730771072305465838140329E-01L)

#define TMPL_DOUBLE_PI_BY_EIGHT (+3.9269908169872415480783042290993786053E-01)
#define TMPL_FLOAT_PI_BY_EIGHT (+3.9269908169872415480783042290993786053E-01F)
#define TMPL_LDOUBLE_PI_BY_EIGHT (+3.9269908169872415480783042290993786053E-01L)

#define TMPL_DOUBLE_PI_BY_TWELVE (+2.617993877991494365385536152732919070E-01)
#define TMPL_FLOAT_PI_BY_TWELVE (+2.617993877991494365385536152732919070E-01F)
#define TMPL_LDOUBLE_PI_BY_TWELVE (+2.617993877991494365385536152732919070E-01L)

#define TMPL_DOUBLE_THREE_PI_BY_FOUR (+2.356194490192344928846982537459627163)
#define TMPL_FLOAT_THREE_PI_BY_FOUR (+2.356194490192344928846982537459627163F)
#define TMPL_LDOUBLE_THREE_PI_BY_FOUR (+2.356194490192344928846982537459627163L)

#define TMPL_DOUBLE_DEG_TO_RAD (+1.74532925199432957692369076848861271344E-02)
#define TMPL_FLOAT_DEG_TO_RAD (+1.74532925199432957692369076848861271344E-02F)
#define TMPL_LDOUBLE_DEG_TO_RAD (+1.74532925199432957692369076848861271344E-02L)

#define TMPL_DOUBLE_PI_BY_SQRT_TWO (+2.22144146907918312350794049503034684931)
#define TMPL_FLOAT_PI_BY_SQRT_TWO (+2.22144146907918312350794049503034684931F)
#define TMPL_LDOUBLE_PI_BY_SQRT_TWO (+2.2214414690791831235079404950303468E+00L)

#define TMPL_DOUBLE_PI_BY_SQRT_EIGHT (+1.110720734539591561753970247515173425)
#define TMPL_FLOAT_PI_BY_SQRT_EIGHT (+1.110720734539591561753970247515173425F)
#define TMPL_LDOUBLE_PI_BY_SQRT_EIGHT (+1.110720734539591561753970247515173425L)

/******************************************************************************
 *                            Multiples of 1 / Pi                             *
 ******************************************************************************/
#define TMPL_DOUBLE_RCPR_PI (+3.183098861837906715377675267450287240689E-01)
#define TMPL_FLOAT_RCPR_PI (+3.183098861837906715377675267450287240689E-01F)
#define TMPL_LDOUBLE_RCPR_PI (+3.183098861837906715377675267450287240689E-01L)

#define TMPL_DOUBLE_TWO_BY_PI (+6.366197723675813430755350534900574481378E-01)
#define TMPL_FLOAT_TWO_BY_PI (+6.366197723675813430755350534900574481378E-01F)
#define TMPL_LDOUBLE_TWO_BY_PI (+6.366197723675813430755350534900574481378E-01L)

#define TMPL_DOUBLE_RCPR_TWO_PI (+1.59154943091895335768883763372514362E-01)
#define TMPL_FLOAT_RCPR_TWO_PI (+1.59154943091895335768883763372514362E-01F)
#define TMPL_LDOUBLE_RCPR_TWO_PI (+1.59154943091895335768883763372514362E-01L)

#define TMPL_DOUBLE_RCPR_FOUR_PI (+7.9577471545947667884441881686257181E-02)
#define TMPL_FLOAT_RCPR_FOUR_PI (+7.9577471545947667884441881686257181E-02F)
#define TMPL_LDOUBLE_RCPR_FOUR_PI (+7.9577471545947667884441881686257181E-02L)

#define TMPL_DOUBLE_RAD_TO_DEG (5.729577951308232087679815481410517033241E+01)
#define TMPL_FLOAT_RAD_TO_DEG (5.729577951308232087679815481410517033241E+01F)
#define TMPL_LDOUBLE_RAD_TO_DEG (5.729577951308232087679815481410517033241E+01L)

/******************************************************************************
 *                           Multiples of Sqrt(Pi)                            *
 ******************************************************************************/
#define TMPL_DOUBLE_SQRT_PI (+1.7724538509055160272981674833411451828E+00)
#define TMPL_FLOAT_SQRT_PI (+1.7724538509055160272981674833411451828E+00F)
#define TMPL_LDOUBLE_SQRT_PI (+1.7724538509055160272981674833411451828E+00L)

#define TMPL_DOUBLE_SQRT_TWO_PI (+2.5066282746310005024157652848110452530E+00)
#define TMPL_FLOAT_SQRT_TWO_PI (+2.5066282746310005024157652848110452530E+00F)
#define TMPL_LDOUBLE_SQRT_TWO_PI (+2.5066282746310005024157652848110452530E+00L)

#define TMPL_DOUBLE_SQRT_PI_BY_TWO (+1.25331413731550025120788264240552262650)
#define TMPL_FLOAT_SQRT_PI_BY_TWO (+1.25331413731550025120788264240552262650F)
#define TMPL_LDOUBLE_SQRT_PI_BY_TWO (+1.25331413731550025120788264240552262650L)

#define TMPL_DOUBLE_SQRT_PI_BY_FOUR (+8.862269254527580136490837416705726E-01)
#define TMPL_FLOAT_SQRT_PI_BY_FOUR (+8.862269254527580136490837416705726E-01F)
#define TMPL_LDOUBLE_SQRT_PI_BY_FOUR (+8.862269254527580136490837416705726E-01L)

#define TMPL_DOUBLE_SQRT_PI_BY_EIGHT (+6.266570686577501256039413212027613E-1)
#define TMPL_FLOAT_SQRT_PI_BY_EIGHT (+6.266570686577501256039413212027613E-1F)
#define TMPL_LDOUBLE_SQRT_PI_BY_EIGHT (+6.266570686577501256039413212027613E-1L)

/******************************************************************************
 *                         Multiples of Sqrt(1 / Pi)                          *
 ******************************************************************************/
#define TMPL_DOUBLE_RCPR_SQRT_PI (+5.641895835477562869480794515607725858E-01)
#define TMPL_FLOAT_RCPR_SQRT_PI (+5.641895835477562869480794515607725858E-01F)
#define TMPL_LDOUBLE_RCPR_SQRT_PI (+5.641895835477562869480794515607725858E-01L)

#define TMPL_DOUBLE_RCPR_SQRT_TWO_PI (+3.989422804014326779399460599343819E-1)
#define TMPL_FLOAT_RCPR_SQRT_TWO_PI (+3.989422804014326779399460599343819E-1F)
#define TMPL_LDOUBLE_RCPR_SQRT_TWO_PI (+3.989422804014326779399460599343819E-1L)

#define TMPL_DOUBLE_TWO_BY_SQRT_PI (+1.12837916709551257389615890312154517169)
#define TMPL_FLOAT_TWO_BY_SQRT_PI (+1.12837916709551257389615890312154517169F)
#define TMPL_LDOUBLE_TWO_BY_SQRT_PI (+1.12837916709551257389615890312154517169L)

#define TMPL_DOUBLE_SQRT_TWO_BY_PI (+7.9788456080286535587989211986876374E-01)
#define TMPL_FLOAT_SQRT_TWO_BY_PI (+7.9788456080286535587989211986876374E-01F)
#define TMPL_LDOUBLE_SQRT_TWO_BY_PI (+7.9788456080286535587989211986876374E-01L)

/******************************************************************************
 *                            Common Square Roots                             *
 ******************************************************************************/
#define TMPL_DOUBLE_SQRT_TWO (+1.41421356237309504880168872420969807857E+00)
#define TMPL_FLOAT_SQRT_TWO (+1.41421356237309504880168872420969807857E+00F)
#define TMPL_LDOUBLE_SQRT_TWO (+1.41421356237309504880168872420969807857E+00L)

#define TMPL_DOUBLE_SQRT_THREE (+1.73205080756887729352744634150587236694E+00)
#define TMPL_FLOAT_SQRT_THREE (+1.73205080756887729352744634150587236694E+00F)
#define TMPL_LDOUBLE_SQRT_THREE (+1.73205080756887729352744634150587236694E+00L)

#define TMPL_DOUBLE_SQRT_FIVE (+2.236067977499789696409173668731276235441E+00)
#define TMPL_FLOAT_SQRT_FIVE (+2.236067977499789696409173668731276235441E+00F)
#define TMPL_LDOUBLE_SQRT_FIVE (+2.236067977499789696409173668731276235441E+00L)

#define TMPL_DOUBLE_RCPR_SQRT_TWO (+7.07106781186547524400844362104849039E-01)
#define TMPL_FLOAT_RCPR_SQRT_TWO (+7.07106781186547524400844362104849039E-01F)
#define TMPL_LDOUBLE_RCPR_SQRT_TWO (+7.07106781186547524400844362104849039E-01L)

#define TMPL_DOUBLE_RCPR_SQRT_THREE (+5.7735026918962576450914878050195745E-1)
#define TMPL_FLOAT_RCPR_SQRT_THREE (+5.7735026918962576450914878050195745E-1F)
#define TMPL_LDOUBLE_RCPR_SQRT_THREE (+5.7735026918962576450914878050195745E-1L)

/******************************************************************************
 *                      Euler's Exponential Constant (e)                      *
 ******************************************************************************/
#define TMPL_DOUBLE_EULER_E (+2.718281828459045235360287471352662497757E+00)
#define TMPL_FLOAT_EULER_E (+2.718281828459045235360287471352662497757E+00F)
#define TMPL_LDOUBLE_EULER_E (+2.718281828459045235360287471352662497757E+00L)

#define TMPL_DOUBLE_RCPR_EULER_E (+3.678794411714423215955237701614608674E-01)
#define TMPL_FLOAT_RCPR_EULER_E (+3.678794411714423215955237701614608674E-01F)
#define TMPL_LDOUBLE_RCPR_EULER_E (+3.678794411714423215955237701614608674E-01L)

/******************************************************************************
 *                              Common Logarithms                             *
 ******************************************************************************/
#define TMPL_DOUBLE_LOG_E_TWO (+6.931471805599453094172321214581765680755E-01)
#define TMPL_FLOAT_LOG_E_TWO (+6.931471805599453094172321214581765680755E-01F)
#define TMPL_LDOUBLE_LOG_E_TWO (+6.931471805599453094172321214581765680755E-01L)

#define TMPL_DOUBLE_LOG_E_TEN (+2.302585092994045684017991454684364207601E+00)
#define TMPL_FLOAT_LOG_E_TEN (+2.302585092994045684017991454684364207601E+00F)
#define TMPL_LDOUBLE_LOG_E_TEN (+2.302585092994045684017991454684364207601E+00L)

/******************************************************************************
 *                              Multiples of Pi                               *
 ******************************************************************************/
extern const float tmpl_float_pi;
extern const double tmpl_double_pi;
extern const long double tmpl_ldouble_pi;

extern const float tmpl_float_two_pi;
extern const double tmpl_double_two_pi;
extern const long double tmpl_LDouble_Two_Pi;

extern const float tmpl_float_four_pi;
extern const double tmpl_double_four_pi;
extern const long double tmpl_LDouble_Four_Pi;

extern const float tmpl_float_eight_pi;
extern const double tmpl_double_eight_pi;
extern const long double tmpl_LDouble_Eight_Pi;

/******************************************************************************
 *                          Fractional Values of Pi                           *
 ******************************************************************************/
extern const float tmpl_Float_Pi_By_Two;
extern const double tmpl_Double_Pi_By_Two;
extern const long double tmpl_LDouble_Pi_By_Two;

extern const float tmpl_Float_Pi_By_Three;
extern const double tmpl_Double_Pi_By_Three;
extern const long double tmpl_LDouble_Pi_By_Three;

extern const float tmpl_Float_Pi_By_Four;
extern const double tmpl_Double_Pi_By_Four;
extern const long double tmpl_LDouble_Pi_By_Four;

extern const float tmpl_Float_Pi_By_Five;
extern const double tmpl_Double_Pi_By_Five;
extern const long double tmpl_LDouble_Pi_By_Five;

extern const float tmpl_Float_Pi_By_Six;
extern const double tmpl_Double_Pi_By_Six;
extern const long double tmpl_LDouble_Pi_By_Six;

extern const float tmpl_Float_Pi_By_Eight;
extern const double tmpl_Double_Pi_By_Eight;
extern const long double tmpl_LDouble_Pi_By_Eight;

extern const float tmpl_Float_Pi_By_Twelve;
extern const double tmpl_Double_Pi_By_Twelve;
extern const long double tmpl_LDouble_Pi_By_Twelve;

extern const float tmpl_Float_Three_Pi_By_Four;
extern const double tmpl_Double_Three_Pi_By_Four;
extern const long double tmpl_LDouble_Three_Pi_By_Four;

extern const float tmpl_Float_Pi_By_Sqrt_Two;
extern const double tmpl_Double_Pi_By_Sqrt_Two;
extern const long double tmpl_LDouble_Pi_By_Sqrt_Two;

/******************************************************************************
 *                      Conversions Radians and Degrees                       *
 ******************************************************************************/
extern const float tmpl_Float_Rad_To_Deg;
extern const double tmpl_Double_Rad_To_Deg;
extern const long double tmpl_LDouble_Rad_To_Deg;

extern const float tmpl_Float_Deg_To_Rad;
extern const double tmpl_Double_Deg_To_Rad;
extern const long double tmpl_LDouble_Deg_To_Rad;

/******************************************************************************
 *                            Multiples of 1 / Pi                             *
 ******************************************************************************/
extern const float tmpl_Float_Rcpr_Pi;
extern const double tmpl_Double_Rcpr_Pi;
extern const long double tmpl_LDouble_Rcpr_Pi;

extern const float tmpl_Float_Two_By_Pi;
extern const double tmpl_Double_Two_By_Pi;
extern const long double tmpl_LDouble_Two_By_Pi;

extern const float tmpl_Float_Rcpr_Two_Pi;
extern const double tmpl_Double_Rcpr_Two_Pi;
extern const long double tmpl_LDouble_Rcpr_Two_Pi;

extern const float tmpl_Float_Rcpr_Four_Pi;
extern const double tmpl_Double_Rcpr_Four_Pi;
extern const long double tmpl_LDouble_Rcpr_Four_Pi;

/******************************************************************************
 *                           Multiples of Sqrt(Pi)                            *
 ******************************************************************************/
extern const float tmpl_Float_Sqrt_Pi;
extern const double tmpl_Double_Sqrt_Pi;
extern const long double tmpl_LDouble_Sqrt_Pi;

extern const float tmpl_Float_Sqrt_Two_Pi;
extern const double tmpl_Double_Sqrt_Two_Pi;
extern const long double tmpl_LDouble_Sqrt_Two_Pi;

extern const float tmpl_Float_Sqrt_Pi_By_Two;
extern const double tmpl_Double_Sqrt_Pi_By_Two;
extern const long double tmpl_LDouble_Sqrt_Pi_By_Two;

extern const double tmpl_Double_Sqrt_Pi_By_Four;
extern const float tmpl_Float_Sqrt_Pi_By_Four;
extern const long double tmpl_LDouble_Sqrt_Pi_By_Four;

extern const double tmpl_Double_Sqrt_Pi_By_Eight;
extern const float tmpl_Float_Sqrt_Pi_By_Eight;
extern const long double tmpl_LDouble_Sqrt_Pi_By_Eight;

/******************************************************************************
 *                         Multiples of Sqrt(1 / Pi)                          *
 ******************************************************************************/
extern const float tmpl_Float_Rcpr_Sqrt_Pi;
extern const double tmpl_Double_Rcpr_Sqrt_Pi;
extern const long double tmpl_LDouble_Rcpr_Sqrt_Pi;

extern const float tmpl_Float_Rcpr_Sqrt_Two_Pi;
extern const double tmpl_Double_Rcpr_Sqrt_Two_Pi;
extern const long double tmpl_LDouble_Rcpr_Sqrt_Two_Pi;

extern const float tmpl_Float_Two_By_Sqrt_Pi;
extern const double tmpl_Double_Two_By_Sqrt_Pi;
extern const long double tmpl_LDouble_Two_By_Sqrt_Pi;

extern const float tmpl_Float_Sqrt_Two_By_Pi;
extern const double tmpl_Double_Sqrt_Two_By_Pi;
extern const long double tmpl_LDouble_Sqrt_Two_By_Pi;

/******************************************************************************
 *                            Common Square Roots                             *
 ******************************************************************************/
extern const float tmpl_Float_Sqrt_Two;
extern const double tmpl_Double_Sqrt_Two;
extern const long double tmpl_LDouble_Sqrt_Two;

extern const float tmpl_Float_Sqrt_Three;
extern const double tmpl_Double_Sqrt_Three;
extern const long double tmpl_LDouble_Sqrt_Three;

extern const float tmpl_Float_Sqrt_Five;
extern const double tmpl_Double_Sqrt_Five;
extern const long double tmpl_LDouble_Sqrt_Five;

extern const float tmpl_Float_Rcpr_Sqrt_Two;
extern const double tmpl_Double_Rcpr_Sqrt_Two;
extern const long double tmpl_LDouble_Rcpr_Sqrt_Two;

extern const float tmpl_Float_Rcpr_Sqrt_Three;
extern const double tmpl_Double_Rcpr_Sqrt_Three;
extern const long double tmpl_LDouble_Rcpr_Sqrt_Three;

/******************************************************************************
 *                      Euler's Exponential Constant (e)                      *
 ******************************************************************************/
extern const float tmpl_Float_Euler_E;
extern const double tmpl_Double_Euler_E;
extern const long double tmpl_LDouble_Euler_E;

extern const float tmpl_Float_Rcpr_Euler_E;
extern const double tmpl_Double_Rcpr_Euler_E;
extern const long double tmpl_LDouble_Rcpr_Euler_E;

/******************************************************************************
 *                              Common Logarithms                             *
 ******************************************************************************/
extern const float tmpl_Float_Log_E_Two;
extern const double tmpl_Double_Log_E_Two;
extern const long double tmpl_LDouble_Log_E_Two;

extern const float tmpl_Float_Log_E_Ten;
extern const double tmpl_Double_Log_E_Ten;
extern const long double tmpl_LDouble_Log_E_Ten;

#endif
