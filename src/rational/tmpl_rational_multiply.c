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
 *                          tmpl_rational_multiply                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for multiplying rational numbers.                                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RationalNumber_Multiply                                          *
 *  Purpose:                                                                  *
 *      Multiplies two rational numbers.                                      *
 *  Arguments:                                                                *
 *      p (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *      q (tmpl_RationalNumber):                                              *
 *          Another rational number.                                          *
 *  Output:                                                                   *
 *      prod (tmpl_RationalNumber):                                           *
 *          The product of p and q.                                           *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Multiply numerators and denominators.                                 *
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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 24, 2021                                                 *
 ******************************************************************************/

/*  Rational numbers and function prototype found here.                       */
#include <libtmpl/include/tmpl_rational.h>

/*  Function for multiplying rational numbers.                                */
tmpl_RationalNumber
tmpl_RationalNumber_Multiply(const tmpl_RationalNumber *p,
                             const tmpl_RationalNumber *q)
{
    /*  Declare necessary variables.                                          */
    tmpl_RationalNumber prod;

    /*  Multiply numerator with numerator, and denominator with denominator.  */
    prod.numerator = p->numerator * q->numerator;
    prod.denominator = p->denominator * q->denominator;
    return prod;
}
/*  End of tmpl_RationalNumber_Multiply.                                      */
