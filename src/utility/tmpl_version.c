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
 ******************************************************************************
 *                                tmpl_version                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Gets the current version as a string.                                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Version                                                          *
 *  Purpose:                                                                  *
 *      Returns the current version as a string.                              *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      version (const char *):                                               *
 *          A pointer to a char array, the string for the tmpl version.       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Return a constant char array with the version number.                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_utility.h:                                                       *
 *          Header file where the function prototype is provided.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 11, 2024                                            *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_utility.h>

/*  Function for getting the current libtmpl version.                         */
const char *tmpl_Version(void)
{
    return "0.1";
}
/*  End of tmpl_Version.                                                      */
