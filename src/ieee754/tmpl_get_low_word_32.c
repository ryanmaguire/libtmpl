#include <libtmpl/include/tmpl_ieee754.h>

tmpl_uint32 tmpl_Get_Low_Word32(tmpl_IEEE754_Word32 x)
{
	tmpl_uint32 out = x.integer;
	out = out & 8388607U;
	return out;
}

