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
 *                          tmpl_rational_as_real                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Code for converting a rational number to a real one.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_RationalNumber_As_Float                                          *
 *      tmpl_RationalNumber_As_Double                                         *
 *      tmpl_RationalNumber_As_LDouble                                        *
 *  Purpose:                                                                  *
 *      Converts a rational number into a floating-point one.                 *
 *  Arguments:                                                                *
 *      p (tmpl_RationalNumber):                                              *
 *          A rational number.                                                *
 *  Output:                                                                   *
 *      r (float/double/long double):                                         *
 *          The number p as a floating-point.                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Cast to floating point and return the quotient.                       *
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

/*  Function for converting a rational number to a float.                     */
float tmpl_RationalNumber_As_Float(const tmpl_RationalNumber *p)
{
    /*  Convert the numerator and denominator into floats and return          *
     *  the quotient of the two.                                              */
    float numer = (float)p->numerator;
    float denom = (float)p->denominator;
    return numer/denom;
}
/*  End of tmpl_RationalNumber_As_Float.                                      */

/*  Function for converting a rational number to a double.                    */
double tmpl_RationalNumber_As_Double(const tmpl_RationalNumber *p)
{
    /*  Convert the numerator and denominator into doubles and return         *
     *  the quotient of the two.                                              */
    double numer = (double)p->numerator;
    double denom = (double)p->denominator;
    return numer/denom;
}
/*  End of tmpl_RationalNumber_As_Double.                                     */

/*  Function for converting a rational number to a long double.               */
long double tmpl_RationalNumber_As_LDouble(const tmpl_RationalNumber *p)
{
    /*  Convert the numerator and denominator into long doubles and return    *
     *  the quotient of the two.                                              */
    long double numer = (long double)p->numerator;
    long double denom = (long double)p->denominator;
    return numer/denom;
}
/*  End of tmpl_RationalNumber_As_LDouble.                                    */
