/*  TMPL_USE_INLINE macro is found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Forward declaration / function prototype.                                 */
extern double tmpl_Double_Coss_Window(const double x, const double width);

/*  Mathematical constants like pi and pi / 2 are found here.                 */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  The coss window is even, symmetric about the origin. We use the absolute  *
 *  value function to reduce the argument to a non-negative value.            */
#if TMPL_USE_INLINE == 1

/*  The absolute value function is small and should be inlined.               */
#include <libtmpl/include/inline/math/tmpl_abs_double.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the function.             */
extern double tmpl_Double_Abs(double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Tell the compiler about the cosine function as well.                      */
extern double tmpl_Double_Cos(const double x);

/*  Function for computing the squared cosine window (coss).                  */
double tmpl_Double_Coss_Window(const double x, const double width)
{
    /*  Declare necessary variables. C89 requires declaring these at the top. */
    double cos_arg, arg;

    /*  Get the absolute value of x. The coss window is symmetric about zero. */
    const double abs_x = tmpl_Double_Abs(x);

    /*  For points outside of the window width, the window is zero.           */
    if (abs_x > 0.5 * width)
        return 0.0;

    /*  The Coss window is cos(pi x / w)^2. Compute this.                     */
    arg = abs_x * tmpl_double_pi / width;
    cos_arg = tmpl_Double_Cos(arg);
    return cos_arg * cos_arg;
}
/*  End of tmpl_Double_Coss_Window.                                           */
