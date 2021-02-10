#include <libtmpl/include/tmpl_ieee754.h>

unsigned int tmpl_Get_Low_Word32(tmpl_IEE754_Word32 x)
{
	unsigned int out = x.integer;
	out = out & 8388607U;
	return out;
}

