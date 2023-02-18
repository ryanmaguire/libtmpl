#include <stdlib.h>
#include <time.h>
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_fft.h>
#include <fftw.h>

int main(void)
{
    clock_t t1, t2;
    size_t n;
    const size_t N = (size_t)1 << 24U;
    tmpl_ComplexDouble *z0 = malloc(sizeof(*z0) * N);
    tmpl_ComplexDouble *w0 = malloc(sizeof(*w0) * N);
    fftw_complex *z1 = malloc(sizeof(*z1) * N);
    fftw_complex *w1 = malloc(sizeof(*w1) * N);
    const double start = -20.0;
    const double end = 20.0;
    const double dt = (end - start)/(double)N;
    double t = start;
    double x, tmp, dx, dy;
    double rms = 0.0;
    double max = 0.0;
    fftw_plan p;

    for (n = (size_t)0; n < N; ++n)
    {
        x = tmpl_Double_Exp(-t*t);
        z0[n] = tmpl_CDouble_Rect(x, 0.0);
        z1[n] = (fftw_complex){x, 0.0};

        t += dt;
    }

    t1 = clock();
    tmpl_CDouble_IFFT_Cooley_Tukey(z0, w0, N);
    t2 = clock();

    printf("libtmpl: %f\n", (double)(t2 - t1)/CLOCKS_PER_SEC);

    t1 = clock();
    p = fftw_create_plan(N, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_one(p, z1, w1);
    t2 = clock();

    printf("FFTW:    %f\n", (double)(t2 - t1)/CLOCKS_PER_SEC);

    for (n = (size_t)0; n < N; ++n)
    {
        dx = w0[n].dat[0] - w1[n].re;
        dy = w0[n].dat[1] - w1[n].im;

        tmp = tmpl_Double_Hypot(dx, dy);

        if (tmp > max)
            max = tmp;

        rms += tmp*tmp;
    }

    rms = tmpl_Double_Sqrt(rms / (double)N);

    printf("Max Abs Error: %e\n", max);
    printf("RMS Abs Error: %e\n", rms);

    free(z0);
    free(z1);
    free(w0);
    free(w1);
}
