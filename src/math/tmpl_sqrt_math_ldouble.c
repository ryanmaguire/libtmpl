#include <libtmpl/include/tmpl_math.h>
#include <math.h>
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
long double tmpl_LDouble_Sqrt(long double x)
{
    return sqrtl(x);
}
#else

long double tmpl_LDouble_Sqrt(long double x)
{
    return (long double)sqrt((double)x);
}
#endif
