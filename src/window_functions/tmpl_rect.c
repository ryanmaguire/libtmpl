/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_window_functions.h>

float tmpl_Float_Rect_Window(float x, float W)                          
{                                                                              
    float abs_x, rect_x;                                                        
                                                                               
    abs_x = tmpl_Float_Abs(x);                                       
                                                                               
    if (abs_x <= 0.5F*W)                                                        
        rect_x = 1.0F;                                                          
    else                                                                       
        rect_x = 0.0F;                                                          
                                                                               
    return rect_x;                                                             
}

