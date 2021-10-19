/******************************************************************************
 *                                 LICENSE                                    *
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
 *                             tmpl_complex_abs                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex modulus (absolute value).        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Abs:                                                      *
 *      tmpl_CDouble_Abs:                                                     *
 *      tmpl_CLDouble_Abs:                                                    *
 *  Purpose:                                                                  *
 *      Computes the absolute value, or modulus, of a complex number:         *
 *                                                                            *
 *          |z| = |x + iy| = sqrt(x^2 + y^2)                                  *
 *                                                                            *
 *      Because x^2 and y^2 are computed as intermediate steps, this method   *
 *      will overflow for values greater than sqrt(DBL_MAX). The safe way to  *
 *      do this is via:                                                       *
 *                                                                            *
 *          |z| = |x| sqrt(1+(y/x)^2)                                         *
 *                                                                            *
 *      if |x| > |y|, and:                                                    *
 *                                                                            *
 *          |z| = |y| sqrt(1 + (x/y)^2)                                       *
 *                                                                            *
 *      otherwise. This is about 1.3-1.5x slower. The faster, naive method    *
 *      is implemented in tmpl_CDouble_QuickAbs, but may overflow for large   *
 *      values. This method avoids overflows at intermediate steps.           *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):                *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      abs_z (float/double/long double):                                     *
 *          The absolute value of z.                                          *
 *  Called Functions:                                                         *
 *      tmpl_Float_Abs          (tmpl_math.h)                                 *
 *      tmpl_Double_Abs         (tmpl_math.h)                                 *
 *      tmpl_LDouble_Abs        (tmpl_math.h)                                 *
 *          Computes the absolute value of a real number.                     *
 *      tmpl_Float_Sqrt         (tmpl_math.h)                                 *
 *      tmpl_Double_Sqrt        (tmpl_math.h)                                 *
 *      tmpl_LDouble_Sqrt       (tmpl_math.h)                                 *
 *          Computes the square root of a float/double/long double.           *
 *      tmpl_CFloat_Real_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Real_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Real_Part (tmpl_complex.h)                              *
 *          Returns the real part of a complex number.                        *
 *      tmpl_CFloat_Imag_Part   (tmpl_complex.h)                              *
 *      tmpl_CDouble_Imag_Part  (tmpl_complex.h)                              *
 *      tmpl_CLDouble_Imag_Part (tmpl_complex.h)                              *
 *          Returns the imaginary part of a complex number.                   *
 *  Method:                                                                   *
 *      Extract the real and imaginary parts of z, label as z = x + iy.       *
 *      determine a = min(|x|, |y|) and b = max(|x|, |y|), returning the      *
 *      value b*sqrt(1 + (a/b)^2).                                            *
 *  Notes:                                                                    *
 *      This code is a fork of the code I wrote for rss_ringoccs.             *
 *      librssringoccs is also released under GPL3.                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing basic math functions.                      *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
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
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley college for librssringoccs).                  *
 *  2020/12/01: Ryan Maguire                                                  *
 *      Added abs squared functions.                                          *
 *  2020/12/02: Ryan Maguire                                                  *
 *      Moved abs squared functions to their own file.                        *
 *      Frozen for rss_ringoccs v1.3.                                         *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from librssringoccs to libtmpl.                                *
 *      Edited code, made it compatibile with the rest of libtmpl. Removed    *
 *      "C99" mode. Removed complex.h as a dependency.                        *
 *      Soft freeze for alpha version of libtmpl.                             *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited license.                                                       *
 *  2021/05/11: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code and comments. *
 *      No more changes unless something breaks.                              *
 *  2021/10/19: Ryan Maguire                                                  *
 *      Changed the algorithm to prevent certain numbers from overflowing.    *
 *      Complex numbers with a magnitude greater than sqrt(DBL_MAX) will      *
 *      overflow, even though they shouldn't for a proper implementation.     *
 *      This has been fixed, albeit at the expense of speed.                  *
 ******************************************************************************/

/*  Header file containing basic math functions.                              */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are given and where complex types are defined.       */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision complex abs function (cabsf equivalent).                 */
float tmpl_CFloat_Abs(tmpl_ComplexFloat z)
{
    /*  Extract the absolute values of the real and imaginary parts from the  *
     *  input complex number.                                                 */
    const float abs_real = tmpl_Float_Abs(tmpl_CFloat_Real_Part(z));
    const float abs_imag = tmpl_Float_Abs(tmpl_CFloat_Imag_Part(z));
    float s, t;

    /*  Special case, to avoid division by zero.                              */
    if (abs_real == 0.0F)
        return abs_imag;
    else if (abs_imag == 0.0F)
        return abs_real;

    /*  Compute the max of |real| and |imag|.                                 */
    if (abs_real < abs_imag)
    {
        t = abs_imag;
        s = abs_real / abs_imag;
    }
    else
    {
        t = abs_real;
        s = abs_imag / abs_real;
    }

    /*  The absolute value is new t * sqrt(1 + s^2). Compute this.            */
    return t*tmpl_Float_Sqrt(1.0F + s*s);
}
/*  End of tmpl_CFloat_Abs.                                                   */

/*  Double precision complex abs function (cabs equivalent).                  */
double tmpl_CDouble_Abs(tmpl_ComplexDouble z)
{
    /*  Extract the absolute values of the real and imaginary parts from the  *
     *  input complex number.                                                 */
    const double abs_real = tmpl_Double_Abs(tmpl_CDouble_Real_Part(z));
    const double abs_imag = tmpl_Double_Abs(tmpl_CDouble_Imag_Part(z));
    double s, t;

    /*  Special case, to avoid division by zero.                              */
    if (abs_real == 0.0)
        return abs_imag;
    else if (abs_imag == 0.0)
        return abs_real;

    /*  Compute the max of |real| and |imag|.                                 */
    if (abs_real < abs_imag)
    {
        t = abs_imag;
        s = abs_real / abs_imag;
    }
    else
    {
        t = abs_real;
        s = abs_imag / abs_real;
    }

    /*  The absolute value is new t * sqrt(1 + s^2). Compute this.            */
    return t*tmpl_Double_Sqrt(1.0 + s*s);
}
/*  End of tmpl_CDouble_Abs.                                                  */

/*  Long double precision complex abs function (cabsl equivalent).            */
long double tmpl_CLDouble_Abs(tmpl_ComplexLongDouble z)
{
    /*  Extract the absolute values of the real and imaginary parts from the  *
     *  input complex number.                                                 */
    const long double abs_real = tmpl_LDouble_Abs(tmpl_CLDouble_Real_Part(z));
    const long double abs_imag = tmpl_LDouble_Abs(tmpl_CLDouble_Imag_Part(z));
    long double s, t;

    /*  Special case, to avoid division by zero.                              */
    if (abs_real == 0.0L)
        return abs_imag;
    else if (abs_imag == 0.0L)
        return abs_real;

    /*  Compute the max of |real| and |imag|.                                 */
    if (abs_real < abs_imag)
    {
        t = abs_imag;
        s = abs_real / abs_imag;
    }
    else
    {
        t = abs_real;
        s = abs_imag / abs_real;
    }

    /*  The absolute value is new t * sqrt(1 + s^2). Compute this.            */
    return t*tmpl_LDouble_Sqrt(1.0L + s*s);
}
/*  End of tmpl_CLDouble_Abs.                                                 */
