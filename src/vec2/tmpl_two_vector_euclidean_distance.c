
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_vec2.h>

double tmpl_TwoVector_Euclidean_Distance(tmpl_TwoVector A, tmpl_TwoVector B)
{
    /*  Extract the x and y components of A.                                  */
    const double Ax = tmpl_TwoVector_X(A);
    const double Ay = tmpl_TwoVector_Y(A);

    /*  Extract the x and y components of B.                                  */
    const double Bx = tmpl_TwoVector_X(B);
    const double By = tmpl_TwoVector_Y(B);

    /*  Compute the distance in the x and y components.                       */
    const double dx = Ax - Bx;
    const double dy = Ay - By;

    /*  Use the Pythagorean formula to compute the distance and return.       */
    return tmpl_Double_Sqrt(dx*dx + dy*dy);
}
/*  End of tmpl_TwoVector_Euclidean_Distance                                  */
