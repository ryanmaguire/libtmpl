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
 *                          tmpl_two_vector_subtract                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide the main tools for working with vectors, both two and three   *
 *      dimensional. The typedef's are provided in kissvg.h.                  *
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
 *  2020/09/20: Ryan Maguire                                                  *
 *      Created file (KissVG).                                                *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 ******************************************************************************/

#include <libtmpl/include/tmpl_euclidean_planar_geometry.h>

/*  Function for computing vector subtraction.                                */
tmpl_TwoVector tmpl_TwoVector_Subtract(tmpl_TwoVector P, tmpl_TwoVector Q)
{
    tmpl_TwoVector diff;

    /*  Declare two doubles for the new output vector.                        */
    double x_new, y_new;

    /*  Do the same thing as kissvg_TwoVectorAdd, but subtract.               */
    x_new = tmpl_TwoVector_X(P) - tmpl_TwoVector_X(Q);
    y_new = tmpl_TwoVector_Y(P) - tmpl_TwoVector_Y(Q);

    /*  Use kissvg_NewTwoVector to generate the output and return.            */
    diff = tmpl_TwoVector_Rect(x_new, y_new);
    return diff;
}

