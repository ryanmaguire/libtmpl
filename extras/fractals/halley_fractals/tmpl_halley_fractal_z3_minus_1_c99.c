#include <stdio.h>
#include <math.h>
#include <complex.h>

struct color {
    unsigned char red, green, blue;
};

static struct color scale_color(struct color c, double t)
{
    struct color out;

    out.red   = (unsigned char)(t * (double)c.red);
    out.green = (unsigned char)(t * (double)c.green);
    out.blue  = (unsigned char)(t * (double)c.blue);

    return out;
}

static void write_color(FILE *fp, struct color c)
{
    fputc(c.red, fp);
    fputc(c.green, fp);
    fputc(c.blue, fp);
}

int main(void)
{
    complex double z, f_of_z, f_prime_of_z, f_double_prime_of_z, denom;
    double z_x, z_y;
    const double EPS = 1.0E-6;
    const double toler = 1.0E-2;

    const unsigned int width  = 2048U;
    const unsigned int height = 2048U;
    const unsigned char max_iters = 0x10U;
    const double x_min = -4.0;
    const double x_max =  4.0;
    const double y_min = -4.0;
    const double y_max =  4.0;
    const double x_factor = (x_max - x_min) / (double)(width - 1U);
    const double y_factor = (y_max - y_min) / (double)(height - 1U);
    const struct color red   = {0xFFU, 0x00U, 0x00U};
    const struct color green = {0x00U, 0xFFU, 0x00U};
    const struct color blue  = {0x00U, 0x00U, 0xFFU};
    const struct color black = {0x00U, 0x00U, 0x00U};
    const complex double root0 =  1.0;
    const complex double root1 = -0.5 + 0.866025403784*(complex double)I;
    const complex double root2 = -0.5 - 0.866025403784*(complex double)I;

    double color_factor;
    unsigned int x, y;
    unsigned char iters;
    struct color current_color;

    FILE *fp = fopen("tmpl_halley_fractal_z3_minus_1.ppm", "w");

    if (!fp)
    {
        puts("fopen failed and returned NULL. Aborting.");
        return -1;
    }
    else
        fprintf(fp, "P6\n%u %u\n255\n", width, height);


    for (y = 0U; y < height; ++y)
    {
        z_y = y_max - (double)y * y_factor;
        for (x = 0U; x < width; ++x)
        {
            z_x = x_min + (double)x * x_factor;
            z = z_x + z_y*(complex double)I;
            iters = 0x00U;

            f_of_z = z*z*z - 1.0;

            while((cabs(f_of_z) > EPS) && (iters < max_iters))
            {
                f_of_z              = z*z*z - 1.0;
                f_prime_of_z        = 3.0*z*z;
                f_double_prime_of_z = 6.0*z;

                denom = 2.0*f_prime_of_z*f_prime_of_z -
                        f_of_z*f_double_prime_of_z;
                z -= 2.0*f_of_z*f_prime_of_z / denom;

                ++iters;
            }
            color_factor = 1.0 - (double)iters / (double)max_iters;

            if (cabs(z - root0) < toler)
                current_color = scale_color(blue, color_factor);
            else if (cabs(z - root1) < toler)
                current_color = scale_color(green, color_factor);
            else if (cabs(z - root2) < toler)
                current_color = scale_color(red, color_factor);
            else
                current_color = black;

            write_color(fp, current_color);
        }
    }

    return 0;
}

