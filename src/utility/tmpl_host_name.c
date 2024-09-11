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
 *                               tmpl_host_name                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Gets the local host name as a string.                                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Host_Name                                                        *
 *  Purpose:                                                                  *
 *      Returns the local hostname, or computer name, as a string.            *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      tmpl_global_host_name_string_array (const char *):                    *
 *          A pointer to a char array, the string for the host name.          *
 *  Called Functions:                                                         *
 *      string.h:                                                             *
 *          memset:                                                           *
 *              Sets the values of a buffer to a constant.                    *
 *          strcpy:                                                           *
 *              Copies one char array into another.                           *
 *          strncpy:                                                          *
 *              Similar to strcpy, but copies no more than N characters.      *
 *      Windows.h: (Windows only)                                             *
 *          GetComputerName:                                                  *
 *              Gets the computer name as a string.                           *
 *      unistd.h: (POSIX only, i.e. GNU, Linux, macOS, BSD, etc.)             *
 *          gethostname:                                                      *
 *              Gets the computer name as a string.                           *
 *  Method:                                                                   *
 *      On POSIX (GNU, Linux, FreeBSD, macOS, etc.) or Windows, use the       *
 *      relevant system function. Otherwise, return "Unknown".                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) string.h:                                                             *
 *          Standard library header providing memset and strncpy.             *
 *  2.) tmpl_utility.h:                                                       *
 *          Header file where the function prototype is provided.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 11, 2024                                            *
 ******************************************************************************/

/*  Function prototype provided here.                                         */
#include <libtmpl/include/tmpl_utility.h>

/*  memset, strcpy, and strncpy provided here.                                */
#include <string.h>

/*  There is no true portable method for this. Check the operating system.    */
#if defined(_WIN32) || defined(_WIN64)

/******************************************************************************
 *                                  Windows                                   *
 ******************************************************************************/

/*  Windows specific header files. GetComputerName is provided here.          */
#include <Windows.h>
#include <tchar.h>

/*  Char array for the string. We'll return a pointer to this.                */
static char tmpl_global_host_name_string_array[256];

/*  Function for returning the host name as a string.                         */
const char *tmpl_Host_Name(void)
{
    TCHAR info_buffer[256];
    DWORD bufCharCount = 256;
    const size_t arr_len = sizeof(tmpl_global_host_name_string_array);
    char hostname[256];
    int success;
    size_t n;

    memset(hostname, 0, arr_len);
    success = GetComputerName(info_buffer, &bufCharCount);

    if (success)
        for (n = 0; n < arr_len; ++n)
            hostname[i] = info_buffer[i];

    else
        strcpy(hostname, "Unknown");

    strncpy(tmpl_global_host_name_string_array, hostname, arr_len);
    return tmpl_global_host_name_string_array;
}
/*  End of tmpl_Host_Name.                                                    */

#elif defined(__unix__)
/*  Else for #if defined(_WIN32) || defined(_WIN64).                          */

/*  gethostname provided here.                                                */
#include <unistd.h>

/*  gethostname does not appear in older versions of POSIX. Check for this.   */
#if _XOPEN_SOURCE >= 500 || _POSIX_C_SOURCE >= 200112L || _BSD_SOURCE

/******************************************************************************
 *                               POSIX (Modern)                               *
 ******************************************************************************/

/*  Char array for the string. We'll return a pointer to this.                */
static char tmpl_global_host_name_string_array[256];

/*  Function for returning the host name as a string.                         */
const char *tmpl_Host_Name(void)
{
    /*  Buffer for the host name. It shouldn't be nearly this big.            */
    char hostname[256];

    /*  Initialize the buffer and zero out the elements.                      */
    memset(hostname, 0, 256);

    /*  POSIX specified routine. Gets the host name of the machine.           */
    gethostname(hostname, 256);

    /*  Copy this into our global variable so we can return it.               */
    strncpy(tmpl_global_host_name_string_array, hostname, 256);

    return tmpl_global_host_name_string_array;
}
/*  End of tmpl_Host_Name.                                                    */

#else
/*  #if _XOPEN_SOURCE >= 500 || _POSIX_C_SOURCE >= 200112L || _BSD_SOURCE     */

/******************************************************************************
 *                               POSIX (Legacy)                               *
 ******************************************************************************/

/*  Function for returning the host name as a string.                         */
const char *tmpl_Host_Name(void)
{
    /*  For older versions of POSIX, just return "Unknown".                   */
    return "Unknown";
}
/*  End of tmpl_Host_Name.                                                    */

#endif
/*  End #if _XOPEN_SOURCE >= 500 || _POSIX_C_SOURCE >= 200112L || _BSD_SOURCE */

#else
/*  Else for #if defined(_WIN32) || defined(_WIN64).                          */

/******************************************************************************
 *                                  Unknown                                   *
 ******************************************************************************/

/*  Function for returning the host name as a string.                         */
const char *tmpl_Host_Name(void)
{
    /*  Without knowing which OS we are on, it's hard to get a meaningful     *
     *  answer. Return "unknown" as a fallback.                               */
    return "Unknown";
}
/*  End of tmpl_Host_Name.                                                    */

#endif
/*  End of #if defined(_WIN32) || defined(_WIN64).                            */
