#include <libtmpl/include/tmpl_math.h>
#include <math.h>
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
float tmpl_Float_Sqrt(float x)
{
    return sqrtf(x);
}
#else

float tmpl_Float_Sqrt(float x)
{
    return (float)sqrt((double)x);
}
#endif
