

#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_integer.h>
#include <libtmpl/include/tmpl_ieee754.h>

double tmpl_Double_Mod_2(double x)
{
    tmpl_IEEE754_Word64 w;
    tmpl_int32 exp;
    tmpl_uint64 low;
    double out;

    w.real = x;
    exp = tmpl_Get_Base_2_Exp64(w);

    if (exp < 1)
        return x;

    low  = tmpl_Get_Low_Word64(w);
    low  = low << exp;
    low  = low & 0x000FFFFFFFFFFFFF;

    out = (double)low * 4.44089209850062616169452667236328125E-16;

    if (x >= 0)
        return out;
    else
        return -out;
}

