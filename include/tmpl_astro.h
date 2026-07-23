/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ASTRO_H
#define TMPL_ASTRO_H

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Light_Distance_KM                                         *
 *  Purpose:                                                                  *
 *      Computes the distance traveled by light in a vacuum, in kilometers.   *
 *  Arguments:                                                                *
 *      t0 (const double):                                                    *
 *          The start time, in seconds.                                       *
 *      t1 (const double):                                                    *
 *          The final time, in seconds.                                       *
 *  Output:                                                                   *
 *      dist (double):                                                        *
 *          The distance traveled in kilometers by light over time |t1 - t0|. *
 *  Notes:                                                                    *
 *      1.) Float and long double precision are also provided.                *
 *                                                                            *
 *      2.) Lengths are in kilometers, times are in seconds.                  *
 *                                                                            *
 *      3.) Distance is a non-negative quantity.                              *
 *                                                                            *
 *      4.) No checks for NaNs or infinity are made.                          *
 *                                                                            *
 *      5.) There is no assumption that t0 < t1 or t1 < t0. That is, you may  *
 *          swap the order of the inputs without changing the output.         *
 ******************************************************************************/
TMPL_CONST_FUNC
extern double
tmpl_Double_Light_Distance_KM(const double t0, double t1)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Light_Distance_KM(const float t0, const float t1)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Light_Distance_KM(const long double t0, const long double t1)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Light_Distance_M                                          *
 *  Purpose:                                                                  *
 *      Computes the distance traveled by light in a vacuum, in meters.       *
 *  Arguments:                                                                *
 *      t0 (const double):                                                    *
 *          The start time, in seconds.                                       *
 *      t1 (const double):                                                    *
 *          The final time, in seconds.                                       *
 *  Output:                                                                   *
 *      dist (double):                                                        *
 *          The distance traveled in meters by light over time |t1 - t0|.     *
 *  Notes:                                                                    *
 *      1.) Float and long double precision are also provided.                *
 *                                                                            *
 *      2.) Lengths are in meters, times are in seconds.                      *
 *                                                                            *
 *      3.) Distance is a non-negative quantity.                              *
 *                                                                            *
 *      4.) No checks for NaNs or infinity are made.                          *
 *                                                                            *
 *      5.) There is no assumption that t0 < t1 or t1 < t0. That is, you may  *
 *          swap the order of the inputs without changing the output.         *
 ******************************************************************************/
TMPL_CONST_FUNC
extern double
tmpl_Double_Light_Distance_M(const double t0, double t1)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Light_Distance_M(const float t0, const float t1)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Light_Distance_M(const long double t0, const long double t1)
TMPL_UNSEQUENCED;

/******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Mean_Longitude                                            *
 *  Purpose:                                                                  *
 *      Computes mean longitude from mean angular motion.                     *
 *  Arguments:                                                                *
 *      epoch_mean_longitude (const double):                                  *
 *          The initial mean longitude at a given epoch.                      *
 *      mean_motion (const double):                                           *
 *          The average angular speed needed to complete one full orbit.      *
 *      epoch (const double):                                                 *
 *          The moment in time for the initial mean longitude angle.          *
 *      time (const double):                                                  *
 *          The time the mean longitude is calculated with respect to.        *
 *  Notes:                                                                    *
 *      1.) Float and long double precision are also provided.                *
 *                                                                            *
 *      2.) The units for the epoch mean longitude and time may be arbitrary, *
 *          but the units for mean motion must be the ratio of your chosen    *
 *          units. That is, mean angular motion must have the units of        *
 *          epoch_mean_longitude / time.                                      *
 *                                                                            *
 *      3.) The units for the output angle will be the same as the units of   *
 *          the epoch mean longitude.                                         *
 *                                                                            *
 *      4.) No checks for NaNs or infinity are made.                          *
 ******************************************************************************/
TMPL_CONST_FUNC
extern double
tmpl_Double_Mean_Longitude(const double epoch_mean_longitude,
                           const double mean_motion,
                           const double epoch,
                           const double time)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Mean_Longitude(const float epoch_mean_longitude,
                          const float mean_motion,
                          const float epoch,
                          const float time)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Mean_Longitude(const long double epoch_mean_longitude,
                            const long double mean_motion,
                            const long double epoch,
                            const long double time)
TMPL_UNSEQUENCED;

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
