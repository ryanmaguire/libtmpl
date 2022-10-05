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
 *                    tmpl_two_by_two_matrix_component                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Returns the (m, n) component of a 2x2 matrix.                         *
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
 *  Date:       March 03, 2021                                                *
 ******************************************************************************/

/*  TMPL_NAN is here.                                                         */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Returns the (m, n) component of a 2x2 matrix.                             */
float
tmpl_FloatTwoByTwoMatrix_Component(tmpl_FloatTwoByTwoMatrix A,
                                   unsigned int m, unsigned int n)
{
    /*  Check for invalid indices.                                            */
    if ((m > 1U) || (n > 1U))
        return TMPL_NANF;
    else
        return A.dat[m][n];
}
/*  End of tmpl_FloatTwoByTwoMatrix_Component.                                */

/*  Returns the (m, n) component of a 2x2 matrix.                             */
double
tmpl_DoubleTwoByTwoMatrix_Component(tmpl_DoubleTwoByTwoMatrix A,
                                    unsigned int m, unsigned int n)
{
    /*  Check for invalid indices.                                            */
    if ((m > 1U) || (n > 1U))
        return TMPL_NAN;
    else
        return A.dat[m][n];
}
/*  End of tmpl_DoubleTwoByTwoMatrix_Component.                               */

/*  Returns the (m, n) component of a 2x2 matrix.                             */
long double
tmpl_LDoubleTwoByTwoMatrix_Component(tmpl_LDoubleTwoByTwoMatrix A,
                                     unsigned int m, unsigned int n)
{
    /*  Check for invalid indices.                                            */
    if ((m > 1U) || (n > 1U))
        return TMPL_NANL;
    else
        return A.dat[m][n];
}
/*  End of tmpl_LDoubleTwoByTwoMatrix_Component.                              */
