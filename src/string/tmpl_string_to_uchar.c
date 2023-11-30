
/*  TMPL_HAS_ASCII macro found here.                                          */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype is here.                                               */
#include <libtmpl/include/tmpl_string.h>

/*  The ASCII version is much more efficient.                                 */
#if TMPL_HAS_ASCII == 1

/******************************************************************************
 *                               ASCII Version                                *
 ******************************************************************************/

/*  Converts a string to an unsigned char.                                    */
unsigned char tmpl_String_To_UChar(const char *str)
{
    unsigned char out = 0x00U;
    unsigned char digit;
    const unsigned char ten = 0x0AU;

    if (!str)
        return 0x00U;

    while (*str)
    {
        if (*str > '9' || *str < '0')
            return 0x00U;

        digit = *str & 0x0F;
        out = (unsigned char)(ten*out + digit);

        str++;
    }

    return out;
}
/*  End of tmpl_String_To_UChar.                                              */

#else
/*  Else for #if TMPL_HAS_ASCII == 1.                                         */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Converts a string to an unsigned char.                                    */
unsigned char tmpl_String_To_UChar(const char *str)
{
    unsigned char digit;
    unsigned char out = 0x00U;
    const unsigned char ten = 0x0AU;

    if (!str)
        return 0x00U;

    while (*str)
    {
        if (!tmpl_Is_Digit(*str))
            return 0x00U;

        digit = tmpl_Character_To_UChar(*str);
        out = ten*out + digit;

        str++;
    }

    return out;
}
/*  End of tmpl_String_To_UChar.                                              */

#endif
/*  End of #if TMPL_HAS_ASCII == 1.                                           */
