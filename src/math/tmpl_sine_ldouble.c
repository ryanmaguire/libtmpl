#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_math.h>

#if __TMPL_HAS_C99_MATH_H__ != 0
long double tmpl_LDouble_Sin(long double x)
{
    return sinl(x);
}
#else
long double tmpl_LDouble_Sin(long double x)
{
    return (long double)sin((double)x);
}
#endif
