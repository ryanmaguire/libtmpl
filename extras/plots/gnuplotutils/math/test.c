#include <stdio.h>
#include <libtmpl/include/tmpl_math.h>

int main(void)
{
    double x, dx;
    unsigned int N = 1024U;
    unsigned int n;

    dx = 1.0 / (double)N;
    x = 0.0;
 
    for (n = 0U; n < N; ++n)
    {
        printf("%f: %f\n", x, tmpl_Double_Sin(x));
        x += dx;
    }
    return 0;
}
