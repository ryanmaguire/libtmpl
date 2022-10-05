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
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 7, 2021                                                   *
 ******************************************************************************/

/*  All constants are declared in this header file.                           */
#include <libtmpl/include/tmpl_math.h>

#if TMPL_HAS_IEEE754_FLOAT == 0  || \
    TMPL_HAS_IEEE754_DOUBLE == 0 || \
    TMPL_HAS_IEEE754_LDOUBLE == 0
#include <float.h>
#endif

/*  sqrt( 1 / (2 pi) )                                                        */
const float
tmpl_Sqrt_One_By_Two_Pi_F = 0.3989422804014326779399460599343818684759F;

const double
tmpl_Sqrt_One_By_Two_Pi = 0.3989422804014326779399460599343818684759;

const long double
tmpl_Sqrt_One_By_Two_Pi_L = 0.3989422804014326779399460599343818684759L;

/*  sqrt( pi / 8 )                                                            */
const float
tmpl_Sqrt_Pi_By_Eight_F = 0.6266570686577501256039413212027613132517F;

const double
tmpl_Sqrt_Pi_By_Eight = 0.6266570686577501256039413212027613132517;

const long double
tmpl_Sqrt_Pi_By_Eight_L = 0.6266570686577501256039413212027613132517L;

/*  sqrt( pi / 2 )                                                            */
const float tmpl_Sqrt_Pi_By_Two_F = 1.253314137315500251207882642405522626503F;
const double tmpl_Sqrt_Pi_By_Two = 1.253314137315500251207882642405522626503;

const long double
tmpl_Sqrt_Pi_By_Two_L = 1.253314137315500251207882642405522626503L;

/*  sqrt( 1 / pi )                                                            */
const float tmpl_Sqrt_One_By_Pi_F = 0.5641895835477562869480794515607725858441F;
const double tmpl_Sqrt_One_By_Pi = 0.5641895835477562869480794515607725858441;

const long double
tmpl_Sqrt_One_By_Pi_L = 0.5641895835477562869480794515607725858441L;

/*  sqrt( 2 / pi )                                                            */
const float tmpl_Sqrt_Two_By_Pi_F = 0.7978845608028653558798921198687637369517F;
const double tmpl_Sqrt_Two_By_Pi = 0.7978845608028653558798921198687637369517;

const long double
tmpl_Sqrt_Two_By_Pi_L = 0.7978845608028653558798921198687637369517L;

/*  1 / pi.                                                                   */
const float tmpl_One_By_Pi_F = 0.318309886183790671537767526745028724068F;
const double tmpl_One_By_Pi = 0.318309886183790671537767526745028724068;
const long double tmpl_One_By_Pi_L = 0.318309886183790671537767526745028724068L;

/*  2 / sqrt( pi )                                                            */
const float tmpl_Two_By_Sqrt_Pi_F = 1.128379167095512573896158903121545171688F;
const double tmpl_Two_By_Sqrt_Pi = 1.128379167095512573896158903121545171688;

const long double
tmpl_Two_By_Sqrt_Pi_L = 1.128379167095512573896158903121545171688L;

/*  pi / 2                                                                    */
const float tmpl_Pi_By_Two_F = 1.570796326794896619231321691639751442099F;
const double tmpl_Pi_By_Two = 1.570796326794896619231321691639751442099;
const long double tmpl_Pi_By_Two_L = 1.570796326794896619231321691639751442099L;

/*  3 pi / 4                                                                  */
const float
tmpl_Three_Pi_By_Four_F = 2.356194490192344928846982537459627163148F;

const double
tmpl_Three_Pi_By_Four = 2.356194490192344928846982537459627163148;

const long double
tmpl_Three_Pi_By_Four_L = 2.356194490192344928846982537459627163148L;

/*  pi / 4                                                                    */
const float tmpl_Pi_By_Four_F = 0.7853981633974483096156608458198757210493F;
const double tmpl_Pi_By_Four = 0.7853981633974483096156608458198757210493;

const long double
tmpl_Pi_By_Four_L = 0.7853981633974483096156608458198757210493L;

/*  pi                                                                        */
const float tmpl_One_Pi_F = 3.141592653589793238462643383279502884197F;
const double tmpl_One_Pi = 3.141592653589793238462643383279502884197;
const long double tmpl_One_Pi_L = 3.141592653589793238462643383279502884197L;

/*  2 pi                                                                      */
const float tmpl_Two_Pi_F = 6.283185307179586476925286766559005768394F;
const double tmpl_Two_Pi = 6.283185307179586476925286766559005768394;
const long double tmpl_Two_Pi_L = 6.283185307179586476925286766559005768394L;

/*  sqrt( 2 )                                                                 */
const float tmpl_Sqrt_Two_F = 1.414213562373095048801688724209698078570F;
const double tmpl_Sqrt_Two = 1.414213562373095048801688724209698078570;
const long double tmpl_Sqrt_Two_L = 1.414213562373095048801688724209698078570L;

/*  e = exp( 1 )                                                              */
const float tmpl_Euler_E_F = 2.718281828459045235360287471352662497757F;
const double tmpl_Euler_E = 2.718281828459045235360287471352662497757;
const long double tmpl_Euler_E_L = 2.718281828459045235360287471352662497757L;

/*  1 / e = exp( -1 )                                                         */
const float tmpl_Rcpr_Euler_E_F = 0.3678794411714423215955237701614608674458F;
const double tmpl_Rcpr_Euler_E = 0.3678794411714423215955237701614608674458;

const long double
tmpl_Rcpr_Euler_E_L = 0.3678794411714423215955237701614608674458L;

/*  log_e( 2 ) = ln( 2 )                                                      */
const float
tmpl_Natural_Log_of_Two_F = 0.6931471805599453094172321214581765680755F;

const double
tmpl_Natural_Log_of_Two = 0.6931471805599453094172321214581765680755;

const long double
tmpl_Natural_Log_of_Two_L = 0.6931471805599453094172321214581765680755L;

/*  log_e( 10 ) = ln( 10 )                                                    */
const float
tmpl_Natural_Log_of_Ten_F = 2.302585092994045684017991454684364207601F;

const double
tmpl_Natural_Log_of_Ten = 2.302585092994045684017991454684364207601;

const long double
tmpl_Natural_Log_of_Ten_L = 2.302585092994045684017991454684364207601L;

/*  pi / 180                                                                  */
const float tmpl_Deg_to_Rad_F = 1.745329251994329576923690768488612713443E-2F;
const double tmpl_Deg_to_Rad = 1.745329251994329576923690768488612713443E-2;

const long double
tmpl_Deg_to_Rad_L = 1.745329251994329576923690768488612713443E-2L;

/*  180 / pi                                                                  */
const float tmpl_Rad_to_Deg_F = 57.2957795130823208767981548141051703324F;
const double tmpl_Rad_to_Deg = 57.2957795130823208767981548141051703324;
const long double tmpl_Rad_to_Deg_L = 57.2957795130823208767981548141051703324L;

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
const long double
tmpl_Max_LDouble_Base_E = LDBL_MAX_10_EXP*2.30258509299404568401799145468436421L;
const long double
tmpl_Min_LDouble_Base_E = LDBL_MIN_10_EXP*2.3025850929940456840179910L;
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN    || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN     || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN  || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN      || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN
const long double
tmpl_Min_LDouble_Base_E = -11354.04709355363926789271586304859990768L;
const long double
tmpl_Max_LDouble_Base_E = 11356.34967864663331357673385450328427189L;
#else
const long double
tmpl_Min_LDouble_Base_E = -706.89362354917202499352337658809981173L;
const long double
tmpl_Max_LDouble_Base_E = 709.19620864216607067754136804278417594L;
#endif

