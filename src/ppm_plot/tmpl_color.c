#include <libtmpl/include/tmpl_ppm_plot.h>

void tmpl_Color(unsigned char red, unsigned char green,
                       unsigned char blue, FILE *fp)
{
    fputc(red,   fp);
    fputc(green, fp);
    fputc(blue,  fp);
}
