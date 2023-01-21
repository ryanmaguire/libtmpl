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
 *                            rss_ringoccs_erf                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the error function Erf.                  *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) rss_ringoccs_math.h:                                                  *
 *          This file provides compatibility between the two standard math.h  *
 *          header files (C89 vs C99 math.h). If C99 math.h exists, it simply *
 *          provides aliases for the functions, and if C89 math.h is used     *
 *          it defines the functions missing in the earlier version.          *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       December 10, 2020                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/12/10 (Ryan Maguire):                                                *
 *      Frozen for v1.3.                                                      *
 ******************************************************************************/

/*  Header file where the prototypes for these functions are defined.         */
#include <libtmpl/include/tmpl_math.h>

/*  Erf is not required in C89, so we provide the algorithm for               *
 *  double, float, and long double inputs.                                    */

/*  Single precision error function (erff equivalent).                        */
float tmpl_Float_Erf(float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float erf, erfc;

    /*  The error function can be computed by the complimentary error         *
     *  Erfc via Erf(x) = 1 - Erfc(x). We'll use this.                        */
    erfc = tmpl_Float_Erfc(x);
    erf = 1.0F - erfc;
    return erf;
}
/*  End of tmpl_Float_Erf.                                                    */

/*  Long double precision error function (erfl equivalent).                   */
long double tmpl_LDouble_Erf(long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double erf, erfc;

    /*  The error function can be computed by the complimentary error         *
     *  Erfc via Erf(x) = 1 - Erfc(x). We'll use this.                        */
    erfc = tmpl_LDouble_Erfc(x);
    erf = 1.0L - erfc;
    return erf;
}
/*  End of tmpl_Double_Erf.                                                   */
