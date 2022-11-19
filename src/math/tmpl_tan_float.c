#include <libtmpl/include/tmpl_math.h>
#include <math.h>
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
float tmpl_Float_Tan(float x)
{
    return tanf(x);
}
#else
float tmpl_Float_Tan(float x)
{
    return (float)tan((double)x);
}
#endif
