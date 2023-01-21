#ifndef TMPL_SPECIAL_FUNCTIONS_REAL_H
#define TMPL_SPECIAL_FUNCTIONS_REAL_H

#include <libtmpl/include/tmpl_config.h>

TMPL_EXPORT extern float tmpl_Float_Bessel_I0(float x);
TMPL_EXPORT extern double tmpl_Double_Bessel_I0(double x);
TMPL_EXPORT extern long double tmpl_LDouble_Bessel_I0(long double x);

#if TMPL_USE_INLINE == 1
#include <libtmpl/include/specfunc/tmpl_bessel_i0_asymptotic_double.h>
#include <libtmpl/include/specfunc/tmpl_bessel_i0_asymptotic_float.h>
#else
TMPL_EXPORT extern float tmpl_Float_Bessel_I0_Asymptotic(float x);
TMPL_EXPORT extern double tmpl_Double_Bessel_I0_Asymptotic(double x);
TMPL_EXPORT extern long double tmpl_LDouble_Bessel_I0_Asymptotic(long double x);
#endif

#if TMPL_USE_INLINE == 1
#include <libtmpl/include/specfunc/tmpl_bessel_i0_chebyshev_double.h>
#include <libtmpl/include/specfunc/tmpl_bessel_i0_chebyshev_float.h>
#else
TMPL_EXPORT extern float tmpl_Float_Bessel_I0_Chebyshev(float x);
TMPL_EXPORT extern double tmpl_Double_Bessel_I0_Chebyshev(double x);
TMPL_EXPORT extern long double tmpl_LDouble_Bessel_I0_Chebyshev(long double x);
#endif

#if TMPL_USE_INLINE == 1
#include <libtmpl/include/specfunc/tmpl_bessel_i0_maclaurin_double.h>
#include <libtmpl/include/specfunc/tmpl_bessel_i0_maclaurin_float.h>
#else
TMPL_EXPORT extern float tmpl_Float_Bessel_I0_Maclaurin(float x);
TMPL_EXPORT extern double tmpl_Double_Bessel_I0_Maclaurin(double x);
TMPL_EXPORT extern long double tmpl_LDouble_Bessel_I0_Maclaurin(long double x);
#endif

TMPL_EXPORT extern float tmpl_Float_Bessel_J0(float x);
TMPL_EXPORT extern double tmpl_Double_Bessel_J0(double x);
TMPL_EXPORT extern long double tmpl_LDouble_Bessel_J0(long double x);

TMPL_EXPORT extern float tmpl_Float_LambertW(float x);
TMPL_EXPORT extern double tmpl_Double_LambertW(double x);
TMPL_EXPORT extern long double tmpl_LDouble_LambertW(long double x);

TMPL_EXPORT extern float tmpl_Float_Fresnel_Cos(float x);
TMPL_EXPORT extern double tmpl_Double_Fresnel_Cos(double x);
TMPL_EXPORT extern long double tmpl_LDouble_Fresnel_Cos(long double x);

TMPL_EXPORT extern float tmpl_Float_Fresnel_Sin(float x);
TMPL_EXPORT extern double tmpl_Double_Fresnel_Sin(double x);
TMPL_EXPORT extern long double tmpl_LDouble_Fresnel_Sin(long double x);

TMPL_EXPORT extern void
tmpl_Legendre_Polynomials(double *legendre_p, double x, unsigned int order);

TMPL_EXPORT extern void
tmpl_Alt_Legendre_Polynomials(double *poly, double *legendre_p, unsigned int order);

TMPL_EXPORT extern void
tmpl_Fresnel_Kernel_Coefficients(double *fresnel_ker_coeffs, double *legendre_p,
                                 double *alt_legendre_p,
                                 double Legendre_Coeff, unsigned int order);

#endif
