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
 *                           tmpl_operating_system                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Gets the OS libtmpl was compiled on.                                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Operating_System                                                 *
 *  Purpose:                                                                  *
 *      Returns the OS libtmpl was compiled on.                               *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      os (const char *):                                                    *
 *          A pointer to a char array, the string for the OS.                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Look for commonly defined macros to find OS info.                     *
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

/*  Function for getting OS libtmpl was compiled on.                          */
const char *tmpl_Operating_System(void)
{
#if defined(_WIN32) || defined(_WIN64)
    return "Windows";
#elif defined(__CYGWIN__)
    return "Cygwin";
#elif defined(__APPLE__) || defined(__MACH__)
    return "macOS";
#elif defined(__linux__)
    return "Linux";
#elif defined(__FreeBSD__)
    return "FreeBSD";
#elif defined(__sun)
    return "Solaris";
#else
    return "Unknown";
#endif
}
/*  End of tmpl_Operating_System.                                             */
