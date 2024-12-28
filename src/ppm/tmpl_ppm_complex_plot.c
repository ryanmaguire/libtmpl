
/*  Avoid silly warning on Windows for using fopen. GNU/Linux, FreeBSD, and   *
 *  macOS have no such warnings for using standard library functions.         */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include <string.h>
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_complex.h>
#include <libtmpl/include/tmpl_ppm.h>

void tmpl_PPM_Complex_Plot(const char *func_name,
                           tmpl_ComplexDouble(*func)(tmpl_ComplexDouble),
                           unsigned int x_size, unsigned int y_size,
                           const double x_min, const double x_max,
                           const double y_min, const double y_max)
{
    unsigned int x, y;
    FILE *fp[4];
    char re_file[256], im_file[256], arg_file[256], mag_file[256];
    double x_rcp_factor, y_rcp_factor;
    tmpl_ComplexDouble z, w;
    double z_x, z_y, w_x, w_y;
    double arg, mag;

    if (func_name == NULL)
    {
        puts("Error Encountered: libtmpl\n"
             "\ttmpl_Easy_Complex_Plots\n\n"
             "Input func_name string is NULL. Aborting.\n");
        return;
    }

    /*  Silly check to make sure the user provided a valid range for x and y. */
    if (x_max <= x_min)
    {
        puts("Error Encountered: libtmpl\n"
             "\ttmpl_Easy_Complex_Plots.c\n\n"
             "x_min is greater than or equal to x_max.\n");
        return;
    }
    else if (y_max <= y_min)
    {
        puts("Error Encountered: libtmpl\n"
             "\ttmpl_Easy_Complex_Plots.c\n\n"
             "y_min is greater than or equal to y_max.\n");
        return;
    }

    /*  Another silly error check to make sure size is greater than 1.        */
    if ((x_size == 0) || (y_size == 0))
    {
        puts("Error Encountered: libtmpl\n"
             "\ttmpl_Easy_Complex_Plots.c\n\n"
             "Input size is zero. Aborting computation.\n");
        return;
    }
    else if ((x_size == 1) || (y_size == 1))
    {
        puts("Error Encountered: libtmpl\n"
             "\ttmpl_Easy_Complex_Plots.c\n\n"
             "Input size is one. This will cause divide-by-zero.\n"
             "Aborting computation.\n");
        return;
    }

    x_rcp_factor = 1.0/(x_size - 1.0);
    y_rcp_factor = 1.0/(y_size - 1.0);

    strcpy(re_file, func_name);
    strcpy(im_file, func_name);
    strcpy(mag_file, func_name);
    strcpy(arg_file, func_name);
    strcat(re_file, "_real.ppm");
    strcat(im_file, "_imag.ppm");
    strcat(mag_file, "_mag.ppm");
    strcat(arg_file, "_arg.ppm");

    fp[0] = fopen(re_file, "w");
    fp[1] = fopen(im_file, "w");
    fp[2] = fopen(mag_file, "w");
    fp[3] = fopen(arg_file, "w");

    /*  Needed to create the output ppm file. This is the preamble.           */
    fprintf(fp[0], "P6\n%d %d\n255\n", x_size, y_size);
    fprintf(fp[1], "P6\n%d %d\n255\n", x_size, y_size);
    fprintf(fp[2], "P6\n%d %d\n255\n", x_size, y_size);
    fprintf(fp[3], "P6\n%d %d\n255\n", x_size, y_size);

    for (y=0; y<y_size; ++y)
    {
        /*  We want to center z_y so scale and shift. This makes the output   *
         *  picture lie in the box [x_min, x_max] x [y_min, y_max].           */
        z_y = (y_size - y - 1.0) * (y_max - y_min) * y_rcp_factor + y_min;

        for (x=0; x<x_size; ++x)
        {
            /*  Similarly, center z_x.                                        */
            z_x = x * (x_max - x_min) * x_rcp_factor + x_min;

            /*  Set z to x+iy.                                                */
            z = tmpl_CDouble_Rect(z_x, z_y);

            /*  Compute the complex cosine of z.                              */
            w = func(z);

            /*  Extract the real and imaginary parts of w.                    */
            w_x = tmpl_CDouble_Real_Part(w);
            w_y = tmpl_CDouble_Imag_Part(w);
            arg = tmpl_CDouble_Argument(w);
            mag = tmpl_CDouble_Abs(w);

            /*  Color the current pixel.                                      */
            tmpl_PPM_Write_Color(fp[0], tmpl_PPM_Scaled_Gradient(w_x));
            tmpl_PPM_Write_Color(fp[1], tmpl_PPM_Scaled_Gradient(w_y));
            tmpl_PPM_Write_Color(fp[2], tmpl_PPM_Scaled_Gradient(mag));
            tmpl_PPM_Write_Color(
                fp[3], tmpl_PPM_Linear_Gradient(arg, -tmpl_Double_Pi, tmpl_Double_Pi)
            );
        }
    }
}
