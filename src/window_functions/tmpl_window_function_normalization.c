/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_window_functions.h>

float tmpl_Float_Window_Normalization(float *ker, long dim,
                                      float dx, float f_scale)
{                                                                              
    /*  Declare variable for indexing.                                        */
    long n;                                                                    
    float out;                                                                  
                                                                               
    /*  Compute the Free-Space integral.                                      */
    float T1 = 0.0;                                                           
                                                                               
    for (n=0; n<dim; ++n)                                                      
        T1 += ker[n];                                                          
                                                                               
    T1 = tmpl_Float_Abs(T1 * dx);                                    
                                                                               
    /* Return the normalization factor.                                       */
    out = tmpl_Sqrt_Two_F * f_scale / T1;                              
    return out;                                                                
}


