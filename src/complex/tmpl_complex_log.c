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
 *                              tmpl_complex_log                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex log function.                *
 *  NOTES:                                                                    *
 *      This function implicitly uses the atan2 function via the              *
 *      tmpl_CDouble_Argument function. Because of this the branch cut        *
 *      for the complex log occurs along the negative x-axis. No option is    *
 *      provided to choose different branches. One can artificially change    *
 *      the branch by adding a multiple of 2 pi to the imaginary part.        *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          This file provides compatibility between the two standard math.h  *
 *          header files (C89 vs C99 math.h). If C99 math.h exists, it simply *
 *          provides aliases for the functions, and if C89 math.h is used     *
 *          it defines the functions missing in the earlier version.          *
 *  2.) tmpl_complex.h:                                                       *
 *          Header file where tmpl_ComplexDouble is defined, as well as the   *
 *          prototype for tmpl_CDouble_Log.                                   *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 ******************************************************************************/

/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision complex log (clogf equivalent (C99)).                    */
tmpl_ComplexFloat tmpl_CFloat_Log(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float r, theta, real;
    tmpl_ComplexFloat ln_z;

    /*  Get the polar representation of the complex number z.                 */
    r = tmpl_CFloat_Abs(z);
    theta = tmpl_CFloat_Argument(z);

    /*  The real part is just ln(r), and the imaginary part is theta.         */
    real = tmpl_Float_Log(r);

    /*  Use tmpl_CFloat_Rect to create the complex number and return.         */
    ln_z = tmpl_CFloat_Rect(real, theta);
    return ln_z;
}
/*  End of tmpl_CFloat_Log.                                                   */

/*  Double precision complex log (clog equivalent (C99)).                     */
tmpl_ComplexDouble tmpl_CDouble_Log(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double r, theta, real;
    tmpl_ComplexDouble ln_z;

    /*  Get the polar representation of the complex number z.                 */
    r = tmpl_CDouble_Abs(z);
    theta = tmpl_CDouble_Argument(z);

    /*  The real part is just ln(r), and the imaginary part is theta.         */
    real = tmpl_Double_Log(r);

    /*  Use tmpl_CDouble_Rect to create the complex number and return.        */
    ln_z = tmpl_CDouble_Rect(real, theta);
    return ln_z;
}
/*  End of tmpl_CDouble_Log.                                                  */

/* Long double precision complex log (clogl equivalent (C99)).                */
tmpl_ComplexLongDouble tmpl_CLDouble_Log(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double r, theta, real;
    tmpl_ComplexLongDouble ln_z;

    /*  Get the polar representation of the complex number z.                 */
    r = tmpl_CLDouble_Abs(z);
    theta = tmpl_CLDouble_Argument(z);

    /*  The real part is just ln(r), and the imaginary part is theta.         */
    real = tmpl_LDouble_Log(r);

    /*  Use tmpl_CLDouble_Rect to create the complex number and return.       */
    ln_z = tmpl_CLDouble_Rect(real, theta);
    return ln_z;
}
/*  End of tmpl_CLDouble_Log.                                                 */
