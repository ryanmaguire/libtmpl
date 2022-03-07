/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                      tmpl_ppm_write_color_from_values                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Write a color to a PPM file using the explicit RGB values.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PPM_Write_Color_From_Values                                      *
 *  Purpose:                                                                  *
 *      Write a color in RGB format to a PPM file.                            *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          The file the color is being written to.                           *
 *      color (tmpl_PPM_Color):                                               *
 *          The color being written to the file.                              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      fputc (stdio.h):                                                      *
 *          Function for printing a byte (char) to a file.                    *
 *  Method:                                                                   *
 *      Use fputc and write the contents of the RGB color byte-by-byte.       *
 *  Notes:                                                                    *
 *      It is assumed the input FILE pointer has been opened and may be       *
 *      written to. No check for a NULL pointer is performed. Improper use    *
 *      of this function may lead to segmentation faults.                     *
 *                                                                            *
 *      This function assumes the PPM is in binary format. Text-based PPM     *
 *      files should use tmpl_PPM_Print_Color_From_Values.                    *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_ppm.h:                                                           *
 *          Header file containing function prototype and PPM color data type.*
 *  2.) stido.h:                                                              *
 *          Standard C library header file containing the FILE data type.     *
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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 7, 2022                                                 *
 ******************************************************************************/

/*  PPM color typedef and function prototype found here.                      */
#include <libtmpl/include/tmpl_ppm.h>

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  Function for writing an RGB color to a PPM file.                          */
void tmpl_PPM_Write_Color_From_Values(FILE *fp,
                                      unsigned char red,
                                      unsigned char green,
                                      unsigned char blue)
{
    fputc(red, fp);
    fputc(green, fp);
    fputc(blue, fp);
}
/*  End of tmpl_PPM_Write_Color_From_Values.                                  */
