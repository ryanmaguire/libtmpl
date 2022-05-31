#include <libtmpl/include/tmpl_math.h>

/*  This file is only compiled if inline support is not requested.            */
#if !defined(TMPL_USE_INLINE) || TMPL_USE_INLINE != 1

/*  With IEEE-754 support we can skip if-then statements.                     */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

/*  Single precision copysign function.                                       */
float tmpl_Float_Copysign(float x, float y)
{
    tmpl_IEEE754_Float wx, wy;

    wx.r = x;
    wy.r = y;
    wx.bits.sign = wy.bits.sign;
    return wx.r;
}
/*  End of tmpl_Float_Copysign.                                               */

#else

/*  Float precision copysign function.                                        */
float tmpl_Float_Copysign(float x, float y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float out;

    /*  If y is negative, compute -|x|.                                       */
    if (y < 0.0F)
        out = -tmpl_Float_Abs(x);

    /*  If y is positive, compute |x|.                                        */
    else if (0.0F < y)
        out = tmpl_Float_Abs(x);

    /*  And lastly, if y is zero, return zero.                                */
    else
        out = 0.0F;

    return out;
}
/*  End of tmpl_Float_Copysign.                                               */

#endif
/*  #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1.       */

#endif
/*  End of #if !defined(TMPL_USE_INLINE) || TMPL_USE_INLINE != 1.             */
