#include <libtmpl/include/tmpl_math.h>
#include <math.h>
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
long double tmpl_LDouble_Exp(long double x)
{
    return expl(x);
}
#else
long double tmpl_LDouble_Exp(long double x)
{
    return (long double)exp((double)x);
}
#endif
