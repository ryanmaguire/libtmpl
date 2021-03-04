/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of rss_ringoccs.                                        *
 *                                                                            *
 *  rss_ringoccs is free software: you can redistribute it and/or modify it   *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  rss_ringoccs is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with rss_ringoccs.  If not, see <https://www.gnu.org/licenses/>.    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Returns the x component of a two dimensional vector/planar point.     *
 *      That is, given (x, y), return x.                                      *
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
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/12/21: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 ******************************************************************************/

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_euclidean_planar_geometry.h>

/*  Function for returning the x component of a two dimensional vector.       */
double tmpl_TwoVector_X(tmpl_TwoVector P)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double x;

    /*  rssringoccs_TwoVector is defined the same way                         *
     *  rssringoccs_ComplexDouble is. It is a struct containing a single      *
     *  double array dat consisting of two entries. The zeroth entry          *
     *  corresponds to the x component. Retrieve this and return.             */
    x = P.dat[0];
    return x;
}
/*  End of rssringoccs_TwoVector_X.                                           */
