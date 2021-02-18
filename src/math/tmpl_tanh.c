/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

float tmpl_Float_Tanh(float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float tanh_x;

    /*  The definition of than(x) is sinh(x)/cosh(x), so return this.         */
    tanh_x = tmpl_Float_Sinh(x) / tmpl_Float_Cosh(-x);
    return tanh_x;
}

double tmpl_Double_Tanh(double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double tanh_x;

    /*  The definition of than(x) is sinh(x)/cosh(x), so return this.         */
    tanh_x = tmpl_Double_Sinh(x) / tmpl_Double_Cosh(-x);
    return tanh_x;
}

long double tmpl_LDouble_Tanh(long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double tanh_x;

    /*  The definition of than(x) is sinh(x)/cosh(x), so return this.         */
    tanh_x = tmpl_LDouble_Sinh(x) / tmpl_LDouble_Cosh(-x);
    return tanh_x;
}
