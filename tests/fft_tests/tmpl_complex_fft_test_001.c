#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_fft.h>

int main(void)
{
    clock_t t1, t2;
    FILE *fp = fopen("data.txt", "w");
    size_t n;
    const size_t N = (size_t)1 << 20U;
    double *x = malloc(sizeof(*x) * N);
    tmpl_ComplexDouble *z0 = malloc(sizeof(*z0) * N);
    tmpl_ComplexDouble *w0 = malloc(sizeof(*w0) * N);
    tmpl_ComplexDouble *z1 = malloc(sizeof(*z1) * N);
    const double start = -10.0;
    const double end = 10.0;
    const double dt = (end - start)/(double)N;
    double t = start;

    for (n = (size_t)0; n < N; ++n)
    {
        x[n] = tmpl_Double_Exp(-t*t);
        z0[n] = tmpl_CDouble_Rect(x[n], 0.0);
        t += dt;
    }

    tmpl_CDouble_FFT_Cooley_Tukey(z0, w0, N);
    tmpl_CDouble_IFFT_Cooley_Tukey(w0, z1, N);

    fputs("x,y,xb\n", fp);
    for (n = (size_t)0; n < N; ++n)
        fprintf(fp, "%f,%f,%f\n", z0[n].dat[0], z1[n].dat[0], w0[n].dat[0]);

    fclose(fp);
    free(z0);
    free(z1);
    free(w0);
    free(x);
}
