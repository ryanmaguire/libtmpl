#ifndef TMPL_SPECIAL_FUNCTIONS_H
#define TMPL_SPECIAL_FUNCTIONS_H

/*  Boolean data type defined here.                                           */
#include <libtmpl/include/tmpl_bool.h>

/*  complex data types are defined here.                                      */
#include <libtmpl/include/tmpl_complex.h>

extern tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Integral_Real(double z);

extern tmpl_ComplexDouble
tmpl_CDouble_Bessel_J0(tmpl_ComplexDouble z);

extern tmpl_ComplexDouble
tmpl_CDouble_Bessel_I0(tmpl_ComplexDouble z);

extern tmpl_ComplexDouble
tmpl_CDouble_LambertW(tmpl_ComplexDouble z);

extern tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Cos(tmpl_ComplexDouble z);

extern tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Sin(tmpl_ComplexDouble z);

extern float
tmpl_Float_Bessel_I0(float x);

extern double
tmpl_Double_Bessel_I0(double x);

extern long double
tmpl_LDouble_Bessel_I0(long double x);

extern float
tmpl_Float_Bessel_J0(float x);

extern double
tmpl_Double_Bessel_J0(double x);

extern long double
tmpl_LDouble_Bessel_J0(long double x);

extern float
tmpl_Float_LambertW(float x);

extern double
tmpl_Double_LambertW(double x);

extern long double
tmpl_LDouble_LambertW(long double x);

extern float
tmpl_Float_Fresnel_Cos(float x);

extern double
tmpl_Double_Fresnel_Cos(double x);

extern long double
tmpl_LDouble_Fresnel_Cos(long double x);

extern float
tmpl_Float_Fresnel_Sin(float x);

extern double
tmpl_Double_Fresnel_Sin(double x);

extern long double
tmpl_LDouble_Fresnel_Sin(long double x);


extern void
tmpl_Legendre_Polynomials(double *legendre_p, double x, unsigned int order);

extern void
tmpl_Alt_Legendre_Polynomials(double *poly, double *legendre_p, unsigned int order);

extern void
tmpl_Fresnel_Kernel_Coefficients(double *fresnel_ker_coeffs, double *legendre_p,
                                 double *alt_legendre_p,
                                 double Legendre_Coeff, unsigned int order);

extern unsigned long **
tmpl_Where_Lesser_Char(char *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Lesser_UChar(unsigned char *data, unsigned long dim,
                        double threshold);

extern unsigned long **
tmpl_Where_Lesser_Short(short *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Lesser_UShort(unsigned short *data, unsigned long dim,
                         double threshold);

extern unsigned long **
tmpl_Where_Lesser_Int(int *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Lesser_UInt(unsigned int *data, unsigned long dim,
                       double threshold);

extern unsigned long **
tmpl_Where_Lesser_Long(long *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Lesser_ULong(unsigned long *data, unsigned long dim,
                        double threshold);


extern unsigned long **
tmpl_Where_Lesser_Float(float *data, unsigned long dim, float threshold);

extern unsigned long **
tmpl_Where_Lesser_Double(double *data, unsigned long dim,
                                      double threshold);

extern unsigned long **
tmpl_Where_Lesser_LDouble(long double *data, unsigned long dim,
                          long double threshold);


extern unsigned long **
tmpl_Where_Greater_Char(char *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Greater_UChar(unsigned char *data, unsigned long dim,
                        double threshold);

extern unsigned long **
tmpl_Where_Greater_Short(short *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Greater_UShort(unsigned short *data, unsigned long dim,
                         double threshold);

extern unsigned long **
tmpl_Where_Greater_Int(int *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Greater_UInt(unsigned int *data, unsigned long dim,
                       double threshold);

extern unsigned long **
tmpl_Where_Greater_Long(long *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Greater_ULong(unsigned long *data, unsigned long dim,
                        double threshold);

extern unsigned long **
tmpl_Where_Greater_Float(float *data, unsigned long dim, float threshold);

extern unsigned long **
tmpl_Where_Greater_Double(double *data, unsigned long dim,
                                      double threshold);

extern unsigned long **
tmpl_Where_Greater_LDouble(long double *data, unsigned long dim,
                          long double threshold);



extern unsigned long **
tmpl_Where_LesserGreater_Char(char *data, unsigned long dim,
                              double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_UChar(unsigned char *data, unsigned long dim,
                               double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_Short(short *data, unsigned long dim,
                               double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_UShort(unsigned short *data, unsigned long dim,
                                double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_Int(int *data, unsigned long dim,
                             double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_UInt(unsigned int *data, unsigned long dim,
                              double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_Long(long *data, unsigned long dim,
                              double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_ULong(unsigned long *data, unsigned long dim,
                               double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_Float(float *data, unsigned long dim,
                               float lower, float upper);

extern unsigned long **
tmpl_Where_LesserGreater_Double(double *data, unsigned long dim,
                                double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_LDouble(long double *data, unsigned long dim,
                                 long double lower, long double upper);

#endif
