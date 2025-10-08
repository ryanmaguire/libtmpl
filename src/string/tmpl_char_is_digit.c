
/*  TMPL_HAS_ASCII macro found here.                                          */
#include <libtmpl/include/tmpl_config.h>

#include <libtmpl/include/tmpl_bool.h>

/*  Function prototype is here.                                               */
#include <libtmpl/include/tmpl_string.h>

/*  The ASCII version is much more efficient.                                 */
#if TMPL_HAS_ASCII == 1

/******************************************************************************
 *                               ASCII Version                                *
 ******************************************************************************/

/*  Function for determining if a character represents a number.              */
tmpl_Bool tmpl_Char_Is_Digit(char c)
{
    /*  All numeric characters fall between '0' = 0x30 = 48 and               *
     *  '9' = 0x39 = 57. All character outside of this range are not numbers. */
    if (c > '9' || c < '0')
        return tmpl_False;

    /*  If 0x30 <= c <= 0x39 we have a digit. Return true.                    */
    return tmpl_True;
}
/*  End of tmpl_Char_Is_Digit.                                                */

#else
/*  Else for #if TMPL_HAS_ASCII == 1.                                         */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for determining if a character represents a number.              */
tmpl_Bool tmpl_Char_Is_Digit(char c)
{
    switch (c)
    {
        case '0':
            return tmpl_True;
        case '1':
            return tmpl_True;
        case '2':
            return tmpl_True;
        case '3':
            return tmpl_True;
        case '4':
            return tmpl_True;
        case '5':
            return tmpl_True;
        case '6':
            return tmpl_True;
        case '7':
            return tmpl_True;
        case '8':
            return tmpl_True;
        case '9':
            return tmpl_True;
        default:
            return tmpl_False;
    }
}
/*  End of tmpl_Char_Is_Digit.                                                */

#endif
/*  End of #if TMPL_HAS_ASCII == 1.                                           */
