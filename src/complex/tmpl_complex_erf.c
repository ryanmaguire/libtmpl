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
 *                             tmpl_complex_erf                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex error function.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Erf:                                                      *
 *      tmpl_CDouble_Erf:                                                     *
 *      tmpl_CLDouble_Erf:                                                    *
 *  Purpose:                                                                  *
 *      Computes the error function of a complex value z.                     *
 *                                                                            *
 *                               z                                            *
 *                               -                                            *
 *                      2       | |                                           *
 *          Erf(z) = -------    |   exp(-t^2) dt                              *
 *                   sqrt(pi) | |                                             *
 *                             -                                              *
 *                             0                                              *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      erf_z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):            *
 *          The error function Erf(z).                                        *
 *  Method:                                                                   *
 *      Use the complementary error function Erfc(z) and apply the formula:   *
 *                                                                            *
 *          Erf(z) = 1 - Erfc(z)                                              *
 *                                                                            *
 *  NOTES:                                                                    *
 *      No actual float or long double algorithms have been implemented by    *
 *      libtmpl. The complementary error functions simply convert float       *
 *      and long double inputs to doubles.                                    *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) rss_ringoccs_complex.h:                                               *
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
 *  2020/12/23: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision complex error function.                                  */
tmpl_ComplexFloat tmpl_CFloat_Erf(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat erfz, erfcz;

    /*  Compute the complementary error function Erfc(z).                     */
    erfcz = tmpl_CFloat_Erfc(z);

    /*  Erf(z) = 1 - Erfc(z). Compute this and return.                        */
    erfz = tmpl_CFloat_Subtract_Real(1.0F, erfcz);
    return erfz;
}
/*  End of tmpl_CFloat_Erf.                                                   */

/*  Double precision complex error function.                                  */
tmpl_ComplexDouble tmpl_CDouble_Erf(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble erfz, erfcz;

    /*  Compute the complementary error function Erfc(z).                     */
    erfcz = tmpl_CDouble_Erfc(z);

    /*  Erf(z) = 1 - Erfc(z). Compute this and return.                        */
    erfz = tmpl_CDouble_Subtract_Real(1.0, erfcz);
    return erfz;
}
/*  End of tmpl_CDouble_Erf.                                                  */

/*  Double precision complex error function.                                  */
tmpl_ComplexLongDouble tmpl_CLDouble_Erf(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble erfz, erfcz;

    /*  Compute the complementary error function Erfc(z).                     */
    erfcz = tmpl_CLDouble_Erfc(z);

    /*  Erf(z) = 1 - Erfc(z). Compute this and return.                        */
    erfz = tmpl_CLDouble_Subtract_Real(1.0L, erfcz);
    return erfz;
}
/*  End of tmpl_CLDouble_Erf.                                                 */

