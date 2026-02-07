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
 *                             tmpl_byte_reverse8                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Swaps the order of a char array with eight elements.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Byte_Reverse8                                                    *
 *  Purpose:                                                                  *
 *      Reverses the order of a char array with 8 elements. Useful for        *
 *      handling data with big vs. little endianness concerns.                *
 *  Arguments:                                                                *
 *      ptr (char * const):                                                   *
 *          A pointer to a char array containing eight elements.              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the TMPL_SWAP macro on the array. The input / output scheme is:   *
 *                                                                            *
 *          -------------------------------------------------                 *
 *      IN  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |                 *
 *          -------------------------------------------------                 *
 *      OUT |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |                 *
 *          -------------------------------------------------                 *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) It is assumed the char pointer has had its memory sufficiently    *
 *          allocated and initialized before being passed to this function.   *
 *                                                                            *
 *      2.) There are no checks for NULL pointers.                            *
 *                                                                            *
 *      3.) This code is a fork of code I originally wrote for                *
 *          rss_ringoccs. That library is also released under the GPLv3.      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_swap.h:                                                          *
 *          Performs a swap on two variables.                                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 11, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
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
 *  2026/02/07: Ryan Maguire                                                  *
 *      Removed include, provided explicit forward declaration. Changed name  *
 *      to clarify the purpose of this function, and make the naming more     *
 *      consistent with other functions in libtmpl. Add TMPL_SWAP macro use.  *
 ******************************************************************************/

/*  TMPL_SWAP macro provided here.                                            */
#include <libtmpl/include/helper/tmpl_swap.h>

/*  Function prototype / forward declaration.                                 */
extern void tmpl_Byte_Reverse8(char * const ptr);

/*  Function for swapping the values in a char array with eight elements.     */
void tmpl_Byte_Reverse8(char * const ptr)
{
    /*  The array contains eight elements, we swap the outer-most pair, then  *
     *  the second outer-most, then the second inner-most, and then the inner *
     *  pair to reverse the entire array.                                     */
    TMPL_SWAP(char, ptr[0], ptr[7]);
    TMPL_SWAP(char, ptr[1], ptr[6]);
    TMPL_SWAP(char, ptr[2], ptr[5]);
    TMPL_SWAP(char, ptr[3], ptr[4]);
}
/*  End of tmpl_Byte_Reverse8.                                                */
