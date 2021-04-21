
/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_optics.h>

/*  Convert a frequency (in hertz) to a wavelength (in kilometers).           */
float tmpl_Float_Frequency_To_Wavelength(float frequency)
{
    /*  The conversion is the speed of light divided by the input frequency.  */
    return tmpl_Speed_Of_Light_KMS_F / frequency;
}

double tmpl_Double_Frequency_To_Wavelength(double frequency)
{
    /*  The conversion is the speed of light divided by the input frequency.  */
    return tmpl_Speed_Of_Light_KMS / frequency;
}

long double tmpl_LDouble_Frequency_To_Wavelength(long double frequency)
{
    /*  The conversion is the speed of light divided by the input frequency.  */
    return tmpl_Speed_Of_Light_KMS_L / frequency;
}
