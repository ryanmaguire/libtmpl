#ifndef TMPL_ASTRO_H
#define TMPL_ASTRO_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

extern float
tmpl_Float_Effecting_Ring_Opening_Angle(const float opening,
                                        const float azimuth);

extern double
tmpl_Double_Effecting_Ring_Opening_Angle(const double opening,
                                         const double azimuth);

extern long double
tmpl_LDouble_Effecting_Ring_Opening_Angle(const long double opening,
                                          const long double azimuth);

extern float
tmpl_Float_Light_Distance(const float t0, const float t1);

extern double
tmpl_Double_Light_Distance(const double t0, double t1);

extern long double
tmpl_LDouble_Light_Distance(const long double t0, const long double t1);

extern float
tmpl_Float_Optical_Depth_Enhancement_Factor(const float opening,
                                            const float azimuth);

extern double
tmpl_Double_Optical_Depth_Enhancement_Factor(const double opening,
                                             const double azimuth);

extern long double
tmpl_LDouble_Optical_Depth_Enhancement_Factor(const long double opening,
                                              const long double azimuth);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
