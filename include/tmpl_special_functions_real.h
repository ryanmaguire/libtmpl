#ifndef TMPL_SPECIAL_FUNCTIONS_REAL_H
#define TMPL_SPECIAL_FUNCTIONS_REAL_H

extern float tmpl_Float_Bessel_I0(float x);
extern double tmpl_Double_Bessel_I0(double x);
extern long double tmpl_LDouble_Bessel_I0(long double x);

extern float tmpl_Float_Bessel_I0_Asymptotic(float x);
extern double tmpl_Double_Bessel_I0_Asymptotic(double x);
extern long double tmpl_LDouble_Bessel_I0_Asymptotic(long double x);

extern float tmpl_Float_Bessel_I0_Small_Asymptotic(float x);
extern double tmpl_Double_Bessel_I0_Small_Asymptotic(double x);
extern long double tmpl_LDouble_Bessel_I0_Small_Asymptotic(long double x);

extern float tmpl_Float_Bessel_I0_Large_Asymptotic(float x);
extern double tmpl_Double_Bessel_I0_Large_Asymptotic(double x);
extern long double tmpl_LDouble_Bessel_I0_Large_Asymptotic(long double x);

extern float tmpl_Float_Bessel_J0(float x);
extern double tmpl_Double_Bessel_J0(double x);
extern long double tmpl_LDouble_Bessel_J0(long double x);

extern float tmpl_Float_LambertW(float x);
extern double tmpl_Double_LambertW(double x);
extern long double tmpl_LDouble_LambertW(long double x);

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

#endif
