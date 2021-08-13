#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_math.h>
#include <float.h>

/*  Function for testing if a float is Not-A-Number.                          */
tmpl_Bool tmpl_Float_Is_NaN(float x)
{
    /*  The compiler will see this as x == x, which for normal values will    *
     *  always return true. It may try to optimize this code away. For        *
     *  NaN values, x == x will return false, whereas for all other values    *
     *  it will return false. To prevent the compiler from optimizing         *
     *  out this code, declare y as "volatile".                               */
    volatile float y = x;

    /*  If y == y, y is a number. Otherwise, it is NaN.                       */
    if (y == y)
        return tmpl_False;
    else
        return tmpl_True;
}
/*  End of tmpl_Float_Is_Inf.                                                 */

/*  Function for testing if a double is Not-A-Number.                         */
tmpl_Bool tmpl_Double_Is_NaN(double x)
{
    /*  The compiler will see this as x == x, which for normal values will    *
     *  always return true. It may try to optimize this code away. For        *
     *  NaN values, x == x will return false, whereas for all other values    *
     *  it will return false. To prevent the compiler from optimizing         *
     *  out this code, declare y as "volatile".                               */
    volatile double y = x;

    /*  If y == y, y is a number. Otherwise, it is NaN.                       */
    if (y == y)
        return tmpl_False;
    else
        return tmpl_True;
}
/*  End of tmpl_Double_Is_NaN.                                                */

/*  Function for testing if a long double is Not-A-Number.                    */
tmpl_Bool tmpl_LDouble_Is_NaN(long double x)
{
    /*  The compiler will see this as x == x, which for normal values will    *
     *  always return true. It may try to optimize this code away. For        *
     *  NaN values, x == x will return false, whereas for all other values    *
     *  it will return false. To prevent the compiler from optimizing         *
     *  out this code, declare y as "volatile".                               */
    volatile long double y = x;

    /*  If y == y, y is a number. Otherwise, it is NaN.                       */
    if (y == y)
        return tmpl_False;
    else
        return tmpl_True;
}
/*  End of tmpl_LDouble_Is_Inf.                                                */

