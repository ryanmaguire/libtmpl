#include <libtmpl/include/tmpl_ieee754.h>

unsigned int tmpl_Get_High_Word32(tmpl_IEE754_Word32 x)
{
	unsigned int out = x.integer;
	out = out >> 23;
	return out;
}

