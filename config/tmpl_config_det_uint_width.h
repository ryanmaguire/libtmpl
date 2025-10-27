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
 *                         tmpl_config_det_uint_width                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines the width of unsigned int.                                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_det_uint_width                                                   *
 *  Purpose:                                                                  *
 *      Determines the number of numerical bits in unsigned int.              *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      config/                                                               *
 *          tmpl_config_det_uchar_width.h:                                    *
 *              tmpl_det_uchar_width:                                         *
 *                  Computes the number of bits in unsigned char.             *
 *  Method:                                                                   *
 *      Start with 1 and iteratively multiply by two. Since unsigned          *
 *      arithmetic is performed mod 2^N, where N is the number of numerical   *
 *      bits in the type, after N iterations we will obtain zero. Count the   *
 *      the number of iterations needed to determine the width.               *
 *  Notes:                                                                    *
 *      1.) C89 requires unsigned arithmetic be performed mod 2^N.            *
 *          Section 6.1.2.5, Paragraph 5 of the C89 draft states:             *
 *                                                                            *
 *              For each of the signed integer types there is a corresponding *
 *              (but different) unsigned integer type (designated with the    *
 *              keyword unsigned) that uses the same amount of storage        *
 *              (including sign information) and has the same alignment       *
 *              requirements. The range of nonnegative values of a signed     *
 *              integer type is a subrange of the corresponding unsigned      *
 *              integer type and the representation of the same value in each *
 *              type is the same. A computation involving unsigned operands   *
 *              can never overflow because a result that cannot be            *
 *              represented by the resulting unsigned integer type is reduced *
 *              modulo the number that is one greater than the largest value  *
 *              that can be represented by the resulting unsigned integer     *
 *              type.                                                         *
 *                                                                            *
 *          This can be found in Section 3.1.2.5 paragraph 5 of the standard: *
 *                                                                            *
 *              https://nvlpubs.nist.gov/nistpubs/Legacy/FIPS/fipspub160.pdf  *
 *                                                                            *
 *          A similar statement is found in 6.2.5 paragraph 9 of the C99 and  *
 *          C11 drafts, as well as 6.2.5 paragraph 11 of the C23 draft.       *
 *                                                                            *
 *      2.) The C standard allows unsigned integer types (other than          *
 *          unsigned char) are allowed to have padding bits. This function    *
 *          computes the number of numerical bits only.                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config_globals.h:                                                *
 *          Header file with all of the globals used by config.c.             *
 *  2.) tmpl_config_det_uchar_width.h:                                        *
 *          Provides the tmpl_det_uchar_width function.                       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/04/08: Ryan Maguire                                                  *
 *      Moved function to its own file.                                       *
 *  2025/10/27: Ryan Maguire                                                  *
 *      Split tmpl_det_widths function into several parts. Moved to own file. *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_DET_UINT_WIDTH_H
#define TMPL_CONFIG_DET_UINT_WIDTH_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  The width of unsigned char can be used to compute the size of int.        */
#include "tmpl_det_uchar_width.h"

/*  Function for determining the number of bits in unsigned int.              */
static void tmpl_det_uint_width(void)
{
    /*  We repeatedly multiply by two until we obtain zero. This happens      *
     *  since unsigned arithmetic is performed mod 2^N, where N is the number *
     *  of bits in the given type.                                            */
    const unsigned int two = 2U;

    /*  Initialize to 1. Repeated multiplication by two will eventually       *
     *  eventually produce zero.                                              */
    unsigned int value = 1U;

    /*  Lastly, set the count to zero. Each time we need to multiply by two   *
     *  corresponds to one bit, and we will increment this counter.           */
    tmpl_uint_width = 0U;

    /*  Unsigned integer types can not overflow since the result is computed  *
     *  mod 2^N where N is the number of bits. By starting with 1 and         *
     *  repeatedly multiplying by 2 we will eventually get 2^N, which will    *
     *  be computed as 0 mod 2^N. By counting the number of times we need to  *
     *  to multiply by 2 in order to get zero we can compute the number of    *
     *  bits in unsigned int.                                                 */
    while (value)
    {
        value = two * value;
        ++tmpl_uint_width;
    }

    /*  The C89, C99, C11, and C23 standards all require unsigned arithmetic  *
     *  to be performed mod 2^N. Because of this, any standard's compliant    *
     *  implementation of the C programming language will correctly produce   *
     *  the number of bits in unsigned int using the code above. Set the      *
     *  Boolean to true.                                                      */
    tmpl_uint_width_is_known = 1U;

    /*  The number of bits in unsigned int can be obtained from the number of *
     *  bits in unsigned char (which does not allow padding) and using the    *
     *  sizeof operator. The C standard allows unsigned int to have padding,  *
     *  hence it is possible for width != number_of_bits, but this is rare.   */
    if (!tmpl_uchar_width_is_known)
        tmpl_det_uchar_width();

    /*  Total number of bits used for storage is the number of bytes used     *
     *  times the number of bits in a byte. Compute this.                     */
    tmpl_number_of_bits_in_uint = sizeof(unsigned int) * tmpl_uchar_width;
}
/*  End of tmpl_det_uint_width.                                               */

#endif
/*  End of include guard.                                                     */
