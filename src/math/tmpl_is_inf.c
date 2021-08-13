#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_math.h>
#include <float.h>

/*  Function for testing if a float is +/- infinity.                          */
tmpl_Bool tmpl_Float_Is_Inf(float x)
{
    /*  The compiler may see this as x < x+1, which for normal values will    *
     *  always return true. It may try to optimize this code away. For        *
     *  infinite values, x == x + 1 will return true, whereas for finite      *
     *  values it will return false. To prevent the compiler from optimizing  *
     *  out this code, declare y as "volatile".                               */
    volatile float y = x + 1.0F;

    /*  If x < x + 1, x is finite. Otherwise, it is infinite.                 */
    if (x < y)
        return tmpl_False;
    else
        return tmpl_True;
}
/*  End of tmpl_Float_Is_Inf.                                                 */

/*  Function for testing if a double is +/- infinity.                         */
tmpl_Bool tmpl_Double_Is_Inf(double x)
{
    /*  The compiler may see this as x < x+1, which for normal values will    *
     *  always return true. It may try to optimize this code away. For        *
     *  infinite values, x == x + 1 will return true, whereas for finite      *
     *  values it will return false. To prevent the compiler from optimizing  *
     *  out this code, declare y as "volatile".                               */
    volatile double y = x + 1.0;

    /*  If x < x + 1, x is finite. Otherwise, it is infinite.                 */
    if (x < y)
        return tmpl_False;
    else
        return tmpl_True;
}
/*  End of tmpl_Double_Is_Inf.                                                */

/*  Function for testing if a double is +/- infinity.                         */
tmpl_Bool tmpl_LDouble_Is_Inf(long double x)
{
    /*  The compiler may see this as x < x+1, which for normal values will    *
     *  always return true. It may try to optimize this code away. For        *
     *  infinite values, x == x + 1 will return true, whereas for finite      *
     *  values it will return false. To prevent the compiler from optimizing  *
     *  out this code, declare y as "volatile".                               */
    volatile long double y = x + 1.0L;

    /*  If x < x + 1, x is finite. Otherwise, it is infinite.                 */
    if (x < y)
        return tmpl_False;
    else
        return tmpl_True;
}
/*  End of tmpl_Double_Is_Inf.                                                */

