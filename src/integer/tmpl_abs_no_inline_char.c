#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE != 1
#include <libtmpl/include/tmpl_integer.h>

signed char tmpl_Char_Abs(signed char n)
{
    if (n < 0x00)
        return -n;
    else
        return n;
}
#endif
