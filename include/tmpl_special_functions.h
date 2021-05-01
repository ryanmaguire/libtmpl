#ifndef __TMPL_SPECIAL_FUNCTIONS_H__
#define __TMPL_SPECIAL_FUNCTIONS_H__

/*  Boolean data type defined here.                                           */
#include <libtmpl/include/tmpl_bool.h>

extern float tmpl_Float_Bessel_I0_Taylor[17];
extern float tmpl_Float_Bessel_I0_Asym[5];

extern double tmpl_Double_Bessel_I0_Taylor[25];
extern double tmpl_Double_Bessel_I0_Asym[7];

extern long double tmpl_LDouble_Bessel_I0_Taylor[29];
extern long double tmpl_LDouble_Bessel_I0_Asym[9];

extern float
tmpl_Float_Bessel_I0(float x);

extern double
tmpl_Double_Bessel_I0(double x);

extern long double
tmpl_LDouble_Bessel_I0(long double x);

extern float tmpl_Float_Bessel_J0_Taylor[17];
extern float tmpl_Float_Bessel_J0_Asym[9];

extern double tmpl_Double_Bessel_J0_Taylor[31];
extern double tmpl_Double_Bessel_J0_Asym[9];

extern long double tmpl_LDouble_Bessel_J0_Taylor[31];
extern long double tmpl_LDouble_Bessel_J0_Asym[9];

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
tmpl_Legendre_Polynomials(double *legendre_p, double x, int order);

extern void
tmpl_Alt_Legendre_Polynomials(double *poly, double *legendre_p, int order);

extern void
tmpl_Fresnel_Kernel_Coefficients(double *fresnel_ker_coeffs, double *legendre_p,
                                 double *alt_legendre_p,
                                 double Legendre_Coeff, int order);

extern float
tmpl_Max_Float(float *arr, long n_elements);

extern double
tmpl_Max_Double(double *arr, long n_elements);

extern long double
tmpl_Max_LDouble(long double *arr, long n_elements);

extern char
tmpl_Max_Char(char *arr, long n_elements);

extern unsigned char
tmpl_Max_UChar(unsigned char *arr, long n_elements);

extern short
tmpl_Max_Short(short *arr, long n_elements);

extern unsigned short
tmpl_Max_UShort(unsigned short *arr, long n_elements);

extern int
tmpl_Max_Int(int *arr, long n_elements);

extern unsigned int
tmpl_Max_UInt(unsigned int *arr, long n_elements);

extern long
tmpl_Max_Long(long *arr, long n_elements);

extern unsigned long
tmpl_Max_ULong(unsigned long *arr, long n_elements);

extern float
tmpl_Min_Float(float *arr, long n_elements);

extern double
tmpl_Min_Double(double *arr, long n_elements);

extern long double
tmpl_Min_LDouble(long double *arr, long n_elements);

extern char
tmpl_Min_Char(char *arr, long n_elements);

extern unsigned char
tmpl_Min_UChar(unsigned char *arr, long n_elements);

extern short
tmpl_Min_Short(short *arr, long n_elements);

extern unsigned short
tmpl_Min_UShort(unsigned short *arr, long n_elements);

extern int
tmpl_Min_Int(int *arr, long n_elements);

extern unsigned int
tmpl_Min_UInt(unsigned int *arr, long n_elements);

extern long
tmpl_Min_Long(long *arr, long n_elements);

extern unsigned long
tmpl_Min_ULong(unsigned long *arr, long n_elements);


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
