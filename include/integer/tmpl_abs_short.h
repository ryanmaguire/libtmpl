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
 *                               tmpl_abs_short                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(n) = |n|, the absolute value of n.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Short_Abs                                                        *
 *  Purpose:                                                                  *
 *      Computes the absolute value of an integer.                            *
 *                   --                                                       *
 *                  |   n,  x >= 0                                            *
 *          |n|  =  |  -n,  else                                              *
 *                   --                                                       *
 *  Arguments:                                                                *
 *      n (signed short int):                                                 *
 *          An integer.                                                       *
 *  Output:                                                                   *
 *      abs_n (signed short int):                                             *
 *          The absolute value of n.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a simple if-then statement. Bit tricks using 2's complement,      *
 *      1's complement, or sign-and-magnitude do not make the computation any *
 *      faster and can be avoided.                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 19, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/05/17: Ryan Maguire                                                  *
 *      Moved all versions to their own files.                                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ABS_SHORT_H
#define TMPL_ABS_SHORT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Computes the absolute value of a signed short int.                        */
TMPL_INLINE_DECL
signed short int tmpl_Short_Abs(signed short int n)
{
    /*  For negative inputs we just negate and return.                        */
    if (n < 0)
        return -n;

    /*  Otherwise, nothing to do. Return the input.                           */
    return n;
}
/*  End of tmpl_Short_Abs.                                                    */

#endif
/*  End of include guard.                                                     */
