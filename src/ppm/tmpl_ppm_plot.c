
/*  Avoid silly warning on Windows for using fopen. GNU/Linux, FreeBSD, and   *
 *  macOS have no such warnings for using standard library functions.         */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_ppm.h>

/*  Routine for plotting the absolute value function.                         */
void tmpl_PPM_Plot(const char *filename,
                   double (*f)(double),
                   unsigned int x_size,
                   unsigned int y_size,
                   double x_min,
                   double x_max)
{
    /*  Declare variables for the pixel (x, y).                               */
    unsigned int x, y;

    const double start = (x_min < x_max ? x_min : x_max);
    const double end = (x_min < x_max ? x_max : x_min);
    const double dx = (end - start) / (double)(x_size - 1U);
    const double xaxis_thickness = 2.0*dx;

    /*  Declare a pointer for f(x) where x varies over [x_min, x_max].        */
    double *f_of;

    /*  Lastly, declare two variables used later in the computation.          */
    double diff, draw_thickness, yaxis_thickness;
    double yval, rcp_factor_y, dy;
    double xval = start;
    double y_min = 0.0;
    double y_max = 0.0;

    /*  Create the file and give it write permissions.                        */
    FILE *fp = fopen(filename, "w");

    if (!fp)
        return;

    /*  Allocate memory for the five variables.                               */
    f_of = malloc(sizeof(*f_of) * x_size);

    if (!f_of)
    {
        fclose(fp);
        return;
    }

    /*  Needed to create the output pgm file. This is the preamble.           */
    fprintf(fp, "P5\n%d %d\n255\n", x_size, y_size);

    for (x = 0U; x < x_size; ++x)
    {
        f_of[x] = f(xval);

        if (f_of[x] < y_min)
            y_min = f_of[x];

        if (f_of[x] > y_max)
            y_max = f_of[x];

        xval += dx;
    }

    dy = 0.05 * (y_max - y_min);
    y_max += dy;
    y_min -= dy;

    rcp_factor_y = (y_max - y_min) / (double)(y_size - 1U);
    draw_thickness = 1.5*rcp_factor_y;
    yaxis_thickness = 2.0*rcp_factor_y;

    /*  Loop over each pixel and color it based on the value |y - |x||.       */
    for (y = 0U; y < y_size; ++y)
    {
        yval = (y_size - y - 1.0) * rcp_factor_y + y_min;

        /*  Loop over all of the x pixels.                                    */
        for (x = 0U; x < x_size; ++x)
        {
            xval = tmpl_Double_Abs(x*dx + x_min);
            diff = tmpl_Double_Abs(yval - f_of[x]);

            /*  Color in the x-axis.                                          */
            if (xval < xaxis_thickness)
                fputc(tmpl_PGM_Gray, fp);

            /*  Color in the y-axis.                                          */
            else if (tmpl_Double_Abs(yval) < yaxis_thickness)
                fputc(tmpl_PGM_Gray, fp);

            /*  Color in the function y = |x|.                                */
            else if (diff < draw_thickness)
                fputc(tmpl_PGM_White, fp);

            /*  Otherwise, color the background black.                        */
            else
                fputc(tmpl_PGM_Black, fp);
        }
        /*  End of looping over the x variable.                               */
    }
    /*  End of looping over the y variable.                                   */

    /*  Close the file.                                                       */
    fclose(fp);
    free(f_of);
}
/*  End of tmpl_Easy_Real_Plots.                                              */
