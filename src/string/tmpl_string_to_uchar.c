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
