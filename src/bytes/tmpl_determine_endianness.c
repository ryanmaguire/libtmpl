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
 *                        tmpl_determine_endianness                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for determining the endianness of a platform.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Determine_Endianness                                             *
 *  Purpose:                                                                  *
 *      Determines the endianness of a platform. That is, whether the system  *
 *      is little-endian, big-endian, or mixed-endian.                        *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      endianness (tmpl_Endian):                                             *
 *          An enum data-type whose value corresponds to the endianness.      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a union data type between an unsigned long int and an unsigned    *
 *      char array that has sizeof(unsigned long int) many elements. Set the  *
 *      unsigned long int part to the number (n-1)...43210, where n is the    *
 *      value of sizeof(unsigned long int). This value is written in base     *
 *      2^CHAR_BIT, where CHAR_BIT is the number of bits in one byte, a       *
 *      value defined in the macro CHAR_BIT in limits.h. We then access       *
 *      the char array part of the union and see which element is 0 and which *
 *      element is n-1. This tells us the endianness. Explicitly, if we let   *
 *      b = 2^CHAR_BIT, and if we set n = sizeof(unsigned long int), then we  *
 *      want the number:                                                      *
 *                                                                            *
 *          x = (n-1) * b^(n-1) + (n-2) * b^(n-2) + ... + 2 * b^2 + 1 * b + 0 *
 *                                                                            *
 *      Since a union has all of its members share the same chunck of memory, *
 *      the char array inside the union would then interpret this as:         *
 *                                                                            *
 *          -------------------------------                                   *
 *          | n-1 | n-2 | ... |  1  |  0  |                                   *
 *          -------------------------------                                   *
 *                                                                            *
 *      For big endian systems, and:                                          *
 *                                                                            *
 *          -------------------------------                                   *
 *          |  0  |  1  | ... | n-2 | n-1 |                                   *
 *          -------------------------------                                   *
 *                                                                            *
 *      For little endian systems. By checking the zeroth element of this     *
 *      array, we can determine the endianness.                               *
 *  Notes:                                                                    *
 *      In the extremely rare case where sizeof(unsigned long int) = 1, this  *
 *      function cannot compute the endianness. sizeof(unsigned long int) = 1 *
 *      is so rare, I know of no systems where this is true. The C standard   *
 *      does not forbid this, however, so it's worth mentioning. In this case *
 *      tmpl_UnknownEndian is returned, unless one has a compiler supporting  *
 *      the C99 standard. In this case, the code will try to use the same     *
 *      trick, but with a union of an unsigned long long int, and an unsigned *
 *      char array. If sizeof(unsigned long long int) is also 1, the function *
 *      returns tmpl_UnknownEndian.                                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bytes.h:                                                         *
 *          Header where tmpl_Endian enum data type is defined, and           *
 *          where the function's prototype is given.                          *
 *  2.) limits.h:                                                             *
 *          Standard C library header file containing the CHAR_BIT macro      *
 *          which tells us how many bits are in one char.                     *
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
 *  2021/04/10: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code/comments. No  *
 *      more changes to comments or code unless something breaks.             *
 *  2021/04/26:                                                               *
 *      Removed tmpl_integer.h from dependencies to improve portability.      *
 *      Using a char array that is sizeof(unsigned long int) in size, rather  *
 *      than 4 or 8 elements wide, to improve portability. The only           *
 *      assumption now is that sizeof(unsigned long int) > 1.                 *
 ******************************************************************************/

/*  Standard library file containing the CHAR_BIT macro and more.             */
#include <limits.h>

/*  Where the function's prototype and tmpl_Endian are defined.               */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for determining the endianness of the system.                    */
tmpl_Endian tmpl_Determine_Endianness(void)
{
    /*  Use the union C-keyword to create a data-type that has an unsigned    *
     *  long int and an unsigned char array share the same address in memory. *
     *  We'll then set the unsigned long int value to the number              *
     *  (n-1)(n-2)...43210, written in base 2^CHAR_BIT, where n is the value  *
     *  of sizeof(unsigned long int). Pretending we're in base-10 for the     *
     *  moment, and sizeof(unsigned long int) = 8, we set the unsigned long   *
     *  int portion of the union to the number 76543210, and then examine the *
     *  the unsigned char array part of the union. Since the char array       *
     *  shares the same memory as the unsigned long int, this will be         *
     *  interpreted as either:                                                *
     *                                                                        *
     *      ---------------------------------                                 *
     *      | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |                                 *
     *      ---------------------------------                                 *
     *                                                                        *
     *  For big endian systems, and:                                          *
     *                                                                        *
     *      ---------------------------------                                 *
     *      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |                                 *
     *      ---------------------------------                                 *
     *                                                                        *
     *  For little endian systems. By checking the zeroth element of this     *
     *  array, we can determine the endianness.                               */
    union {
        unsigned long int x;
        unsigned char arr[sizeof(unsigned long int)];
    } e;

    /*  Letting n = sizeof(unsigned long int), we'll write (n-1)...43210 via  *
     *  the sum:                                                              *
     *      (n-1) * b^(n-1) + ... + 2 * b^2 + 1 * b + 0                       *
     *  where b is the base, b = 2^CHAR_BIT. We'll need a variable for        *
     *  indexing this sum and computing these powers. Declare these here. The *
     *  ISO C90 standard forbids mixed-declarations with code, hence we place *
     *  declarations at the top.                                              */
    unsigned long int k, power;

    /*  There is one, extremely rare, exceptional case that needs to be       *
     *  handled separately. If sizeof(unsigned long int) = 1, then the char   *
     *  array will have one element, which is the same number as the unsigned *
     *  long int value. Because of this we would be unable to determine the   *
     *  endianness. If this is true, return tmpl_UnknownEndian. I know of no  *
     *  systems where sizeof(unsigned long int) = 1, but the ISO C90 standard *
     *  does NOT specify that this is impossible, so we do this for the sake  *
     *  of portability.                                                       */
    if (sizeof(unsigned long int) == 1)
    {
        /*  If your compiler supports C99 or higher, we can try this scheme   *
         *  with unsigned long long int, which should definitely have sizeof  *
         *  greater than 1 (but again, is NOT required to). Check this with   *
         *  the standard macro __STDC_VERSION__.                              */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

        /*  See the comments below for an explanation of this algorithm. This *
         *  is an exact copy of the code after the preprocessor #if statement *
         *  but with unsigned long long int instead of unsigned long int.     *
         *  If sizeof unsigned long long int is also 1, nothing can be done.  */
        union {
            unsigned long long int x;
            unsigned char arr[sizeof(unsigned long long int)];
        } ell;

        unsigned long long int powerll, kll;

        if (sizeof(unsigned long long int) == 1)
            return tmpl_UnknownEndian;

        /*  The ULL suffix means unsigned long long.                          */
        ell.x = 0ULL;
        powerll = 1ULL << CHAR_BIT;

        for (kll = 1ULL; kll < sizeof(unsigned long long int); ++kll)
        {
            ell.x += kll * powerll;
            powerll = powerll << CHAR_BIT;
        }

        if (ell.arr[0] == 0U)
            return tmpl_LittleEndian;
        else if (ell.arr[0] == sizeof(unsigned long long int) - 1U)
            return tmpl_BigEndian;
        else if (ell.arr[0] < sizeof(unsigned long long int) - 1U)
            return tmpl_MixedEndian;
        else
            return tmpl_UnknownEndian;

#else
/*  Else for #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.    */

        /*  If we get here, sizeof(unsigned long int) = 1 and your compiler   *
         *  does not support the C99, or higher, standard so unsigned long    *
         *  long int may not be defined. Return tmpl_UnknownEndian.           */
        return tmpl_UnknownEndian;
#endif
/*  End of #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.      */

    }
    /* End of if (sizeof(unsigned long int) == 1).                            */

    /*  Initialize the unsigned long int part of the union to 0. We'll        *
     *  compute the number (n-1)...43210 (written in base 2^CHAR_BIT) using   *
     *  a sum later. The suffix UL means unsigned long, which is the data     *
     *  type of e.x.                                                          */
    e.x = 0UL;

    /*  To compute 2^CHAR_BIT we can either multiply by 2 CHAR_BIT many times *
     *  or use a simple bit-wise trick. The number 2^CHAR_BIT is just         *
     *  100...00, where there are CHAR_BIT many zeroes, when written in       *
     *  binary. We can write this number using bit-shifting. The number       *
     *  1 << N is the number 1 with N zeroes after it, in binary. So we can   *
     *  write 2^CHAR_BIT via 1 << CHAR_BIT. The suffix UL means unsigned long *
     *  which is the data type of power.                                      */
    power = 1UL << CHAR_BIT;

    /*  Compute the sum (n-1)*b^(n-1) + ... + 2*b^2 + 1*b + 0 via a for loop. */
    for (k = 1UL; k < sizeof(unsigned long int); ++k)
    {
        e.x += k * power;

        /*  Given (2^CHAR_BIT)^k, we can get (2^CHAR_BIT)^(k+1) by taking     *
         *  (2^CHAR_BIT)^k and bit-shifting it CHAR_BIT to the left. In       *
         *  decimal, if we had 100, and wanted the next power of ten, we      *
         *  simply add on another zero (or "shift" one to the left)           *
         *  giving us 1000. This is the base 2^CHAR_BIT equivalent.           */
        power = power << CHAR_BIT;
    }

    /*  Now that the unsigned int part of our union is set to the appropriate *
     *  value, treat it as an unsigned char array by accessing this element   *
     *  of the union. Check the zeroth element to determine the endianness.   */
    if (e.arr[0] == 0U)
        return tmpl_LittleEndian;
    else if (e.arr[0] == sizeof(unsigned long int) - 1U)
        return tmpl_BigEndian;
    else if ((0U < e.arr[0]) && (e.arr[0] < sizeof(unsigned long int) - 1U))
        return tmpl_MixedEndian;
    else
        return tmpl_UnknownEndian;
}
/*  End of tmpl_Determine_Endianness.                                         */

