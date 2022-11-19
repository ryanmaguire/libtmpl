#ifndef TMPL_OPTICS_H
#define TMPL_OPTICS_H

/*  The speed of light in km/s.                                               */
#define tmpl_Speed_Of_Light_KMS_F  299792.4580F
#define tmpl_Speed_Of_Light_KMS    299792.4580
#define tmpl_Speed_Of_Light_KMS_L  299792.4580L

#include <libtmpl/include/tmpl_complex.h>

TMPL_EXPORT extern float
Fresnel_Scale_Float(float lambda, float d, float phi, float b);

TMPL_EXPORT extern double
Fresnel_Scale_Double(double lambda, double d, double phi, double b);

TMPL_EXPORT extern long double
Fresnel_Scale_LDouble(long double lambda, long double d,
                      long double phi, long double b);

TMPL_EXPORT extern float tmpl_Float_Resolution_Inverse(float x);
TMPL_EXPORT extern double tmpl_Double_Resolution_Inverse(double x);
TMPL_EXPORT extern long double tmpl_LDouble_Resolution_Inverse(long double x);

TMPL_EXPORT extern float tmpl_Float_Wavelength_To_Wavenumber(float x);
TMPL_EXPORT extern double tmpl_Double_Wavelength_To_Wavenumber(double x);
TMPL_EXPORT extern long double tmpl_LDouble_Wavelength_To_Wavenumber(long double x);

extern float tmpl_Float_Frequency_To_Wavelength(float x);
extern double tmpl_Double_Frequency_To_Wavelength(double x);
extern long double tmpl_LDouble_Frequency_To_Wavelength(long double x);

/*  The ringlet and gap modeling functions.                                   */
TMPL_EXPORT extern tmpl_ComplexDouble
tmpl_CDouble_Ringlet_Diffraction(double x, double a, double b, double F);

TMPL_EXPORT extern tmpl_ComplexDouble
tmpl_CDouble_Gap_Diffraction(double x, double a, double b, double F);

/*  Functions for computing the phase of a ringlet.                           */

extern float
tmpl_Float_Ringlet_Diffraction_Phase(float x, float a, float b, float F);

extern double
tmpl_Double_Ringlet_Diffraction_Phase(double x, double a, double b, double F);

TMPL_EXPORT extern tmpl_ComplexDouble
tmpl_CDouble_Square_Wave_Diffraction(double x, double W, double F,
                                     unsigned int N);

extern long double
tmpl_LDouble_Ringlet_Diffraction_Phase(long double x, long double a,
                                       long double b, long double F);

/*  Left and right straightedge modeling tools.                               */
TMPL_EXPORT extern tmpl_ComplexDouble
tmpl_CDouble_Right_Straightedge_Diffraction(double x, double edge, double F);

TMPL_EXPORT extern tmpl_ComplexDouble
tmpl_CDouble_Left_Straightedge_Diffraction(double x, double edge, double F);

/******************************************************************************
 *--------------------Single Slit Fraunhofer Diffraction----------------------*
 ******************************************************************************/

extern float
tmpl_Float_One_Slit_Fraunhofer_Diffraction(float x, float z, float a);

extern double
tmpl_Double_One_Slit_Fraunhofer_Diffraction(double x, double z, double a);

extern long double
tmpl_LDouble_One_Slit_Fraunhofer_Diffraction(long double x, long double z,
                                             long double a);

/******************************************************************************
 *--------------------Double Slit Fraunhofer Diffraction----------------------*
 ******************************************************************************/

extern float
tmpl_Float_Two_Slit_Fraunhofer_Diffraction(float x, float z, float a,
                                           float d, float lambda);

extern double
tmpl_Double_Two_Slit_Fraunhofer_Diffraction(double x, double z, double a,
                                            double d, double lambda);

extern long double
tmpl_LDouble_Two_Slit_Fraunhofer_Diffraction(long double x, long double z,
                                             long double a, long double d,
                                             long double lambda);
#endif
