/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                            tmpl_rational_create                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for creating rational numbers.                                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Create_RationalNumber                                            *
 *  Purpose:                                                                  *
 *      Creates a rational number from two requested signed integers, the     *
 *      numerator and the denominator.                                        *
 *  Arguments:                                                                *
 *      numer (signed long int):                                              *
 *          The numerator of the rational number.                             *
 *      denom (signed long int):                                              *
 *          The denominator of the rational number.                           *
 *  Output:                                                                   *
 *      q (tmpl_RationalNumber):                                              *
 *          The number numer/denom.                                           *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Set the numerator and denominator of a rational number to the         *
 *      requested values.                                                     *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_rational.h:                                                      *
 *          Function prototype found here.                                    *
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
 *  Date:       June 24, 2021                                                 *
 ******************************************************************************/

/*  Function prototype declared here.                                         */
#include <libtmpl/include/tmpl_rational.h>

/*  Function for creating rational numbers.                                   */
tmpl_RationalNumber
tmpl_Create_RationalNumber(signed long int numer, signed long int denom)
{
    /*  Declare a rational number, set its attributes, and return.            */
    tmpl_RationalNumber q;
    q.numerator = numer;
    q.denominator = denom;
    return q;
}
/*  End of tmpl_Create_RationalNumber.                                        */
