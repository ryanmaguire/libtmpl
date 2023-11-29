
/*  TMPL_HAS_ASCII macro found here.                                          */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype is here.                                               */
#include <libtmpl/include/tmpl_string.h>

/*  The ASCII version is much more efficient.                                 */
#if TMPL_HAS_ASCII == 1

/******************************************************************************
 *                               ASCII Version                                *
 ******************************************************************************/

/*  Converts a string to an unsigned int.                                     */
unsigned int tmpl_String_To_UInt(const char *str)
{
    unsigned int out = 0U;
    const unsigned int ten = 10U;
    unsigned char digit;

    if (!str)
        return 0U;

    while (*str)
    {
        if (*str > '9' || *str < '0')
            return 0U;

        digit = *str & 0x0F;
        out = ten*out + (unsigned int)digit;

        str++;
    }

    return out;
}
/*  End of tmpl_String_To_UInt.                                               */

#else
/*  Else for #if TMPL_HAS_ASCII == 1.                                         */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Converts a string to an unsigned int.                                     */
unsigned int tmpl_String_To_UInt(const char *str)
{
    unsigned char digit;
    unsigned int out = 0U;
    const unsigned int ten = 10U;

    if (!str)
        return 0U;

    while (*str)
    {
        if (!tmpl_Is_Digit(*str))
            return 0U;

        digit = tmpl_Character_To_UChar(*str);
        out = ten*out + (unsigned int)digit;

        str++;
    }

    return out;
}
/*  End of tmpl_String_To_UInt.                                               */

#endif
/*  End of #if TMPL_HAS_ASCII == 1.                                           */
