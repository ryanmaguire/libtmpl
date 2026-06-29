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
 *                        tmpl_binary_ppm_from_data                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for creating binary PPM files.                          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Binary_PPM_From_Data                                             *
 *  Purpose:                                                                  *
 *      Create a binary-based PPM file from a given data set.                 *
 *  Arguments:                                                                *
 *      filename (const char *):                                              *
 *          The name of the file. This string should end in ".ppm".           *
 *      data (tmpl_PPM_Color *):                                              *
 *          A pointer to an array of tmpl_PPM_Color's containing the data.    *
 *          The (x, y) pixel will have the color data[x + y*width]. The array *
 *          must have width*height many elements.                             *
 *      width (unsigned int):                                                 *
 *          The width of the PPM file, the number of pixels in the x axis.    *
 *      height (unsigned int):                                                *
 *          The height of the PPM file, the number of pixels in the y axis.   *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      fopen (stdio.h):                                                      *
 *          Open a file and provide a FILE pointer to it.                     *
 *      fprintf (stdio.h):                                                    *
 *          Print a formatted string to a file.                               *
 *      tmpl_PPM_Write_Color (tmpl_ppm.h):                                    *
 *          Write a color to a file.                                          *
 *  Method:                                                                   *
 *      Create a file and give it write permissions with fopen. Write the     *
 *      preamble for the PPM with fprintf, and then loop over the data and    *
 *      write it to the file with tmpl_PPM_Write_Color.                       *
 *  Notes:                                                                    *
 *      1.) This function checks for NULL pointers. If the input data pointer *
 *          is NULL, nothing is done.                                         *
 *                                                                            *
 *      2.) If fopen fails, nothing is done.                                  *
 *                                                                            *
 *      3.) The input data array should have width * height elements.         *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_ppm.h:                                                           *
 *          Header file containing function prototype.                        *
 *  2.) stdio.h:                                                              *
 *          Standard C library header file containing fopen, fprintf, etc.    *
 *  3.) limits.h:                                                             *
 *          Standard C library header file containing the UCHAR_MAX macro.    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2022                                                *
 ******************************************************************************/

/*  Disable warnings for using standard library functions with MSVC.          */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#endif

/*  TMPL_CAST macro provided here.                                            */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  The TMPL_RESTRICT macro is defined here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype defined here.                                          */
#include <libtmpl/include/tmpl_ppm.h>

/*  Needed for fopen, fprintf, and fwrite.                                    */
#include <stdio.h>

/*  Function for creating a binary PGM file from data.                        */
void
tmpl_Binary_PPM_From_Data(const char * TMPL_RESTRICT const filename,
                          const tmpl_RGB24 * TMPL_RESTRICT const data,
                          const unsigned int width,
                          const unsigned int height)
{
    /*  The total number of pixels in the image.                              */
    const size_t width_size = TMPL_CAST(width, size_t);
    const size_t height_size = TMPL_CAST(height, size_t);
    const size_t count = width_size * height_size;

    /*  The file the PPM is being written to.                                 */
    FILE *fp;

    /*  Check for NULL pointers before proceeding.                            */
    if (!data)
        return;

    /*  Open the file and give it write permissions.                          */
    fp = fopen(filename, "wb");

    /*  fopen returns NULL on failure. Check for this.                        */
    if (!fp)
        return;

    /*  Print the preamble to the PPM file.                                   */
    fprintf(fp, "P6\n%u %u\n%u\n", width, height, 255U);

    /*  Write all of the data to the file.                                    */
    fwrite(data, sizeof(*data), count, fp);

    /*  Close the file since we're done with it.                              */
    fclose(fp);
}
/*  End of tmpl_Binary_PPM_From_Data.                                         */
