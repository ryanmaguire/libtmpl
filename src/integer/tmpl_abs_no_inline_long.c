#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE != 1
#include <libtmpl/include/tmpl_integer.h>

long int tmpl_Long_Abs(long int n)
{
    if (n < 0L)
        return -n;
    else
        return n;
}
#endif
