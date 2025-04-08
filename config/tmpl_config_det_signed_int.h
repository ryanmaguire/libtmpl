/******************************************************************************
 *                                  LICENSE                                   *
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
 *                         tmpl_config_det_signed_int                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines the representation of a signed integer.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_det_signed_int                                                   *
 *  Purpose:                                                                  *
 *      Determines if signed integers are represented by sign and magnitude,  *
 *      one's complement, or two's complement.                                *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      int_type (enum tmpl_signed_integer_rep):                              *
 *          enum indicating how signed integers are represented.              *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Using bitwise and, -1 & 3 uniquely distinguishes between sign and     *
 *      magnitude, one's complement, and two's complement. Check this.        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/04/06: Ryan Maguire                                                  *
 *      Moved function to its own file.                                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_DET_SIGNED_INT_H
#define TMPL_CONFIG_DET_SIGNED_INT_H

/*  There are three (common) representations for signed integers. In the      *
 *  modern world, most computers use two's complement. The C23 standard       *
 *  requires two's complement to be implemented for signed integers.          */
enum tmpl_signed_integer_rep {
    tmpl_ones_complement,
    tmpl_twos_complement,
    tmpl_sign_and_magnitude,
    tmpl_unknown_signed_rep
};

/*  Function for detecting what type of signed integer representation is used.*/
static enum tmpl_signed_integer_rep tmpl_det_signed_int(void)
{
    /*  We need to check the lower bits of the constant negative 1. This will *
     *  uniquely determine which of the three representations we have.        */
    const signed int n = -1;
    const signed int n_and_3 = n & 3;

    /*  Sign and magnitude would have:                                        *
     *                                                                        *
     *      -1 = 100...001                                                    *
     *       3 = 000...011                                                    *
     *                                                                        *
     *  Taking the bitwise and will produce 1. Check for this.                */
    if (n_and_3 == 1)
        return tmpl_sign_and_magnitude;

    /*  One's complement has:                                                 *
     *                                                                        *
     *      -1 = 111...110                                                    *
     *       3 = 000...011                                                    *
     *                                                                        *
     *  Taking the bitwise and will produce 2. Check.                         */
    if (n_and_3 == 2)
        return tmpl_ones_complement;

    /*  Two's complement, by far the most common (and required in C23), has:  *
     *                                                                        *
     *      -1 = 111...111                                                    *
     *       3 = 000...011                                                    *
     *                                                                        *
     *  Bitwise and thus produces 3. Check for this.                          */
    if (n_and_3 == 3)
        return tmpl_twos_complement;

    /*  Any other output uses an unknown (to libtmpl) representation.         */
    return tmpl_unknown_signed_rep;
}
/*  End of tmpl_det_signed_int.                                               */

#endif
/*  End of include guard.                                                     */
