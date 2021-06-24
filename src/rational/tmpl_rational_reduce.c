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
 *                            tmpl_rational_reduce                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for reducing a rational number so that the numerator and         *
 *      denominator are coprime.                                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RationalNumber_Reduce                                            *
 *  Purpose:                                                                  *
 *      Reduces a rational number to coprime values.                          *
 *  Arguments:                                                                *
 *      p (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *  Output:                                                                   *
 *      q (tmpl_RationalNumber):                                              *
 *          The number p in reduced form.                                     *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Find the GCD of the numerator and denominator and divide by this.     *
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

/*  Function for reducing a rational number.                                  */
tmpl_RationalNumber
tmpl_RationalNumber_Reduce(tmpl_RationalNumber p)
{
    /*  Declare variables for the reduction.                                  */
    signed long int reduced_numer, reduced_denom;

    /*  And a variable for the GCD, and absolute values of the numerator      *
     *  and denominator of the input rational number.                         */
    signed long int GCD, abs_numer, abs_denom;

    /*  If the denominator is zero, return.                                   */
    if (p.denominator == 0L)
        return p;

    /*  If the numerator is zero, reduce to (0, 1).                           */
    else if (p.numerator == 0L)
        return tmpl_RationalNumber_Create(0L, 1L);

    /*  If not, get the absolute values of the numerator and denominator.     */
    if (p.numerator >= 0L)
        abs_numer = p.numerator;
    else
        abs_numer = -p.numerator;

    if (p.denominator >= 0L)
        abs_denom = p.denominator;
    else
        abs_denom = -p.denominator;

    /*  Get the GCD.                                                          */
    while(abs_numer != abs_denom)
    {
        if(abs_numer > abs_denom)
            abs_numer -= abs_denom;
        else
            abs_denom -= abs_numer;
    }

    GCD = abs_numer;

    /*  Compute the reduction of p.                                           */
    reduced_numer = p.numerator / GCD;
    reduced_denom = p.denominator / GCD;

    /*  Have the numerator be signed, and the denominator unsigned.           */
    if (p.denominator >= 0L)
        return tmpl_RationalNumber_Create(reduced_numer, reduced_denom);
    else
        return tmpl_RationalNumber_Create(-reduced_numer, -reduced_denom);
}
/*  End of tmpl_RationalNumber_Reduce.                                        */
