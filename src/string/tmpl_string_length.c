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
 *                             tmpl_string_length                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the strlen function.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_String_Length                                                    *
 *  Purpose:                                                                  *
 *      Counts the number of characters in a string. Equivalent to strlen.    *
 *  Arguments:                                                                *
 *      str (const char *):                                                   *
 *          The string whose size is to be determined.                        *
 *  Output:                                                                   *
 *      string_length (size_t):                                               *
 *          The length of the string str.                                     *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through the string until we find the NULL terminator.            *
 *  Notes:                                                                    *
 *      If the input string is NULL, the value zero is returned.              *
 *                                                                            *
 *      This is the K&R algorithm. glibc offers a routine that reads 4 or 8   *
 *      bytes at a time, giving quite a speed boost. It should be noted that  *
 *      for very large strings, say 10^8 characters, this function takes a    *
 *      fraction of a second on modern computers. So the speed boost may not  *
 *      be all that important for most applications.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard library header file where size_t is defined.             *
 *  2.) tmpl_string.h:                                                        *
 *          Header where tmpl_String_Length is declared.                      *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   August 7, 2023                                                    *
 ******************************************************************************/

/*  size_t data type is found here.                                           */
#include <stddef.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_string.h>

/*  Counts the number of characters in a string.                              */
size_t tmpl_String_Length(const char *str)
{
    /*  Initialize the count to zero.                                         */
    size_t string_length = (size_t)0;

    /*  Avoid dereferencing a NULL pointer. Return zero in this case.         */
    if (!str)
        return string_length;

    /*  Loop through the characters in str and find the null terminator.      */
    while (str[string_length])
        string_length++;

    return string_length;
}
/*  End of tmpl_String_Length.                                                */
