
#include <libtmpl/include/tmpl_rational.h>

tmpl_RationalNumber
tmpl_RationalNumber_Multiply(tmpl_RationalNumber p, tmpl_RationalNumber q)
{
    tmpl_RationalNumber prod;
    
    prod.numerator = p.numerator * q.numerator;
    prod.denominator = p.denominator * q.denominator;
    
    return prod;
}
