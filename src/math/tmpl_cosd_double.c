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
 *                              tmpl_cosd_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes cosine of an argument in degrees.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cosd                                                      *
 *  Purpose:                                                                  *
 *      Computes cos(x) where x is in degrees.                                *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cos_x (double):                                                       *
 *          The cosine of x, taken in degrees.                                *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Sind_Maclaurin:                                       *
 *              Computes sind via a Maclaurin series for small x.             *
 *          tmpl_Double_Cosd_Maclaurin:                                       *
 *              Computes cosd via a Maclaurin series for small x.             *
 *          tmpl_Double_Mod_360:                                              *
 *              Reduces a real number mod 360.                                *
 *          tmpl_Double_Abs:                                                  *
 *              Computes the absolute value of a real number.                 *
 *  Method:                                                                   *
 *      Using the fact that cosine is even, reduce x to |x|. Since cosine     *
 *      is periodic with period 360, in degrees, reduce x mod 360. Further    *
 *      reduce x to lie between 0 and 180 via cos(x) = -cos(x - 180). Then    *
 *      write x = n + r where |r| < 1 and n is an integer. Pre-computed       *
 *      values of cos(x) exist in a table for integer inputs. Applying the    *
 *      addition formula:                                                     *
 *                                                                            *
 *          cos(n + r) = cos(n)cos(r) - sin(n)sin(r)                          *
 *                                                                            *
 *      means we only need to compute cos(r) and sin(r) for small values.     *
 *      This is done using polynomial approximations.                         *
 *  Error:                                                                    *
 *      Based on 2,245,334,220 samples with -10^6 < x < 10^6.                 *
 *          max relative error: 2.2547000044530448e-16                        *
 *          rms relative error: 7.2237283260265052e-17                        *
 *          max absolute error: 2.2204460492503131e-16                        *
 *          rms absolute error: 7.2667392491256475e-17                        *
 *      Values are computed using glibc and defining cosd(x) as               *
 *      cos(fmod(x, 360) * M_PI / 180) using the standard libm functions.     *
 *      The samples were chosen away from values 360n +/- 90. See below.      *
 *  Notes:                                                                    *
 *      Defining cosd(x) = cos(fmod(x, 360.0) * M_PI / 180.0) results in      *
 *      poor relative error for values 360n +/- 90. This is caused by M_PI    *
 *      only being accurate to double precision. For example, taking x = 90   *
 *      yields cosd(90) = 6.123233995736766e-17. The approach we've taken     *
 *      using lookup tables yields exact answers for such integers,           *
 *      tmpl_Double_Cosd(90) = 0.0 will be computed.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 25, 2022                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/02/23: Ryan Maguire                                                  *
 *      Added license and function description.                               *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Polynomial approximation for cosine, in degrees, provided here.           */
#include "auxiliary/tmpl_cosd_maclaurin_double.h"

/*  Polynomial approximation for sine, in degrees, given here.                */
#include "auxiliary/tmpl_sind_maclaurin_double.h"

/*  Computes cosine for an argument in degrees at double precision.           */
double tmpl_Double_Cosd(double x)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    double sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    /*  Cosine is even. Reduce x to |x| for the computation.                  */
    const double abs_x = tmpl_Double_Abs(x);

    /*  cosine is periodic with period 360, in degrees. Reduce mod 360.       */
    double arg = tmpl_Double_Mod_360(abs_x);

    /*  Further reduce using cos(x) = -cos(x - 180).                          */
    if (arg >= 180.0)
    {
        sgn_x = -1.0;
        arg = arg - 180.0;
    }
    else
        sgn_x = 1.0;

    /*  arg now lies between 0 and 180. Get the integer part of this.         */
    ind = (unsigned int)arg;

    /*  Decompose x into x = n + dx with dx bounded by 1.                     */
    dx = arg - (double)ind;

    /*  cos(n + dx) = cos(n)cos(dx) - sin(n)sin(dx). cos(n) and sin(n) have   *
     *  been pre-computed, in degrees, for all integers between 0 and 180.    */
    sx = tmpl_double_sind_table[ind];
    cx = tmpl_double_cosd_table[ind];

    /*  dx is small so cos(dx) and sin(dx) can be computed with polynomials.  */
    sdx = tmpl_Double_Sind_Maclaurin(dx);
    cdx = tmpl_Double_Cosd_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}
/*  End of tmpl_Double_Cosd.                                                  */
