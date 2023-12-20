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
 *                          tmpl_complex_exp_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex exponentiation function.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Exp                                                      *
 *  Purpose:                                                                  *
 *      Computes the complex exponential of a complex number.                 *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      exp_z (tmpl_ComplexDouble):                                           *
 *          The complex exponential of z.                                     *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Exp:                                                  *
 *              Computes the exponential of a real number.                    *
 *          tmpl_Double_SinCos:                                               *
 *              Computes sin(t) and cos(t) simultaneously.                    *
 *  Method:                                                                   *
 *      Use Euler's formula. Given z = x + iy we have the following:          *
 *                                                                            *
 *          exp(z) = exp(x + iy) = exp(x) exp(iy)                             *
 *                               = exp(x) [cos(y) + i sin(y)]                 *
 *                               = [exp(x) cos(y)] + i [exp(x) sin(y)]        *
 *                                                                            *
 *      Hence the real and imaginary parts can be computed separately using   *
 *      the real valued exponential and trig functions.                       *
 *  Notes:                                                                    *
 *      This function checks if the imaginary part is zero. In this case,     *
 *      the complex number returned is just exp(real(z)).                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file providing trigonometric and exponential functions.    *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/12/27: Ryan Maguire                                                  *
 *      Added float and long double support. Frozen for v1.3.                 *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2023/12/20: Ryan Maguire                                                  *
 *      Greatly simplified code. Moved float and long double to own files.    *
 ******************************************************************************/

/*  Header file providing trig and exponential functions.                     */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are given and where complex types are defined.       */
#include <libtmpl/include/tmpl_complex.h>

/*  Compute the complex exponential of a complex number z = x + iy.           */
tmpl_ComplexDouble tmpl_CDouble_Exp(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble exp_z;
    double sin_y, cos_y;

    /*  We'll use the fact that exp(x+iy) = exp(x)*exp(iy). Then we'll use    *
     *  Euler's formula to write exp(iy) as cos(y) + i*sin(y), giving us      *
     *  exp(z) = exp(x)*cos(y) + i*exp(x)*sin(y).                             */
    const double exp_real = tmpl_Double_Exp(z.dat[0]);

    /*  In the case that z is real, use the real valued exponential. This     *
     *  avoid the result of exp(inf) = inf + i nan. The imaginary part of     *
     *  complex exp(inf) will be exp(inf) * sin(0) = inf * 0 which results in *
     *  nan. This if-then statement avoids this.                              */
    if (z.dat[1] == 0.0)
    {
        exp_z.dat[0] = exp_real;
        exp_z.dat[1] = 0.0;
    }

    /*  When we have non-zero imaginary part, resort to Euler's formula.      */
    else
    {
        /*  Compute sin(y) and cos(y) simultaneously with SinCos.             */
        tmpl_Double_SinCos(z.dat[1], &sin_y, &cos_y);

        /*  We've computed exp(x) already. Scale by cos(y) and sin(y).        */
        exp_z.dat[0] = exp_real * cos_y;
        exp_z.dat[1] = exp_real * sin_y;
    }

    return exp_z;
}
/*  End of tmpl_CDouble_Exp.                                                  */
