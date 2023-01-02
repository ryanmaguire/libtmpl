#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for determining if three planar vectors are collinear.           */
tmpl_Bool
tmpl_2DFloat_Are_Collinear(const tmpl_TwoVectorFloat *A,
                           const tmpl_TwoVectorFloat *B,
                           const tmpl_TwoVectorFloat *C)
{
    /*  Compute the vectors pointing from A to B and A to C.                  */
    const tmpl_TwoVectorFloat AB = tmpl_2DFloat_Subtract(B, A);
    const tmpl_TwoVectorFloat AC = tmpl_2DFloat_Subtract(C, A);

    /*  Compute the determinant of the matrix [AB | AC].                      */
    const float det = AB.dat[0]*AC.dat[1] - AB.dat[1]*AC.dat[0];

    if (det == 0.0F)
        return tmpl_True;
    else
        return tmpl_False;
}
/*  End of tmpl_2DFloat_Are_Collinear.                                        */
