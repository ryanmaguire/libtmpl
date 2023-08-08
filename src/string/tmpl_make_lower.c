/******************************************************************************
 *                                  LICENSE                                   *
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
 *                          tmpl_destroy_svg_canvas                           *
 ******************************************************************************
 *                              tmpl_make_lower                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Convert a string to all lower case.                                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Make_Lower                                                       *
 *  Purpose:                                                                  *
 *      Convert a string to it's lower-case equivalent.                       *
 *  Arguments:                                                                *
 *      str (char *):                                                         *
 *          A string.                                                         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      tmpl_string.h:                                                        *
 *          tmpl_Lower_Case:                                                  *
 *              Converts a single character char c to lower case.             *
 *  Method:                                                                   *
 *      Loop over the characters of the string and call tmpl_Lower_Case.      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_string.h:                                                        *
 *          Header file where the function prototype is defined.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 19 2021                                                  *
 ******************************************************************************/

/*  Function prototype here.                                                  */
#include <libtmpl/include/tmpl_string.h>

/*  Function for converting a string to it's lower-case equivalent.           */
void tmpl_Make_Lower(char *str)
{
    /*  Trying to access a NULL pointer could cause a segfault. Check this.   */
    if (!str)
        return;

    /*  Loop over the elements of the string and convert them to lower case.  */
    while (*str)
    {
        *str = tmpl_Lower_Case(*str);
        ++str;
    }
}
/*  End of tmpl_Make_Lower.                                                   */
