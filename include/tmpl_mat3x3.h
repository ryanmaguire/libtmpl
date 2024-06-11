/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MAT3x3_H
#define TMPL_MAT3x3_H

/*  Typedef's for 3x3 matrices at various precisions.                         */
#include <libtmpl/include/tmpl_mat3x3_double.h>
#include <libtmpl/include/tmpl_mat3x3_float.h>
#include <libtmpl/include/tmpl_mat3x3_ldouble.h>

extern double
tmpl_3x3Double_Component(const tmpl_ThreeByThreeMatrixDouble * const A,
                         unsigned int m, unsigned int n);

#endif
/*  End of include guard.                                                     */
