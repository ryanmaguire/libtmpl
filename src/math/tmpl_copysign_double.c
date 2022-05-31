
#include <libtmpl/include/tmpl_math.h>

/*  This file is only compiled if inline support is not requested.            */
#if !defined(TMPL_USE_INLINE) || TMPL_USE_INLINE != 1

/*  With IEEE-754 support we can skip if-then statements.                     */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

/*  Double precision copysign function.                                       */
double tmpl_Double_Copysign(double x, double y)
{
    tmpl_IEEE754_Double wx, wy;

    wx.r = x;
    wy.r = y;
    wx.bits.sign = wy.bits.sign;
    return wx.r;
}
/*  End of tmpl_Double_Copysign.                                              */

#else

/*  Double precision copysign function.                                       */
double tmpl_Double_Copysign(double x, double y)
{
    /*  If y is negative, compute -|x|.                                       */
    if (y < 0.0)
        return -tmpl_Double_Abs(x);

    /*  If y is positive, compute |x|.                                        */
    else if (0.0 < y)
        return tmpl_Double_Abs(x);

    /*  And lastly, if y is zero, return x.                                   */
    else
        return x;
}
/*  End of tmpl_Double_Copysign.                                              */

#endif
/*  #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1.     */

#endif
/*  End of #if !defined(TMPL_USE_INLINE) || TMPL_USE_INLINE != 1.             */
