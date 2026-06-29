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
 *                            tmpl_ppm_print_color                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Print a color to a PPM file.                                          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PPM_Print_Color                                                  *
 *  Purpose:                                                                  *
 *      Print a color in RGB format to a PPM file.                            *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          The file the color is being written to.                           *
 *      color (tmpl_RGB24):                                                   *
 *          The color being written to the file.                              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      fprintf (stdio.h):                                                    *
 *          Function for printing a string to a file.                         *
 *  Method:                                                                   *
 *      Use fprintf and write the contents of the RGB color to the file.      *
 *  Notes:                                                                    *
 *      It is assumed the input FILE pointer has been opened and may be       *
 *      written to. No check for a NULL pointer is performed. Improper use    *
 *      of this function may lead to segmentation faults.                     *
 *                                                                            *
 *      This function assumes the PPM is in text format. Binary-based PPM     *
 *      files should use tmpl_PPM_Write_Color.                                *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_ppm.h:                                                           *
 *          Header file containing function prototype and PPM color data type.*
 *  2.) stdio.h:                                                              *
 *          Standard C library header file containing the FILE data type.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 7, 2022                                                 *
 ******************************************************************************/

/*  PPM color typedef and function prototype found here.                      */
#include <libtmpl/include/tmpl_ppm.h>

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  Function for writing an RGB color to a PPM file.                          */
void tmpl_PPM_Print_Color(FILE *fp, tmpl_RGB24 color)
{
    fprintf(fp, "%u %u %u\n", color.dat[0], color.dat[1], color.dat[2]);
}
/*  End of tmpl_PPM_Print_Color.                                              */
