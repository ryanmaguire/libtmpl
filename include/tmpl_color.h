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

/*  Standard color struct for 24-bit colors using three color channels.       */
typedef struct tmpl_RGB24_Def {

    /*  Unsigned is required to be at least 8 bits by the standard. It is     *
     *  usually 8 bits exactly on nearly every computer imaginable. Use an    *
     *  array with three unsigned chars representing "red", "green", and      *
     *  "blue", in that order. The array ensures that the data is contiguous. */
    unsigned char dat[3];
} tmpl_RGB24;

/*  Color struct for using 24-bit colors and alpha compositing.               */
typedef struct tmpl_RGBA24_Def {

    /*  Same idea as before, use an array with 3 unsigned chars for colors.   */
    unsigned char dat[3];

    /*  And a real number (should be between 0 and 1) for alpha compositing.  */
    double alpha;
} tmpl_RGBA24;

/*  Color struct for 30-bit colors. Common in HDR images.                     */
typedef struct tmpl_RGB30_Def {

    /*  Unsigned int is required to be at least 16 bits long. We can create   *
     *  a 30-bit color using a bit field with 3 10-bit integers. Note, the    *
     *  compiler will almost surely pad the struct with two bits to create a  *
     *  single 32-bit object, but that's fine.                                */
    unsigned int red : 10;
    unsigned int green : 10;
    unsigned int blue : 10;
} tmpl_RGB30;

/*  Color struct for 30-bit colors with alpha compositing.                    */
typedef struct tmpl_RGBA30_Def {

    /*  Again, we mimic the previous struct but add an alpha parameter.       */
    unsigned int red : 10;
    unsigned int green : 10;
    unsigned int blue : 10;

    /*  Real number for alpha compositing (should be between 0 and 1).        */
    double alpha;
} tmpl_RGBA30;

/*  Color struct for 48-bit colors in RGB format.                             */
typedef struct tmpl_RGB48_Def {

    /*  Unsigned short is required to be at least 16 bits wide. It is usually *
     *  exactly this size on most computers. Use an array of three unsigned   *
     *  shorts to represent the three colors.                                 */
    unsigned short dat[3];
} tmpl_RGB48;

/*  Color struct for 48-bit colors with alpha compositing.                    */
typedef struct tmpl_RGBA48_Def {

    /*  Same idea as before, use an array of three unsigned shorts for colors.*/
    unsigned short dat[3];

    /*  Parameter for alpha compositing (real number between 0 and 1).        */
    double alpha;
} tmpl_RGBA48;

/*  Color struct for "arbitrary" RGB color depth. In reality double has a     *
 *  52-bit mantissa, so this is a 156-bit color. There are 10^47 possible     *
 *  colors, far beyond the 10^14 colors possible with 48-bit colors, and      *
 *  much higher than the 10^7 colors present in standard 24-bit depths. So    *
 *  one may safely consider this "arbitrary" color depth.                     */
typedef struct tmpl_RGB_Def {

    /*  To make the data contiguous, use an array of three doubles.           */
    double dat[3];
} tmpl_RGB;

/*  RGB color with alpha compositing.                                         */
typedef struct tmpl_RGBA_Def {

    /*  The alpha and color parameters are represented by the same type, a    *
     *  double. Use an array with four doubles for all of the data.           */
    double dat[4];
} tmpl_RGBA;

/******************************************************************************
 *                             Predefined Colors                              *
 ******************************************************************************/

/*  Commonly used colors in 24-bit RGB format.                                */
extern const tmpl_RGB24 tmpl_RGB24_Black;
extern const tmpl_RGB24 tmpl_RGB24_White;
extern const tmpl_RGB24 tmpl_RGB24_Red;
extern const tmpl_RGB24 tmpl_RGB24_Green;
extern const tmpl_RGB24 tmpl_RGB24_Blue;
extern const tmpl_RGB24 tmpl_RGB24_Cyan;
extern const tmpl_RGB24 tmpl_RGB24_Magenta;
extern const tmpl_RGB24 tmpl_RGB24_Yellow;

/*  Same colors with alpha compositing, alpha parameter set to 1.             */
extern const tmpl_RGBA24 tmpl_RGBA24_Black;
extern const tmpl_RGBA24 tmpl_RGBA24_White;
extern const tmpl_RGBA24 tmpl_RGBA24_Red;
extern const tmpl_RGBA24 tmpl_RGBA24_Green;
extern const tmpl_RGBA24 tmpl_RGBA24_Blue;
extern const tmpl_RGBA24 tmpl_RGBA24_Cyan;
extern const tmpl_RGBA24 tmpl_RGBA24_Magenta;
extern const tmpl_RGBA24 tmpl_RGBA24_Yellow;

/*  Commonly used colors in 30-bit RGB format.                                */
extern const tmpl_RGB30 tmpl_RGB30_Black;
extern const tmpl_RGB30 tmpl_RGB30_White;
extern const tmpl_RGB30 tmpl_RGB30_Red;
extern const tmpl_RGB30 tmpl_RGB30_Green;
extern const tmpl_RGB30 tmpl_RGB30_Blue;
extern const tmpl_RGB30 tmpl_RGB30_Cyan;
extern const tmpl_RGB30 tmpl_RGB30_Magenta;
extern const tmpl_RGB30 tmpl_RGB30_Yellow;

/*  Same colors with alpha compositing, alpha parameter set to 1.             */
extern const tmpl_RGBA30 tmpl_RGBA30_Black;
extern const tmpl_RGBA30 tmpl_RGBA30_White;
extern const tmpl_RGBA30 tmpl_RGBA30_Red;
extern const tmpl_RGBA30 tmpl_RGBA30_Green;
extern const tmpl_RGBA30 tmpl_RGBA30_Blue;
extern const tmpl_RGBA30 tmpl_RGBA30_Cyan;
extern const tmpl_RGBA30 tmpl_RGBA30_Magenta;
extern const tmpl_RGBA30 tmpl_RGBA30_Yellow;

/*  Commonly used colors in 48-bit RGB format.                                */
extern const tmpl_RGB48 tmpl_RGB48_Black;
extern const tmpl_RGB48 tmpl_RGB48_White;
extern const tmpl_RGB48 tmpl_RGB48_Red;
extern const tmpl_RGB48 tmpl_RGB48_Green;
extern const tmpl_RGB48 tmpl_RGB48_Blue;
extern const tmpl_RGB48 tmpl_RGB48_Cyan;
extern const tmpl_RGB48 tmpl_RGB48_Magenta;
extern const tmpl_RGB48 tmpl_RGB48_Yellow;

/*  Same colors with alpha compositing, alpha parameter set to 1.             */
extern const tmpl_RGBA48 tmpl_RGBA48_Black;
extern const tmpl_RGBA48 tmpl_RGBA48_White;
extern const tmpl_RGBA48 tmpl_RGBA48_Red;
extern const tmpl_RGBA48 tmpl_RGBA48_Green;
extern const tmpl_RGBA48 tmpl_RGBA48_Blue;
extern const tmpl_RGBA48 tmpl_RGBA48_Cyan;
extern const tmpl_RGBA48 tmpl_RGBA48_Magenta;
extern const tmpl_RGBA48 tmpl_RGBA48_Yellow;

/*  Commonly used colors in real RGB format.                                  */
extern const tmpl_RGB tmpl_RGB_Black;
extern const tmpl_RGB tmpl_RGB_White;
extern const tmpl_RGB tmpl_RGB_Red;
extern const tmpl_RGB tmpl_RGB_Green;
extern const tmpl_RGB tmpl_RGB_Blue;
extern const tmpl_RGB tmpl_RGB_Cyan;
extern const tmpl_RGB tmpl_RGB_Magenta;
extern const tmpl_RGB tmpl_RGB_Yellow;

/*  Same colors with alpha compositing, alpha parameter set to 1.             */
extern const tmpl_RGBA tmpl_RGBA_Black;
extern const tmpl_RGBA tmpl_RGBA_White;
extern const tmpl_RGBA tmpl_RGBA_Red;
extern const tmpl_RGBA tmpl_RGBA_Green;
extern const tmpl_RGBA tmpl_RGBA_Blue;
extern const tmpl_RGBA tmpl_RGBA_Cyan;
extern const tmpl_RGBA tmpl_RGBA_Magenta;
extern const tmpl_RGBA tmpl_RGBA_Yellow;

/******************************************************************************
 *                                 Functions                                  *
 ******************************************************************************/

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
 *      If the sum overflows beyond the the maximum possible value in a       *
 *      given channel, the sum is set to the maximum possible value.          *
 ******************************************************************************/
extern tmpl_RGB24 tmpl_RGB24_Add(tmpl_RGB24 c0, const tmpl_RGB24 c1);
extern tmpl_RGB30 tmpl_RGB30_Add(tmpl_RGB30 c0, const tmpl_RGB30 c1);
extern tmpl_RGB48 tmpl_RGB48_Add(tmpl_RGB48 c0, const tmpl_RGB48 c1);
extern tmpl_RGB tmpl_RGB_Add(const tmpl_RGB *c0, const tmpl_RGB *c1);

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
