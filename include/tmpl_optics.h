#ifndef __TMPL_OPTICS_H__
#define __TMPL_OPTICS_H__

/*  The speed of light in km/s.                                               */
#define tmpl_Speed_Of_Light_KMS_F  299792.4580F
#define tmpl_Speed_Of_Light_KMS    299792.4580
#define tmpl_Speed_Of_Light_KMS_L  299792.4580L

extern float
Fresnel_Scale_Float(float lambda, float d, float phi, float b);

extern double
Fresnel_Scale_Double(double lambda, double d, double phi, double b);

extern long double
Fresnel_Scale_LDouble(long double lambda, long double d,
                      long double phi, long double b);

extern float
tmpl_Float_Resolution_Inverse(float x);

extern double
tmpl_Double_Resolution_Inverse(double x);

extern long double
tmpl_LDouble_Resolution_Inverse(long double x);

extern float
tmpl_Float_Wavelength_To_Wavenumber(float x);

extern double
tmpl_Double_Wavelength_To_Wavenumber(double x);

extern long double
tmpl_LDouble_Wavelength_To_Wavenumber(long double x);

extern float
tmpl_Float_Frequency_To_Wavelength(float x);

extern double
tmpl_Double_Frequency_To_Wavelength(double x);

extern long double
tmpl_LDouble_Frequency_To_Wavelength(long double x);

#endif

