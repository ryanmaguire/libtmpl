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
 *                          tmpl_complex_reciprocal                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex addition.                        *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       November 30, 2020                                             *
 ******************************************************************************/

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z1  *
 *  and double _Complex z2, you can just do z1 * z2. Structs cannot be        *
 *  multiplied so we need a function for computing this.                      */

/*  Function for computing the reciprocal (or inverse) of a complex number.   */
tmpl_ComplexFloat tmpl_CFloat_Reciprocal(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexFloat conj_z, rcpr_z;
    float rcp_abs_z_sq;

    /*  Compute the conjugate of z and its absolute value.                    */
    conj_z = tmpl_CFloat_Conjugate(z);
    rcp_abs_z_sq = tmpl_CFloat_Abs_Squared(z);

    /*  The inverse of z is conj_z / abs_z^2, so return this.                 */
    rcpr_z = tmpl_CFloat_Multiply_Real(rcp_abs_z_sq, conj_z);
    return rcpr_z;
}
/*  End of tmpl_CFloat_Reciprocal.                                            */

/*  Function for computing the reciprocal (or inverse) of a complex number.   */
tmpl_ComplexDouble tmpl_CDouble_Reciprocal(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble conj_z, rcpr_z;
    double rcp_abs_z_sq;

    /*  Compute the conjugate of z and its absolute value.                    */
    conj_z = tmpl_CDouble_Conjugate(z);
    rcp_abs_z_sq = tmpl_CDouble_Abs_Squared(z);

    /*  The inverse of z is conj_z / abs_z^2, so return this.                 */
    rcpr_z = tmpl_CDouble_Multiply_Real(rcp_abs_z_sq, conj_z);
    return rcpr_z;
}
/*  End of tmpl_CDouble_Reciprocal.                                           */

/*  Function for computing the reciprocal (or inverse) of a complex number.   */
tmpl_ComplexLongDouble tmpl_CLDouble_Reciprocal(tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble conj_z, rcpr_z;
    long double rcp_abs_z_sq;

    /*  Compute the conjugate of z and its absolute value.                    */
    conj_z = tmpl_CLDouble_Conjugate(z);
    rcp_abs_z_sq = tmpl_CLDouble_Abs_Squared(z);

    /*  The inverse of z is conj_z / abs_z^2, so return this.                 */
    rcpr_z = tmpl_CLDouble_Multiply_Real(rcp_abs_z_sq, conj_z);
    return rcpr_z;
}
/*  End of tmpl_CLDouble_Reciprocal.                                          */
