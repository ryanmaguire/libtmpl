/*
 *  To Compile:
 *      gcc -I../../ -L./ $(pkg-config --cflags --libs cairo) \
 *      kissvg_EuclidBookOnePropOne.c -o test -lcairo -lkissvg
 */

#include <stdio.h>
#include <stdlib.h>
#include <kissvg/include/kissvg.h>

/*  The limits of the coordinates in our computations. These correspond the   *
 *  the maximum (x, y) values we wish to plot.                                */
#define X_MIN -3.0
#define X_MAX  3.0
#define Y_MIN -3.0
#define Y_MAX  3.0

/*  The size of the actual output image.                                      */
#define X_INCHES 3 * 72.0
#define Y_INCHES 2 * 72.0

#define FILENAME "kissvg_ApolloniusProblem"

static void draw(cairo_t *cr)
{
    kissvg_TwoVector center;
    kissvg_Circle *C0, *C1, *C2;
    kissvg_Circle **apo;
    kissvg_Canvas2D *canvas;
    double radius;
    long n, N;
    N = 8;

    canvas = kissvg_CreateCanvas2D(X_INCHES, Y_INCHES, X_MIN, X_MAX,
                                   Y_MIN, Y_MAX, kissvg_True, kissvg_PDF);

    radius = 0.5;
    center = kissvg_NewTwoVector(1.0, 1.0);
    C0 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C0, kissvg_Aqua);
    kissvg_FillDrawCircle2D(cr, C0);

    center = kissvg_NewTwoVector(-1.0, 1.0);
    C1 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C1, kissvg_Aqua);
    kissvg_FillDrawCircle2D(cr, C1);

    center = kissvg_NewTwoVector(0, -1.0);
    C2 = kissvg_CreateCircle(center, radius, canvas);
    kissvg_SetFillColor(C2, kissvg_Aqua);
    kissvg_FillDrawCircle2D(cr, C2);

    apo = kissvg_ApolloniusProblem(C0, C1, C2);
    kissvg_DestroyCircle(C0);
    kissvg_DestroyCircle(C1);
    kissvg_DestroyCircle(C2);

    for (n=0; n<N; ++n)
    {
        C0 = apo[n];
        kissvg_DrawCircle2D(cr, C0);
        kissvg_DestroyCircle(C0);
    }

    kissvg_DestroyCanvas2D(canvas);
    free(apo);
    return;
}

int main (void)
{
    kissvg_GenerateFile(FILENAME, &draw, kissvg_PDF, X_INCHES, Y_INCHES);
    return 0;
}
