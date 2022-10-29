/******************************************************************************
 *                                 LICENSE                                    *
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
 *                                  tmpl_ppm                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide tools for creating PPM images.                                *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Complex data types found here. Used for creating complex plots.   *
 *  2.) stdio.h:                                                              *
 *          Standard library header file containing the FILE data type.       *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *                                EXAMPLES                                    *
 ******************************************************************************
 *  Examples of all of the functions can be found in:                         *
 *      libtmpl/examples/ppm_examples/                                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 7, 2022                                                 *
 ******************************************************************************/

/*  Include guard for this file to prevent including this twice.              */
#ifndef TMPL_PPM_H
#define TMPL_PPM_H

/*  Complex numbers defined here.                                             */
#include <libtmpl/include/tmpl_complex.h>

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  Struct for working with PPM files. Colors are represented in RGB format.  */
typedef struct tmpl_PPM_Color_Def {
    unsigned char red, green, blue;
} tmpl_PPM_Color;

/*  Commonly used colors.                                                     */
extern const tmpl_PPM_Color tmpl_PPM_Black;
extern const tmpl_PPM_Color tmpl_PPM_White;
extern const tmpl_PPM_Color tmpl_PPM_Red;
extern const tmpl_PPM_Color tmpl_PPM_Green;
extern const tmpl_PPM_Color tmpl_PPM_Blue;
extern const tmpl_PPM_Color tmpl_PPM_Cyan;
extern const tmpl_PPM_Color tmpl_PPM_Magenta;
extern const tmpl_PPM_Color tmpl_PPM_Yellow;

/*  Useful values for grayscale images.                                       */
extern const unsigned char tmpl_PGM_Black;
extern const unsigned char tmpl_PGM_Gray;
extern const unsigned char tmpl_PGM_White;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Binary_PGM_From_Data                                             *
 *  Purpose:                                                                  *
 *      Create a PGM file from a data set.                                    *
 *  Arguments:                                                                *
 *      filename (const char *):                                              *
 *          The name of the file. This must end in ".ppm".                    *
 *      data (unsigned char *):                                               *
 *          A pointer to an unsigned char array containing the data to        *
 *          be drawn. It is assumed data has width*height many elements.      *
 *      width (unsigned int):                                                 *
 *          The number of pixels in the x axis.                               *
 *      height (unsigned int):                                                *
 *          The number of pixels in the y axis.                               *
 *  Output:                                                                   *
 *      None (void). (tmpl_PPM_Color):                                        *
 *  Notes:                                                                    *
 *      The data pointer is checked to see if it is NULL or not. It is        *
 *      assumed that width*height many elements have been allocated for the   *
 *      data pointer. If less than this many elements exist a segmentation    *
 *      fault may occur.                                                      *
 *                                                                            *
 *      This function makes a call to fopen. fopen returns NULL on failure.   *
 *      If this occurs, no output file will be created.                       *
 *                                                                            *
 *      There are no checks on the filename string. Ensure it is a valid      *
 *      string and that it ends in ".ppm".                                    *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_binary_pgm_from_data.c                           *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/                                        *
 *          tmpl_ppm_print_color_from_values_example.c                        *
 ******************************************************************************/
TMPL_EXPORT extern void
tmpl_Binary_PGM_From_Data(const char *filename,
                          unsigned char *data,
                          unsigned int width,
                          unsigned int height);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Binary_PPM_From_Data                                             *
 *  Purpose:                                                                  *
 *      Create a PPM file from a data set.                                    *
 *  Arguments:                                                                *
 *      filename (const char *):                                              *
 *          The name of the file. This must end in ".ppm".                    *
 *      data (tmpl_PPM_Color *):                                              *
 *          A pointer to an array of tmpl_PPM_Color's containing the data to  *
 *          be drawn. It is assumed data has width*height many elements.      *
 *      width (unsigned int):                                                 *
 *          The number of pixels in the x axis.                               *
 *      height (unsigned int):                                                *
 *          The number of pixels in the y axis.                               *
 *  Output:                                                                   *
 *      None (void). (tmpl_PPM_Color):                                        *
 *  Notes:                                                                    *
 *      The data pointer is checked to see if it is NULL or not. It is        *
 *      assumed that width*height many elements have been allocated for the   *
 *      data pointer. If less than this many elements exist a segmentation    *
 *      fault may occur.                                                      *
 *                                                                            *
 *      This function makes a call to fopen. fopen returns NULL on failure.   *
 *      If this occurs, no output file will be created.                       *
 *                                                                            *
 *      There are no checks on the filename string. Ensure it is a valid      *
 *      string and that it ends in ".ppm".                                    *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_binary_ppm_from_data.c                           *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/                                        *
 *          tmpl_ppm_print_color_from_values_example.c                        *
 ******************************************************************************/
TMPL_EXPORT extern void
tmpl_Binary_PPM_From_Data(const char *filename,
                          tmpl_PPM_Color *data,
                          unsigned int width,
                          unsigned int height);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Color_Addition                                               *
 *  Purpose:                                                                  *
 *      Adds two colors using an additive color model.                        *
 *  Arguments:                                                                *
 *      C0 (tmpl_PPM_Color):                                                  *
 *          The first color to be added.                                      *
 *      C1 (tmpl_PPM_Color):                                                  *
 *          The second color to be added.                                     *
 *  Output:                                                                   *
 *      sum (tmpl_PPM_Color):                                                 *
 *          The sum of C0 and C1. The components are min(x + y, UCHAR_MAX)    *
 *          where x is a component of C0, and y is the corresponding          *
 *          component of C1.                                                  *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_color_addition.c                             *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/                                        *
 *          tmpl_ppm_print_color_from_values_example.c                        *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_PPM_Color
tmpl_PPM_Color_Addition(tmpl_PPM_Color C0, tmpl_PPM_Color C1);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Color_Average                                                *
 *  Purpose:                                                                  *
 *      Averages two colors component-wise.                                   *
 *  Arguments:                                                                *
 *      C0 (tmpl_PPM_Color):                                                  *
 *          The first color to be averaged.                                   *
 *      C1 (tmpl_PPM_Color):                                                  *
 *          The second color to be averaged.                                  *
 *  Output:                                                                   *
 *      avg (tmpl_PPM_Color):                                                 *
 *          The average of C0 and C1. The components are 0.5(x + y)           *
 *          where x is a component of C0, and y is the corresponding          *
 *          component of C1.                                                  *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_color_average.c                              *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/                                        *
 *          tmpl_ppm_print_color_from_values_example.c                        *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_PPM_Color
tmpl_PPM_Color_Average(tmpl_PPM_Color C0, tmpl_PPM_Color C1);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Color_Blend                                                  *
 *  Purpose:                                                                  *
 *      Blends two colors component-wise.                                     *
 *  Arguments:                                                                *
 *      C0 (tmpl_PPM_Color):                                                  *
 *          The first color to be averaged.                                   *
 *      C1 (tmpl_PPM_Color):                                                  *
 *          The second color to be averaged.                                  *
 *      t (double):                                                           *
 *          The blending parameter. t = 0 corresponds to C0, t = 1 is C1.     *
 *  Output:                                                                   *
 *      blend (tmpl_PPM_Color):                                               *
 *          A mixture of C0 and C1 based on the blending parameter t.         *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_color_blend.c                                *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/                                        *
 *          tmpl_ppm_print_color_from_values_example.c                        *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_PPM_Color
tmpl_PPM_Color_Blend(tmpl_PPM_Color C0, tmpl_PPM_Color C1, double t);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Complex_Plot                                                 *
 *  Purpose:                                                                  *
 *      Creates 4 plots for a complex function. Real part, imaginary part,    *
 *      modulus (magnitude), and argument (phase).                            *
 *  Arguments:                                                                *
 *      func_name (const char *):                                             *
 *          The name of the plots as a string.                                *
 *      f (tmpl_ComplexDouble(*)(tmpl_ComplexDouble)):                        *
 *          The function being plotted.                                       *
 *      x_size (unsigned int):                                                *
 *          The number of pixels in the x direction.                          *
 *      y_size (unsigned int):                                                *
 *          The number of pixels in the y direction.                          *
 *      x_min (double):                                                       *
 *          The smallest value in the real axis being plotted.                *
 *      x_max (double):                                                       *
 *          The largest value in the real axis being plotted.                 *
 *      y_min (double):                                                       *
 *          The smallest value in the imaginary axis being plotted.           *
 *      y_max (double):                                                       *
 *          The largest value in the imaginary axis being plotted.            *
 *  Output:                                                                   *
 *      None (void):                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_complex_plot.c                               *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/complex_plots/                          *
 ******************************************************************************/
TMPL_EXPORT extern void
tmpl_PPM_Complex_Plot(const char *func_name,
                      tmpl_ComplexDouble(*f)(tmpl_ComplexDouble),
                      unsigned int x_size,
                      unsigned int y_size,
                      double x_min,
                      double x_max,
                      double y_min,
                      double y_max);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Create_Color                                                 *
 *  Purpose:                                                                  *
 *      Create a tmpl_PPM_Color from the RGB values.                          *
 *  Arguments:                                                                *
 *      red (unsigned char):                                                  *
 *          The amount of red in the color.                                   *
 *      green (unsigned char):                                                *
 *          The amount of green in the color.                                 *
 *      blue (unsigned char):                                                 *
 *          The amount of blue in the color.                                  *
 *  Output:                                                                   *
 *      color (tmpl_PPM_Color):                                               *
 *          The color (r, g, b).                                              *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_create_color.c                               *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/                                        *
 *          tmpl_ppm_print_color_from_values_example.c                        *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_PPM_Color
tmpl_PPM_Create_Color(unsigned char r, unsigned char g, unsigned char b);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Linear_Color_Wheel                                           *
 *  Purpose:                                                                  *
 *      Given a number between min and max, return a color based on a linear  *
 *      wheel of blue -> cyan -> green -> yellow -> red -> magenta -> blue.   *
 *  Arguments:                                                                *
 *      val (double):                                                         *
 *          The value we're computing the color of. Values close to (or less  *
 *          than) min and closer to (or greater than) max are blue.           *
 *      min (double):                                                         *
 *          The minimum value in the scale. Values less than min are blue.    *
 *      max (double):                                                         *
 *          The maximum value in the scale. Values greater than max are blue. *
 *  Output:                                                                   *
 *      color (tmpl_PPM_Color).                                               *
 *          The output color.                                                 *
 *  Notes:                                                                    *
 *      NaN returns black.                                                    *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_linear_gradient.c                            *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/tmpl_ppm_print_color_example.c          *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_PPM_Color
tmpl_PPM_Linear_Color_Wheel(double val, double min, double max);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Normalized_Linear_Gradient                                   *
 *  Purpose:                                                                  *
 *      Given a number between min and max, return a color based on a linear  *
 *      gradient of blue -> cyan -> green -> yellow -> red. The colors are    *
 *      normalized to have constant magnitude of UCHAR_MAX along the gradient.*
 *  Arguments:                                                                *
 *      val (double):                                                         *
 *          The value we're computing the color of. Values close to (or less  *
 *          than) min are blue, values closer to (or greater than) max are    *
 *          red.                                                              *
 *      min (double):                                                         *
 *          The minimum value in the scale. Values less than min are red.     *
 *      max (double):                                                         *
 *          The maximum value in the scale. Values greater than max are blue. *
 *  Output:                                                                   *
 *      color (tmpl_PPM_Color).                                               *
 *          The output color.                                                 *
 *  Notes:                                                                    *
 *      NaN returns black.                                                    *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_normalized_linear_gradient.c                 *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/tmpl_ppm_print_color_example.c          *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_PPM_Color
tmpl_PPM_Normalized_Linear_Gradient(double val, double min, double max);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Linear_Gradient                                              *
 *  Purpose:                                                                  *
 *      Given a number between min and max, return a color based on a linear  *
 *      gradient of blue -> cyan -> green -> yellow -> red.                   *
 *  Arguments:                                                                *
 *      val (double):                                                         *
 *          The value we're computing the color of. Values close to (or less  *
 *          than) min are blue, values closer to (or greater than) max are    *
 *          red.                                                              *
 *      min (double):                                                         *
 *          The minimum value in the scale. Values less than min are red.     *
 *      max (double):                                                         *
 *          The maximum value in the scale. Values greater than max are blue. *
 *  Output:                                                                   *
 *      color (tmpl_PPM_Color).                                               *
 *          The output color.                                                 *
 *  Notes:                                                                    *
 *      NaN returns black.                                                    *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_linear_gradient.c                            *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/tmpl_ppm_print_color_example.c          *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_PPM_Color
tmpl_PPM_Linear_Gradient(double val, double min, double max);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Complex_Plot                                                 *
 *  Purpose:                                                                  *
 *      Creates a plot of a real-valued function.                             *
 *  Arguments:                                                                *
 *      func_name (const char *):                                             *
 *          The name of the plots as a string.                                *
 *      f (double(*)(double)):                                                *
 *          The function being plotted.                                       *
 *      x_size (unsigned int):                                                *
 *          The number of pixels in the x direction.                          *
 *      y_size (unsigned int):                                                *
 *          The number of pixels in the y direction.                          *
 *      x_min (double):                                                       *
 *          The smallest value in the real axis being plotted.                *
 *      x_max (double):                                                       *
 *          The largest value in the real axis being plotted.                 *
 *  Output:                                                                   *
 *      None (void):                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_complex_plot.c                               *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/complex_plots/                          *
 ******************************************************************************/
TMPL_EXPORT extern void
tmpl_PPM_Plot(const char *func_name,
              double (*f)(double),
              unsigned int x_size,
              unsigned int y_size,
              double x_min,
              double x_max);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Print_Color                                                  *
 *  Purpose:                                                                  *
 *      Print a given color to a PPM file.                                    *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          The file the color is being written to.                           *
 *      color (tmpl_PPM_Color):                                               *
 *          The color being written to the file.                              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      It is assumed the FILE pointer fp has successfully been opened and it *
 *      may be written to. No checks for NULL pointers are performed.         *
 *      Improper use of this function may cause a segmentation fault.         *
 *                                                                            *
 *      This function should be used for text-based PPM files. Binary-based   *
 *      PPM files should use tmpl_PPM_Write_Color.                            *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_print_color.c                                *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/tmpl_ppm_print_color_example.c          *
 ******************************************************************************/
TMPL_EXPORT extern void tmpl_PPM_Print_Color(FILE *fp, tmpl_PPM_Color color);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Print_Color_From_Values                                      *
 *  Purpose:                                                                  *
 *      Print a given color to a PPM file from explicit values.               *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          The file the color is being written to.                           *
 *      red (unsigned char):                                                  *
 *          The amount of red in the color.                                   *
 *      green (unsigned char):                                                *
 *          The amount of green in the color.                                 *
 *      blue (unsigned char):                                                 *
 *          The amount of blue in the color.                                  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      It is assumed the FILE pointer fp has successfully been opened and it *
 *      may be written to. No checks for NULL pointers are performed.         *
 *      Improper use of this function may cause a segmentation fault.         *
 *                                                                            *
 *      This function should be used for text-based PPM files. Binary-based   *
 *      PPM files should use tmpl_PPM_Write_Color_From_Values.                *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_print_color_from_values.c                    *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/                                        *
 *          tmpl_ppm_print_color_from_values_example.c                        *
 ******************************************************************************/
TMPL_EXPORT extern void
tmpl_PPM_Print_Color_From_Values(FILE *fp,
                                 unsigned char red,
                                 unsigned char green,
                                 unsigned char blue);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Scale_Color                                                  *
 *  Purpose:                                                                  *
 *      Scale a color by a real number.                                       *
 *  Arguments:                                                                *
 *      color (tmpl_PPM_Color):                                               *
 *          The color being scaled.                                           *
 *      t (double):                                                           *
 *          The number that is being multiplied to the components of color.   *
 *  Output:                                                                   *
 *      scaled (tmpl_PPM_Color).                                              *
 *          The color (t*r, t*g, t*b), with color = (r, g, b).                *
 *  Notes:                                                                    *
 *      If t*r, t*g, or t*b overflows, the result is computed mod UCHAR_MAX.  *
 *      For 8-bit unsigned char this is 255.                                  *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_scale_color.c                                *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/tmpl_ppm_scale_color_example.c          *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_PPM_Color tmpl_PPM_Scale_Color(tmpl_PPM_Color color, double t);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Scaled_Color_Wheel                                           *
 *  Purpose:                                                                  *
 *      Given a a real number, return a color based on a scaled gradient of   *
 *      blue -> cyan -> green -> yellow -> red. The arctan function is used   *
 *      to compress val between the range 0 and 1 and then the function       *
 *      tmpl_PPM_Scaled_Gradient is applied.                                  *
 *  Arguments:                                                                *
 *      val (double):                                                         *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      color (tmpl_PPM_Color).                                               *
 *          The output color.                                                 *
 *  Notes:                                                                    *
 *      NaN returns black.                                                    *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_linear_gradient.c                            *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/tmpl_ppm_print_color_example.c          *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_PPM_Color
tmpl_PPM_Scaled_Color_Wheel(double val);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Scaled_Gradient                                              *
 *  Purpose:                                                                  *
 *      Given a a real number, return a color based on a scaled gradient of   *
 *      blue -> cyan -> green -> yellow -> red. The arctan function is used   *
 *      to compress val between the range 0 and 1 and then the function       *
 *      tmpl_PPM_Scaled_Gradient is applied.                                  *
 *  Arguments:                                                                *
 *      val (double):                                                         *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      color (tmpl_PPM_Color).                                               *
 *          The output color.                                                 *
 *  Notes:                                                                    *
 *      NaN returns black.                                                    *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_linear_gradient.c                            *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/tmpl_ppm_print_color_example.c          *
 ******************************************************************************/
TMPL_EXPORT extern tmpl_PPM_Color
tmpl_PPM_Scaled_Gradient(double val);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Write_Color                                                  *
 *  Purpose:                                                                  *
 *      Writes a given color to a PPM file.                                   *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          The file the color is being written to.                           *
 *      color (tmpl_PPM_Color):                                               *
 *          The color being written to the file.                              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      It is assumed the FILE pointer fp has successfully been opened and it *
 *      may be written to. No checks for NULL pointers are performed.         *
 *      Improper use of this function may cause a segmentation fault.         *
 *                                                                            *
 *      This function should be used for binary-based PPM files. Text-based   *
 *      PPM files should use tmpl_PPM_Print_Color.                            *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_write_color.c                                *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/tmpl_ppm_write_color_example.c          *
 ******************************************************************************/
TMPL_EXPORT extern void tmpl_PPM_Write_Color(FILE *fp, tmpl_PPM_Color color);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Write_Color_From_Values                                      *
 *  Purpose:                                                                  *
 *      Writes a given color to a PPM file from explicit values.              *
 *  Arguments:                                                                *
 *      fp (FILE*):                                                           *
 *          The file the color is being written to.                           *
 *      red (unsigned char):                                                  *
 *          The amount of red in the color.                                   *
 *      green (unsigned char):                                                *
 *          The amount of green in the color.                                 *
 *      blue (unsigned char):                                                 *
 *          The amount of blue in the color.                                  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      It is assumed the FILE pointer fp has successfully been opened and it *
 *      may be written to. No checks for NULL pointers are performed.         *
 *      Improper use of this function may cause a segmentation fault.         *
 *                                                                            *
 *      This function should be used for binary-based PPM files. Text-based   *
 *      PPM files should use tmpl_PPM_Print_Color_From_Values.                *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_write_color_from_values.c                    *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/                                        *
 *          tmpl_ppm_write_color_from_values_example.c                        *
 ******************************************************************************/
TMPL_EXPORT extern void
tmpl_PPM_Write_Color_From_Values(FILE *fp,
                                 unsigned char red,
                                 unsigned char green,
                                 unsigned char blue);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Text_PGM_From_Data                                               *
 *  Purpose:                                                                  *
 *      Create a PGM file from a data set.                                    *
 *  Arguments:                                                                *
 *      filename (const char *):                                              *
 *          The name of the file. This must end in ".ppm".                    *
 *      data (unsigned char *):                                               *
 *          A pointer to an unsigned char array containing the data to        *
 *          be drawn. It is assumed data has width*height many elements.      *
 *      width (unsigned int):                                                 *
 *          The number of pixels in the x axis.                               *
 *      height (unsigned int):                                                *
 *          The number of pixels in the y axis.                               *
 *  Output:                                                                   *
 *      None (void). (tmpl_PPM_Color):                                        *
 *  Notes:                                                                    *
 *      The data pointer is checked to see if it is NULL or not. It is        *
 *      assumed that width*height many elements have been allocated for the   *
 *      data pointer. If less than this many elements exist a segmentation    *
 *      fault may occur.                                                      *
 *                                                                            *
 *      This function makes a call to fopen. fopen returns NULL on failure.   *
 *      If this occurs, no output file will be created.                       *
 *                                                                            *
 *      There are no checks on the filename string. Ensure it is a valid      *
 *      string and that it ends in ".ppm".                                    *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_binary_pgm_from_data.c                           *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/                                        *
 *          tmpl_ppm_print_color_from_values_example.c                        *
 ******************************************************************************/
TMPL_EXPORT extern void
tmpl_Text_PGM_From_Data(const char *filename,
                        unsigned char *data,
                        unsigned int width,
                        unsigned int height);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Text_PPM_From_Data                                               *
 *  Purpose:                                                                  *
 *      Create a PGM file from a data set.                                    *
 *  Arguments:                                                                *
 *      filename (const char *):                                              *
 *          The name of the file. This must end in ".ppm".                    *
 *      data (unsigned char *):                                               *
 *          A pointer to an unsigned char array containing the data to        *
 *          be drawn. It is assumed data has width*height many elements.      *
 *      width (unsigned int):                                                 *
 *          The number of pixels in the x axis.                               *
 *      height (unsigned int):                                                *
 *          The number of pixels in the y axis.                               *
 *  Output:                                                                   *
 *      None (void). (tmpl_PPM_Color):                                        *
 *  Notes:                                                                    *
 *      The data pointer is checked to see if it is NULL or not. It is        *
 *      assumed that width*height many elements have been allocated for the   *
 *      data pointer. If less than this many elements exist a segmentation    *
 *      fault may occur.                                                      *
 *                                                                            *
 *      This function makes a call to fopen. fopen returns NULL on failure.   *
 *      If this occurs, no output file will be created.                       *
 *                                                                            *
 *      There are no checks on the filename string. Ensure it is a valid      *
 *      string and that it ends in ".ppm".                                    *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_binary_pgm_from_data.c                           *
 *  Examples:                                                                 *
 *      libtmpl/examples/ppm_examples/                                        *
 *          tmpl_ppm_print_color_from_values_example.c                        *
 ******************************************************************************/
TMPL_EXPORT extern void
tmpl_Text_PPM_From_Data(const char *filename,
                        tmpl_PPM_Color *data,
                        unsigned int width,
                        unsigned int height);

#endif
/*  End of include guard.                                                     */
