
#include <libtmpl/include/tmpl_math.h>

#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  64-bit double, 80-bit extended, and 128-bit quadruple implementations     *
 *  of long double use the same idea.                                         */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

long double tmpl_LDouble_Pow2(signed int expo)
{
    tmpl_IEEE754_LDouble w;
    w.r = 1.0L;

    if (expo <= -TMPL_LDOUBLE_BIAS)
    {
        if (expo <= -TMPL_LDOUBLE_BIAS - TMPL_LDOUBLE_MANTISSA_LENGTH)
            return 0.0L;

        expo += TMPL_LDOUBLE_MANTISSA_LENGTH;
        w.bits.expo =
            (unsigned int)(TMPL_LDOUBLE_BIAS + expo) & TMPL_LDOUBLE_NANINF_EXP;
        w.r /= TMPL_LDOUBLE_NORMALIZE;
        return w.r;
    }
    else if (expo > TMPL_LDOUBLE_BIAS)
    {
        w.bits.expo = TMPL_LDOUBLE_NANINF_EXP;
        return w.r;
    }

    w.bits.expo =
        (unsigned int)(TMPL_LDOUBLE_BIAS + expo) & TMPL_LDOUBLE_NANINF_EXP;
    return w.r;
}

#else

long double tmpl_LDouble_Pow2(signed int expo)
{
    tmpl_IEEE754_Double w;
    tmpl_IEEE754_LDouble wl;
    w.r = 1.0;
    wl.d[1] = 0.0;

    if (expo < -1022)
    {
        if (expo < -1074)
            return 0.0L;

        expo += 52;
        w.bits.expo =
            (unsigned int)(TMPL_DOUBLE_BIAS + expo) & TMPL_LDOUBLE_NANINF_EXP;
        w.r /= 4.503599627370496E15;

        wl.d[0] = w.r;
        return wl.r;
    }
    else if (expo > 1023)
    {
        w.bits.expo = TMPL_DOUBLE_NANINF_EXP;
        wl.d[0] = w.r;
        return wl.r;
    }

    w.bits.expo =
        (unsigned int)(TMPL_DOUBLE_BIAS + expo) & TMPL_LDOUBLE_NANINF_EXP;
    wl.d[0] = w.r;
    return wl.r;
}

#endif

#else

#include <libtmpl/include/tmpl_integer.h>
#include <float.h>

long double tmpl_LDouble_Pow2(signed int expo)
{
    signed int n;
    long double x = 1.0L;

    if (expo == 0)
        return x;

    n = tmpl_Int_Abs(expo);

#if LDBL_MAX_10_EXP > 4932

    /*  First two hundred digits of 2^16384.                                  */
#define TWO_TO_THE_16384 \
(1.18973149535723176508575932662800713076344468709651023747267482123326135818\
04836869044885954726120399151154374848393092588976673813086874262745246983415\
650060808716343660048975221432516195314468459523E4932L)
    while (n >= 16384)
    {
        x *= TWO_TO_THE_16384;
        n -= 16384;
    }
#undef TWO_TO_THE_16384
#endif
/*  End of #if LDBL_MAX_10_EXP > 4932.                                        */

    /*  Same idea for 2^8192.                                                 */
#if LDBL_MAX_10_EXP > 2466

    /*  First two hundred digits of 2^8192.                                   */
#define TWO_TO_THE_8192 \
(1.09074813561941592946298424473378286244826416199623269243183278618972133184\
91192952162642345252019872239572917961570252731098708201771840636109797650775\
547990789062988421929895386098252280482051596969E2466L)
    while (n >= 8192)
    {
        x *= TWO_TO_THE_8192;
        n -= 8192;
    }
#undef TWO_TO_THE_8192
#endif
/*  End of #if LDBL_MAX_10_EXP > 2466.                                        */

    /*  Same idea for 2^4096.                                                 */
#if LDBL_MAX_10_EXP > 1233

    /*  First two hundred digits of 2^4096.                                   */
#define TWO_TO_THE_4096 \
(1.04438888141315250669175271071662438257996424904738378038423348328395390797\
15574568488268119349975583408901067144392628379875734381857936072632360878513\
652779459569765437099983403615901343837183144281E1233L)
    while (n >= 4096)
    {
        x *= TWO_TO_THE_4096;
        n -= 4096;
    }
#undef TWO_TO_THE_4096
#endif
/*  End of #if LDBL_MAX_10_EXP > 1233.                                        */

    /*  Same idea for 2^2048.                                                 */
#if LDBL_MAX_10_EXP > 616

    /*  First two hundred digits of 2^2048.                                   */
#define TWO_TO_THE_2048 \
(3.2317006071311007300714876688669951960444102669715484032130345427524655138\
8678908931972014115229134636887179609218980194941195591504909210950881523864\
48283120630877367300996091750197750389652106796058E616L)
    while (n >= 2048)
    {
        x *= TWO_TO_THE_2048;
        n -= 2048;
    }
#undef TWO_TO_THE_2048
#endif
/*  End of #if LDBL_MAX_10_EXP > 616.                                         */

    /*  Same idea for 2^1024.                                                 */
#if LDBL_MAX_10_EXP > 308

    /*  First two hundred digits of 2^1024.                                   */
#define TWO_TO_THE_1024 \
(1.7976931348623159077293051907890247336179769789423065727343008115773267580\
5500963132708477322407536021120113879871393357658789768814416622492847430639\
47412437776789342486548527630221960124609411945308E308L)
    while (n >= 1024)
    {
        x *= TWO_TO_THE_1024;
        n -= 1024;
    }
#undef TWO_TO_THE_1024
#endif
/*  End of #if LDBL_MAX_10_EXP > 308.                                         */

#if LDBL_MAX_10_EXP > 154
#define TWO_TO_THE_512 \
(1.3407807929942597099574024998205846127479365820592393377723561443\
721764030073546976801874298166903427690031858186486050853753882811\
946569946433649006084096E+154L)
    while (n >= 512)
    {
        x *= TWO_TO_THE_512;
        n -= 512;
    }
#undef TWO_TO_THE_512
#endif
/*  End of #if LDBL_MAX_10_EXP > 154.                                         */

#if LDBL_MAX_10_EXP > 77
#define \
TWO_TO_THE_256 \
(1.1579208923731619542357098500868\
7907853269984665640564039457584007913129639936E+77L)
    while (n >= 256)
    {
        x *= TWO_TO_THE_256;
        n -= 256;
    }
#undef TWO_TO_THE_256
#endif
/*  End of #if LDBL_MAX_10_EXP > 77.                                          */

#if LDBL_MAX_10_EXP > 38
#define TWO_TO_THE_128 (3.40282366920938463463374607431768211456E+38L)
    while (n >= 128)
    {
        x *= TWO_TO_THE_128;
        n -= 128;
    }
#undef TWO_TO_THE_128
#endif
/*  End of #if LDBL_MAX_10_EXP > 38.                                          */

#if LDBL_MAX_10_EXP > 19
#define TWO_TO_THE_64 (1.8446744073709551616E+19L)
    while (n >= 64)
    {
        x *= TWO_TO_THE_64;
        n -= 64;
    }
#undef TWO_TO_THE_64
#endif
/*  End of #if LDBL_MAX_10_EXP > 19.                                          */

#if LDBL_MAX_10_EXP > 9
#define TWO_TO_THE_32 (4.294967296E+09L)
    while (n >= 32)
    {
        x *= TWO_TO_THE_32;
        n -= 32;
    }
#undef TWO_TO_THE_32
#endif
/*  End of #if LDBL_MAX_10_EXP > 9.                                           */

    while (n >= 16)
    {
        x *= 65536.0L;
        n -= 16;
    }

    if (n >= 8)
    {
        x *= 256.0L;
        n -= 8;
    }

    if (n >= 4)
    {
        x *= 16.0L;
        n -= 4;
    }

    if (n >= 2)
    {
        x *= 4.0L;
        n -= 2;
    }

    if (n >= 1)
    {
        x *= 2.0L;
        n -= 1;
    }

    if (expo < 0)
        return 1.0L / x;
    else
        return x;
}

#endif
