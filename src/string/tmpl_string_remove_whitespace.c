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
 *                       tmpl_string_remove_whitespace                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Function for removing whitespace from a string.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_String_Remove_Whitespace                                         *
 *  Purpose:                                                                  *
 *      Removes all spaces from a string.                                     *
 *  Arguments:                                                                *
 *      str (char *):                                                         *
 *          A string.                                                         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through the string and remove all whitespace characters.         *
 *  Notes:                                                                    *
 *      If the input string is NULL, nothing is done.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_string.h:                                                        *
 *          Header where tmpl_String_Remove_Whitespace is declared.           *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   April 8, 2021                                                     *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/08/08: Ryan Maguire                                                  *
 *      Added comments, simplified code.                                      *
 ******************************************************************************/

/*  Function prototype is given here.                                         */
#include <libtmpl/include/tmpl_string.h>

/*  Function for removing all whitespace from a string.                       */
void tmpl_String_Remove_Whitespace(char *str)
{
    const char *ptr = str;

    /*  If the input is NULL, the following will cause a segfault. Check.     */
    if (!str)
        return;

    do {
        /*  Keep incremementing the pointer until we find a non-space.        */
        while (*ptr == ' ')
            ptr++;

        /*  Set the value of the string to the non-space character in ptr.    */
        *str = *ptr;

        /*  Increment both pointers and start all over again.                 */
        str++;
        ptr++;
    } while (*str);
}
/*  End of tmpl_String_Remove_Whitespace.                                     */
