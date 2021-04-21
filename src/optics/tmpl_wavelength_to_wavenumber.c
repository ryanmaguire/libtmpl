
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_optics.h>

/*  Convert a wavelength to a wavelength.                                     */                        
float tmpl_Float_Wavelength_To_Wavenumber(float lambda)                
{                                                                              
    /*  The conversion is two pi over the wavelength.                         */
    return tmpl_Two_Pi_F / lambda;                                        
}

/*  Convert a wavelength to a wavelength.                                     */                        
double tmpl_Double_Wavelength_To_Wavenumber(double lambda)                
{                                                                              
    /*  The conversion is two pi over the wavelength.                         */
    return tmpl_Two_Pi / lambda;                                        
}

/*  Convert a wavelength to a wavelength.                                     */                        
long double tmpl_LDouble_Wavelength_To_Wavenumber(long double lambda)                
{                                                                              
    /*  The conversion is two pi over the wavelength.                         */
    return tmpl_Two_Pi_L / lambda;                                        
}

