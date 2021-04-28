

#include <libtmpl/include/tmpl_rational.h>

tmpl_RationalNumber
tmpl_RationalNumber_Add(tmpl_RationalNumber p, tmpl_RationalNumber q)
{
    tmpl_RationalNumber sum;
    sum.denominator = p.denominator * q.denominator;
    sum.numerator = p.denominator * q.numerator + p.numerator * q.denominator;
    return sum;
}
