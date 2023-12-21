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
 *                        tmpl_complex_log_abs_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the function f(z) = ln(|z|).             *
 *  Method:                                                                   *
 *      Write:                                                                *
 *          ln(|z|) = ln(|x+iy|)                                              *
 *                  = ln(sqrt(x^2 + y^2))                                     *
 *                  = 0.5 * ln(x^2 + y^2)                                     *
 *      This avoids the square root computation and is more accurate.         *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file providing logarithmic functions.                      *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where the function prototype is given.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2021/02/18: Ryan Maguire                                                  *
 *      Created file.                                                         *
 *  2023/12/20: Ryan Maguire                                                  *
 *      Simplified code. Move float and long double to their own files.       *
 ******************************************************************************/

/*  Header file providing log and other math routines.                        */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Double precision complex log(|z|) function.                               */
double tmpl_CDouble_Log_Abs(tmpl_ComplexDouble z)
{
    /*  Compute |z|^2. We can skip the sqrt root using log rules.             */
    const double abs_squared = z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1];

    /*  By log rules we have ln(|x+iy)| = 0.5 ln(x^2+y^2). Use this.          */
    return 0.5 * tmpl_Double_Log(abs_squared);
}
/*  End of tmpl_CDouble_Log_Abs.                                              */
