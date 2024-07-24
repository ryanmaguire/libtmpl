
/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SPECIAL_FUNCTIONS_REAL_H
#define TMPL_SPECIAL_FUNCTIONS_REAL_H

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Bessel_I0                                                 *
 *  Purpose:                                                                  *
 *      Compute the Bessel I0 function.                                       *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number, the argument for I0(x).                            *
 *  Output:                                                                   *
 *      double I0_x:                                                          *
 *          The Bessel I0 function evaluated at x.                            *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern float tmpl_Float_Bessel_I0(float x);
extern double tmpl_Double_Bessel_I0(double x);
extern long double tmpl_LDouble_Bessel_I0(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Bessel_J0                                                 *
 *  Purpose:                                                                  *
 *      Compute the Bessel J0 function.                                       *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number, the argument for J0(x).                            *
 *  Output:                                                                   *
 *      double I0_x:                                                          *
 *          The Bessel J0 function evaluated at x.                            *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
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

extern float tmpl_Float_Fresnel_Cos(float x);
extern double tmpl_Double_Fresnel_Cos(double x);
extern long double tmpl_LDouble_Fresnel_Cos(long double x);

extern float tmpl_Float_Fresnel_Sin(float x);
extern double tmpl_Double_Fresnel_Sin(double x);
extern long double tmpl_LDouble_Fresnel_Sin(long double x);

extern float tmpl_Float_Normalized_Fresnel_Cos(float x);
extern double tmpl_Double_Normalized_Fresnel_Cos(double x);
extern long double tmpl_LDouble_Normalized_Fresnel_Cos(long double x);

extern void
tmpl_Legendre_Polynomials(double *legendre_p, double x, unsigned int order);

extern void
tmpl_Alt_Legendre_Polynomials(double *poly, double *legendre_p, unsigned int order);

extern void
tmpl_Fresnel_Kernel_Coefficients(double *fresnel_ker_coeffs, double *legendre_p,
                                 double *alt_legendre_p,
                                 double Legendre_Coeff, unsigned int order);

extern const float tmpl_float_normalized_fresnel_cos_table[128];
extern const double tmpl_double_normalized_fresnel_cos_table[288];

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
