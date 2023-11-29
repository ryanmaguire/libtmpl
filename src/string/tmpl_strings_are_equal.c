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
 *                           tmpl_strings_are_equal                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Checks if two strings are equal up to their null terminators.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Strings_Are_Equal                                                *
 *  Purpose:                                                                  *
 *      Compares equality for two strings character-by-character.             *
 *  Arguments:                                                                *
 *      str0 (const char *):                                                  *
 *          A string.                                                         *
 *      str1 (const char *):                                                  *
 *          Another string.                                                   *
 *  Output:                                                                   *
 *      are_equal (tmpl_Bool):                                                *
 *          Boolean for if the two strings are equal.                         *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Examine each character of the two strings and check if they are the   *
 *      same. Also check for the position of the first null terminator in the *
 *      strings. If all of these agree, return true. If both pointers are     *
 *      NULL, this function also returns true. Return false otherwise.        *
 *  Notes:                                                                    *
 *      If the input pointers are not NULL, it is assumed that the strings    *
 *      end with their null terminators.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  2.) tmpl_string.h:                                                        *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 29, 2023                                             *
 ******************************************************************************/

/*  Booleans provided here.                                                   */
#include <libtmpl/include/tmpl_bool.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_string.h>

/*  Function for checking if two strings are equal.                           */
tmpl_Bool tmpl_Strings_Are_Equal(const char *str0, const char *str1)
{
    /*  First, check for NULL pointers before trying to access.               */
    if (!str0)
    {
        /*  If both pointers are NULL, we'll treat this as equal strings.     */
        if (!str1)
            return tmpl_True;

        /*  Otherwise we have a NULL pointer and a non-NULL pointer.          */
        return tmpl_False;
    }

    /*  We've checked that str0 is not NULL. If str1 is NULL, the strings are *
     *  different. Check for this before accessing str1.                      */
    if (!str1)
        return tmpl_False;

    /*  Loop through all of the elements of the string until we hit the       *
     *  null terminator.                                                      */
    while (*str0)
    {
        /*  If the current characters differ, the strings are not equal. Note *
         *  that is *str0 is not the null terminator, if *str1 is a null      *
         *  terminator this function will exit here. We don't risk accessing  *
         *  data beyond the end of str1's range.                              */
        if ((*str0) != (*str1))
            return tmpl_False;

        /*  Move to the next entries in the strings.                          */
        str0++;
        str1++;
    }

    /*  str0 is now at it's null terminator. If str1 is not at its null       *
     *  terminator that means this string keeps going, so it is not identical *
     *  to str0. Check for this.                                              */
    if (*str1)
        return tmpl_False;

    /*  Otherwise, the first null terminators for str0 and str1 occur at the  *
     *  same place and all characters up to this are the same. Return True.   */
    return tmpl_True;
}
/*  End of tmpl_Strings_Are_Equal.                                            */
