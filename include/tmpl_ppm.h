/*  Include guard for this file to prevent including this twice.              */
#ifndef TMPL_PPMPLOT_H
#define TMPL_PPMPLOT_H

#include <stdio.h>
#include <libtmpl/include/tmpl_complex.h>

typedef struct _tmpl_PPM_Color {
    unsigned char red, green, blue;
} tmpl_PPM_Color;

extern void tmpl_Write_PPM_Color(FILE *fp, tmpl_PPM_Color color);

extern tmpl_PPM_Color
tmpl_Scale_PPM_Color(tmpl_PPM_Color color, double t);

extern tmpl_PPM_Color
tmpl_Create_PPM_Color(unsigned char red,
                      unsigned char green,
                      unsigned char blue);

extern void
tmpl_Write_PPM_Color_From_Values(unsigned char red,unsigned char green,
                                 unsigned char blue, FILE *fp);

extern tmpl_PPM_Color
tmpl_RGB_Scaled_Gradient(double val);

extern tmpl_PPM_Color
tmpl_RGB_Linear_Gradient(double val, double min, double max);

extern void
tmpl_Easy_Complex_Plots(const char *func_name,
                        tmpl_ComplexDouble(*f)(tmpl_ComplexDouble),
                        unsigned int x_size, unsigned int y_size,
                        const double x_min, const double x_max,
                        const double y_min, const double y_max);

extern void
tmpl_Easy_Real_Plots(const char *func_name, double (*f)(double),
                     unsigned int x_size, unsigned int y_size,
                     const double x_min, const double x_max,
                     const double y_min, const double y_max);

extern void
tmpl_PGM_From_Data(unsigned char **data, unsigned int length, FILE *fp);

extern void
tmpl_PPM_From_Data(unsigned char ***data, unsigned int xw,
                   unsigned int yw, FILE *fp);

#endif

