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
 *      1.) If the input string is NULL, nothing is done.                     *
 *      2.) If the input is not NULL, then it is assumed that the string ends *
 *          with its null terminator.                                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   April 8, 2021                                                     *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/08/08: Ryan Maguire                                                  *
 *      Added comments, simplified code.                                      *
 ******************************************************************************/

/*  Forward declaration / function prototype, found in tmpl_string.h as well. */
extern void tmpl_String_Remove_Whitespace(char * str);

/*  Function for removing all whitespace from a string.                       */
void tmpl_String_Remove_Whitespace(char *str)
{
    /*  We use two pointers. One is used for writing (str), so that every     *
     *  character behind it is a non-whitespace, and the other (ptr) is used  *
     *  for scanning ahead through any whitespace characters. Both pointers   *
     *  start at the same location.                                           */
    const char *ptr = str;

    /*  If the input is NULL, the following would cause a segfault. Check.    */
    if (!str)
        return;

    do {
        /*  Keep incremementing the pointer until we find a non-space.        */
        while (*ptr == ' ')
            ++ptr;

        /*  Set the value of the string to the non-space character in ptr.    */
        *str = *ptr;

        /*  Increment both pointers and start all over again.                 */
        ++str;
        ++ptr;

    } while (*str);
}
/*  End of tmpl_String_Remove_Whitespace.                                     */
