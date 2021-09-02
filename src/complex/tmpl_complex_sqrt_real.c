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
 *                         tmpl_complex_sqrt_real                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the square root function for all reals.  *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Sqrt_Real:                                                *
 *      tmpl_CDouble_Sqrt_Real:                                               *
 *      tmpl_CLDouble_Sqrt_Real:                                              *
 *  Purpose:                                                                  *
 *      Computes the complex square root of a real number.                    *
 *  Arguments:                                                                *
 *      x (float/double/long double):                                         *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (tmpl_ComplexFloat/ComplexDouble/ComplexLongDouble):           *
 *          The complex square root of x.                                     *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          This file provides compatibility between the two standard math.h  *
 *          header files (C89 vs C99 math.h). If C99 math.h exists, it simply *
 *          provides aliases for the functions, and if C89 math.h is used     *
 *          it defines the functions missing in the earlier version.          *
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
 *  Date:       September 2, 2021                                             *
 ******************************************************************************/

/*  math functions found here.                                                */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Sincle precision square root of a real number.                            */
tmpl_ComplexFloat tmpl_CFloat_Sqrt_Real(float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float real, imag;

    /*  If x >= 0, return sqrt(x). Otherwise, return i*sqrt(|x|).             */
    if (x >= 0.0F)
    {
        real = tmpl_Float_Sqrt(x);
        imag = 0.0F;
    }
    else
    {
        real = 0.0F;
        imag = tmpl_Float_Sqrt(-x);
    }

    /*  Create the complex number with tmpl_CFloat_Rect and return.           */
    return tmpl_CFloat_Rect(real, imag);
}
/*  End of tmpl_CFloat_Sqrt_Real.                                             */

/*  Double precision square root of a real number.                            */
tmpl_ComplexDouble tmpl_CDouble_Sqrt_Real(double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double real, imag;

    /*  If x >= 0, return sqrt(x). Otherwise, return i*sqrt(|x|).             */
    if (x >= 0.0)
    {
        real = tmpl_Double_Sqrt(x);
        imag = 0.0;
    }
    else
    {
        real = 0.0;
        imag = tmpl_Double_Sqrt(-x);
    }

    /*  Create the complex number with tmpl_CDouble_Rect and return.          */
    return tmpl_CDouble_Rect(real, imag);
}
/*  End of tmpl_CDouble_Sqrt_Real.                                            */

/*  Long double precision square root of a real number.                       */
tmpl_ComplexLongDouble tmpl_CLDouble_Sqrt_Real(long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double real, imag;

    /*  If x >= 0, return sqrt(x). Otherwise, return i*sqrt(|x|).             */
    if (x >= 0.0L)
    {
        real = tmpl_LDouble_Sqrt(x);
        imag = 0.0L;
    }
    else
    {
        real = 0.0L;
        imag = tmpl_LDouble_Sqrt(-x);
    }

    /*  Create the complex number with tmpl_CDouble_Rect and return.          */
    return tmpl_CLDouble_Rect(real, imag);
}
/*  End of tmpl_CLDouble_Sqrt_Real.                                           */
