#include <stdio.h>
#include <libtmpl/include/tmpl_ppm.h>

void tmpl_Write_PPM_Color(FILE *fp, tmpl_PPM_Color color)
{
    fputc(color.red,   fp);
    fputc(color.green, fp);
    fputc(color.blue,  fp);
}
