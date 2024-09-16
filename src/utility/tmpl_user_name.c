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
 *                               tmpl_user_name                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Gets the current user name as a string.                               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_User_Name                                                        *
 *  Purpose:                                                                  *
 *      Returns the current user name as a string.                            *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      username (const char *):                                              *
 *          A pointer to a char array, the string for the user name.          *
 *  Called Functions:                                                         *
 *      stdlib.h:                                                             *
 *          getenv:                                                           *
 *              Retrieves an environment variable.                            *
 *  Method:                                                                   *
 *      Use getenv on the "USER" environment variable, returning "Unknown"    *
 *      if this fails.                                                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library header providing getenv.                         *
 *  2.) tmpl_utility.h:                                                       *
 *          Header file where the function prototype is provided.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 11, 2024                                            *
 ******************************************************************************/

/*  getenv provided here.                                                     */
#include <stdlib.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_utility.h>

/*  Windows has the USERNAME environment variable. POSIX / UNIX uses USER.    */
#if defined(_WIN32) || defined(_WIN64)
#define TMPL_USER_VARIABLE "USERNAME"
#else
#define TMPL_USER_VARIABLE "USER"
#endif

/*  TODO:
 *      Consider implementing this in a way that doesn't
 *      use environment variables.
 */

/*  Function for getting the current user name.                               */
const char *tmpl_User_Name(void)
{
    /*  Try getenv on the "USER" / "USERNAME" environment variable. This      *
     *  should work on most systems.                                          */
    const char *username = getenv(TMPL_USER_VARIABLE);

    /*  If it fails, return Unknown.                                          */
    if (!username)
        return "Unknown";

    return username;
}
/*  End of tmpl_User_Name.                                                    */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_USER_VARIABLE
