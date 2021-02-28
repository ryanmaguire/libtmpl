#include <libtmpl/include/tmpl_integer.h>
#include <libtmpl/include/tmpl_ieee754.h>

float tmpl_Get_Mantissa32(tmpl_IEEE754_Word32 w)
{
    tmpl_IEEE754_Word32 out;
    out.integer = (w.integer & 0x007FFFFF) + 0x3F800000;
	return out.real;
}

