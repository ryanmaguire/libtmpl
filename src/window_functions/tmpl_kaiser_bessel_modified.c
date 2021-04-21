/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions.h>
#include <libtmpl/include/tmpl_window_functions.h>

float tmpl_Float_Modified_Kaiser_Bessel(float x, float W, float alpha)
{                                                                              
    float kbmd, arg, abs_x;
                                                                               
    abs_x = tmpl_Float_Abs(x);
                                                                               
    if (alpha == 0.0F)
    {
        if (abs_x < 0.5F*W)                                                     
            kbmd = 1.0F;                                                        
        else                                                                   
            kbmd = 0.0F;                                                        
    }                                                                          
    else                                                                       
    {                                                                          
        if (abs_x < 0.5F*W)                                                     
        {                                                                      
            arg = 2.0F*abs_x/W;                                                 
            arg = tmpl_Float_Sqrt(1.0F - arg*arg);                    
                                                                               
            alpha *= tmpl_One_Pi_F;                                         
            kbmd = (tmpl_Float_Bessel_I0(alpha * arg) - 1.0F) /
                   (tmpl_Float_Bessel_I0(alpha) - 1.0F);              
        }                                                                      
        else                                                                   
            kbmd = 0.0F;                                                        
    }                                                                          
                                                                               
    return kbmd;                                                               
}

