/******************************************************************************
 *                                 LICENSE                                    *
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
 *                          tmpl_complex_add_imag                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Add_Imag:                                                 *
 *      tmpl_CDouble_Add_Imag:                                                *
 *      tmpl_CLDouble_Add_Imag:                                               *
 *  Purpose:                                                                  *
 *      Adds an imaginary number to a complex one.                            *
 *                                                                            *
 *          w = z + iy = (a + ib) + iy = a + i(b+y)                           *
 *                                                                            *
 *  Arguments:                                                                *
 *      y (float/double/long double):                                         *
 *          The imaginary number we wish to add to z.                         *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      w (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          The sum of z and iy.                                              *
 *  Called Functions:                                                         *
 *      tmpl_CFloat_Real_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Real_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Real_Part (tmpl_complex.h)                              *
 *          Returns the real part of a complex number.                        *
 *      tmpl_CFloat_Imag_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Imag_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Imag_Part (tmpl_complex.h)                              *
 *          Returns the imaginary part of a complex number.                   *
 *      tmpl_CFloat_Rect        (tmpl_complex.h)                              *
 *      tmpl_CDouble_Rect       (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Rect      (tmpl_complex.h)                              *
 *          Creates a complex number from two real ones.                      *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts and compute a component-wise sum.*
 *  Notes:                                                                    *
 *      This file is a fork of the code I wrote for rss_ringoccs.             *
 *      librssringoccs is also released under GPL3.                           *
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
 *  2021/06/03: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code and comments. *
 *      No more changes unless something breaks.                              *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, doubles and _Complex      *
 *  doubles can be added via y*_Complex_I + z. With C89 we use structs to     *
 *  define complex numbers. Since we can't add a double to a struct, and      *
 *  since the _Complex_I macro is undefined, we need a function for computing *
 *  the sum of complex numbers with imaginary ones.                           */

/*  Single precision complex addition where one variable is imaginary.        */
tmpl_ComplexFloat tmpl_CFloat_Add_Imag(float y, tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat sum;
    float real, imag, sum_im;

    /*  Extract the real and imaginary parts from the input.                  */
    real = tmpl_CFloat_Real_Part(z);
    imag = tmpl_CFloat_Imag_Part(z);

    /*  Add the imaginary variable to the imaginary part of z.                */
    sum_im = y + imag;

    /*  Create the output from real and sum_im and return.                    */
    sum = tmpl_CFloat_Rect(real, sum_im);
    return sum;
}
/*  End of tmpl_CFloat_Add_Imag.                                              */

/*  Double precision complex addition where one variable is imaginary.        */
tmpl_ComplexDouble tmpl_CDouble_Add_Imag(double y, tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble sum;
    double real, imag, sum_im;

    /*  Extract the real and imaginary parts from the input.                  */
    real = tmpl_CDouble_Real_Part(z);
    imag = tmpl_CDouble_Imag_Part(z);

    /*  Add the imaginary variable to the imaginary part of z.                */
    sum_im = y + imag;

    /*  Create the output from real and sum_im and return.                    */
    sum = tmpl_CDouble_Rect(real, sum_im);
    return sum;
}
/*  End of tmpl_CDouble_Add_Imag.                                             */

/*  Long double precision complex addition where one variable is imaginary.   */
tmpl_ComplexLongDouble
tmpl_CLDouble_Add_Imag(long double y, tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble sum;
    long double real, imag, sum_im;

    /*  Extract the real and imaginary parts from the input.                  */
    real = tmpl_CLDouble_Real_Part(z);
    imag = tmpl_CLDouble_Imag_Part(z);

    /*  Add the imaginary variable to the imaginary part of z.                */
    sum_im = y + imag;

    /*  Create the output from real and sum_im and return.                    */
    sum = tmpl_CLDouble_Rect(real, sum_im);
    return sum;
}
/*  End of tmpl_CLDouble_Add_Imag.                                            */

