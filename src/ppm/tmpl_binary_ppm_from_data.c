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
 *      If fopen fails, nothing is done.                                      *
 *                                                                            *
 *      If the input data pointer is NULL, nothing is done.                   *
 *                                                                            *
 *      If the input data pointer does not have width*height many             *
 *      elements allocated for it a segmentation fault may occur.             *
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
 *  Date:       March 10, 2022                                                *
 ******************************************************************************/

/*  Avoid silly warning on Windows for using fopen. GNU/Linux, FreeBSD, and   *
 *  macOS have no such warnings for using standard library functions.         */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

/*  PPM color struct and function prototype defined here.                     */
#include <libtmpl/include/tmpl_ppm.h>

/*  Needed for fopen, fprintf, and fputc.                                     */
#include <stdio.h>

/*  UCHAR_MAX is found here.                                                  */
#include <limits.h>

/*  Function for creating a PPM file from a data set.                         */
void
tmpl_Binary_PPM_From_Data(const char *filename,
                          tmpl_PPM_Color *data,
                          unsigned int width,
                          unsigned int height)
{
    /*  Variable for indexing.                                                */
    unsigned int n;

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
    fprintf(fp, "P6\n%u %u\n%u\n", width, height, (unsigned int)UCHAR_MAX);

    /*  Write all of the data to the file.                                    */
    for (n = 0U; n < width*height; ++n)
        tmpl_PPM_Write_Color(fp, data[n]);

    /*  Close the file since we're done with it.                              */
    fclose(fp);
}
/*  End of tmpl_Binary_PPM_From_Data.                                         */
