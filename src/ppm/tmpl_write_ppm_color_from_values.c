

#include <stdio.h>
#include <libtmpl/include/tmpl_ppm.h>

void tmpl_Write_PPM_Color_From_Values(unsigned char red, unsigned char green,
                                      unsigned char blue, FILE *fp)
{
    fputc(red,   fp);
    fputc(green, fp);
    fputc(blue,  fp);
}
