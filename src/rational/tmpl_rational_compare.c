
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_rational.h>

tmpl_Bool
tmpl_RationalNumber_Compare(tmpl_RationalNumber p, tmpl_RationalNumber q)
{
    if (p.numerator * q.denominator == p.denominator * q.numerator)
        return tmpl_True;
    else
        return tmpl_False;
}
