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
 *                           tmpl_rational_subtract                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for subtracting rational numbers.                                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RationalNumber_Subtract                                          *
 *  Purpose:                                                                  *
 *      Subtracts two rational numbers.                                       *
 *  Arguments:                                                                *
 *      p (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *      q (tmpl_RationalNumber):                                              *
 *          Another rational number.                                          *
 *  Output:                                                                   *
 *      diff (tmpl_RationalNumber):                                           *
 *          The difference of p and q.                                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the "cross-multiply" rule to subtract the two numbers.            *
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

/*  Rational numbers and function prototype found here.                       */
#include <libtmpl/include/tmpl_rational.h>

/*  Function for subtracting two rational numbers.                            */
tmpl_RationalNumber
tmpl_RationalNumber_Subtract(tmpl_RationalNumber p, tmpl_RationalNumber q)
{
    /*  Declare a variable for the difference.                                */
    tmpl_RationalNumber diff;

    /*  We add a/b - c/d via the following:                                   *
     *      a     c     ad     cb     ad - cb                                 *
     *      -  -  -  =  --  -  --  =  -------                                 *
     *      b     d     bd     bd       bd                                    *
     *  This is the so-called "cross-multiply" rule.                          */
    diff.numerator = p.denominator * q.numerator - p.numerator * q.denominator;
    diff.denominator = p.denominator * q.denominator;
    return diff;
}
/*  End of tmpl_RationalNumber_Subtract.                                      */
