/*  The C Standard Library header for math functions and more found here.     */
#include <libtmpl/include/tmpl_math.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_special_functions.h>

float tmpl_Float_LambertW(float x)
{
    float EPS = 1.0e-4F;
    float x0, dx, exp_x0;
    if ((x < tmpl_Infinity_F) && (x>-tmpl_Rcpr_Euler_E_F))
    {
        if (x > 2.0F)
            x0 = tmpl_Float_Log(x/tmpl_Float_Log(x));
        else if (x > -tmpl_Rcpr_Euler_E_F)
            x0 = x;
        else if (x == -tmpl_Rcpr_Euler_E_F)
            return -1.0F;
        else
            return tmpl_NaN_F;

        exp_x0 = tmpl_Float_Exp(x0);
        dx = (x0*exp_x0-x)/(exp_x0*(x0+1.0F) -
                            (x0+2.0F)*(x0*exp_x0-x)/(2.0F*x0+2.0F));
        x0 = x0 - dx;

        while (tmpl_Float_Abs(dx) > EPS)
        {
            exp_x0 = tmpl_Float_Exp(x0);
            dx = (x0*exp_x0-x)/(exp_x0*(x0+1.0F) -
                                (x0+2.0F)*(x0*exp_x0-x)/(2.0F*x0+2.0F));
            x0 = x0 - dx;
        }
        return x0;
    }
    else if (x==-tmpl_Rcpr_Euler_E_F)
        return -1.0F;
    else if (x<-tmpl_Rcpr_Euler_E_F)
        return tmpl_NaN_F;
    else
        return tmpl_Infinity_F;
}

double tmpl_Double_LambertW(double x)
{
    double EPS = 1.0e-8;
    double x0, dx, exp_x0;
    if ((x < tmpl_Infinity) && (x>-tmpl_Rcpr_Euler_E))
    {
        if (x > 2.0){
            x0 = tmpl_Double_Log(x/tmpl_Double_Log(x));
        }
        else if (x > -tmpl_Rcpr_Euler_E){
            x0 = x;
        }
        else if (x == -tmpl_Rcpr_Euler_E){
            return -1.0;
        }
        else {
            return tmpl_NaN;
        }
        exp_x0 = tmpl_Double_Exp(x0);
        dx = (x0*exp_x0-x)/(exp_x0*(x0+1.0) -
                            (x0+2.0)*(x0*exp_x0-x)/(2.0*x0+2.0));
        x0 = x0 - dx;
        while (tmpl_Double_Abs(dx) > EPS)
        {
            exp_x0 = tmpl_Double_Exp(x0);
            dx = (x0*exp_x0-x)/(exp_x0*(x0+1.0) -
                                (x0+2.0)*(x0*exp_x0-x)/(2.0*x0+2.0));
            x0 = x0 - dx;
        }
        return x0;
    }
    else if (x==-tmpl_Rcpr_Euler_E)
        return -1.0;
    else if (x<-tmpl_Rcpr_Euler_E)
        return tmpl_NaN;
    else
        return tmpl_Infinity;
}

long double tmpl_LDouble_LambertW(long double x)
{
    long double EPS = 1.0e-16;
    long double x0, dx, exp_x0;
    if ((x < tmpl_Infinity_L) && (x>-tmpl_Rcpr_Euler_E))
    {
        if (x > 2.0){
            x0 = tmpl_LDouble_Log(x/tmpl_LDouble_Log(x));
        }
        else if (x > -tmpl_Rcpr_Euler_E){
            x0 = x;
        }
        else if (x == -tmpl_Rcpr_Euler_E){
            return -1.0;
        }
        else {
            return tmpl_NaN_L;
        }
        exp_x0 = tmpl_LDouble_Exp(x0);
        dx = (x0*exp_x0-x)/(exp_x0*(x0+1.0) -
                            (x0+2.0)*(x0*exp_x0-x)/(2.0*x0+2.0));
        x0 = x0 - dx;
        while (tmpl_LDouble_Abs(dx) > EPS){
            exp_x0 = tmpl_LDouble_Exp(x0);
            dx = (x0*exp_x0-x)/(exp_x0*(x0+1.0) -
                                (x0+2.0)*(x0*exp_x0-x)/(2.0*x0+2.0));
            x0 = x0 - dx;
        }
        return x0;
    }
    else if (x==-tmpl_Rcpr_Euler_E)
        return -1.0;
    else if (x<-tmpl_Rcpr_Euler_E)
        return tmpl_NaN_L;
    else
        return tmpl_Infinity_L;
}
