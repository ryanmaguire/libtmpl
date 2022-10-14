#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE != 1
#include <libtmpl/include/tmpl_integer.h>

int tmpl_Int_Abs(int n)
{
    if (n < 0)
        return -n;
    else
        return n;
}
#endif
