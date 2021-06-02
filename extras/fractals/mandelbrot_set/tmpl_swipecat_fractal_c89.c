
#include <stdio.h>
#include <math.h>

#define PI_BY_TWO 1.5707963267948966

struct complex_number {
    double real, imag;
};

int main(void)
{
    const unsigned int width = 1200U;
    const unsigned int height = 960U;
    const unsigned int imax = 100U;
    const double zmax = 150.0;

    const double x_min = -6.6;
    const double x_max = -0.4;
    const double y_min = -3.1;
    const double y_max = 3.1;

    const double x_factor = (x_max - x_min) / ((double)width - 1.0);
    const double y_factor = (y_max - y_min) / ((double)height - 1.0);

    unsigned int x, y, iters;
    double c_x, c_y, backgnd, val, exp_x;
    struct complex_number z, c;

    FILE *fp = fopen("tmpl_swipecat_fractal_c89.ppm", "w");

    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }

    fprintf(fp, "P6\n%u %u\n255\n", width, height);

    for (y = 0U; y < height; ++y)
    {
        c_y = y_max - (double)y * y_factor;
        for (x = 0U; x < width; ++x)
        {
            c_x = x_min + (double)x * x_factor;
            c.real = c_x;
            c.imag = c_y;
            z.real = 0.0;
            z.imag = 0.0;
            backgnd = 0.0;
            for (iters = 0U; iters < imax; ++iters)
            {
                exp_x = exp(z.real);
                z.real = PI_BY_TWO*(exp_x*cos(z.imag) - z.real) + c.real;
                z.imag = PI_BY_TWO*(exp_x*sin(z.imag) - z.imag) + c.imag;
                if (fabs(z.real) >= zmax)
                {
                    backgnd = log(log(fabs(z.real) + 1.0) * 0.33333333333);
                    backgnd = log(fabs((double)iters - backgnd));
                    backgnd = backgnd * 0.3076923076923077;
                    break;
                }
            }

            val = 1.0 - fabs(1.0 - backgnd);
            if (val < 0.0)
                val = 0.0;

            if (backgnd <= 1.0)
            {
                fputc((unsigned char)(255.0 * pow(val, 4.0)), fp);
                fputc((unsigned char)(255.0 * pow(val, 2.5)), fp);
                fputc((unsigned char)(255.0 * val), fp);
            }
            else
            {
                fputc((unsigned char)(255.0 * val), fp);
                fputc((unsigned char)(255.0 * pow(val, 1.5)), fp);
                fputc((unsigned char)(255.0 * pow(val, 3.0)), fp);
            }
        }
    }

    fclose(fp);
    return 0;

}

              
