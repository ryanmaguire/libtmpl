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
 *                             tmpl_complex_pow                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the complex power function with a        *
 *      real exponent.                                                        *
 *  NOTES:                                                                    *
 *      This function implicitly uses the complex log function, and hence     *
 *      there is a branch cut in the second variable. The function is         *
 *      continuous in the first variable, i.e. no branch cut.                 *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Header file where tmpl_ComplexDouble is defined, as well          *
 *          as the prototype for tmpl_CDouble_Pow.                            *
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
 *                                History                                     *
 ******************************************************************************
 *  2021/02/18: Ryan Maguire                                                  *
 *      Created file.                                                         *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Compute the complex power z^x for x real.                                 */
tmpl_ComplexFloat
tmpl_CFloat_Pow_Real(tmpl_ComplexFloat z, float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat z_to_the_x, ln_z, x_ln_z;

    /*  We can write z^x as exp(x ln(z)) and this is how we'll compute for    *
     *  complex powers. First compute log(z).                                 */
    ln_z = tmpl_CFloat_Log(z);

    /*  Next use tmpl_CFloat_Multiply_Real to compute the product with x.     */
    x_ln_z = tmpl_CFloat_Multiply_Real(x, ln_z);

    /*  And finally exponentiate.                                             */
    z_to_the_x = tmpl_CFloat_Exp(x_ln_z);
    return z_to_the_x;
}
/*  End of tmpl_CFloat_Pow_Real.                                              */

/*  Compute the complex power z^x for x real.                                 */
tmpl_ComplexDouble
tmpl_CDouble_Pow_Real(tmpl_ComplexDouble z, double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble z_to_the_x, ln_z, x_ln_z;

    /*  We can write z^x as exp(x ln(z)) and this is how we'll compute for    *
     *  complex powers. First compute log(z).                                 */
    ln_z = tmpl_CDouble_Log(z);

    /*  Next use tmpl_CDouble_Multiply_Real to compute the product with x.    */
    x_ln_z = tmpl_CDouble_Multiply_Real(x, ln_z);

    /*  And finally exponentiate.                                             */
    z_to_the_x = tmpl_CDouble_Exp(x_ln_z);
    return z_to_the_x;
}
/*  End of tmpl_CDouble_Pow_Real.                                             */

/*  Compute the complex power z^x for x real.                                 */
tmpl_ComplexLongDouble
tmpl_CLDouble_Pow_Real(tmpl_ComplexLongDouble z, long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble z_to_the_x, ln_z, x_ln_z;

    /*  We can write z^x as exp(x ln(z)) and this is how we'll compute for    *
     *  complex powers. First compute log(z).                                 */
    ln_z = tmpl_CLDouble_Log(z);

    /*  Next use tmpl_CLDouble_Multiply_Real to compute the product with x.   */
    x_ln_z = tmpl_CLDouble_Multiply_Real(x, ln_z);

    /*  And finally exponentiate.                                             */
    z_to_the_x = tmpl_CLDouble_Exp(x_ln_z);
    return z_to_the_x;
}
/*  End of tmpl_CLDouble_Pow_Real.                                            */

