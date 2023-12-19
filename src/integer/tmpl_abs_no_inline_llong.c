#include <libtmpl/include/tmpl_inttype.h>
#if TMPL_HAS_LONGLONG == 1
#include <libtmpl/include/tmpl_config.h>
#if TMPL_USE_INLINE != 1
#include <libtmpl/include/tmpl_integer.h>

long long int tmpl_LLong_Abs(long long int n)
{
    if (n < 0LL)
        return -n;
    else
        return n;
}
#endif
#endif
