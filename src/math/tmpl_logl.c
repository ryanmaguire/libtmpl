

#include <libtmpl/include/tmpl_math.h>


#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <math.h>
long double tmpl_LDouble_Log(long double x)
{
    return logl(x);
}

#else

#include <float.h>

long double tmpl_LDouble_Log(long double x)
{
    long double mant, A, A_sq, log_x, factor, expo;

    if (x < 0.0L)
        return tmpl_NaN_L;
    else if (x == 0.0L)
        return -tmpl_Infinity_L;

    if (x < 1.0L)
        mant = 1.0L/x;
    else
        mant = x;

    expo = 0.0L;

#if LDBL_MAX_10_EXP >= 1024
    while (mant >= 1.0E1024L)
    {
        mant *= 1.0E-1024L;
        expo += 1024.0L;
    }

    if (mant >= 1.0E512L)
    {
        mant *= 1.0E-512L;
        expo += 512.0L;
    }

    if (mant >= 1.0E256L)
    {
        mant *= 1.0E-256L;
        expo += 256.0L;
    }

    if (mant >= 1.0E128L)
    {
        mant *= 1.0E-128L;
        expo += 128.0L;
    }

    if (mant >= 1.0E64L)
    {
        mant *= 1.0E-64L;
        expo += 64.0L;
    }
#elif LDBL_MAX_10_EXP >= 512
    while (mant >= 1.0E512L)
    {
        mant *= 1.0E-512L;
        expo += 512.0L;
    }

    if (mant >= 1.0E256L)
    {
        mant *= 1.0E-256L;
        expo += 256.0L;
    }

    if (mant >= 1.0E128L)
    {
        mant *= 1.0E-128L;
        expo += 128.0L;
    }

    if (mant >= 1.0E64L)
    {
        mant *= 1.0E-64L;
        expo += 64.0L;
    }
#elif LDBL_MAX_10_EXP >= 256
    while (mant >= 1.0E256L)
    {
        mant *= 1.0E-256L;
        expo += 256.0L;
    }

    if (mant >= 1.0E128L)
    {
        mant *= 1.0E-128L;
        expo += 128.0L;
    }

    if (mant >= 1.0E64L)
    {
        mant *= 1.0E-64L;
        expo += 64.0L;
    }
#elif LDBL_MAX_10_EXP >= 128
    while (mant >= 1.0E128L)
    {
        mant *= 1.0E-128L;
        expo += 128.0L;
    }

    if (mant >= 1.0E64)
    {
        mant *= 1.0E-64L;
        expo += 64.0L;
    }
#elif LDBL_MAX_10_EXP >= 64
    while (mant >= 1.0E64L)
    {
        mant *= 1.0E-64L;
        expo += 64.0L;
    }
#endif

    if (mant >= 1.0E32L)
    {
        mant *= 1.0E-32L;
        expo += 32.0L;
    }

    if (mant >= 1.0E16L)
    {
        mant *= 1.0E-16L;
        expo += 16.0L;
    }

    if (mant >= 1.0E8L)
    {
        mant *= 1.0E-8L;
        expo += 8.0L;
    }

    if (mant >= 1.0E4L)
    {
        mant *= 1.0E-4L;
        expo += 4.0L;
    }

    if (mant >= 1.0E2L)
    {
        mant *= 1.0E-2L;
        expo += 2.0L;
    }

    if (mant >= 1.0E1L)
    {
        mant *= 1.0E-1L;
        expo += 1.0L;
    }

    factor = 2.3025850929940456840179914546844L * expo;

    if (mant >= 8.0L)
    {
        mant *= 0.125L;
        factor += 2.0794415416798359282516963643745L;
    }
    else if (mant >= 4.0L)
    {
        mant *= 0.25L;
        factor += 1.3862943611198906188344642429164L;
    }
    else if (mant >= 2.0L)
    {
        mant *= 0.5L;
        factor += 0.69314718055994530941723212145818L;
    }    if (mant >= 1.5L)
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

