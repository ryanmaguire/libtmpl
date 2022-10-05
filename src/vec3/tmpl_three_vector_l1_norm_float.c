/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Absolute value function found here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  Function for computing the L1 norm of a 3D vector at single precision.    */
float tmpl_3DFloat_L1_Norm(tmpl_ThreeVectorFloat P)
{
    return tmpl_Float_Abs(P.dat[0]) +
           tmpl_Float_Abs(P.dat[1]) +
           tmpl_Float_Abs(P.dat[2]);
}
/*  End of tmpl_3DFloat_L1_Norm.                                              */
