
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_vec2.h>
#include <float.h>

/*  Function for determining if three planar vectors are collinear.           */
tmpl_Bool
tmpl_TwoVector_Euclidean_Is_Collinear(tmpl_TwoVector A,
                                      tmpl_TwoVector B,
                                      tmpl_TwoVector C)
{
    /*  The method simply checks the determinant of the matrix formed by      *
     *  the column vectors AB and AC. This is equivalent to seeing if the     *
     *  cross product of AB and AC is zero using the standard embedding of    *
     *  the plane into three dimensional space.                               */
    tmpl_TwoVector AB;
    tmpl_TwoVector AC;
    double ABx, ABy;
    double ACx, ACy;
    double det;

    /*  Compute the vectors pointing from A to B and A to C.                  */
    AB = tmpl_TwoVector_Subtract(B, A);
    AC = tmpl_TwoVector_Subtract(C, A);

    /*  Extract the x and y components of AB.                                 */
    ABx = tmpl_TwoVector_X(AB);
    ABy = tmpl_TwoVector_Y(AB);

    /*  Extract the x and y components of AC.                                 */
    ACx = tmpl_TwoVector_X(AC);
    ACy = tmpl_TwoVector_Y(AC);

    /*  Compute the determinant of the matrix [AB | AC].                      */
    det = ABx*ACy - ABy*ACx;

    if ((det < DBL_MIN) && (-det < DBL_MIN))
        return tmpl_True;
    else
        return tmpl_False;
}
/*  End of tmpl_TwoVector_Euclidean_Is_Collinear.                             */
