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
 *                           tmpl_complex_compare                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for comparing complex data types.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Compare:                                                  *
 *      tmpl_CDouble_Compare:                                                 *
 *      tmpl_CLDouble_Compare:                                                *
 *  Purpose:                                                                  *
 *      Compares two complex numbers.                                         *
 *  Arguments:                                                                *
 *      z0 (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):               *
 *          A complex number.                                                 *
 *      z1 (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):               *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      compare (tmpl_Bool):                                                  *
 *          True if z0 = z1, false otherwise.                                 *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts of both inputs and compare them. *
 *  NOTES:                                                                    *
 *      This file is a fork of code I wrote for rss_ringoccs.                 *
 *      librssringoccs is also released under GPL3.                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 *  2.) tmpl_bool.h:                                                          *
 *          Header containing Boolean typedef.                                *
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
 *  2020/12/02: Ryan Maguire                                                  *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Soft freeze for alpha release of libtmpl.                             *
 ******************************************************************************/

/*  Boolean data type and True/False are defined here.                        */
#include <libtmpl/include/tmpl_bool.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  C does not allow structures to be compared, so we need to compare the     *
 *  members of the two complex structs.                                       */

/*  Single precision complex comparison.                                      */
tmpl_Bool tmpl_CFloat_Compare(tmpl_ComplexFloat z0, tmpl_ComplexFloat z1)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float z0_real, z0_imag, z1_real, z1_imag;

    /*  Extract the real and imaginary parts from z0 and z1.                  */
    z0_real = tmpl_CFloat_Real_Part(z0);
    z0_imag = tmpl_CFloat_Imag_Part(z0);
    z1_real = tmpl_CFloat_Real_Part(z1);
    z1_imag = tmpl_CFloat_Imag_Part(z1);

    /*  Two complex numbers are equal if and only if their real and imaginary *
     *  parts are both equal, so check this.                                  */
    if ((z0_real == z1_real) && (z0_imag == z1_imag))
        return tmpl_True;
    else
        return tmpl_False;
}
/*  End of tmpl_CFloat_Compare.                                               */

/*  Double precision complex comparison.                                      */
tmpl_Bool tmpl_CDouble_Compare(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double z0_real, z0_imag, z1_real, z1_imag;

    /*  Extract the real and imaginary parts from z0 and z1.                  */
    z0_real = tmpl_CDouble_Real_Part(z0);
    z0_imag = tmpl_CDouble_Imag_Part(z0);
    z1_real = tmpl_CDouble_Real_Part(z1);
    z1_imag = tmpl_CDouble_Imag_Part(z1);

    /*  Two complex numbers are equal if and only if their real and imaginary *
     *  parts are both equal, so check this.                                  */
    if ((z0_real == z1_real) && (z0_imag == z1_imag))
        return tmpl_True;
    else
        return tmpl_False;
}
/*  End of tmpl_CDouble_Compare.                                              */

/*  Long double precision complex comparison.                                 */
tmpl_Bool
tmpl_CLDouble_Compare(tmpl_ComplexLongDouble z0, tmpl_ComplexLongDouble z1)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    long double z0_real, z0_imag, z1_real, z1_imag;

    /*  Extract the real and imaginary parts from z and w.                    */
    z0_real = tmpl_CLDouble_Real_Part(z0);
    z0_imag = tmpl_CLDouble_Imag_Part(z0);
    z1_real = tmpl_CLDouble_Real_Part(z1);
    z1_imag = tmpl_CLDouble_Imag_Part(z1);

    /*  Two complex numbers are equal if and only if their real and imaginary *
     *  parts are both equal, so check this.                                  */
    if ((z0_real == z1_real) && (z0_imag == z1_imag))
        return tmpl_True;
    else
        return tmpl_False;
}
/*  End of tmpl_CLDouble_Compare.                                             */

