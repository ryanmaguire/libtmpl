/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_window_functions.h>

float tmpl_Float_Rect_Window(float x, float W)
{
    float abs_x, rect_x;

    abs_x = tmpl_Float_Abs(x);

    if (abs_x <= 0.5F*W)
        rect_x = 1.0F;
    else
        rect_x = 0.0F;

    return rect_x;
}


double tmpl_Double_Rect_Window(double x, double W)
{
    double abs_x, rect_x;

    abs_x = tmpl_Double_Abs(x);

    if (abs_x <= 0.5*W)
        rect_x = 1.0;
    else
        rect_x = 0.0;

    return rect_x;
}


long double tmpl_LDouble_Rect_Window(long double x, long double W)
{
    long double abs_x, rect_x;

    abs_x = tmpl_LDouble_Abs(x);

    if (abs_x <= 0.5L*W)
        rect_x = 1.0L;
    else
        rect_x = 0.0L;

    return rect_x;
}

