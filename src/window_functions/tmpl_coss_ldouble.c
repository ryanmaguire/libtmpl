/*  TMPL_USE_INLINE macro is found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Forward declaration / function prototype.                                 */
extern long double
tmpl_LDouble_Coss_Window(const long double x, const long double width);

/*  Mathematical constants like pi and pi / 2 are found here.                 */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  The coss window is even, symmetric about the origin. We use the absolute  *
 *  value function to reduce the argument to a non-negative value.            */
#if TMPL_USE_INLINE == 1

/*  The absolute value function is small and should be inlined.               */
#include <libtmpl/include/inline/math/tmpl_abs_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the function.             */
extern long double tmpl_LDouble_Abs(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Tell the compiler about the cosine function as well.                      */
extern long double tmpl_LDouble_Cos(const long double x);

/*  Function for computing the squared cosine window (coss).                  */
long double
tmpl_LDouble_Coss_Window(const long double x, const long double width)
{
    /*  Declare necessary variables. C89 requires declaring these at the top. */
    long double cos_arg, arg;

    /*  Get the absolute value of x. The coss window is symmetric about zero. */
    const long double abs_x = tmpl_LDouble_Abs(x);

    /*  For points outside of the window width, the window is zero.           */
    if (abs_x > 0.5L * width)
        return 0.0L;

    /*  The Coss window is cos(pi x / w)^2. Compute this.                     */
    arg = abs_x * tmpl_ldouble_pi / width;
    cos_arg = tmpl_LDouble_Cos(arg);
    return cos_arg * cos_arg;
}
/*  End of tmpl_LDouble_Coss_Window.                                          */
