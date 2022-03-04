/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Absolute value function found here.                                       */
#include <libtmpl/include/tmpl_math.h>
#include <math.h>
#include <float.h>

double
tmpl_3DDouble_Laplacian(tmpl_3DDouble_Functional f, tmpl_ThreeVectorDouble P)
{
    const double h = pow(DBL_EPSILON, 0.25) * tmpl_3DDouble_Norm(P);
    const double f2 = 30.0*f(P);
    double f0, f1, f3, f4, lapx, lapy, lapz;
    tmpl_ThreeVectorDouble Q;

    Q.dat[1] = P.dat[1];
    Q.dat[2] = P.dat[2];

    Q.dat[0] = P.dat[0] + 2.0*h;
    f0 = f(Q);

    Q.dat[0] = P.dat[0] + h;
    f1 = 16.0*f(Q);

    Q.dat[0] = P.dat[0] - h;
    f3 = 16.0*f(Q);

    Q.dat[0] = P.dat[0] - 2.0*h;
    f4 = f(Q);

    lapx = (-f0 + f1 - f2 + f3 - f4) / (12.0 * h * h);
    Q.dat[0] = P.dat[0];

    Q.dat[1] = P.dat[1] + 2.0*h;
    f0 = f(Q);
    Q.dat[1] = P.dat[1] + h;
    f1 = 16.0*f(Q);
    Q.dat[1] = P.dat[1] - h;
    f3 = 16.0*f(Q);
    Q.dat[1] = P.dat[1] - 2.0*h;
    f4 = f(Q);

    lapy = (-f0 + f1 - f2 + f3 - f4) / (12.0 * h * h);

    Q.dat[1] = P.dat[1];

    Q.dat[2] = P.dat[2] + 2.0*h;
    f0 = f(Q);
    Q.dat[2] = P.dat[2] + h;
    f1 = 16.0*f(Q);
    Q.dat[2] = P.dat[2] - h;
    f3 = 16.0*f(Q);
    Q.dat[2] = P.dat[2] - 2.0*h;
    f4 = f(Q);

    lapz = (-f0 + f1 - f2 + f3 - f4) / (12.0 * h * h);
    return lapx + lapy + lapz;
}
