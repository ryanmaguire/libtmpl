#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for determining if three planar vectors are collinear.           */
tmpl_Bool
tmpl_2DDouble_Are_Collinear(const tmpl_TwoVectorDouble *A,
                            const tmpl_TwoVectorDouble *B,
                            const tmpl_TwoVectorDouble *C)
{
    /*  Compute the vectors pointing from A to B and A to C.                  */
    const tmpl_TwoVectorDouble AB = tmpl_2DDouble_Subtract(B, A);
    const tmpl_TwoVectorDouble AC = tmpl_2DDouble_Subtract(C, A);

    /*  Compute the determinant of the matrix [AB | AC].                      */
    const double det = AB.dat[0]*AC.dat[1] - AB.dat[1]*AC.dat[0];

    if (det == 0.0)
        return tmpl_True;
    else
        return tmpl_False;
}
/*  End of tmpl_2DDouble_Are_Collinear.                                       */
