#ifndef TMPL_INTEGER_ABS_INLINE_H
#define TMPL_INTEGER_ABS_INLINE_H

#include <libtmpl/include/tmpl_inttype.h>
#include <libtmpl/include/tmpl_config.h>

TMPL_INLINE_DECL
signed char tmpl_Char_Abs(signed char n)
{
    return (n < 0x00 ? -n : n);
}

TMPL_INLINE_DECL
short int tmpl_Short_Abs(short int n)
{
    return (n < 0 ? -n : n);
}

TMPL_INLINE_DECL
int tmpl_Int_Abs(int n)
{
    return (n < 0 ? -n : n);
}

TMPL_INLINE_DECL
long int tmpl_Long_Abs(long int n)
{
    return (n < 0L ? -n : n);
}

#if TMPL_HAS_LONGLONG == 1
TMPL_INLINE_DECL
long long int tmpl_LLong_Abs(long long int n)
{
    return (n < 0LL ? -n : n);
}
#endif

#endif
