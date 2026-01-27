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
 *                         tmpl_config_det_uchar_width                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines the width of unsigned char.                                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_det_uchar_width                                                  *
 *  Purpose:                                                                  *
 *      Determines the number of numerical bits in unsigned char.             *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
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
 *      2.) Section 6.2.6.2 paragraph 1 of the C99, C11, and C23 drafts       *
 *          also requires unsigned char to not have any padding. C11 says:    *
 *          Section 6.2.6.2 Paragraph 1:                                      *
 *                                                                            *
 *              For unsigned integer types other than unsigned char, the bits *
 *              of the object representation shall be divided into two        *
 *              groups: value bits and padding bits (there need not be any of *
 *              the latter). If there are N value bits, each bit shall        *
 *              represent a different power of 2 between 1 and 2^(N - 1), so  *
 *              that objects of that type shall be capable of representing    *
 *              values from 0 to 2^N - 1 using a pure binary representation;  *
 *              this shall be known as the value representation. The values   *
 *              of any padding bits are unspecified.                          *
 *                                                                            *
 *          C23 is even more explicit, adding:                                *
 *                                                                            *
 *              Otherwise, there is no requirement to have any padding bits;  *
 *              unsigned char shall not have any padding bits.                *
 *                                                                            *
 *          Because of this, the total number of bits in unsigned char is     *
 *          equal to the total number of bits used for storage.               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
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
#ifndef TMPL_CONFIG_DET_UCHAR_WIDTH_H
#define TMPL_CONFIG_DET_UCHAR_WIDTH_H

/*  Globals for the config file are all found here.                           */
#include "tmpl_config_globals.h"

/*  Function for determining the number of bits in unsigned char.             */
static void tmpl_det_uchar_width(void)
{
    /*  We repeatedly multiply by two until we obtain zero. This happens      *
     *  since unsigned arithmetic is performed mod 2^N, where N is the number *
     *  of bits in the given type.                                            */
    const unsigned char two = 0x02U;

    /*  Initialize to 1. Repeated multiplication by two will eventually       *
     *  eventually produce zero.                                              */
    unsigned char value = 0x01U;

    /*  Lastly, set the count to zero. Each time we need to multiply by two   *
     *  corresponds to one bit, and we will increment this counter.           */
    tmpl_uchar_width = 0U;

    /*  Unsigned integer types can not overflow since the result is computed  *
     *  mod 2^N where N is the number of bits. By starting with 1 and         *
     *  repeatedly multiplying by 2 we will eventually get 2^N, which will    *
     *  be computed as 0 mod 2^N. By counting the number of times we need to  *
     *  to multiply by 2 in order to get zero we can compute the number of    *
     *  bits in unsigned char.                                                */
    while (value)
    {
        value = two * value;
        ++tmpl_uchar_width;
    }

    /*  The C89, C99, C11, and C23 standards all require unsigned arithmetic  *
     *  to be performed mod 2^N. Because of this, any standard's compliant    *
     *  implementation of the C programming language will correctly produce   *
     *  the number of bits in unsigned char using the code above. Set the     *
     *  Boolean to true.                                                      */
    tmpl_uchar_width_is_known = 1U;

    /*  The C99 and higher standards do not allow padding for unsigned char.  *
     *  The width is equal to the number of bits used for storage.            */
    tmpl_number_of_bits_in_uchar = tmpl_uchar_width;
}
/*  End of tmpl_det_uchar_width.                                              */

#endif
/*  End of include guard.                                                     */
