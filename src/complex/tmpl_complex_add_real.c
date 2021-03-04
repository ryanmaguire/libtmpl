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
 *                           tmpl_complex_add_real                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Add_Real:                                                 *
 *      tmpl_CDouble_Add_Real:                                                *
 *      tmpl_CLDouble_Add_Real:                                               *
 *  Purpose:                                                                  *
 *      Adds a real number to a complex one.                                  *
 *                                                                            *
 *          w = z + x = (a + ib) + x = (a + x) + ib                           *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (float/double/long double):                                         *
 *          The real number we wish to add to z.                              *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      w (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          The sum of z and x.                                               *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
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
 *  2020/12/03: Ryan Maguire                                                  *
 *      Created function (Wellesley college for librssringoccs).              *
 *      Moved here from rss_ringoccs_complex_add.c.                           *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Made compatible with libtmpl.                                         *
 *      Soft freeze for alpha release of libtmpl.                             *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, doubles and _Complex      *
 *  doubles can be added via x + z. With C89 we use structs to define complex *
 *  numbers. Since we can't add a double to a struct, we need a function      *
 *  for computing the sum of complex numbers with real ones.                  */

/*  Single precision complex addition where one variable is real.             */
tmpl_ComplexFloat tmpl_CFloat_Add_Real(float x, tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat sum;
    float real, imag, sum_re;

    /*  Extract the real and imaginary parts from the input.                  */
    real = tmpl_CFloat_Real_Part(z);
    imag = tmpl_CFloat_Imag_Part(z);

    /*  Add the real variable to the real part of z.                          */
    sum_re = x + real;

    /*  Create the output from sum_re and imag and return.                    */
    sum = tmpl_CFloat_Rect(sum_re, imag);
    return sum;
}
/*  End of tmpl_CFloat_Add_Real.                                              */

/*  Double precision complex addition where one variable is real.             */
tmpl_ComplexDouble tmpl_CDouble_Add_Real(double x, tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble sum;
    double real, imag, sum_re;

    /*  Extract the real and imaginary parts from the input.                  */
    real = tmpl_CDouble_Real_Part(z);
    imag = tmpl_CDouble_Imag_Part(z);

    /*  Add the real variable to the real part of z.                          */
    sum_re = x + real;

    /*  Create the output from sum_re and imag and return.                    */
    sum = tmpl_CDouble_Rect(sum_re, imag);
    return sum;
}
/*  End of tmpl_CDouble_Add_Real.                                             */

/*  Long double precision complex addition where one variable is real.        */
tmpl_ComplexLongDouble
tmpl_CLDouble_Add_Real(long double x, tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble sum;
    long double real, imag, sum_re;

    /*  Extract the real and imaginary parts from the input.                  */
    real = tmpl_CLDouble_Real_Part(z);
    imag = tmpl_CLDouble_Imag_Part(z);

    /*  Add the real variable to the real part of z.                          */
    sum_re = x + real;

    /*  Create the output from sum_re and imag and return.                    */
    sum = tmpl_CLDouble_Rect(sum_re, imag);
    return sum;
}
/*  End of tmpl_CLDouble_Add_Real.                                            */

