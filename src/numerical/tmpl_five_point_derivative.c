#include <libtmpl/include/tmpl_numerical.h>

float tmpl_Float_Five_Point_Derivative(float (*f)(float), float x, float h)
{
    float y0, y1 ,y2, y3, der;

    y0 = -f(x + 2.0F*h);
    y1 =  8.0F * f(x + h);
    y2 = -8.0F * f(x - h);
    y3 = f(x - 2.0F * h);

    der = (y0 + y1 + y2 + y3)/(12.0F * h);

    return der;
}

double
tmpl_Double_Five_Point_Derivative(double (*f)(double), double x, double h)
{
    double y0, y1 ,y2, y3, der;

    y0 = -f(x + 2.0*h);
    y1 =  8.0*f(x + h);
    y2 = -8.0*f(x - h);
    y3 = f(x - 2.0*h);

    der = (y0 + y1 + y2 + y3)/(12.0*h);

    return der;
}

long double
tmpl_LDouble_Five_Point_Derivative(long double (*f)(long double),
                                   long double x, long double h)
{
    long double y0, y1 ,y2, y3, der;

    y0 = -f(x + 2.0L*h);
    y1 =  8.0L*f(x + h);
    y2 = -8.0L*f(x - h);
    y3 = f(x - 2.0L*h);

    der = (y0 + y1 + y2 + y3)/(12.0L*h);

    return der;
}
