/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_WINDOW_FUNCTIONS_H
#define TMPL_WINDOW_FUNCTIONS_H

/*  complex data types are defined here.                                      */
#include <libtmpl/include/types/tmpl_complex_double.h>
#include <libtmpl/include/types/tmpl_complex_float.h>
#include <libtmpl/include/types/tmpl_complex_ldouble.h>

/*  Window function typedefs found here (function pointers).                  */
#include <libtmpl/include/types/tmpl_window_function_double.h>
#include <libtmpl/include/types/tmpl_window_function_float.h>
#include <libtmpl/include/types/tmpl_window_function_ldouble.h>

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

extern double
tmpl_Complex_Window_Normalization(tmpl_ComplexDouble *ker,
                                  long dim, double dx, double f_scale);

#define RectNormEQ 1.0
#define CossNormEQ 1.5
#define KB20NormEQ 1.49634231
#define KB25NormEQ 1.65191895
#define KB35NormEQ 1.92844639
#define KBMD20NormEQ 1.52048382
#define KBMD25NormEQ 1.65994438
#define KBMD35NormEQ 1.52048382

/*  As a side comment, the FresT function pointer takes a different number of *
 *  variables depending on which method of diffraction correction is being    *
 *  performed, so we can't just typedef it here. We'll need to declare it     *
 *  individually for each diffraction correction method instead.              */

extern float
tmpl_Float_Kaiser_Bessel_2_0(float x, float W);

extern double
tmpl_Double_Kaiser_Bessel_2_0(double x, double W);

extern long double
tmpl_LDouble_Kaiser_Bessel_2_0(long double x, long double W);

extern float
tmpl_Float_Kaiser_Bessel_2_5(float x, float W);

extern double
tmpl_Double_Kaiser_Bessel_2_5(double x, double W);

extern long double
tmpl_LDouble_Kaiser_Bessel_2_5(long double x, long double W);

extern float
tmpl_Float_Kaiser_Bessel_3_5(float x, float W);

extern double
tmpl_Double_Kaiser_Bessel_3_5(double x, double W);

extern long double
tmpl_LDouble_Kaiser_Bessel_3_5(long double x, long double W);

extern float
tmpl_Float_Modified_Kaiser_Bessel_2_0(float x, float W);

extern double
tmpl_Double_Modified_Kaiser_Bessel_2_0(double x, double W);

extern long double
tmpl_LDouble_Modified_Kaiser_Bessel_2_0(long double x, long double W);

extern float
tmpl_Float_Modified_Kaiser_Bessel_2_5(float x, float W);

extern double
tmpl_Double_Modified_Kaiser_Bessel_2_5(double x, double W);

extern long double
tmpl_LDouble_Modified_Kaiser_Bessel_2_5(long double x, long double W);

extern float
tmpl_Float_Modified_Kaiser_Bessel_3_5(float x, float W);

extern double
tmpl_Double_Modified_Kaiser_Bessel_3_5(double x, double W);

extern long double
tmpl_LDouble_Modified_Kaiser_Bessel_3_5(long double x, long double W);

extern float
tmpl_Float_Rect_Window(float x, float W);

extern double
tmpl_Double_Rect_Window(double x, double W);

extern long double
tmpl_LDouble_Rect_Window(long double x, long double W);

extern float
tmpl_Float_Coss_Window(float x, float W);

extern double
tmpl_Double_Coss_Window(double x, double W);

extern long double
tmpl_LDouble_Coss_Window(long double x, long double W);

extern float
tmpl_Float_Kaiser_Bessel(float x, float W, float alpha);

extern double
tmpl_Double_Kaiser_Bessel(double x, double W, double alpha);

extern long double
tmpl_LDouble_Kaiser_Bessel(long double x, long double W, long double alpha);

extern float
tmpl_Float_Modified_Kaiser_Bessel(float x, float W, float alpha);

extern double
tmpl_Double_Modified_Kaiser_Bessel(double x, double W, double alpha);

extern long double
tmpl_LDouble_Modified_Kaiser_Bessel(long double x, long double W,
                                    long double alpha);

extern float
tmpl_Normeq_Float(float *w_func, long n_elements);

extern double
tmpl_Normeq_Double(double *w_func, long n_elements);

extern long double
tmpl_Normeq_LDouble(long double *w_func, long n_elements);

extern double
tmpl_Normeq_Short(short *w_func, long n_elements);

extern double
tmpl_Normeq_Int(int *w_func, long n_elements);

extern double
tmpl_Normeq_Long(long *w_func, long n_elements);

/*  Window Normalization Functions                                            */
extern float
tmpl_Float_Window_Normalization(float *ker, long dim, float dx, float f_scale);

extern double
tmpl_Double_Window_Normalization(double *ker, long dim,
                                 double dx, double f_scale);

extern long double
tmpl_LDouble_Window_Normalization(long double *ker, long dim, long double dx,
                                  long double f_scale);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
