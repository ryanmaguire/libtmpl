/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_FRESNEL_DIFFRACTION_H
#define TMPL_FRESNEL_DIFFRACTION_H

/*  Complex numbers defined here.                                             */
#include <libtmpl/include/tmpl_complex.h>

/*  If using with C++ (and not C) we need to wrap the entire header file in   *
 *  an extern "C" statement. Check if C++ is being used with __cplusplus.     */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_Fresnel_Diffraction_Well                                 *
 *  Purpose:                                                                  *
 *      Computes the Fresnel diffraction profile of a square well.            *
 *  Argument:                                                                 *
 *      double x:                                                             *
 *          The coordinate of the real axis the profile is being computed at. *
 *      double left_edge:                                                     *
 *          The x-coordinate of the left edge of the square well.             *
 *      double right_edge:                                                    *
 *          The y-coordinate of the right edge of the square well.            *
 *      double fresnel_scale:                                                 *
 *          The Fresnel scale, in the same units as left_edge and right_edge, *
 *          of the wave of light incident on the square well.                 *
 *  Outputs:                                                                  *
 *      tmpl_ComplexDouble T:                                                 *
 *          The complex optical transmittance at the point x.                 *
 ******************************************************************************/
extern tmpl_ComplexFloat
tmpl_CFloat_Fresnel_Diffraction_Well(float x,
                                     float left_edge,
                                     float right_edge,
                                     float fresnel_scale);

extern tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Diffraction_Well(double x,
                                      double left_edge,
                                      double right_edge,
                                      double fresnel_scale);

extern tmpl_ComplexLongDouble
tmpl_CLDouble_Fresnel_Diffraction_Well(long double x,
                                       long double left_edge,
                                       long double right_edge,
                                       long double fresnel_scale);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Fresnel_Diffraction_Well_Phase                            *
 *  Purpose:                                                                  *
 *      Computes the phase of the Fresnel diffraction of a square well.       *
 *  Argument:                                                                 *
 *      double x:                                                             *
 *          The coordinate of the real axis the profile is being computed at. *
 *      double left_edge:                                                     *
 *          The x-coordinate of the left edge of the square well.             *
 *      double right_edge:                                                    *
 *          The y-coordinate of the right edge of the square well.            *
 *      double fresnel_scale:                                                 *
 *          The Fresnel scale, in the same units as left_edge and right_edge, *
 *          of the wave of light incident on the square well.                 *
 *  Outputs:                                                                  *
 *      double theta:                                                         *
 *          The phase of the complex profile at the point x.                  *
 ******************************************************************************/
extern float
tmpl_Float_Fresnel_Diffraction_Well_Phase(float x,
                                          float left_edge,
                                          float right_edge,
                                          float fresnel_scale);

extern double
tmpl_Double_Fresnel_Diffraction_Well_Phase(double x,
                                           double left_edge,
                                           double right_edge,
                                           double fresnel_scale);

extern double
tmpl_LDouble_Fresnel_Diffraction_Well_Phase(long double x,
                                            long double left_edge,
                                            long double right_edge,
                                            long double fresnel_scale);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_Fresnel_Diffraction_Gap                                  *
 *  Purpose:                                                                  *
 *      Computes the Fresnel diffraction profile of a square gap.             *
 *  Argument:                                                                 *
 *      double x:                                                             *
 *          The coordinate of the real axis the profile is being computed at. *
 *      double left_edge:                                                     *
 *          The x-coordinate of the left edge of the square well.             *
 *      double right_edge:                                                    *
 *          The y-coordinate of the right edge of the square well.            *
 *      double fresnel_scale:                                                 *
 *          The Fresnel scale, in the same units as left_edge and right_edge, *
 *          of the wave of light incident on the square well.                 *
 *  Outputs:                                                                  *
 *      tmpl_ComplexDouble T:                                                 *
 *          The complex optical transmittance at the point x.                 *
 ******************************************************************************/
extern tmpl_ComplexFloat
tmpl_CFloat_Fresnel_Diffraction_Gap(float x,
                                    float left_edge,
                                    float right_edge,
                                    float fresnel_scale);

extern tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Diffraction_Gap(double x,
                                     double left_edge,
                                     double right_edge,
                                     double fresnel_scale);

extern tmpl_ComplexLongDouble
tmpl_CLDouble_Fresnel_Diffraction_Gap(long double x,
                                      long double left_edge,
                                      long double right_edge,
                                      long double fresnel_scale);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Fresnel_Diffraction_Gap_Phase                             *
 *  Purpose:                                                                  *
 *      Computes the phase of the Fresnel diffraction of a square gap.        *
 *  Argument:                                                                 *
 *      double x:                                                             *
 *          The coordinate of the real axis the profile is being computed at. *
 *      double left_edge:                                                     *
 *          The x-coordinate of the left edge of the square well.             *
 *      double right_edge:                                                    *
 *          The y-coordinate of the right edge of the square well.            *
 *      double fresnel_scale:                                                 *
 *          The Fresnel scale, in the same units as left_edge and right_edge, *
 *          of the wave of light incident on the square well.                 *
 *  Outputs:                                                                  *
 *      double theta:                                                         *
 *          The phase of the complex profile at the point x.                  *
 ******************************************************************************/
extern float
tmpl_Float_Fresnel_Diffraction_Gap_Phase(float x,
                                         float left_edge,
                                         float right_edge,
                                         float fresnel_scale);

extern double
tmpl_Double_Fresnel_Diffraction_Gap_Phase(double x,
                                          double left_edge,
                                          double right_edge,
                                          double fresnel_scale);

extern double
tmpl_LDouble_Fresnel_Diffraction_Gap_Phase(long double x,
                                           long double left_edge,
                                           long double right_edge,
                                           long double fresnel_scale);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_Fresnel_Diffraction_Left_Straightedge                    *
 *  Purpose:                                                                  *
 *      Computes the Fresnel diffraction profile of a straight-edge.          *
 *  Argument:                                                                 *
 *      double x:                                                             *
 *          The coordinate of the real axis the profile is being computed at. *
 *      double edge:                                                          *
 *          The x-coordinate of the edge of the straight-edge.                *
 *      double fresnel_scale:                                                 *
 *          The Fresnel scale, in the same units as left_edge and right_edge, *
 *          of the wave of light incident on the square well.                 *
 *  Outputs:                                                                  *
 *      tmpl_ComplexDouble T:                                                 *
 *          The complex optical transmittance at the point x.                 *
 ******************************************************************************/
extern tmpl_ComplexFloat
tmpl_CFloat_Fresnel_Diffraction_Left_Straightedge(float x,
                                                  float edge,
                                                  float fresnel_scale);

extern tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Diffraction_Left_Straightedge(double x,
                                                   double edge,
                                                   double fresnel_scale);

extern tmpl_ComplexLongDouble
tmpl_CLDouble_Fresnel_Diffraction_Left_Straightedge(long double x,
                                                    long double edge,
                                                    long double fresnel_scale);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_Fresnel_Diffraction_Right_Straightedge                   *
 *  Purpose:                                                                  *
 *      Computes the Fresnel diffraction profile of a straight-edge.          *
 *  Argument:                                                                 *
 *      double x:                                                             *
 *          The coordinate of the real axis the profile is being computed at. *
 *      double edge:                                                          *
 *          The x-coordinate of the edge of the straight-edge.                *
 *      double fresnel_scale:                                                 *
 *          The Fresnel scale, in the same units as left_edge and right_edge, *
 *          of the wave of light incident on the square well.                 *
 *  Outputs:                                                                  *
 *      tmpl_ComplexDouble T:                                                 *
 *          The complex optical transmittance at the point x.                 *
 ******************************************************************************/
extern tmpl_ComplexFloat
tmpl_CFloat_Fresnel_Diffraction_Right_Straightedge(float x,
                                                   float edge,
                                                   float fresnel_scale);

extern tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Diffraction_Right_Straightedge(double x,
                                                    double edge,
                                                    double fresnel_scale);

extern tmpl_ComplexLongDouble
tmpl_CLDouble_Fresnel_Diffraction_Right_Straightedge(long double x,
                                                     long double edge,
                                                     long double fresnel_scale);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_Fresnel_Diffraction_Square_Wave                          *
 *  Purpose:                                                                  *
 *      Computes the Fresnel diffraction profile of a square wave.            *
 *  Argument:                                                                 *
 *      double x:                                                             *
 *          The coordinate of the real axis the profile is being computed at. *
 *      double well_width:                                                    *
 *          The width of the individual square wells.                         *
 *      double fresnel_scale:                                                 *
 *          The Fresnel scale, in the same units as well_width,               *
 *          of the wave of light incident on the square well.                 *
 *      unsigned int number_of_wells:                                         *
 *          The number of wells comprising the wave.                          *
 *  Outputs:                                                                  *
 *      tmpl_ComplexDouble T:                                                 *
 *          The complex optical transmittance at the point x.                 *
 ******************************************************************************/
extern tmpl_ComplexFloat
tmpl_CFloat_Fresnel_Diffraction_Square_Wave(float x,
                                            float well_width,
                                            float fresnel_scale,
                                            unsigned int number_of_wells);

extern tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Diffraction_Square_Wave(double x,
                                             double well_width,
                                             double fresnel_scale,
                                             unsigned int number_of_wells);

extern tmpl_ComplexLongDouble
tmpl_CLDouble_Fresnel_Diffraction_Square_Wave(long double x,
                                              long double well_width,
                                              long double fresnel_scale,
                                              unsigned int number_of_wells);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
