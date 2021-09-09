#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_math.h>

/*  Function for testing if a float is +/- infinity.                          */
tmpl_Bool tmpl_Float_Is_Inf(float x)
{
    /*  Check for IEEE-754. This is the easiest way check for infinity.       */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

    /*  Declare a variable for the IEEE-754 float object.                     */
    tmpl_IEEE754_Float w;

    /*  Set the float part to the input.                                      */
    w.r = x;

    /*  Infinity for IEEE-754 is exponent set to all 1's and the mantissa set *
     *  to all zeros. The sign can be 0 or 1 for +/- infinity.                */
    if (w.bits.expo == 0xFFU && w.bits.man0 == 0x0U && w.bits.man1 == 0x0U)
        return tmpl_True;
    else
        return tmpl_False;
#else
/*  Else #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1   */

    /*  A portable way to check (without IEEE-754 support) is to see if       *
     *  x = x + x, and x is not zero. x == x + 1 is another way to check, but *
     *  this can return true for finite numbers if x is greater in magnitude  *
     *  than the precision implemented for float. x == x + x avoids this      *
     *  problem. To avoid the compiler trying to optimize this code away,     *
     *  declare y as volatile.                                                */
    volatile float y = x + x;

    /*  If x == x + x for x = 0 and x = +/- infinity.                         */
    if (x == y && x != 0.0F)
        return tmpl_True;
    else
        return tmpl_False;
#endif
/*  End #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1    */
}
/*  End of tmpl_Float_Is_Inf.                                                 */

/*  Function for testing if a double is +/- infinity.                         */
tmpl_Bool tmpl_Double_Is_Inf(double x)
{
    /*  Check for IEEE-754 support. This is the easiest way to work with inf. */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

    /*  Declare a variable for the IEEE-754 double object.                    */
    tmpl_IEEE754_Double w;

    /*  Set the double part to the input.                                     */
    w.r = x;

    /*  Infinity for IEEE-754 is exponent set to all 1's and the mantissa set *
     *  to all zeros. The sign can be 0 or 1 for +/- infinity.                */
    if (w.bits.expo == 0xFFU &&
        w.bits.man0 == 0x00U &&
        w.bits.man1 == 0x00U &&
        w.bits.man2 == 0x00U &&
        w.bits.man3 == 0x00U)
        return tmpl_True;
    else
        return tmpl_False;
#else
    /*  A portable way to check (without IEEE-754 support) is to see if       *
     *  x = x + x, and x is not zero. x == x + 1 is another way to check, but *
     *  this can return true for finite numbers if x is greater in magnitude  *
     *  than the precision implemented for float. x == x + x avoids this      *
     *  problem. To avoid the compiler trying to optimize this code away,     *
     *  declare y as volatile.                                                */
    volatile double y = x + x;

    /*  If x == x + x for x = 0 and x = +/- infinity.                         */
    if (x == y && x != 0.0)
        return tmpl_True;
    else
        return tmpl_False;
#endif
}
/*  End of tmpl_Double_Is_Inf.                                                */

/*  Function for testing if a double is +/- infinity.                         */
tmpl_Bool tmpl_LDouble_Is_Inf(long double x)
{
    /*  A portable way to check (without IEEE-754 support) is to see if       *
     *  x = x + x, and x is not zero. x == x + 1 is another way to check, but *
     *  this can return true for finite numbers if x is greater in magnitude  *
     *  than the precision implemented for long double. x == x + x avoids     *
     *  this. To avoid the compiler trying to optimize this code away,        *
     *  declare y as volatile.                                                */
    volatile long double y = x + x;

    /*  If x < x + 1, x is finite. Otherwise, it is infinite.                 */
    if (x == y && x != 0.0L)
        return tmpl_True;
    else
        return tmpl_False;
}
/*  End of tmpl_LDouble_Is_Inf.                                               */

