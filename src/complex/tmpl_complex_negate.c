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
 *                            tmpl_complex_negate                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex negative.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Negate:                                                   *
 *      tmpl_CDouble_Negate:                                                  *
 *      tmpl_CLDouble_Negate:                                                 *
 *  Purpose:                                                                  *
 *      Computes the negative of a complex number.                            *
 *                                                                            *
 *          neg(z) = neg(x + iy) = -x - iy                                    *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      neg_z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):            *
 *          The negative of z.                                                *
 *  Method:                                                                   *
 *      Negate the real and imaginary part of z and return.                   *
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
 *  Date:       February 18, 2020                                             *
 ******************************************************************************
 *  2021/02/18: Ryan Maguire                                                  *
 *      Created file.                                                         *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision complex negative function.                               */
tmpl_ComplexFloat tmpl_CFloat_Negate(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float real, imag;
    tmpl_ComplexFloat neg_z;

    /*  Extract the values from the complex number.                           */
    real = tmpl_CFloat_Real_Part(z);
    imag = tmpl_CFloat_Imag_Part(z);

    /*  The negative of x+iy is just -x-iy, compute this.                     */
    neg_z = tmpl_CFloat_Rect(-real, -imag);
    return neg_z;
}
/*  End of tmpl_CFloat_Negate.                                                */

/*  Double precision complex negative function.                               */
tmpl_ComplexDouble tmpl_CDouble_Negate(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double real, imag;
    tmpl_ComplexDouble neg_z;

    /*  Extract the values from the complex number.                           */
    real = tmpl_CDouble_Real_Part(z);
    imag = tmpl_CDouble_Imag_Part(z);

    /*  The negative of x+iy is just -x-iy, compute this.                     */
    neg_z = tmpl_CDouble_Rect(-real, -imag);
    return neg_z;
}
/*  End of tmpl_CDouble_Negate.                                               */

/*  Long double precision complex negative function.                          */
tmpl_ComplexLongDouble tmpl_CLDouble_Negate(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double real, imag;
    tmpl_ComplexLongDouble neg_z;

    /*  Extract the values from the complex number.                           */
    real = tmpl_CLDouble_Real_Part(z);
    imag = tmpl_CLDouble_Imag_Part(z);

    /*  The negative of x+iy is just -x-iy, compute this.                     */
    neg_z = tmpl_CLDouble_Rect(-real, -imag);
    return neg_z;
}
/*  End of tmpl_CLDouble_Negate.                                              */
