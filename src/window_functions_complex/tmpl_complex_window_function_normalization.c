/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_window_functions_complex.h>

double
tmpl_Complex_Window_Normalization(tmpl_ComplexDouble *ker,
                                  long dim, double dx, double f_scale)
{
    /*  Declare variable for indexing.                                        */
    long n;
    double abs_T1, out;

    /*  Compute the Free-Space integral.                                      */
    tmpl_ComplexDouble T1 = tmpl_CDouble_Zero;

    for (n=0; n<dim; ++n)
        T1 = tmpl_CDouble_Add(T1, ker[n]);

    abs_T1 = dx*tmpl_CDouble_Abs(T1);

    /* Return the normalization factor.                                       */
    out = tmpl_Sqrt_Two * f_scale / abs_T1;
    return out;
}
