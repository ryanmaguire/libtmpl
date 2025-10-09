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
 *                            tmpl_string_to_uchar                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Converts a string to an unsigned char.                                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_String_To_UChar                                                  *
 *  Purpose:                                                                  *
 *      Converts a string (like "+123") to a number (123).                    *
 *  Arguments:                                                                *
 *      str (const char *):                                                   *
 *          A string.                                                         *
 *  Output:                                                                   *
 *      val (unsigned char):                                                  *
 *          The numerical value of the string.                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If the input string is NULL or empty, return zero. Next, remove all   *
 *      leading whitespace and zeros. Examine the next character and check if *
 *      it is a "+" or "-", we'll negate the output if it is a minus sign.    *
 *      After that, loop through the characters until the first non-numerical *
 *      char is found, and convert this leading continuous sequence of        *
 *      numerical characters into a number (read in base 10). We do this by   *
 *      performing out = 10 * out + k, where k is the current digit.          *
 *  Notes:                                                                    *
 *      1.) The input is base 10, "123" represents one hundred twenty three.  *
 *      2.) If the input starts with a non-numerical character other than     *
 *          whitespace or the "+" or "-" symbols, then zero is returned.      *
 *      3.) All characters after the first continuous sequence of numerical   *
 *          characters are ignored. "  +123_blah_blah_45" will output 123.    *
 *      4.) The minus sign is allowed as a leading character. Since the       *
 *          output is unsigned, the returned value is 2^N - |out| where N is  *
 *          the number of bits in unsigned char (which is usually 8).         *
 *      5.) It is assumed the string ends with a null terminator.             *
 *      6.) If the input is NULL, then zero will be returned.                 *
 *      7.) If the input is larger than the width of unsigned char, then the  *
 *          output will be reduced mod 2^N where N is the width of unsigned   *
 *          char (which is usually 8 bits).                                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_HAS_ASCII is defined.                      *
 *  2.) tmpl_cast.h:                                                          *
 *          Provides a macro for casting with C vs. C++ compatibility.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 29, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/10/08: Ryan Maguire                                                  *
 *      Added doc-string and license, made function compliant with atoi.      *
 ******************************************************************************/

/*  TMPL_CAST macro found here, providing C vs. C++ compatibility.            */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  TMPL_HAS_ASCII macro found here.                                          */
#include <libtmpl/include/tmpl_config.h>

/*  Forward declaration / function prototype, also found in tmpl_string.h.    */
extern unsigned char tmpl_String_To_UChar(const char *str);

/*  The ASCII version is much more efficient.                                 */
#if TMPL_HAS_ASCII == 1

/******************************************************************************
 *                               ASCII Version                                *
 ******************************************************************************/

/*  Converts a string to an unsigned char.                                    */
unsigned char tmpl_String_To_UChar(const char *str)
{
    /*  Constant for the number 10. The string is assumed to represent a      *
     *  base 10 number, so we use this to set the digits of the output. 10 is *
     *  equivalent to 0x0A in hexidecimal.                                    */
    const unsigned char ten = 0x0AU;

    /*  Initialize the output to zero. This serves two purposes. Firstly, it  *
     *  allows us to loop through the string and convert it to a number by    *
     *  performing out = 10*out + k, where k is the current digit. Secondly   *
     *  it allows us to satisfy the standard library requirement of returning *
     *  zero for invalid strings. If the first characters of the string are   *
     *  not whitespace or digits, the while loops below will be skipped and   *
     *  zero will be returned, in compliance with atoi's requirements.        */
    unsigned char out = 0x00U;

    /*  The leading character is allowed to be a plus or a minus. This        *
     *  variable keeps track of this. Note, since the output is unsigned, if  *
     *  the leading character is '-' then the output is 2^N - |out| where N   *
     *  is the number of bits in unsigned char (usually 8). We initialize the *
     *  sign to positive, but we'll check later for a minus sign.             */
    unsigned char sign = 0x00U;

    /*  NULL strings are treated as invalid. Return zero.                     */
    if (!str)
        return out;

    /*  Skip all leading whitespace and all leading zeros.                    */
    while (*str == ' ' || *str == '0')
        ++str;

    /*  The first character of the number is allowed to be a plus or a minus  *
     *  sign. If it is a minus we need to set the sign Boolean to true.       */
    if (*str == '-')
    {
        sign = 0x01;
        ++str;
    }

    /*  If the sign is positive, simply increment the pointer. The sign       *
     *  variable was initialized to positive at the start.                    */
    else if (sign == '+')
        ++str;

    /*  Loop through the digits of the string and convert it to a number.     */
    while (*str)
    {
        /*  We have ASCII support so the numerical value of the current       *
         *  character can be computed by calculating the difference of this   *
         *  character with the character for zero.                            */
        const unsigned char digit = TMPL_CAST(*str - '0', unsigned char);

        /*  Since we have ASCII support, if the current value for this        *
         *  character does not fall between 0 and 9, then it is not a digit.  *
         *  We may break out of the while loop and return the output. Since   *
         *  we cast digit to unsigned char, this is equivalent to checking    *
         *  if digit is greater than 9, which is 0x09 in hexidecimal.         */
        if (digit > 0x09)
            break;

        /*  The string is interpreted to be a base 10 integer. Add the        *
         *  current digit to the output.                                      */
        out = ten * out + digit;

        /*  Move on to the next character in the string.                      */
        ++str;
    }

    /*  If the user set a minus sign at the start of the string, negate the   *
     *  output. Again, this is equivalent to returning 2^N - out where N is   *
     *  number of bits in unsigned char.                                      */
    if (sign)
        return -out;

    /*  Otherwise we are done, simply return the output.                      */
    return out;
}
/*  End of tmpl_String_To_UChar.                                              */

#else
/*  Else for #if TMPL_HAS_ASCII == 1.                                         */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  tmpl_Char_Is_Digit and tmpl_Char_To_UChar provided here.                  */
#include <libtmpl/include/tmpl_string.h>

/*  Converts a string to an unsigned char.                                    */
unsigned char tmpl_String_To_UChar(const char *str)
{
    /*  Constant for the number 10. The string is assumed to represent a      *
     *  base 10 number, so we use this to set the digits of the output. 10 is *
     *  equivalent to 0x0A in hexidecimal.                                    */
    const unsigned char ten = 0x0AU;

    /*  Initialize the output to zero. This serves two purposes. Firstly, it  *
     *  allows us to loop through the string and convert it to a number by    *
     *  performing out = 10*k + out, where k is the current digit. Secondly   *
     *  it allows us to satisfy the standard library requirement of returning *
     *  zero for invalid strings. If the first characters of the string are   *
     *  not whitespace or digits, the while loops below will be skipped and   *
     *  zero will be returned, in compliance with atoi's requirements.        */
    unsigned char out = 0x00U;

    /*  The leading character is allowed to be a plus or a minus. This        *
     *  variable keeps track of this. Note, since the output is unsigned, if  *
     *  the leading character is '-' then the output is 2^N - |out| where N   *
     *  is the number of bits in unsigned char (usually 8). We initialize the *
     *  sign to positive, but we'll check later for a minus sign.             */
    unsigned char sign = 0x00U;

    /*  Variable for storing the individual digits of the string.             */
    unsigned char digit;

    /*  NULL strings are treated as invalid. Return zero.                     */
    if (!str)
        return out;

    /*  Skip all leading whitespace and all leading zeros.                    */
    while (*str == ' ' || *str == '0')
        ++str;

    /*  The first character of the number is allowed to be a plus or a minus  *
     *  sign. If it is a minus we need to set the sign Boolean to true.       */
    if (*str == '-')
    {
        sign = 0x01;
        ++str;
    }

    /*  If the sign is positive, simply increment the pointer. The sign       *
     *  variable was initialized to positive at the start.                    */
    else if (sign == '+')
        ++str;

    /*  Loop through the digits of the string and convert it to a number.     */
    while (*str)
    {
        /*  Lacking ASCII support, use the tmpl_Char_Is_Digit function to     *
         *  determine if we are examining an actual number.                   */
        if (!tmpl_Char_Is_Digit(*str))
            break;

        /*  Convert this character to a number.                               */
        digit = tmpl_Char_To_UChar(*str);

        /*  The string is interpreted to be a base 10 integer. Add the        *
         *  current digit to the output.                                      */
        out = ten * out + digit;

        /*  Move on to the next character in the string.                      */
        ++str;
    }

    /*  If the user set a minus sign at the start of the string, negate the   *
     *  output. Again, this is equivalent to returning 2^N - out where N is   *
     *  number of bits in unsigned char.                                      */
    if (sign)
        return -out;

    /*  Otherwise we are done, simply return the output.                      */
    return out;
}
/*  End of tmpl_String_To_UChar.                                              */

#endif
/*  End of #if TMPL_HAS_ASCII == 1.                                           */
