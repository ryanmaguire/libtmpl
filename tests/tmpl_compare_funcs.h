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
 *  Purpose:                                                                  *
 *      Provide functions for comparing the accuracy and efficiency of        *
 *      functions in libtmpl as opposed to other libraries.                   *
 *  NOTE:                                                                     *
 *      libtmpl does not have any dependencies and will compile on any        *
 *      compiler capable of handling C89/C90 or C99 compliant code. The tests *
 *      using these functions use external libraries to compare the results   *
 *      of tmpl with others. To run these tests requires having these         *
 *      libraries available. These tests are NOT required to use libtmpl      *
 *      and are mainly for internal use.                                      *
 *                                                                            *
 *      The code written for these tests is augmented from the code I wrote   *
 *      for rss_ringoccs. rss_ringoccs is released under the GPL3.            *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 26, 2020                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/12/12: Ryan Maguire                                                  *
 *      Created file (rss_ringoccs for Wellesley College).                    *
 *  2021/02/26: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *      Added typedef's for function pointers.                                *
 *      Added comments and license.                                           *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_COMPARE_FUNCS_H__
#define __TMPL_COMPARE_FUNCS_H__

#include <libtmpl/include/tmpl_complex.h>
#include <complex.h>
#include <stdio.h>

/*  Used for testing functions of the form y = f(x) at single precision.      *
 *  Examples:                                                                 *
 *      C99:      sinf, cosf, logf                                            *
 *      libtmpl:  tmpl_Float_Sin, tmpl_Float_Cos, tmpl_Float_Log              */
typedef float (*float_1in1out)(float);

/*  Used for testing functions of the form y = f(x0, x1) at single precision. *
 *  Examples:                                                                 *
 *      C99:      atan2f, copysignf                                           *
 *      libtmpl:  tmpl_Float_Atan2, tmpl_Float_Copysign                       */
typedef float (*float_2in1out)(float, float);

/*  Used for testing functions of the form y = f(x) at double precision.      *
 *  Examples:                                                                 *
 *      C89:      sin, cos, log                                               *
 *      libtmpl:  tmpl_Double_Sin, tmpl_Double_Cos, tmpl_Double_Log           */
typedef double (*double_1in1out)(double);

/*  Used for testing functions of the form y = f(x0, x1) at double precision. *
 *  Examples:                                                                 *
 *      C99:      atan2, copysign                                             *
 *      libtmpl:  tmpl_Double_Atan2, tmpl_Double_Copysign                     */
typedef double (*double_2in1out)(double, double);

typedef long double (*ldouble_1in1out)(long double);
typedef long double (*ldouble_2in1out)(long double, long double);

typedef float (*cfloat_1cin1rout)(tmpl_ComplexFloat);
typedef float (*cfloat_2cin1rout)(tmpl_ComplexFloat, tmpl_ComplexFloat);
typedef tmpl_ComplexFloat (*cfloat_1cin1cout)(tmpl_ComplexFloat);
typedef tmpl_ComplexFloat (*cfloat_2cin1cout)(tmpl_ComplexFloat,
                                              tmpl_ComplexFloat);

typedef double (*cdouble_1cin1rout)(tmpl_ComplexDouble);
typedef double (*cdouble_2cin1rout)(tmpl_ComplexDouble, tmpl_ComplexDouble);
typedef tmpl_ComplexDouble (*cdouble_1cin1cout)(tmpl_ComplexDouble);
typedef tmpl_ComplexDouble (*cdouble_2cin1cout)(tmpl_ComplexDouble,
                                                tmpl_ComplexDouble);

typedef long double (*cldouble_1cin1rout)(tmpl_ComplexLongDouble);
typedef long double (*cldouble_2cin1rout)(tmpl_ComplexLongDouble,
                                          tmpl_ComplexLongDouble);
typedef tmpl_ComplexLongDouble (*cldouble_1cin1cout)(tmpl_ComplexLongDouble);
typedef tmpl_ComplexLongDouble (*cldouble_2cin2cout)(tmpl_ComplexLongDouble,
                                                     tmpl_ComplexLongDouble);

typedef float (*cfloat99_1cin1rout)(_Complex float);
typedef float (*cfloat99_2cin1rout)(_Complex float, _Complex float);
typedef _Complex float (*cfloat99_1cin1cout)(_Complex float);
typedef _Complex float (*cfloat99_2cin1cout)(_Complex float, _Complex float);

typedef double (*cdouble99_1cin1rout)(_Complex double);
typedef double (*cdouble99_2cin1rout)(_Complex double, _Complex double);
typedef _Complex double (*cdouble99_1cin1cout)(_Complex double);
typedef _Complex double (*cdouble99_2cin1cout)(_Complex double,
                                               _Complex double);

typedef long double (*cldouble99_1cin1rout)(_Complex long double);
typedef long double (*cldouble99_2cin1rout)(_Complex long double,
                                            _Complex long double);
typedef _Complex long double (*cldouble99_1cin1cout)(_Complex long double);
typedef _Complex long double (*cldouble99_2cin1cout)(_Complex long double,
                                                     _Complex long double);

extern void
tmpl_Compare_Float_1in1out(const char *ftmpl_name, float_1in1out ftmpl,
                           const char *fext_name,  float_1in1out fext,
                           const float start, const float end,
                           const unsigned long N, float eps, FILE *fp);

extern void
tmpl_Compare_Float_2in1out(const char *ftmpl_name, float_2in1out ftmpl,
                           const char *fext_name,  float_2in1out fext,
                           const float start, const float end,
                           const unsigned long N, float eps, FILE *fp);

extern void
tmpl_Compare_Double_1in1out(const char *ftmpl_name, double_1in1out ftmpl,
                            const char *fext_name,  double_1in1out fext,
                            const double start, const double end,
                            const unsigned long N, double eps, FILE *fp);

extern void
tmpl_Compare_Double_2in1out(const char *ftmpl_name, double_2in1out ftmpl,
                            const char *fext_name,  double_2in1out fext,
                            const double start, const double end,
                            const unsigned long N, double eps, FILE *fp);

extern void
tmpl_Compare_LDouble_1in1out(const char *ftmpl_name, ldouble_1in1out ftmpl,
                             const char *fext_name,  ldouble_1in1out fext,
                             const long double start, const long double end,
                             const unsigned long N, long double eps, FILE *fp);

extern void
tmpl_Compare_LDouble_2in1out(const char *ftmpl_name, ldouble_2in1out ftmpl,
                             const char *fext_name,  ldouble_2in1out fext,
                             const long double start, const long double end,
                             const unsigned long N, long double eps, FILE *fp);

extern void
tmpl_Compare_CFloat_1cin1rout(const char *ftmpl_name, cfloat_1cin1rout ftmpl,
                              const char *fext_name,  cfloat99_1cin1rout fext,
                              const float start, const float end,
                              const unsigned long N, float eps, FILE *fp);

extern void
tmpl_Compare_CFloat_2cin1rout(const char *ftmpl_name, cfloat_2cin1rout ftmpl,
                              const char *fext_name,  cfloat99_2cin1rout fext,
                              const float start, const float end,
                              const unsigned long N, float eps, FILE *fp);

extern void
tmpl_Compare_CFloat_1cin1cout(const char *ftmpl_name, cfloat_1cin1cout ftmpl,
                              const char *fext_name,  cfloat99_1cin1cout fext,
                              const float start, const float end,
                              const unsigned long N, float eps, FILE *fp);

extern void
tmpl_Compare_CFloat_2cin1cout(const char *ftmpl_name, cfloat_2cin1cout ftmpl,
                              const char *fext_name,  cfloat99_2cin1cout fext,
                              const float start, const float end,
                              const unsigned long N, float eps, FILE *fp);

extern void
tmpl_Compare_CDouble_1cin1rout(const char *ftmpl_name, cdouble_1cin1rout ftmpl,
                               const char *fext_name,  cdouble99_1cin1rout fext,
                               const double start, const double end,
                               const unsigned long N, double eps, FILE *fp);

extern void
tmpl_Compare_CDouble_2cin1rout(const char *ftmpl_name, cdouble_2cin1rout ftmpl,
                               const char *fext_name,  cdouble99_2cin1rout fext,
                               const double start, const double end,
                               const unsigned long N, double eps, FILE *fp);

extern void
tmpl_Compare_CDouble_1cin1cout(const char *ftmpl_name, cdouble_1cin1cout ftmpl,
                               const char *fext_name,  cdouble99_1cin1cout fext,
                               const double start, const double end,
                               const unsigned long N, double eps, FILE *fp);

extern void
tmpl_Compare_CDouble_2cin1cout(const char *ftmpl_name, cdouble_2cin1cout ftmpl,
                               const char *fext_name,  cdouble99_2cin1cout fext,
                               const double start, const double end,
                               const unsigned long N, double eps, FILE *fp);

extern void
tmpl_Compare_CLDouble_1cin1rout(const char *ftmpl_name, cldouble_1cin1rout ftmpl,
                                const char *fext_name,  cldouble99_1cin1rout fext,
                                const long double start, const long double end,
                                const unsigned long N, long double eps, FILE *fp);

#endif
/*  End of include guard.                                                     */

