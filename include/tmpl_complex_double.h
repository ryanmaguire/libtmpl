#ifndef TMPL_COMPLEX_DOUBLE_H
#define TMPL_COMPLEX_DOUBLE_H

/*  The GNU Scientific Library (GSL) v2.6 defines complex variables via a     *
 *  data structure containing a single array double dat[2];. If you are using *
 *  the GSL v2.6, you can use libtmpl functions with that library. That is,   *
 *  if you have a pointer tmpl_ComplexDouble *z; and another pointer          *
 *  gsl_complex *w; you can safely cast via:                                  *
 *      z = (tmpl_ComplexDouble *)w;                                          *
 *  And similarly we can do w = (gsl_complex *)z;                             */
typedef struct tmpl_ComplexDouble_Def {
    double dat[2];
} tmpl_ComplexDouble;

#endif
