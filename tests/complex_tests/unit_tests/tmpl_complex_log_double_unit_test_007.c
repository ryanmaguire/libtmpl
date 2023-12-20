#include <libtmpl/include/tmpl.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <float.h>

int main(void)
{
    const double s = 1.0 - DBL_EPSILON;
    const complex double a = (complex double)s;
    const complex double b = clog(a);

    const tmpl_ComplexDouble z = tmpl_CDouble_Rect(s, 0.0);
    const tmpl_ComplexDouble w = tmpl_CDouble_Log(z);

    const double dx = creal(b) - tmpl_CDouble_Real_Part(w);
    const double dy = cimag(b) - tmpl_CDouble_Imag_Part(w);
    const double err = hypot (dx, dy) / cabs(b);

    if (err > 1.0E-14)
        puts("FAIL");

    else
        puts("PASS");

    return 0;
}
