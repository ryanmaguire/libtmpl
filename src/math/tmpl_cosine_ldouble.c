#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_math.h>
#include <math.h>

#if __TMPL_HAS_C99_MATH_H__ != 0
long double tmpl_LDouble_Cos(long double x)
{
    return cosl(x);
}
#else
long double tmpl_LDouble_Cos(long double x)
{
    return (long double)cos((double)x);
}
#endif
