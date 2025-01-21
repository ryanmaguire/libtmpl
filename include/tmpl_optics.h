#ifndef TMPL_OPTICS_H
#define TMPL_OPTICS_H

/*  The speed of light in km/s.                                               */
#define tmpl_Speed_Of_Light_KMS_F (299792.4580F)
#define tmpl_Speed_Of_Light_KMS (299792.4580)
#define tmpl_Speed_Of_Light_KMS_L (299792.4580L)

#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_complex.h>

extern float tmpl_Float_Resolution_Inverse(float x);
extern double tmpl_Double_Resolution_Inverse(double x);
extern long double tmpl_LDouble_Resolution_Inverse(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Frequency_To_Wavelength                                   *
 *  Purpose:                                                                  *
 *      Converts the frequency of light to the corresponding wavelength.      *
 *  Arguments:                                                                *
 *      frequency (double):                                                   *
 *          The frequency of the light ray.                                   *
 *  Outputs:                                                                  *
 *      lambda (double):                                                      *
 *          The wavelength corresponding to the given frequency.              *
 ******************************************************************************/

/*  These functions are small enough to inline.                               */
#if TMPL_USE_INLINE == 1

/*  Inline versions are located in libtmpl/include/inline/optics/             */
#include <libtmpl/include/inline/optics/tmpl_frequency_to_wavelength_float.h>
#include <libtmpl/include/inline/optics/tmpl_frequency_to_wavelength_double.h>
#include <libtmpl/include/inline/optics/tmpl_frequency_to_wavelength_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise use the source code in src/optics/.                             */
extern float tmpl_Float_Frequency_To_Wavelength(float frequency);
extern double tmpl_Double_Frequency_To_Wavelength(double frequency);
extern long double tmpl_LDouble_Frequency_To_Wavelength(long double frequency);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Frequency_To_Wavenumber                                   *
 *  Purpose:                                                                  *
 *      Converts the wave number of light for the given frequency.            *
 *  Arguments:                                                                *
 *      frequency (double):                                                   *
 *          The frequency of the light ray.                                   *
 *  Outputs:                                                                  *
 *      wavenumber (double):                                                  *
 *          The wave number corresponding to the given frequency.             *
 ******************************************************************************/

/*  These functions are small enough to inline.                               */
#if TMPL_USE_INLINE == 1

/*  Inline versions are located in libtmpl/include/inline/optics/             */
#include <libtmpl/include/inline/optics/tmpl_frequency_to_wavenumber_float.h>
#include <libtmpl/include/inline/optics/tmpl_frequency_to_wavenumber_double.h>
#include <libtmpl/include/inline/optics/tmpl_frequency_to_wavenumber_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise use the source code in src/optics/.                             */
extern float tmpl_Float_Frequency_To_Wavenumber(float frequency);
extern double tmpl_Double_Frequency_To_Wavenumber(double frequency);
extern long double tmpl_LDouble_Frequency_To_Wavenumber(long double frequency);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_Optical_Phase                                            *
 *  Purpose:                                                                  *
 *      Computes the phase angle from a complex optical transmittance.        *
 *  Arguments:                                                                *
 *      transmittance (tmpl_ComplexDouble):                                   *
 *          The input optical transmittance.                                  *
 *  Outputs:                                                                  *
 *      phase (double):                                                       *
 *          The phase of the transmittance.                                   *
 ******************************************************************************/

/*  These functions are small enough to inline.                               */
#if TMPL_USE_INLINE == 1

/*  Inline versions are located in libtmpl/include/inline/optics/             */
#include <libtmpl/include/inline/optics/tmpl_optical_phase_float.h>
#include <libtmpl/include/inline/optics/tmpl_optical_phase_double.h>
#include <libtmpl/include/inline/optics/tmpl_optical_phase_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise use the source code in src/optics/.                             */
extern float tmpl_CFloat_Optical_Phase(tmpl_ComplexFloat frequency);
extern double tmpl_CDouble_Optical_Phase(tmpl_ComplexDouble frequency);

extern long double
tmpl_CLDouble_Optical_Phase(tmpl_ComplexLongDouble frequency);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_Optical_Power                                            *
 *  Purpose:                                                                  *
 *      Computes the power from a complex optical transmittance.              *
 *  Arguments:                                                                *
 *      transmittance (tmpl_ComplexDouble):                                   *
 *          The input optical transmittance.                                  *
 *  Outputs:                                                                  *
 *      power (double):                                                       *
 *          The power of the transmittance.                                   *
 ******************************************************************************/

/*  These functions are small enough to inline.                               */
#if TMPL_USE_INLINE == 1

/*  Inline versions are located in libtmpl/include/inline/optics/             */
#include <libtmpl/include/inline/optics/tmpl_optical_power_float.h>
#include <libtmpl/include/inline/optics/tmpl_optical_power_double.h>
#include <libtmpl/include/inline/optics/tmpl_optical_power_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise use the source code in src/optics/.                             */
extern float tmpl_CFloat_Optical_Power(tmpl_ComplexFloat frequency);
extern double tmpl_CDouble_Optical_Power(tmpl_ComplexDouble frequency);

extern long double
tmpl_CLDouble_Optical_Power(tmpl_ComplexLongDouble frequency);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Wavelength_To_Wavenumber                                  *
 *  Purpose:                                                                  *
 *      Computes the wave number of light given the wavelength.               *
 *  Arguments:                                                                *
 *      lambda (double):                                                      *
 *          The wavelength of the light ray.                                  *
 *  Outputs:                                                                  *
 *      wavenumber (double):                                                  *
 *          The wave number corresponding to the given wavelength.            *
 ******************************************************************************/

/*  These functions are small enough to inline.                               */
#if TMPL_USE_INLINE == 1

/*  Inline versions are located in libtmpl/include/inline/optics/             */
#include <libtmpl/include/inline/optics/tmpl_wavelength_to_wavenumber_float.h>
#include <libtmpl/include/inline/optics/tmpl_wavelength_to_wavenumber_double.h>
#include <libtmpl/include/inline/optics/tmpl_wavelength_to_wavenumber_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise use the source code in src/optics/.                             */
extern float tmpl_Float_Wavelength_To_Wavenumber(float lambda);
extern double tmpl_Double_Wavelength_To_Wavenumber(double lambda);
extern long double tmpl_LDouble_Wavelength_To_Wavenumber(long double lambda);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_Optical_Transmittance                                    *
 *  Purpose:                                                                  *
 *      Computes the complex transmittance from optical power and phase.      *
 *  Arguments:                                                                *
 *      power (double):                                                       *
 *          The normalized optical power, normalized to 1.                    *
 *      phase (double):                                                       *
 *          The phase, in radians.                                            *
 *  Outputs:                                                                  *
 *      T (tmpl_ComplexDouble):                                               *
 *          The complex transmittance, sqrt(power) * e^{i phase}.             *
 ******************************************************************************/

/*  These functions are small enough to inline.                               */
#if TMPL_USE_INLINE == 1

/*  Inline versions are located in libtmpl/include/inline/optics/             */
#include <libtmpl/include/inline/optics/tmpl_optical_transmittance_float.h>
#include <libtmpl/include/inline/optics/tmpl_optical_transmittance_double.h>
#include <libtmpl/include/inline/optics/tmpl_optical_transmittance_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise use the source code in src/optics/.                             */
extern tmpl_ComplexFloat
tmpl_CFloat_Optical_Transmittance(float power, float phase);

extern tmpl_ComplexDouble
tmpl_CDouble_Optical_Transmittance(double power, double phase);

extern tmpl_ComplexLongDouble
tmpl_CLDouble_Optical_Transmittance(long double power, long double phase);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_Optical_Transmittance_Deg                                *
 *  Purpose:                                                                  *
 *      Computes the complex transmittance from optical power and phase,      *
 *      where the phase is given in degrees.                                  *
 *  Arguments:                                                                *
 *      power (double):                                                       *
 *          The normalized optical power, normalized to 1.                    *
 *      phase (double):                                                       *
 *          The phase, in degrees.                                            *
 *  Outputs:                                                                  *
 *      T (tmpl_ComplexDouble):                                               *
 *          The complex transmittance, sqrt(power) * e^{i phase}.             *
 ******************************************************************************/

/*  These functions are small enough to inline.                               */
#if TMPL_USE_INLINE == 1

/*  Inline versions are located in libtmpl/include/inline/optics/             */
#include <libtmpl/include/inline/optics/tmpl_optical_transmittance_deg_float.h>
#include <libtmpl/include/inline/optics/tmpl_optical_transmittance_deg_double.h>
#include <libtmpl/include/inline/optics/tmpl_optical_transmittance_deg_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise use the source code in src/optics/.                             */
extern tmpl_ComplexFloat
tmpl_CFloat_Optical_Transmittance_Deg(float power, float phase);

extern tmpl_ComplexDouble
tmpl_CDouble_Optical_Transmittance_Deg(double power, double phase);

extern tmpl_ComplexLongDouble
tmpl_CLDouble_Optical_Transmittance_Deg(long double power, long double phase);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
