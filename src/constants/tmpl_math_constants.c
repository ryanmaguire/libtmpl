/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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

/*  sqrt( 1 / (2 pi) )                                                        */
const float tmpl_Sqrt_One_By_Two_Pi_F       = 0.398942280F;
const double tmpl_Sqrt_One_By_Two_Pi        = 0.39894228040143267;
const long double tmpl_Sqrt_One_By_Two_Pi_L = 0.3989422804014326779399461L;

/*  sqrt( pi / 8 )                                                            */
const float tmpl_Sqrt_Pi_By_Eight_F       = 0.626657069F;
const double tmpl_Sqrt_Pi_By_Eight        = 0.62665706865775012;
const long double tmpl_Sqrt_Pi_By_Eight_L = 0.6266570686577501256039413L;

/*  sqrt( pi / 2 )                                                            */
const float tmpl_Sqrt_Pi_By_Two_F       = 1.253314137F;
const double tmpl_Sqrt_Pi_By_Two        = 1.25331413731550025;
const long double tmpl_Sqrt_Pi_By_Two_L = 1.2533141373155002512078830L;

/*  sqrt( 1 / pi )                                                            */
const float tmpl_Sqrt_One_By_Pi_F       = 0.564189584F;
const double tmpl_Sqrt_One_By_Pi        = 0.56418958354775628;
const long double tmpl_Sqrt_One_By_Pi_L = 0.5641895835477562869480795L;

/*  sqrt( 2 / pi )                                                            */
const float tmpl_Sqrt_Two_By_Pi_F       = 0.797884561F;
const double tmpl_Sqrt_Two_By_Pi        = 0.79788456080286535;
const long double tmpl_Sqrt_Two_By_Pi_L = 0.7978845608028653558798921L;

/*  2 / sqrt( pi )                                                            */
const float tmpl_Two_By_Sqrt_Pi_F       = 1.128379167F;
const double tmpl_Two_By_Sqrt_Pi        = 1.12837916709551257;
const long double tmpl_Two_By_Sqrt_Pi_L = 1.1283791670955125738961590L;

/*  pi / 2                                                                    */
const float tmpl_Pi_By_Two_F       = 1.570796327F;
const double tmpl_Pi_By_Two        = 1.57079632679489661;
const long double tmpl_Pi_By_Two_L = 1.5707963267948966192313220L;

/*  3 pi / 4                                                                  */
const float tmpl_Three_Pi_By_Four_F       = 2.356194490F;
const double tmpl_Three_Pi_By_Four        = 2.35619449019234492;
const long double tmpl_Three_Pi_By_Four_L = 2.3561944901923449288469830L;

/*  pi / 4                                                                    */
const float tmpl_Pi_By_Four_F       = 0.785398163F;
const double tmpl_Pi_By_Four        = 0.78539816339744830;
const long double tmpl_Pi_By_Four_L = 0.7853981633974483096156608L;

/*  pi                                                                        */
const float tmpl_One_Pi_F       = 3.141592654F;
const double tmpl_One_Pi        = 3.14159265358979323;
const long double tmpl_One_Pi_L = 3.1415926535897932384626430L;

/*  2 pi                                                                      */
const float tmpl_Two_Pi_F       = 6.283185307F;
const double tmpl_Two_Pi        = 6.28318530717958647;
const long double tmpl_Two_Pi_L = 6.2831853071795864769252870L;

/*  sqrt( 2 )                                                                 */
const float tmpl_Sqrt_Two_F       = 1.414213562F;
const double tmpl_Sqrt_Two        = 1.41421356237309504;
const long double tmpl_Sqrt_Two_L = 1.4142135623730950488016890L;

/*  e = exp( 1 )                                                              */
const float tmpl_Euler_E_F       = 2.718281828F;
const double tmpl_Euler_E        = 2.71828182845904523;
const long double tmpl_Euler_E_L = 2.7182818284590452353602875L;

/*  1 / e = exp( -1 )                                                         */
const float tmpl_Rcpr_Euler_E_F       = 0.367879441F;
const double tmpl_Rcpr_Euler_E        = 0.36787944117144232;
const long double tmpl_Rcpr_Euler_E_L = 0.3678794411714423215955238L;

/*  log_e( 2 ) = ln( 2 )                                                      */
const float tmpl_Natural_Log_of_Two_F       = 0.693147181F;
const double tmpl_Natural_Log_of_Two        = 0.69314718055994531;
const long double tmpl_Natural_Log_of_Two_L = 0.6931471805599453094172321L;

/*  log_e( 10 ) = ln( 10 )                                                    */
const float tmpl_Natural_Log_of_Ten_F       = 2.302585093F;
const double tmpl_Natural_Log_of_Ten        = 2.30258509299404568;
const long double tmpl_Natural_Log_of_Ten_L = 2.3025850929940456840179910L;

/*  pi / 180                                                                  */
const float tmpl_Deg_to_Rad_F       = 1.745329251E-2F;
const double tmpl_Deg_to_Rad        = 1.74532925199432957E-2;
const long double tmpl_Deg_to_Rad_L = 1.74532925199432957692369076E-2L;

