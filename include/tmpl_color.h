/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                                 tmpl_color                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for working with RGB colors in various formats (24-bit,*
 *      30-bit, 48-bit, and real), as well as RGB colors with alpha           *
 *      compositing. These can be used to create PPM and SVG images.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *    None.                                                                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COLOR_H
#define TMPL_COLOR_H

/******************************************************************************
 *                                  Typedefs                                  *
 ******************************************************************************/

/*  RGB structs without alpha compositing.                                    */
#include <libtmpl/include/types/tmpl_rgb.h>
#include <libtmpl/include/types/tmpl_rgb24.h>
#include <libtmpl/include/types/tmpl_rgb30.h>
#include <libtmpl/include/types/tmpl_rgb48.h>

/*  RGB structs with alpha compositing.                                       */
#include <libtmpl/include/types/tmpl_rgba.h>
#include <libtmpl/include/types/tmpl_rgba24.h>
#include <libtmpl/include/types/tmpl_rgba30.h>
#include <libtmpl/include/types/tmpl_rgba48.h>

/*
 *  nbh_color_write_to_file(const struct nbh_color *c, FILE *fp)
 *  nbh_color_write_to_ppm(const struct nbh_color *c, struct nbh_ppm *PPM)
 *  nbh_color_scale(const struct nbh_color *c, double t)
 *  nbh_color_scaleby(struct nbh_color *c, double t)
 *  nbh_color_addto(struct nbh_color *c0, const struct nbh_color *c1)
 *  nbh_checker_board(const struct nbh_vec6 *u)
 *  nbh_angle_gradient(const struct nbh_vec6 *u)
 *  nbh_color_gradient_checker_board(const struct nbh_vec6 *u)
 *  nf_color_normalize(const struct nf_color *c)
 *  nf_color_normalizeself(struct nf_color *c)
 *  nf_negate_channel(unsigned char *channel)
 *  nf_color_negate(struct nf_color *c)
 */

/******************************************************************************
 *                                 Functions                                  *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RGB24_Add                                                        *
 *  Purpose:                                                                  *
 *      Adds two colors by summing over the individual channels.              *
 *  Arguments:                                                                *
 *      c0 (tmpl_RGB24):                                                      *
 *          The first color.                                                  *
 *      c1 (tmpl_RGB24):                                                      *
 *          The second color.                                                 *
 *  Outputs:                                                                  *
 *      sum (tmpl_RGB24):                                                     *
 *          The sum of the two input colors.                                  *
 *  Notes:                                                                    *
 *      30-bit and 48-bit equivalents are provided as well.                   *
 *      Floating-point (RBG) type is provided as well. This version takes in  *
 *      pointers, instead of the structs themselves.                          *
 *      If the sum overflows beyond the the maximum possible value in a       *
 *      given channel, the sum is set to the maximum possible value.          *
 ******************************************************************************/
extern tmpl_RGB24 tmpl_RGB24_Add(tmpl_RGB24 c0, const tmpl_RGB24 c1);
extern tmpl_RGB30 tmpl_RGB30_Add(tmpl_RGB30 c0, const tmpl_RGB30 c1);
extern tmpl_RGB48 tmpl_RGB48_Add(tmpl_RGB48 c0, const tmpl_RGB48 c1);

extern tmpl_RGB
tmpl_RGB_Add(const tmpl_RGB * const c0, const tmpl_RGB * const c1);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RGBA24_Add                                                       *
 *  Purpose:                                                                  *
 *      Adds two colors by summing over the individual channels.              *
 *  Arguments:                                                                *
 *      c0 (tmpl_RGBA24):                                                     *
 *          The first color.                                                  *
 *      c1 (tmpl_RGBA24):                                                     *
 *          The second color.                                                 *
 *  Outputs:                                                                  *
 *      sum (tmpl_RGBA24):                                                    *
 *          The sum of the two input colors.                                  *
 *  Notes:                                                                    *
 *      30-bit and 48-bit equivalents are provided as well.                   *
 *      If the sum overflows beyond the the maximum possible value in a       *
 *      given channel, the sum is set to the maximum possible value.          *
 ******************************************************************************/
extern tmpl_RGBA24 tmpl_RGBA24_Add(tmpl_RGBA24 c0, const tmpl_RGBA24 c1);
extern tmpl_RGBA30 tmpl_RGBA30_Add(tmpl_RGBA30 c0, const tmpl_RGBA30 c1);
extern tmpl_RGBA48 tmpl_RGBA48_Add(tmpl_RGBA48 c0, const tmpl_RGBA48 c1);
extern tmpl_RGBA tmpl_RGBA_Add(const tmpl_RGBA *c0, const tmpl_RGBA *c1);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RGB24_Create                                                     *
 *  Purpose:                                                                  *
 *      Creates a color from three color channels.                            *
 *  Arguments:                                                                *
 *      red (unsigned char):                                                  *
 *          The amount of red in the color.                                   *
 *      green (unsigned char):                                                *
 *          The amount of green in the color.                                 *
 *      blue (unsigned char):                                                 *
 *          The amount of blue in the color.                                  *
 *  Outputs:                                                                  *
 *      color (tmpl_RGB24):                                                   *
 *          The color with color channels set to (red, green, blue).          *
 *  Notes:                                                                    *
 *      30-bit, 48-bit, and double equivalents are provided as well.          *
 ******************************************************************************/
extern tmpl_RGB24
tmpl_RGB24_Create(unsigned char red,
                  unsigned char green,
                  unsigned char blue);

extern tmpl_RGB30
tmpl_RGB30_Create(unsigned short int red,
                  unsigned short int green,
                  unsigned short int blue);

extern tmpl_RGB48
tmpl_RGB48_Create(unsigned short int red,
                  unsigned short int green,
                  unsigned short int blue);

extern tmpl_RGB
tmpl_RGB_Create(double red, double green, double blue);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RGBA24_Create                                                    *
 *  Purpose:                                                                  *
 *      Creates a color from three color channels.                            *
 *  Arguments:                                                                *
 *      r (unsigned char):                                                    *
 *          The amount of red in the color.                                   *
 *      g (unsigned char):                                                    *
 *          The amount of green in the color.                                 *
 *      b (unsigned char):                                                    *
 *          The amount of blue in the color.                                  *
 *      a (double):                                                           *
 *          The alpha parameter, between 0 and 1.                             *
 *  Outputs:                                                                  *
 *      color (tmpl_RGBA24):                                                  *
 *          The color with color channels set to (red, green, blue) and       *
 *          alpha parameter set to the given input.                           *
 *  Notes:                                                                    *
 *      30-bit, 48-bit, and double equivalents are provided as well.          *
 ******************************************************************************/
extern tmpl_RGBA24
tmpl_RGBA24_Create(unsigned char red,
                   unsigned char green,
                   unsigned char blue,
                   double alpha);

extern tmpl_RGBA30
tmpl_RGBA30_Create(unsigned short int red,
                   unsigned short int green,
                   unsigned short int blue,
                   double alpha);

extern tmpl_RGBA48
tmpl_RGBA48_Create(unsigned short int red,
                   unsigned short int green,
                   unsigned short int blue,
                   double alpha);

extern tmpl_RGBA
tmpl_RGBA_Create(double red, double green, double blue, double alpha);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RGB24_Average                                                    *
 *  Purpose:                                                                  *
 *      Averages two colors component-wise.                                   *
 *  Arguments:                                                                *
 *      c0 (tmpl_RGB24):                                                      *
 *          The first color to be averaged.                                   *
 *      c1 (tmpl_RGB24):                                                      *
 *          The second color to be averaged.                                  *
 *  Output:                                                                   *
 *      avg (tmpl_RGB24):                                                     *
 *          The average of c0 and c1. The components are 0.5(x + y)           *
 *          where x is a component of c0, and y is the corresponding          *
 *          component of c1.                                                  *
 ******************************************************************************/
extern tmpl_RGB24 tmpl_RGB24_Average(tmpl_RGB24 c0, tmpl_RGB24 c1);
extern tmpl_RGB30 tmpl_RGB30_Average(tmpl_RGB30 c0, tmpl_RGB30 c1);
extern tmpl_RGB48 tmpl_RGB48_Average(tmpl_RGB48 c0, tmpl_RGB48 c1);
extern tmpl_RGB tmpl_RGB_Average(const tmpl_RGB *c0, const tmpl_RGB *c1);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RGBA24_Average                                                   *
 *  Purpose:                                                                  *
 *      Averages two colors component-wise.                                   *
 *  Arguments:                                                                *
 *      c0 (tmpl_RGBA24):                                                     *
 *          The first color to be averaged.                                   *
 *      c1 (tmpl_RGBA24):                                                     *
 *          The second color to be averaged.                                  *
 *  Output:                                                                   *
 *      avg (tmpl_RGBA24):                                                    *
 *          The average of c0 and c1. The components are 0.5(x + y)           *
 *          where x is a component of c0, and y is the corresponding          *
 *          component of c1.                                                  *
 ******************************************************************************/
extern tmpl_RGBA24 tmpl_RGBA24_Average(tmpl_RGBA24 c0, tmpl_RGBA24 c1);
extern tmpl_RGBA30 tmpl_RGBA30_Average(tmpl_RGBA30 c0, tmpl_RGBA30 c1);
extern tmpl_RGBA48 tmpl_RGBA48_Average(tmpl_RGBA48 c0, tmpl_RGBA48 c1);
extern tmpl_RGBA tmpl_RGBA_Average(const tmpl_RGBA *c0, const tmpl_RGBA *c1);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RGB24_Blend                                                      *
 *  Purpose:                                                                  *
 *      Averages two colors component-wise.                                   *
 *  Arguments:                                                                *
 *      c0 (tmpl_RGB24):                                                      *
 *          The first color to be averaged.                                   *
 *      c1 (tmpl_RGB24):                                                      *
 *          The second color to be averaged.                                  *
 *      t (double):                                                           *
 *          The blending parameter. t = 0 corresponds to c0, t = 1 is c1.     *
 *  Output:                                                                   *
 *      blend (tmpl_RGB24):                                                   *
 *          A mixture of C0 and C1 based on the blending parameter t.         *
 ******************************************************************************/
extern tmpl_RGB24 tmpl_RGB24_Blend(tmpl_RGB24 c0, tmpl_RGB24 c1, double t);
extern tmpl_RGB30 tmpl_RGB30_Blend(tmpl_RGB30 c0, tmpl_RGB30 c1, double t);
extern tmpl_RGB48 tmpl_RGB48_Blend(tmpl_RGB48 c0, tmpl_RGB48 c1, double t);

extern tmpl_RGB
tmpl_RGB_Blend(const tmpl_RGB *c0, const tmpl_RGB *c1, double t);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RGBA24                                                           *
 *  Purpose:                                                                  *
 *      Blends two colors using alpha compositing.                            *
 *  Arguments:                                                                *
 *      c0 (tmpl_RGB24):                                                      *
 *          The first color to be averaged.                                   *
 *      c1 (tmpl_RGB24):                                                      *
 *          The second color to be averaged.                                  *
 *      t (double):                                                           *
 *          The blending parameter. t = 0 corresponds to c0, t = 1 is c1.     *
 *  Output:                                                                   *
 *      blend (tmpl_RGB24):                                                   *
 *          A mixture of C0 and C1 based on the blending parameter t.         *
 ******************************************************************************/
extern tmpl_RGBA24 tmpl_RGBA24_Blend(tmpl_RGBA24 back, tmpl_RGBA24 fore);
extern tmpl_RGBA30 tmpl_RGBA30_Blend(tmpl_RGBA30 back, tmpl_RGBA30 fore);
extern tmpl_RGBA48 tmpl_RGBA48_Blend(tmpl_RGBA48 back, tmpl_RGBA48 fore);
extern tmpl_RGBA tmpl_RGBA_Blend(const tmpl_RGBA *c0, const tmpl_RGBA *c1);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RGB24_Quick_Add                                                  *
 *  Purpose:                                                                  *
 *      Adds two colors by summing over the individual channels.              *
 *  Arguments:                                                                *
 *      c0 (tmpl_RGB24):                                                      *
 *          The first color.                                                  *
 *      c1 (tmpl_RGB24):                                                      *
 *          The second color.                                                 *
 *  Outputs:                                                                  *
 *      sum (tmpl_RGB24):                                                     *
 *          The sum of the two input colors.                                  *
 *  Notes:                                                                    *
 *      30-bit and 48-bit equivalents are provided as well.                   *
 *      If the sum overflows beyond the the maximum possible value in a       *
 *      given channel, the sum is set to the maximum possible value.          *
 ******************************************************************************/
extern tmpl_RGB24 tmpl_RGB24_Quick_Add(tmpl_RGB24 c0, const tmpl_RGB24 c1);
extern tmpl_RGB30 tmpl_RGB30_Quick_Add(tmpl_RGB30 c0, const tmpl_RGB30 c1);
extern tmpl_RGB48 tmpl_RGB48_Quick_Add(tmpl_RGB48 c0, const tmpl_RGB48 c1);
extern tmpl_RGB tmpl_RGB_Quick_Add(const tmpl_RGB *c0, const tmpl_RGB *c1);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_RGBA24_Quick_Add                                                 *
 *  Purpose:                                                                  *
 *      Adds two colors by summing over the individual channels. This is done *
 *      without checking for possible overflows in the individual channels.   *
 *  Arguments:                                                                *
 *      c0 (tmpl_RGBA24):                                                     *
 *          The first color.                                                  *
 *      c1 (tmpl_RGBA24):                                                     *
 *          The second color.                                                 *
 *  Outputs:                                                                  *
 *      sum (tmpl_RGBA24):                                                    *
 *          The sum of the two input colors.                                  *
 *  Notes:                                                                    *
 *      30-bit and 48-bit equivalents are provided as well.                   *
 *      If the sum overflows beyond the the maximum possible value in a       *
 *      given channel, an undesirable color may occur. This routine is        *
 *      faster than tmpl_RGBA24_Add, but not as safe.                         *
 ******************************************************************************/
extern tmpl_RGBA24 tmpl_RGBA24_Quick_Add(tmpl_RGBA24 c0, const tmpl_RGBA24 c1);
extern tmpl_RGBA30 tmpl_RGBA30_Quick_Add(tmpl_RGBA30 c0, const tmpl_RGBA30 c1);
extern tmpl_RGBA48 tmpl_RGBA48_Quick_Add(tmpl_RGBA48 c0, const tmpl_RGBA48 c1);
extern tmpl_RGBA tmpl_RGBA_Quick_Add(const tmpl_RGBA *c0, const tmpl_RGBA *c1);

#endif
/*  End of include guard.                                                     */
