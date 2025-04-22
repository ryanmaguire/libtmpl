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
 *                     tmpl_swap_most_significant_bit_8                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for swapping the values in a char array containing      *
 *      eight elements.                                                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Swap_Most_Significant_Bit_8                                      *
 *  Purpose:                                                                  *
 *      Swaps the values of a pointer to an array of 8 char elements. Useful  *
 *      for dealing with binary data files with big vs. little endianness     *
 *      concerns. The original use was for extracting the data from binary RSR*
 *      files for the NASA Cassini mission which had big endianness, and read *
 *      them on little endian platforms.                                      *
 *  Arguments:                                                                *
 *      ptr (char *):                                                         *
 *          A pointer to a char array containing eight elements.              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      tmpl_Swap_Bytes (tmpl_bytes.h).                                       *
 *  Method:                                                                   *
 *      Use tmpl_Swap_Bytes four times on the elements. The input/output      *
 *      scheme is as follows:                                                 *
 *                                                                            *
 *          -------------------------------------------------                 *
 *      IN  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |                 *
 *          -------------------------------------------------                 *
 *      OUT |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |                 *
 *          -------------------------------------------------                 *
 *                                                                            *
 *  Notes:                                                                    *
 *      It is assumed the char pointer has had its memory sufficiently        *
 *      allocated and initialized before being passed to this function.       *
 *      Failure to do so may result in a segmentation fault as the function   *
 *      will try to access memory you do not own.                             *
 *                                                                            *
 *      This code is a duplicate of the code I originally wrote for           *
 *      rss_ringoccs. That library is also released under GPL3.               *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bytes.h:                                                         *
 *          Header where tmpl_Endian enum data type is defined, and           *
 *          where the function's prototype is given.                          *
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
 *  Date:       February 11, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2021/01/14: Ryan Maguire                                                  *
 *      Created file (rss_ringoccs for Wellesley College).                    *
 *  2021/02/11: Ryan Maguire                                                  *
 *      Ported to libtmpl.                                                    *
 *  2021/02/11: Ryan Maguire                                                  *
 *      Added comments and license.                                           *
 *      Soft freeze for alpha release of libtmpl.                             *
 *  2021/04/30: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code/comments. No  *
 *      more changes to comments or code unless something breaks.             *
 ******************************************************************************/

/*  The function prototype is found here.                                     */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for swapping the values in a char array with eight elements.     */
void tmpl_Swap_Most_Significant_Bit_8(char *ptr)
{
    /*  Simply use tmpl_Swap_Bytes four times and return. tmpl_Swap_Bytes     *
     *  wants two pointers to the char values, but we just have a single      *
     *  pointer to a char array. To get a pointer to the zeroth value we      *
     *  first dereference with ptr[0] (we could also do *ptr, but ptr[0] is   *
     *  clearer in my opinion). We then grab the address with &. So in total  *
     *  we have &(ptr[0]), which is a pointer to the zeroth element of the    *
     *  char array. Similarly for &(ptr[1]), up to &(ptr[7]). We pass these   *
     *  to tmpl_Swap_Bytes and return.                                        */
    tmpl_Swap_Bytes(&(ptr[0]), &(ptr[7]));
    tmpl_Swap_Bytes(&(ptr[1]), &(ptr[6]));
    tmpl_Swap_Bytes(&(ptr[2]), &(ptr[5]));
    tmpl_Swap_Bytes(&(ptr[3]), &(ptr[4]));
    return;
}
/*  End of tmpl_Swap_Most_Significant_Bit_8.                                  */
