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
 *      Contains the source code for the complex power function.              *
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
 *  2020/11/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/11/14 (Ryan Maguire):                                                *
 *      Frozen for v1.3 of rss_ringoccs.                                      *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Compute the complex power z0^z1.                                          */
tmpl_ComplexFloat
tmpl_CFloat_Pow(tmpl_ComplexFloat z0, tmpl_ComplexFloat z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat z0_to_the_z1, ln_z0, z1_ln_z0;

    /*  We can write x^y as exp(y ln(x)) and this is how we'll compute for    *
     *  complex powers. First compute log(z1).                                */
    ln_z0 = tmpl_CFloat_Log(z0);

    /*  Next use tmpl_Complex_Multiply to compute the product with z0.        */
    z1_ln_z0 = tmpl_CFloat_Multiply(z1, ln_z0);

    /*  And finally exponentiate.                                             */
    z0_to_the_z1 = tmpl_CFloat_Exp(z1_ln_z0);
    return z0_to_the_z1;
}
/*  End of tmpl_CDouble_Pow.                                                  */

/*  Compute the complex power z0^z1.                                          */
tmpl_ComplexDouble
tmpl_CDouble_Pow(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble z0_to_the_z1, ln_z0, z1_ln_z0;

    /*  We can write x^y as exp(y ln(x)) and this is how we'll compute for    *
     *  complex powers. First compute log(z1).                                */
    ln_z0 = tmpl_CDouble_Log(z0);

    /*  Next use tmpl_Complex_Multiply to compute the product with z0.        */
    z1_ln_z0 = tmpl_CDouble_Multiply(z1, ln_z0);

    /*  And finally exponentiate.                                             */
    z0_to_the_z1 = tmpl_CDouble_Exp(z1_ln_z0);
    return z0_to_the_z1;
}
/*  End of tmpl_CDouble_Pow.                                                  */

/*  Compute the complex power z0^z1.                                          */
tmpl_ComplexLongDouble
tmpl_CLDouble_Pow(tmpl_ComplexLongDouble z0, tmpl_ComplexLongDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble z0_to_the_z1, ln_z0, z1_ln_z0;

    /*  We can write x^y as exp(y ln(x)) and this is how we'll compute for    *
     *  complex powers. First compute log(z1).                                */
    ln_z0 = tmpl_CLDouble_Log(z0);

    /*  Next use tmpl_Complex_Multiply to compute the product with z0.        */
    z1_ln_z0 = tmpl_CLDouble_Multiply(z1, ln_z0);

    /*  And finally exponentiate.                                             */
    z0_to_the_z1 = tmpl_CLDouble_Exp(z1_ln_z0);
    return z0_to_the_z1;
}
/*  End of tmpl_CLDouble_Pow.                                                 */

