

#include <libtmpl/include/tmpl_math.h>


#if __TMPL_HAS_C99_MATH_H__ == 1

long double tmpl_LDouble_Log(long double x)
{
    return logl(x);
}

#else

#include <libtmpl/include/tmpl_integer.h>

long double tmpl_LDouble_Log(long double x)
{
    tmpl_uint64 exp;
    long double mant, A, A_sq, log_x, factor;

    if (x < 0.0L)
        return tmpl_NaN;
    else if (x == 0.0L)
        return -tmpl_Infinity;

    if (x < 1.0L)
        mant = 1.0L/x;
    else
        mant = x;

    exp = 0UL;

    while (mant >= 128.0L)
    {
        mant = 0.0078125L*mant;
        exp += 7UL;
    }

    if (mant >= 64.0L)
    {
        mant = 0.015625L*mant;
        exp += 6UL;
    }
    else if (mant >= 32.0L)
    {
        mant = 0.03125L*mant;
        exp += 5UL;
    }
    else if (mant >= 16.0L)
    {
        mant = 0.0625L*mant;
        exp += 4UL;
    }
    else if (mant >= 8.0L)
    {
        mant = 0.125L*mant;
        exp += 3UL;
    }
    else if (mant >= 4.0L)
    {
        mant = 0.25L*mant;
        exp += 2UL;
    }
    else if (mant >= 2.0L)
    {
        mant = 0.5L*mant;
        ++exp;
    }

    factor = 0.693147180559945309417232L * (long double)exp;

    if (mant >= 1.5L)
    {
        mant = 0.666666666666666666666667L*mant;
        factor = factor + 0.4054651081081643819780131L;
    }

    A = (mant - 1.0L)/(mant + 1.0L);
    A_sq = A*A;

    log_x = 0.095238095238095238L*A_sq + 0.10526315789473684L;
    log_x = log_x*A_sq + 0.117647058823529411764706L;
    log_x = log_x*A_sq + 0.133333333333333333333333L;
    log_x = log_x*A_sq + 0.153846153846153846153846L;
    log_x = log_x*A_sq + 0.181818181818181818181818L;
    log_x = log_x*A_sq + 0.222222222222222222222222L;
    log_x = log_x*A_sq + 0.285714285714285714285714L;
    log_x = log_x*A_sq + 0.400000000000000000000000L;
    log_x = log_x*A_sq + 0.666666666666666666666667L;
    log_x = log_x*A_sq + 2.000000000000000000000000L;
    log_x = A*log_x;

    log_x = log_x + factor;

    if (x < 1.0L)
        return -log_x;
    else
        return log_x;
}

#endif
/*  End of #if __HAS_C99_MATH_H__ == 0                                        */
