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
 *                           tmpl_complex_argument                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex argument.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Argument:                                                 *
 *      tmpl_CDouble_Argument:                                                *
 *      tmpl_CLDouble_Argument:                                               *
 *  Purpose:                                                                  *
 *      Computes the argument of a complex number:                            *
 *                                                                            *
 *          arg(z) =  arg(r * exp(i theta)) = theta                           *
 *                                                                            *
 *      Equivalently:                                                         *
 *                                                                            *
 *          arg(z) = arg(x + iy) = arctan(y, x)                               *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      arg (float/double/long double):                                       *
 *          The argument of z.                                                *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts and return atan2(y, x).          *
 *  NOTES:                                                                    *
 *      Because the atan2 function is used, there is a discontinuity along    *
 *      the negative real axis. That is, the argument returns a real value    *
 *      in the interval (-pi, pi] (+pi is inclusive).                         *
 *                                                                            *
 *      This file is a fork of the code I wrote for rss_rinoccs.              *
 *      librssringoccs is also released under GPL3.                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          This file provides compatibility between the two standard math.h  *
 *          header files (C89 vs C99 math.h). If C99 math.h exists, it simply *
 *          provides aliases for the functions, and if C89 math.h is used     *
 *          it defines the functions missing in the earlier version.          *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
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
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/12/02 (Ryan Maguire):                                                *
 *      Frozen for v1.3.                                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Made compatible with the rest of libtmpl.                             *
 *      Soft freeze for alpha release of libtmpl.                             *
 ******************************************************************************/

/*  Header file which contains aliases for the functions in the standard C    *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision complex argument function (cargf equivalent).            */
float tmpl_CFloat_Argument(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float real, imag, theta;

    /*  Extract the real and imaginary parts from the input complex number.   */
    real = tmpl_CFloat_Real_Part(z);
    imag = tmpl_CFloat_Imag_Part(z);

    /*  Compute the argument using arctan and return.                         */
    theta = tmpl_Float_Arctan2(imag, real);
    return theta;
}
/*  End of tmpl_CFloat_Argument.                                              */

/*  Double precision complex argument function (carg equivalent).             */
double tmpl_CDouble_Argument(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double real, imag, theta;

    /*  Extract the real and imaginary parts from the input complex number.   */
    real = tmpl_CDouble_Real_Part(z);
    imag = tmpl_CDouble_Imag_Part(z);

    /*  Compute the argument using arctan and return.                         */
    theta = tmpl_Double_Arctan2(imag, real);
    return theta;
}
/*  End of tmpl_CDouble_Argument.                                             */

/*  Long double precision complex argument function (cargl equivalent).       */
long double tmpl_CLDouble_Argument(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double real, imag, theta;

    /*  Extract the real and imaginary parts from the input complex number.   */
    real = tmpl_CLDouble_Real_Part(z);
    imag = tmpl_CLDouble_Imag_Part(z);

    /*  Compute the argument using arctan and return.                         */
    theta = tmpl_LDouble_Arctan2(imag, real);
    return theta;
}
/*  End of tmpl_CLDouble_Argument.                                            */

