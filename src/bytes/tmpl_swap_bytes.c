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
 *                             tmpl_swap_bytes                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for swapping the values of two char pointers.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Swap_Bytes                                                       *
 *  Purpose:                                                                  *
 *      Swaps the value of two char pointers. Useful for dealing with binary  *
 *      data files with big vs. little endianness concerns.                   *
 *  Arguments:                                                                *
 *      ptr1 (char *):                                                        *
 *          A pointer to a char.                                              *
 *      ptr2 (char *):                                                        *
 *          Another pointer to a char.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a temporary char variable "tmp" to swap the two values.           *
 *  Notes:                                                                    *
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
 *  Author:     Ryan Maguire, Dartmouth College                               *
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

/*  Function prototype is declared here.                                      */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for swapping the values of two char pointers.                    */
void tmpl_Swap_Bytes(char *ptr1, char *ptr2)
{
    /*  We'll use a third temporary variable to store the intermediate value. */
    char tmp;

    /*  Set tmp to the value pointed to by ptr1. This way we don't lose the   *
     *  value when we reassign ptr1. You can do this whole thing in one line  *
     *  with a bitwise XOR, but to me it is very unreadable and offers no     *
     *  computational time advantage.                                         */
    tmp = *ptr1;

    /*  Set the value of ptr1 to ptr2, and ptr2 to tmp (which is ptr1's       *
     *  original value).                                                      */
    *ptr1 = *ptr2;
    *ptr2 = tmp;
    return;
}
/*  End of tmpl_Swap_Bytes.                                                   */
