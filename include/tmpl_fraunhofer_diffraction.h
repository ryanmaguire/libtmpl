#ifndef TMPL_FRAUNHOFER_DIFFRACTION_H
#define TMPL_FRAUNHOFER_DIFFRACTION_H

extern float
tmpl_Float_Fraunhofer_Diffraction_Double_Slit(float x,
                                              float z,
                                              float a,
                                              float d,
                                              float lambda);

extern double
tmpl_Double_Fraunhofer_Diffraction_Double_Slit(double x,
                                               double z,
                                               double a,
                                               double d,
                                               double lambda);

extern long double
tmpl_LDouble_Fraunhofer_Diffraction_Double_Slit(long double x,
                                                long double z,
                                                long double a,
                                                long double d,
                                                long double lambda);

extern double
tmpl_Double_Fraunhofer_Diffraction_Single_Slit(double x, double z, double a);

#endif
