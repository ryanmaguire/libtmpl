#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

/*  We'll need the following data types for planar and spherical points.      */
typedef struct root_struct {
    complex double *roots;
    unsigned int n_roots;
} root_struct;

struct color {
    unsigned char red, green, blue;
};

static const double PI = 3.14159265358979323846264338327950288419716;

static complex double f(complex double z, complex double *arr, unsigned int deg)
{
    complex double out;
    unsigned int n;

    out = arr[0];
    for (n = 1U; n <= deg; ++n)
        out = z*out + arr[n];

    return out;
}

static complex double
f_prime(complex double z, complex double *arr, unsigned int deg)
{
    complex double out;
    unsigned int n;

    out = (double)deg*arr[0];
    for (n = 1U; n < deg; ++n)
        out = z*out + (double)deg*arr[n];

    return out;
}

static complex double
f_2prime(complex double z, complex double *arr, unsigned int deg)
{
    complex double out;
    double factor = (double)deg * ((double)deg - 1.0);
    unsigned int n;

    out = factor*arr[0];
    for (n = 1; n < deg-1; ++n)
        out = z*out + factor*arr[n];

    return out;
}

static struct root_struct *get_roots(complex double *arr, unsigned int deg,
                                     unsigned int max_iters)
{
    root_struct *out = malloc(sizeof(*out));
    complex double p, root, f_p, df_p, d2f_p;
    unsigned int m, n, ell, iter, s, N, n_roots;
    double r, theta, factor_1, factor_2, min, temp, s_double, N_double;

    out->roots = malloc(sizeof(*out->roots) * deg);

    s_double = ceil(0.26632*log((double)deg));
    N_double = ceil(8.32547*deg*log((double)deg));

    s = (unsigned int)s_double;
    N = (unsigned int)N_double;
    n_roots = 0;

    factor_1 = 1.0+sqrt(2);
    factor_2 = (deg-1.0)/deg;

    root = 0.0;
    for (m=0; m<s; ++m)
    {
        if (n_roots >= deg)
            break;

        r = factor_1 + pow(factor_2, (2*m+1)/(4*s));

        for (n=0; n<N; ++n)
        {
            if (n_roots >= deg)
                break;

            theta = 2*PI*n/N;
            p = r * (cos(theta) + (complex double)_Complex_I*sin(theta));

            for (iter=0; iter < max_iters; ++iter)
            {
                f_p = f(p, arr, deg);
                df_p = f_prime(p, arr, deg);
                d2f_p = f_2prime(p, arr, deg);
                root = p - 2*f_p * df_p / (2*df_p*df_p - f_p * d2f_p);
                if (cabs(f(root, arr, deg)) < 1.0e-10)
                    break;

                p = root;
            }

            if (cabs(f(root, arr, deg)) < 1.0e-8)
            {
                if (n_roots == 0)
                {
                    n_roots += 1;
                    out->roots[0] = root;
                }
                else
                {
                    min = cabs(root - out->roots[0]);
                    for (ell=1; ell<n_roots; ++ell)
                    {
                        temp = cabs(root - out->roots[ell]);
                        if (temp < min)
                            min = temp;
                    }
                    if (min >= 0.000001)
                    {
                        out->roots[n_roots] = root;
                        n_roots += 1;
                    }
                }
            }
        }
    }

    if (n_roots == 0)
    {
        puts("\nError:");
        puts("\tFailed to find the roots. Aborting.\n");
        exit(0);
    }
    else
        out->n_roots = n_roots;

    printf("Number of roots: %d\n", n_roots);
    for (n=0; n<n_roots; ++n)
        printf(
            "\troot %d: %f + i%f\n", n,
            creal(out->roots[n]), cimag(out->roots[n])
        );

    return out;
}

static void write_color(FILE *fp, struct color c)
{
    fputc(c.red,   fp);
    fputc(c.green, fp);
    fputc(c.blue,  fp);
}

static struct color scale_color(struct color c, double t)
{
    struct color out;
    out.red   = (unsigned char)(t * (double)c.red);
    out.green = (unsigned char)(t * (double)c.green);
    out.blue  = (unsigned char)(t * (double)c.blue);
    return out;
}

int main(void)
{
    /*  Declare a variable for the output file and give it write permission.  */
    FILE *fp;
    fp = fopen("halley_fractal.ppm", "w");

    const unsigned int size = 1024U;
    const unsigned int MaxIters = 32;
    const unsigned int root_finder_max_iter = 200;
    #define deg 10U
    complex double coeffs[deg+1] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1};

    /*  Struct for the roots.                                                 */
    root_struct *roots_of_f = get_roots(coeffs, deg, root_finder_max_iter);

    complex double f_z, df_z, d2f_z;
    unsigned int n_roots = roots_of_f->n_roots;
    complex double *roots = roots_of_f->roots;

    /*  Values for the min and max of the x and y axes.                       */
    const double x_min = -1.0;
    const double x_max =  1.0;
    const double y_min = -1.0;
    const double y_max =  1.0;

    /*  Factor for giving the image a gradient.                               */
    unsigned char factor = 255/MaxIters;

    /* Dummy variables to loop over.                                          */
    unsigned int iters, ind, n;

    /*  More dummy variables to loop over.                                    */
    unsigned int x, y;
    double z_x, z_y, min, temp, scale;
    complex double z, root;

    fprintf(fp, "P6\n%d %d\n255\n", size, size);

    struct color current_color;
    const struct color black = {0x00U, 0x00U, 0x00U};
    struct color colors[14] = {
        {0xFFU, 0x00U, 0x1FU},  /*  Red.           */
        {0x00U, 0xFFU, 0x1FU},  /*  Green.         */
        {0x00U, 0x1FU, 0xFFU},  /*  Blue.          */
        {0xFFU, 0xFFU, 0x33U},  /*  Yellow.        */
        {0x80U, 0xD4U, 0xFFU},  /*  Light Blue.    */
        {0xFFU, 0x1DU, 0xCCU},  /*  Magenta.       */
        {0x00U, 0x80U, 0x80U},  /*  Teal.          */
        {0xFFU, 0x00U, 0xFFU},  /*  Purple.        */
        {0xFFU, 0x55U, 0x00U},  /*  Orange.        */
        {0x4DU, 0xFFU, 0xC3U},  /*  Turquoise.     */
        {0x00U, 0x80U, 0x6AU},  /*  Pine.          */
        {0xFFU, 0xBFU, 0xB3U},  /*  Melon.         */
        {0xFFU, 0xB3U, 0xE6U},  /*  Mauve.         */
        {0x66U, 0x43U, 0x66U}   /*  Midnight blue. */
    };

    for (y=0; y<size; ++y)
    {
        z_y = y * (y_max - y_min)/(size - 1) + y_min;
        z_y = -z_y;

        for (x=0; x<size; ++x)
        {
            z_x = x * (x_max - x_min)/(size - 1) + x_min;
            z = z_x + (complex double)_Complex_I*z_y;

            /*  Allow MaxIters number of iterations of Newton-Raphson.        */
            for (iters=0; iters<MaxIters; ++iters)
            {
                /*  Perfrom Halley's Method on the polynomial f.              */
                f_z = f(z, coeffs, deg);
                df_z = f_prime(z, coeffs, deg);
                d2f_z = f_2prime(z, coeffs, deg);
                root = z - 2*f_z * df_z / (2*df_z*df_z - f_z * d2f_z);

                /*  Checks for convergence.                                   */
                if (cabs(root - z) < 10e-10)
                    break;

                z = root;
            }

            /*  Find which roots the final iteration is closest too.          */
            min = cabs(z-roots[0]);
            ind = 0;

            for (n=1; n<n_roots; ++n)
            {
                temp = cabs(z - roots[n]);
                if (temp < min)
                {
                    min = temp;
                    ind = n;
                }
            }

            if (min > 0.1)
                current_color = black;
            else
            {
                scale = (255.0-factor*iters)/255.0;
                current_color = scale_color(colors[ind], scale);
            }
            write_color(fp, current_color);
        }
    }

    /*  Free the memory allocated to colors before returning.                 */
    free(roots_of_f->roots);
    free(roots_of_f);
    return 0;
}
