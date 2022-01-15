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
 *                           tmpl_complex_log_abs                             *
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
 *  2021/02/18: Ryan Maguire                                                  *
 *      Created file.                                                         *
 ******************************************************************************/

/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision complex log(|z|) function.                               */
float tmpl_CFloat_Log_Abs(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float abs_squared, ln_abs_z;

    /*  Compute |z|^2.                                                        */
    abs_squared = tmpl_CFloat_Abs_Squared(z);

    /*  By log rules we have ln(|x+iy)| = 0.5 ln(x^2+y^2). Use this.          */
    ln_abs_z = 0.5F * tmpl_Float_Log(abs_squared);
    return ln_abs_z;
}
/*  End of tmpl_CFloat_Log_Abs.                                               */

/*  Double precision complex log(|z|) function.                               */
double tmpl_CDouble_Log_Abs(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double abs_squared, ln_abs_z;

    /*  Compute |z|^2.                                                        */
    abs_squared = tmpl_CDouble_Abs_Squared(z);

    /*  By log rules we have ln(|x+iy)| = 0.5 ln(x^2+y^2). Use this.          */
    ln_abs_z = 0.5 * tmpl_Double_Log(abs_squared);
    return ln_abs_z;
}
/*  End of tmpl_CDouble_Log_Abs.                                              */

/*  long double precision complex log(|z|) function.                          */
long double tmpl_CLDouble_Log_Abs(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double abs_squared, ln_abs_z;

    /*  Compute |z|^2.                                                        */
    abs_squared = tmpl_CLDouble_Abs_Squared(z);

    /*  By log rules we have ln(|x+iy)| = 0.5 ln(x^2+y^2). Use this.          */
    ln_abs_z = 0.5L * tmpl_LDouble_Log(abs_squared);
    return ln_abs_z;
}
/*  End of tmpl_CLDouble_Log_Abs.                                             */
