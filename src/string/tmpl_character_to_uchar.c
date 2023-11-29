

/*  TMPL_HAS_ASCII macro found here.                                          */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype is here.                                               */
#include <libtmpl/include/tmpl_string.h>

/*  The ASCII version is much more efficient.                                 */
#if TMPL_HAS_ASCII == 1

/******************************************************************************
 *                               ASCII Version                                *
 ******************************************************************************/

/*  Function for converting a character to a number.                          */
unsigned char tmpl_Character_To_UChar(char c)
{
    if (c > '9' || c < '0')
        return 0x00U;

    return c & 0x0F;
}
/*  End of tmpl_Character_To_UChar.                                           */

#else
/*  Else for #if TMPL_HAS_ASCII == 1.                                         */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for converting a character to a number.                          */
unsigned char tmpl_Character_To_UChar(char c)
{
    switch (c)
    {
        case '1':
            return 0x01U;
        case '2':
            return 0x02U;
        case '3':
            return 0x03U;
        case '4':
            return 0x04U;
        case '5':
            return 0x05U;
        case '6':
            return 0x06U;
        case '7':
            return 0x07U;
        case '8':
            return 0x08U;
        case '9':
            return 0x09U;
        default:
            return 0x00U;
    }
}
/*  End of tmpl_Character_To_UChar.                                           */

#endif
/*  End of #if TMPL_HAS_ASCII == 1.                                           */
