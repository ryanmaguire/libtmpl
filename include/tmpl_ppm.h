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

/*  There are six types of PPM files, 3 text-based, 3 binary.                 */
typedef enum {
    tmpl_PPM_Text_Black_And_White,
    tmpl_PPM_Text_Grayscale,
    tmpl_PPM_Text_RGB,
    tmpl_PPM_Binary_Black_And_White,
    tmpl_PPM_Binary_Grayscale,
    tmpl_PPM_Binary_RGB
} tmpl_PPM_Type;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Print_Color                                                  *
 *  Purpose:                                                                  *
 *      Print a given color to a PPM file.                                    *
 *  Arguments:                                                                *
 *      fp (FILE*):                                                           *
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
 *      libtmpl/examples/bytes_examples/tmpl_determine_endianness_example.c   *
 ******************************************************************************/
extern void tmpl_PPM_Print_Color(FILE *fp, tmpl_PPM_Color color);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Print_Color_From_Values                                      *
 *  Purpose:                                                                  *
 *      Print a given color to a PPM file from explicit values.               *
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
 *      This function should be used for text-based PPM files. Binary-based   *
 *      PPM files should use tmpl_PPM_Print_Color_From_Values.                *
 *  Source Code:                                                              *
 *      libtmpl/src/ppm/tmpl_ppm_print_color_from_values.c                    *
 *  Examples:                                                                 *
 *      libtmpl/examples/bytes_examples/tmpl_determine_endianness_example.c   *
 ******************************************************************************/
extern void
tmpl_PPM_Print_Color_From_Values(FILE *fp,
                                 unsigned char red,
                                 unsigned char green,
                                 unsigned char blue);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PPM_Write_Color                                                  *
 *  Purpose:                                                                  *
 *      Writes a given color to a PPM file.                                   *
 *  Arguments:                                                                *
 *      fp (FILE*):                                                           *
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
 *      libtmpl/examples/bytes_examples/tmpl_determine_endianness_example.c   *
 ******************************************************************************/
extern void tmpl_PPM_Write_Color(FILE *fp, tmpl_PPM_Color color);

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
 *      libtmpl/examples/bytes_examples/tmpl_determine_endianness_example.c   *
 ******************************************************************************/
extern void
tmpl_PPM_Write_Color_From_Values(FILE *fp,
                                 unsigned char red,
                                 unsigned char green,
                                 unsigned char blue);

extern tmpl_PPM_Color
tmpl_Scale_PPM_Color(tmpl_PPM_Color color, double t);

extern tmpl_PPM_Color
tmpl_Create_PPM_Color(unsigned char r, unsigned char g, unsigned char b);

extern tmpl_PPM_Color
tmpl_PPM_Scaled_Gradient(double val);

extern tmpl_PPM_Color
tmpl_PPM_Linear_Gradient(double val, double min, double max);

extern void
tmpl_PPM_Complex_Plot(const char *func_name,
                      tmpl_ComplexDouble(*f)(tmpl_ComplexDouble),
                      unsigned int x_size, unsigned int y_size,
                      const double x_min, const double x_max,
                      const double y_min, const double y_max);

extern void
tmpl_PPM_Plot(const char *func_name, double (*f)(double),
              unsigned int x_size, unsigned int y_size,
              const double x_min, const double x_max,
              const double y_min, const double y_max);

extern void
tmpl_PGM_From_Data(unsigned char **data, unsigned int length, FILE *fp);

extern void
tmpl_PPM_From_Data(unsigned char ***data, unsigned int xw,
                   unsigned int yw, FILE *fp);

#endif

