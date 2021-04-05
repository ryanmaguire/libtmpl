

#include <libtmpl/include/tmpl_math.h>

#if __TMPL_USE_IEEE754_ALGORITHMS__ != 0
#include <libtmpl/include/tmpl_ieee754.h>
#include <libtmpl/include/tmpl_integer.h>

double tmpl_Double_Floor(double x)
{
    tmpl_int32 exp;
    tmpl_uint32 i, j;
    tmpl_IEEE754_Word64 w;

    w.real = x;
    exp = tmpl_Get_Base_2_Exp64(w);

    if (exp < 20)
    {
        if (exp < 0)
        {
            if (x >= 0)
	            return 0.0;
            else
                return -1.0;
        }
        else
	      {
            i = 0x000FFFFFU >> exp;
            if (((w.uparts.most_significant_word & i) |
                  w.uparts.least_significant_word) == 0)
                return x;

            if (w.parts.most_significant_word < 0)
                w.parts.most_significant_word += (0x00100000) >> exp;

            w.uparts.most_significant_word &= (~i);
            w.uparts.least_significant_word = 0x00000000;
        }
    }
    else if (exp > 51)
	      return x;
    else
    {
        i = ((tmpl_uint32) (0xffffffff)) >> (exp - 20);
        if ((w.uparts.least_significant_word & i) == 0)
            return x;

        if (w.parts.most_significant_word < 0)
	      {
	          if (exp == 20)
	              w.parts.most_significant_word += 1;
	          else
	          {
	              j = (tmpl_uint32)
                    (w.parts.least_significant_word + (1 << (52 - exp)));

	              if (j < w.uparts.least_significant_word)
		                w.parts.most_significant_word += 1;

	              w.parts.least_significant_word = (tmpl_int32)j;
	          }
	      }

        w.uparts.least_significant_word &= (~i);
    }
    return w.real;
}

#else

#include <math.h>

double tmpl_Double_Floor(double x)
{
    return floor(x);
}

#endif

