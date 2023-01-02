#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for determining if three planar vectors are collinear.           */
tmpl_Bool
tmpl_2DLDouble_Are_Collinear(const tmpl_TwoVectorLongDouble *A,
                             const tmpl_TwoVectorLongDouble *B,
                             const tmpl_TwoVectorLongDouble *C)
{
    /*  Compute the vectors pointing from A to B and A to C.                  */
    const tmpl_TwoVectorLongDouble AB = tmpl_2DLDouble_Subtract(B, A);
    const tmpl_TwoVectorLongDouble AC = tmpl_2DLDouble_Subtract(C, A);

    /*  Compute the determinant of the matrix [AB | AC].                      */
    const long double det = AB.dat[0]*AC.dat[1] - AB.dat[1]*AC.dat[0];

    if (det == 0.0L)
        return tmpl_True;
    else
        return tmpl_False;
}
/*  End of tmpl_2DLDouble_Are_Collinear.                                      */
