#ifndef __TMPL_MATH_PRIVATE_H__
#define __TMPL_MATH_PRIVATE_H__

/*  Auxilliary functions for computing sine and cosine.                       */
extern float tmpl_do_sinf(float x);
extern double tmpl_do_sin(double x);
extern long double tmpl_do_sinl(long double x);

extern float tmpl_do_cosf(float x);
extern double tmpl_do_cos(double x);
extern long double tmpl_do_cosl(long double x);

extern float tmpl_sinf_table(unsigned int n);
extern double tmpl_sin_table(unsigned int n);
extern long double tmpl_sinl_table(unsigned int n);

extern float tmpl_cosf_table(unsigned int n);
extern double tmpl_cos_table(unsigned int n);
extern long double tmpl_cosl_table(unsigned int n);

#endif
