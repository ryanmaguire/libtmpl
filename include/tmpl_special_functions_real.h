#ifndef TMPL_SPECIAL_FUNCTIONS_REAL_H
#define TMPL_SPECIAL_FUNCTIONS_REAL_H

#include <libtmpl/include/tmpl_config.h>

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/*  TODO:
 *      I0 is pretty-well optimized for |x| > 8. The Chebyshev and asymptotic
 *      expansions give better performance than other libraries tested against.
 *      Need to optimize better for |x| <= 8. Try the rational approximation in:
 *          Rational Approximations for the Modified Bessel Function of
 *          the First Kind - I0(x) for Computations with Double Precision.
 *      and:
 *          Stable rational minimax approximations to the modified
 *          Bessel functions I0 and I1.
 */
extern float tmpl_Float_Bessel_I0(float x);
extern double tmpl_Double_Bessel_I0(double x);
extern long double tmpl_LDouble_Bessel_I0(long double x);

#if TMPL_USE_INLINE == 1
#include <libtmpl/include/specfunc/tmpl_bessel_i0_asymptotic_double.h>
#include <libtmpl/include/specfunc/tmpl_bessel_i0_asymptotic_float.h>
#else
extern float tmpl_Float_Bessel_I0_Asymptotic(float x);
extern double tmpl_Double_Bessel_I0_Asymptotic(double x);
extern long double tmpl_LDouble_Bessel_I0_Asymptotic(long double x);
#endif

#if TMPL_USE_INLINE == 1
#include <libtmpl/include/specfunc/tmpl_bessel_i0_chebyshev_double.h>
#include <libtmpl/include/specfunc/tmpl_bessel_i0_chebyshev_float.h>
#else
extern float tmpl_Float_Bessel_I0_Chebyshev(float x);
extern double tmpl_Double_Bessel_I0_Chebyshev(double x);
extern long double tmpl_LDouble_Bessel_I0_Chebyshev(long double x);
#endif

#if TMPL_USE_INLINE == 1
#include <libtmpl/include/specfunc/tmpl_bessel_i0_maclaurin_double.h>
#include <libtmpl/include/specfunc/tmpl_bessel_i0_maclaurin_float.h>
#else
extern float tmpl_Float_Bessel_I0_Maclaurin(float x);
extern double tmpl_Double_Bessel_I0_Maclaurin(double x);
extern long double tmpl_LDouble_Bessel_I0_Maclaurin(long double x);
#endif

extern float tmpl_Float_Bessel_J0(float x);
extern double tmpl_Double_Bessel_J0(double x);
extern long double tmpl_LDouble_Bessel_J0(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_LambertW                                                  *
 *  Purpose:                                                                  *
 *      Compute the Lambert W function of x.                                  *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number, the argument for W(x).                             *
 *  Output:                                                                   *
 *      double W_x:                                                           *
 *          The Lambert W function of x.                                      *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern float tmpl_Float_LambertW(float x);
extern double tmpl_Double_LambertW(double x);
extern long double tmpl_LDouble_LambertW(long double x);

/*  TODO:
 *      Implement the following paper:
 *          Precise and fast computation of Lambert-functions
 *          without transcendental function evaluations.
 *      This may be much faster than the standard Halley algorithm.
 *      For small |x|, the Maclaurin and Pade approximants give excellent
 *      performance. Better than other libraries. Do not alter this.
 */

/*  TODO:
 *      Implement the other branch, LambertWm1.
 */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_LambertW_Negative                                         *
 *  Purpose:                                                                  *
 *      Compute the Lambert W function for negative values.                   *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number, the argument for W(x).                             *
 *  Output:                                                                   *
 *      double W_x:                                                           *
 *          The Lambert W function of x.                                      *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/

/*  TODO:
 *      Rewrite this.
 *      The expansions used are slight modifications of the rational
 *      approximations found in the boost library. I'd rather implement
 *      something more concrete with a simpler way of reproducing the.
 *      approximation. Shifted Pade approximants or rational
 *      Remez approximations.
 */
extern float tmpl_Float_LambertW_Negative(float x);
extern double tmpl_Double_LambertW_Negative(double x);
extern long double tmpl_LDouble_LambertW_Negative(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_LambertW_Positive                                         *
 *  Purpose:                                                                  *
 *      Compute the Lambert W function for positive values.                   *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number, the argument for W(x).                             *
 *  Output:                                                                   *
 *      double W_x:                                                           *
 *          The Lambert W function of x.                                      *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/

/*  TODO:
 *      Rewrite this.
 *      Similar to the negative function, rewrite this in a way that is both
 *      fast, accurate, but also easy to understand where the approximation
 *      comes from. Note for large arguments one can try:
 *          W(x) - log(x) = W(e^y) - y
 *      And this latter expression can be approximated by Remez Minimax
 *      polynomial, or Chebyshev expansions. A dozen or so terms gets this to
 *      double precision for 2 < y < 10. This only costs one log computation
 *      and is faster than the standard Halley method.
 */
extern float tmpl_Float_LambertW_Positive(float x);
extern double tmpl_Double_LambertW_Positive(double x);
extern long double tmpl_LDouble_LambertW_Positive(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_LambertW_Halley                                           *
 *  Purpose:                                                                  *
 *      Compute the Lambert W function of x using Halley's method.            *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number, the argument for W(x).                             *
 *      double x0:                                                            *
 *          The initial guess for Halley's method. This is usually either     *
 *          x0 = x or x0 = log(x/log(x)).                                     *
 *      double tol:                                                           *
 *          The tolerance for Halley's method. When |dx| < tol the function   *
 *          returns. This is usually |x0|*EPSILON.                            *
 *  Output:                                                                   *
 *      double W_x:                                                           *
 *          The Lambert W function of x.                                      *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern float tmpl_Float_LambertW_Halley(float x, float x0, float tol);
extern double tmpl_Double_LambertW_Halley(double x, double x0, double tol);

extern long double
tmpl_LDouble_LambertW_Halley(long double x, long double x0, long double tol);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_LambertW_Maclaurin                                        *
 *  Purpose:                                                                  *
 *      Compute the Lambert W function of x using a Maclaurin series.         *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number, the argument for W(x).                             *
 *  Output:                                                                   *
 *      double W_x:                                                           *
 *          The Lambert W function of x.                                      *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern float tmpl_Float_LambertW_Maclaurin(float x);
extern double tmpl_Double_LambertW_Maclaurin(double x);
extern long double tmpl_LDouble_LambertW_Maclaurin(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_LambertW_Near_Branch                                      *
 *  Purpose:                                                                  *
 *      Compute the Lambert W function of x for x near -1/e.                  *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number, the argument for W(x).                             *
 *  Output:                                                                   *
 *      double W_x:                                                           *
 *          The Lambert W function of x.                                      *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern float tmpl_Float_LambertW_Near_Branch(float x);
extern double tmpl_Double_LambertW_Near_Branch(double x);
extern long double tmpl_LDouble_LambertW_Near_Branch(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_LambertW_Pade                                             *
 *  Purpose:                                                                  *
 *      Compute the Lambert W function of x using a Pade approximant.         *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number, the argument for W(x).                             *
 *  Output:                                                                   *
 *      double W_x:                                                           *
 *          The Lambert W function of x.                                      *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern float tmpl_Float_LambertW_Pade(float x);
extern double tmpl_Double_LambertW_Pade(double x);
extern long double tmpl_LDouble_LambertW_Pade(long double x);

extern float tmpl_Float_Fresnel_Cos(float x);
extern double tmpl_Double_Fresnel_Cos(double x);
extern long double tmpl_LDouble_Fresnel_Cos(long double x);

extern float tmpl_Float_Fresnel_Sin(float x);
extern double tmpl_Double_Fresnel_Sin(double x);
extern long double tmpl_LDouble_Fresnel_Sin(long double x);

extern void
tmpl_Legendre_Polynomials(double *legendre_p, double x, unsigned int order);

extern void
tmpl_Alt_Legendre_Polynomials(double *poly, double *legendre_p, unsigned int order);

extern void
tmpl_Fresnel_Kernel_Coefficients(double *fresnel_ker_coeffs, double *legendre_p,
                                 double *alt_legendre_p,
                                 double Legendre_Coeff, unsigned int order);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
