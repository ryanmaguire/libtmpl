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
 *                          rss_ringoccs_copysign                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the copysign function defined in C99.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Abs:                                                *
 *      tmpl_Double_Abs:                                               *
 *      tmpl_LDouble_Abs:                                              *
 *  Purpose:                                                                  *
 *      Computes the product of sgn(y) with |x|.                              *
 *          copysign(x, y) = sgn(y) * |x|                                     *
 *  Arguments:                                                                *
 *      x (float/double/long double):                                         *
 *          A real number.                                                    *
 *      y (float/double/long double):                                         *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      copysign_x (float/double/long double):                                *
 *          The value sgn(y) * |x|.                                           *
 *  Method:                                                                   *
 *      Check the sign of y with an if-then statement and compute |x|, -|x|,  *
 *      or zero accordingly.                                                  *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) rss_ringoccs_math.h:                                                  *
 *          This file provides compatibility between the two standard math.h  *
 *          header files (C89 vs C99 math.h). If C99 math.h exists, it simply *
 *          provides aliases for the functions, and if C89 math.h is used     *
 *          it defines the functions missing in the earlier version.          *
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
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       December 8, 2020                                              *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/12/10 (Ryan Maguire):                                                *
 *      Frozen for v1.3.                                                      *
 ******************************************************************************/

/*  Header file where the prototypes for these functions are defined.         */
#include <libtmpl/include/tmpl_math.h>

/*  Copysign is not required in C89, so we provide the algorithm for          *
 *  double, float, and long double inputs.                                    */

/*  Float precision copysign function.                                        */
float tmpl_Float_Copysign(float x, float y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float out;

    /*  If y is negative, compute -|x|.                                       */
    if (y < 0.0F)
        out = -tmpl_Float_Abs(x);

    /*  If y is positive, compute |x|.                                        */
    else if (0.0F < y)
        out = tmpl_Float_Abs(x);

    /*  And lastly, if y is zero, return zero.                                */
    else
        out = 0.0F;

    return out;
}
/*  End of tmpl_Float_Copysign.                                               */

/*  Long double precision copysign function.                                  */
long double tmpl_LDouble_Copysign(long double x, long double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double out;

    /*  If y is negative, compute -|x|.                                       */
    if (y < 0.0L)
        out = -tmpl_LDouble_Abs(x);

    /*  If y is positive, compute |x|.                                        */
    else if (0.0L < y)
        out = tmpl_LDouble_Abs(x);

    /*  And lastly, if y is zero, return zero.                                */
    else
        out = 0.0L;

    return out;
}
/*  End of tmpl_LDouble_Copysign.                                      */
