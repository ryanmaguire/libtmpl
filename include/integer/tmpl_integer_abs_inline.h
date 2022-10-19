#ifndef TMPL_INTEGER_ABS_INLINE_H
#define TMPL_INTEGER_ABS_INLINE_H

#include <libtmpl/include/tmpl_inttype.h>
#include <libtmpl/include/tmpl_config.h>

TMPL_INLINE_DECL
signed char tmpl_Char_Abs(signed char n)
{
    if (n < 0x00)
        return -n;
    else
        return n;
}

TMPL_INLINE_DECL
short int tmpl_Short_Abs(short int n)
{
    if (n < 0)
        return -n;
    else
        return n;
}

TMPL_INLINE_DECL
int tmpl_Int_Abs(int n)
{
    if (n < 0)
        return -n;
    else
        return n;
}

TMPL_INLINE_DECL
long int tmpl_Long_Abs(long int n)
{
    if (n < 0L)
        return -n;
    else
        return n;
}

#if TMPL_HAS_LONGLONG == 1
TMPL_INLINE_DECL
long long int tmpl_LLong_Abs(long long int n)
{
    return (n < 0LL ? -n : n);
}
#endif

#endif
/*  End of include guard.                                                     */
