/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                                tmpl_math                                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This header file is provided to improve the portability of            *
 *      libtmpl. The C99 math library is a superset of the C89/C90            *
 *      version and contains float and long double support for all of the     *
 *      standard functions. So if "func" is provided in C89/C90, C99 contains *
 *      func as well as:                                                      *
 *          funcf:                                                            *
 *              Float version of func.                                        *
 *          funcl:                                                            *
 *              Long double version of func.                                  *
 *      For example, sinf, sinl, fabsf, fabsl, etc. The older C89/C90 math.h  *
 *      do not provide these functions, and rather if a function recieves a   *
 *      non-double (like passing a float to cos), then an implicit type       *
 *      conversion occurs, which may be computationally expensive. The funcf  *
 *      and funcl versions are meant to rid of this conversion step.          *
 *      For float and long double functions libtmpl uses, if available,       *
 *      these functions. Aliases for the functions in math.h are provided here*
 *      depending on whether or not the __TMPL_USING_C99_MATH_H__ macro is    *
 *      defined (it's defined in tmpl_config.h).                              *
 *                                                                            *
 *      If your compiler supports the IEEE 754 standard for floating-point    *
 *      arithmetic (most do), then tmpl_math.h can be combined with           *
 *      tmpl_ieee754.h to provide in-house routines for the standard math     *
 *      functions like log, sqrt, etc. This is not to replace the standard or *
 *      reinvent the wheel, but mostly for the sake of learning how computers *
 *      work, the mathematics behind it, and understanding the IEEE 754       *
 *      format. I will note that the in-house functions tested with similar   *
 *      speed and accuracy as the functions provided by glibc                 *
 *      (GNU's C library).                                                    *
 *                                                                            *
 *      There are also new functions in the C99 version, such as the          *
 *      hyperbolic trig functions, the copysign function, and more. These are *
 *      provided here for C89/C90 users, and the algorithms for these         *
 *      functions can be found in the math/ subdirectory of src/.             *
 *                                                                            *
 *      I do not assume you are using a C99 capable compiler and instead      *
 *      assume strict C89/C90 (also called ANSI C) compliance. The code still *
 *      compiles on C99 and C11 compliant compilers. Adjust tmpl_config.h as  *
 *      needed.                                                               *
 *                                                                            *
 *      This file also provides NaN and infinity macros if they are not set.  *
 *      NOTE:                                                                 *
 *          Infinity is set as the standard macro HUGE_VAL defined in math.h  *
 *          and for most implementations this should do. Indeed, this is the  *
 *          same manner the Py_HUGE_VAL is set. The python source code issues *
 *          the following warning (cpython/Include/pymath.h):                 *
 *              HUGE_VAL is supposed to expand to a positive double infinity. *
 *              Python uses Py_HUGE_VAL instead because some platforms are    *
 *              broken in this respect.  We used to embed code in pyport.h to *
 *              try to worm around that, but different platforms are broken   *
 *              in conflicting ways.  If you're on a platform where HUGE_VAL  *
 *              is defined incorrectly, fiddle your Python config to          *
 *              #define Py_HUGE_VAL to something that works on your platform. *
 *                                                                            *
 *          Similarly, NaN is defined as HUGE_VAL * 0, which should be        *
 *          infinity times zero, which is Not-A-Number. Python does this as   *
 *          well, issuing the following warning:                              *
 *              Py_NAN                                                        *
 *              A value that evaluates to a NaN. On IEEE 754 platforms INF*0  *
 *              or INF/INF works. Define Py_NO_NAN in pyconfig.h if your      *
 *              platform doesn't support NaNs.                                *
 *          If necessary, redefine NAN here to whatever your platform allows. *
 *      Lastly, this file provides a bunch of constants that are commonly     *
 *      used, like sqrt(2) and multiples of pi.                               *
 *                                                                            *
 *      This file is a fork of the code I wrote for rss_ringoccs. That        *
 *      library is also released under GPL3.                                  *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) math.h:                                                               *
 *      Standard library for mathematical functions like sin, cos, atan.      *
 *  2.) float.h:                                                              *
 *      Standard library which contains macros for the smallest and largest   *
 *      values allowed by your system.                                        *
 *  3.) tmpl_config.h:                                                        *
 *      Header file which contains the __TMPL_HAS_C99_MATH_H__ macro. This    *
 *      tells the compiler how to build libtmpl.                              *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/09/12 (Ryan Maguire):                                                *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16 (Ryan Maguire):                                                *
 *      Copied from rss_ringoccs.                                             *
 ******************************************************************************/

/*  Include guard for this file to prevent including it twice.                */
#ifndef TMPL_MATH_H
#define TMPL_MATH_H

/* Declare Miscellaneous Constants.                                           */

/*  sqrt( 1 / (2pi) )                                                         */
extern const float tmpl_Sqrt_One_By_Two_Pi_F;
extern const double tmpl_Sqrt_One_By_Two_Pi;
extern const long double tmpl_Sqrt_One_By_Two_Pi_L;

/*  sqrt( pi / 8 )                                                            */
extern const float tmpl_Sqrt_Pi_By_Eight_F;
extern const double tmpl_Sqrt_Pi_By_Eight;
extern const long double tmpl_Sqrt_Pi_By_Eight_L;

/*  sqrt( pi / 2 )                                                            */
extern const float tmpl_Sqrt_Pi_By_Two_F;
extern const double tmpl_Sqrt_Pi_By_Two;
extern const long double tmpl_Sqrt_Pi_By_Two_L;

/*  sqrt( 1 / pi )                                                            */
extern const float tmpl_Sqrt_One_By_Pi_F;
extern const double tmpl_Sqrt_One_By_Pi;
extern const long double tmpl_Sqrt_One_By_Pi_L;

/*  sqrt( 2 / pi )                                                            */
extern const float tmpl_Sqrt_Two_By_Pi_F;
extern const double tmpl_Sqrt_Two_By_Pi;
extern const long double tmpl_Sqrt_Two_By_Pi_L;

/*  2 / sqrt( pi )                                                            */
extern const float tmpl_Two_By_Sqrt_Pi_F;
extern const double tmpl_Two_By_Sqrt_Pi;
extern const long double tmpl_Two_By_Sqrt_Pi_L;

/*  pi / 2                                                                    */
extern const float tmpl_Pi_By_Two_F;
extern const double tmpl_Pi_By_Two;
extern const long double tmpl_Pi_By_Two_L;

/*  3 pi / 4                                                                  */
extern const float tmpl_Three_Pi_By_Four_F;
extern const double tmpl_Three_Pi_By_Four;
extern const long double tmpl_Three_Pi_By_Four_L;

/*  pi / 4                                                                    */
extern const float tmpl_Pi_By_Four_F;
extern const double tmpl_Pi_By_Four;
extern const long double tmpl_Pi_By_Four_L;

/*  pi                                                                        */
extern const float tmpl_One_Pi_F;
extern const double tmpl_One_Pi;
extern const long double tmpl_One_Pi_L;

/*  2 pi                                                                      */
extern const float tmpl_Two_Pi_F;
extern const double tmpl_Two_Pi;
extern const long double tmpl_Two_Pi_L;

/*  sqrt( 2 )                                                                 */
extern const float tmpl_Sqrt_Two_F;
extern const double tmpl_Sqrt_Two;
extern const long double tmpl_Sqrt_Two_L;

/*  e = exp( 1 )                                                              */
extern const float tmpl_Euler_E_F;
extern const double tmpl_Euler_E;
extern const long double tmpl_Euler_E_L;

/*  1 / e = exp( -1 )                                                         */
extern const float tmpl_Rcpr_Euler_E_F;
extern const double tmpl_Rcpr_Euler_E;
extern const long double tmpl_Euler_E_L;

/*  log_e( 2 ) = ln( 2 )                                                      */
extern const float tmpl_Natural_Log_of_Two_F;
extern const double tmpl_Natural_Log_of_Two;
extern const long double tmpl_Natural_Log_of_Two_L;

/*  log_e( 10 ) = ln( 10 )                                                    */
extern const float tmpl_Natural_Log_of_Ten_F;
extern const double tmpl_Natural_Log_of_Ten;
extern const long double tmpl_Natural_Log_of_Ten_L;

/*  pi / 180                                                                  */
extern const float tmpl_Deg_to_Rad_F;
extern const double tmpl_Deg_to_Rad;
extern const long double tmpl_Deg_to_Rad_L;

/*  180 / pi                                                                  */
extern const float tmpl_Rad_to_Deg_F;
extern const double tmpl_Rad_to_Deg;
extern const long double tmpl_Rad_to_Deg_L;

/*  Positive Infinity                                                         */
extern const float tmpl_Infinity_F;
extern const double tmpl_Infinity;
extern const long double tmpl_Infinity_L;

/*  Largest value such that exp(x) will not return inifinity.                 */
extern const float tmpl_Max_Float_Base_E;
extern const double tmpl_Max_Double_Base_E;
extern const long double tmpl_Max_LDouble_Base_E;

/*  Smallest positive value such that exp(x) will not return zero.            */
extern const float tmpl_Min_Float_Base_E;
extern const double tmpl_Min_Double_Base_E;
extern const long double tmpl_M_LDouble_Base_E;

/*  We'll use the CPYTHON method of defining NAN, the source code of which is *
 *  contained in python/cpython/Include/pymath.h.                             */
#define tmpl_NaN (tmpl_Infinity * 0.0)
#define tmpl_NaN_F ((float)(tmpl_NaN))
#define tmpl_NaN_L ((long double)(tmpl_NaN))

#define tmpl_Is_Inf(x) ((x) == ((x)+1))
#define tmpl_Is_NaN(x) ((x) != (x))

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Abs                                                       *
 *  Purpose:                                                                  *
 *      Compute the absolute value of a real number (fabs alias).             *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double abs_x:                                                         *
 *          The absolute value of x, |x|.                                     *
 ******************************************************************************/
extern float tmpl_Float_Abs(float x);
extern double tmpl_Double_Abs(double x);
extern long double tmpl_LDouble_Abs(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Arctan                                                    *
 *  Purpose:                                                                  *
 *      Compute the arctan (inverse tangent) of a real number.                *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double atan_x:                                                        *
 *          The inverse tangent of x, tan^-1(x).                              *
 ******************************************************************************/
extern float tmpl_Float_Arctan(float x);
extern double tmpl_Double_Arctan(double x);
extern long double tmpl_LDouble_Arctan(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Arctan2                                                   *
 *  Purpose:                                                                  *
 *      Compute the 2-dimensional arctan (inverse tangent) of a point in the  *
 *      Cartesian plane. This is the angle the point makes with the positive  *
 *      x-axis.                                                               *
 *  Arguments:                                                                *
 *      double y:                                                             *
 *          A real number.                                                    *
 *      double x:                                                             *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      double atan:                                                          *
 *          The angle the point (x,y) makes with (1,0) in the plane.          *
 *  NOTES:                                                                    *
 *      By convention dating back to (at least) the 1970s, Arctan2 takes the  *
 *      input as (y,x), not (x,y). i.e. the first argument is the y           *
 *      component and the second argument is the x component. This is contrary*
 *      to most 2 dimensional functions that want their inputs as (x,y).      *
 *      This is probably because we are trying to compute tan^-1(y/x) but     *
 *      need to be careful about the signs of y and x, so we write            *
 *      arctan(y,x).                                                          *
 *                                                                            *
 *      This returns a number between -pi and pi, so there is a "branch cut"  *
 *      along the negative x axis. Because of this, use of this function      *
 *      in complex routines results in actual branch cuts.                    *
 ******************************************************************************/
extern float tmpl_Float_Arctan2(float y, float x);
extern double tmpl_Double_Arctan2(double y, double x);
extern long double tmpl_LDouble_Arctan2(long double y, long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Copysign                                                  *
 *  Purpose:                                                                  *
 *      Given two numbers x and y, returns a value that has the magnitude of  *
 *      x and the sign of y.                                                  *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *      double y:                                                             *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      double z:                                                             *
 *          The value sgn(y) * |x|.                                           *
 ******************************************************************************/
extern float tmpl_Float_Copysign(float x, float y);
extern double tmpl_Double_Copysign(double x, double y);
extern long double tmpl_LDouble_Copysign(long double x, long double y);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Cos                                                       *
 *  Purpose:                                                                  *
 *      Computes the cosine of a real number.                                 *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cos_x:                                                         *
 *          The cosine of x, cos(x).                                          *
 ******************************************************************************/
extern float tmpl_Float_Cos(float x);
extern double tmpl_Double_Cos(double x);
extern long double tmpl_LDouble_Cos(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Cosh                                                      *
 *  Purpose:                                                                  *
 *      Computes the hyperbolic cosine of a real number.                      *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cos_x:                                                         *
 *          The hyperbolic cosine of x, cosh(x).                              *
 ******************************************************************************/
extern float tmpl_Float_Cosh(float x);
extern double tmpl_Double_Cosh(double x);
extern long double tmpl_LDouble_Cosh(long double x);

/*  Aliases for the sine trig function found in math.h.                       */
extern float tmpl_Float_Sin(float x);
extern double tmpl_Double_Sin(double x);
extern long double tmpl_LDouble_Sin(long double x);

/*  Aliases for the cosine tan function found in math.h.                      */
extern float tmpl_Float_Tan(float x);
extern double tmpl_Double_Tan(double x);
extern long double tmpl_LDouble_Tan(long double x);

/*  Aliases for the square root function found in math.h.                     */
extern float tmpl_Float_Sqrt(float x);
extern double tmpl_Double_Sqrt(double x);
extern long double tmpl_LDouble_Sqrt(long double x);

/*  Aliases for the exponential function found in math.h.                     */
extern float tmpl_Float_Exp(float x);
extern double tmpl_Double_Exp(double x);
extern long double tmpl_LDouble_Exp(long double x);

/*  Aliases for the exponential function found in math.h.                     */
extern float tmpl_Float_Log(float x);
extern double tmpl_Double_Log(double x);
extern long double tmpl_LDouble_Log(long double x);

extern float tmpl_Float_Floor(float x);
extern double tmpl_Double_Floor(double x);
extern long double tmpl_LDouble_Floor(long double x);

extern float tmpl_Float_Sinc(float x);
extern double tmpl_Double_Sinc(double x);
extern long double tmpl_LDouble_Sinc(long double x);

extern float tmpl_Float_Sinh(float x);
extern double tmpl_Double_Sinh(double x);
extern long double tmpl_LDouble_Sinh(long double x);

extern float tmpl_Float_Tanh(float x);
extern double tmpl_Double_Tanh(double x);
extern long double tmpl_LDouble_Tanh(long double x);

extern float tmpl_Float_Erf(float x);
extern double tmpl_Double_Erf(double x);
extern long double tmpl_LDouble_Erf(long double x);

extern float tmpl_Float_Erfc(float x);
extern double tmpl_Double_Erfc(double x);
extern long double tmpl_LDouble_Erfc(long double x);

extern float tmpl_Float_Erfcx(float x);
extern double tmpl_Double_Erfcx(double x);
extern long double tmpl_LDouble_Erfcx(long double x);

extern float tmpl_Float_Faddeeva_Im(float x);
extern double tmpl_Double_Faddeeva_Im(double x);
extern long double tmpl_LDouble_Faddeeva_Im(long double x);

extern unsigned long tmpl_Factorial(unsigned int n);

extern unsigned long
tmpl_Falling_Factorial(unsigned int x, unsigned int N);

extern float
tmpl_Real_Poly_Float_Coeffs(float *coeffs, unsigned int degree, float x);

extern double
tmpl_Real_Poly_Double_Coeffs(double *coeffs,
                                    unsigned int degree,
                                    double x);

extern long double
tmpl_Real_Poly_LDouble_Coeffs(long double *coeffs,
                                     unsigned int degree,
                                     long double x);

extern float
tmpl_Real_Poly_Deriv_Float_Coeffs(float *coeffs, unsigned int degree,
                                         unsigned int deriv, float x);

extern double
tmpl_Real_Poly_Deriv_Double_Coeffs(double *coeffs, unsigned int degree,
                                          unsigned int deriv, double x);

extern long double
tmpl_Real_Poly_Deriv_LDouble_Coeffs(long double *coeffs,
                                           unsigned int degree,
                                           unsigned int deriv,
                                           long double x);

extern void
tmpl_Reverse_Float_Array(float *arr, unsigned long arrsize);

extern void
tmpl_Reverse_Double_Array(double *arr, unsigned long arrsize);

extern void
tmpl_Reverse_LDouble_Array(long double *arr, unsigned long arrsize);

extern float tmpl_Float_Mod_2(float x);
extern double tmpl_Double_Mod_2(double n);
extern long double tmpl_LDouble_Mod_2(long double x);

extern const float tmpl_Float_Cos_Lookup_Table[100];
extern const double tmpl_Double_Cos_Lookup_Table[100];
extern const long double tmpl_LDouble_Cos_Lookup_Table[100];

extern const float tmpl_Float_Sin_Lookup_Table[100];
extern const double tmpl_Double_Sin_Lookup_Table[100];
extern const long double tmpl_LDouble_Sin_Lookup_Table[100];

extern float
tmpl_Max_Float(float *arr, unsigned long n_elements);

extern double
tmpl_Max_Double(double *arr, unsigned long n_elements);

extern long double
tmpl_Max_LDouble(long double *arr, unsigned long n_elements);

extern char
tmpl_Max_Char(char *arr, unsigned long n_elements);

extern unsigned char
tmpl_Max_UChar(unsigned char *arr, unsigned long n_elements);

extern short
tmpl_Max_Short(short *arr, unsigned long n_elements);

extern unsigned short
tmpl_Max_UShort(unsigned short *arr, unsigned long n_elements);

extern int
tmpl_Max_Int(int *arr, unsigned long n_elements);

extern unsigned int
tmpl_Max_UInt(unsigned int *arr, unsigned long n_elements);

extern long
tmpl_Max_Long(long *arr, unsigned long n_elements);

extern unsigned long
tmpl_Max_ULong(unsigned long *arr, unsigned long n_elements);

extern float
tmpl_Min_Float(float *arr, unsigned long n_elements);

extern double
tmpl_Min_Double(double *arr, unsigned long n_elements);

extern long double
tmpl_Min_LDouble(long double *arr, unsigned long n_elements);

extern char
tmpl_Min_Char(char *arr, unsigned long n_elements);

extern unsigned char
tmpl_Min_UChar(unsigned char *arr, unsigned long n_elements);

extern short
tmpl_Min_Short(short *arr, unsigned long n_elements);

extern unsigned short
tmpl_Min_UShort(unsigned short *arr, unsigned long n_elements);

extern int
tmpl_Min_Int(int *arr, unsigned long n_elements);

extern unsigned int
tmpl_Min_UInt(unsigned int *arr, unsigned long n_elements);

extern long
tmpl_Min_Long(long *arr, unsigned long n_elements);

extern unsigned long
tmpl_Min_ULong(unsigned long *arr, unsigned long n_elements);


#endif
/*  End of include guard.                                                     */
