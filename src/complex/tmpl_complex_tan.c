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
 *                            tmpl_complex_tan                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex tangent function.            *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Tan:                                                      *
 *      tmpl_CDouble_Tan:                                                     *
 *      tmpl_CLDouble_Tan:                                                    *
 *  Purpose:                                                                  *
 *      Computes the complex tangent of a complex number.                     *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      tan_z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):            *
 *          The complex tangent of z.                                         *
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
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/11/14: Ryan Maguire                                                  *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Added float and long double support.                                  *
 ******************************************************************************/

/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision complex tangent (ctan equivalent).                       */
tmpl_ComplexFloat tmpl_CFloat_Tan(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat sin_z, cos_z, tan_z;

    /*  Compute sin(z), cos(z), and then return sin(z)/cos(z).                */
    sin_z = tmpl_CFloat_Sin(z);
    cos_z = tmpl_CFloat_Cos(z);
    tan_z = tmpl_CFloat_Divide(sin_z, cos_z);
    return tan_z;
}
/*  End of tmpl_CLDouble_Tan.                                                 */

/*  Double precision complex tangent (ctan equivalent).                       */
tmpl_ComplexDouble tmpl_CDouble_Tan(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble sin_z, cos_z, tan_z;

    /*  Compute sin(z), cos(z), and then return sin(z)/cos(z).                */
    sin_z = tmpl_CDouble_Sin(z);
    cos_z = tmpl_CDouble_Cos(z);
    tan_z = tmpl_CDouble_Divide(sin_z, cos_z);
    return tan_z;
}
/*  End of tmpl_CDouble_Tan.                                                  */

/*  Long double precision complex tangent (ctan equivalent).                  */
tmpl_ComplexLongDouble tmpl_CLDouble_Tan(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble sin_z, cos_z, tan_z;

    /*  Compute sin(z), cos(z), and then return sin(z)/cos(z).                */
    sin_z = tmpl_CLDouble_Sin(z);
    cos_z = tmpl_CLDouble_Cos(z);
    tan_z = tmpl_CLDouble_Divide(sin_z, cos_z);
    return tan_z;
}
/*  End of tmpl_CLDouble_Tan.                                                 */

