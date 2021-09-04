/******************************************************************************
 *                                 LICENSE                                    *
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
 *                                det_end                                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This file is used in both the Makefile and make.sh shell script when  *
 *      libtmpl is built. It determines the endianness of your platform and   *
 *      creates the file include/tmpl_endianness.h in the process. This file  *
 *      is not directly part of libtmpl, but you'll need to run it for        *
 *      libtmpl to function properly. If your compiler gives you an error     *
 *      that libtmpl/include/tmpl_endianness.h was not found, run this.       *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) limits.h:                                                             *
 *          Standard C library header file containing the macro CHAR_BITS,    *
 *          which stores the number of bits in a byte.                        *
 *  2.) stdio.h:                                                              *
 *          Standard C library header file containing the fprintf function    *
 *          which we'll use to create the file include/tmpl_endianness.h.     *
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
 *  Date:       March 10, 2021                                                *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2021/04/26: Ryan Maguire                                                  *
 *      Made the code more portable by allowing CHAR_BIT to be any value.     *
 *  2021/08/24: Ryan Maguire                                                  *
 *      Removed string.h dependency and simplified a bit.                     *
 *  2021/09/3:  Ryan Maguire:                                                 *
 *      Added macro for floating-point endianness for IEEE-754 support.       *
 ******************************************************************************/

/*  Macros for determining the size of integer data types found here. In      *
 *  particular, the macro CHAR_BIT is here telling us how many bits in a byte.*/
#include <limits.h>

/*  Needed for FILE data type and fprintf.                                    */
#include <stdio.h>

/*  Function for creating include/tmpl_endianness.h.                          */
int main(void)
{
    /*  We'll use a union between an unsigned long int and an unsigned char   *
     *  array with as many elements as there are bytes in an unsigned long    *
     *  int. This is usually either 8 (unix-based, i.e. GNU, Linux, FreeBSD,  *
     *  macOS), or 4 (Microsoft Windows), but the value is not specified in   *
     *  the C standard.                                                       */
    union {
        unsigned long int n;
        unsigned char arr[sizeof(unsigned long int)];
    } e;

    /*  libtmpl has many tools that can take advantage of the IEEE-754        *
     *  floating point format, if your compiler supports it. The format does  *
     *  not specify the endianness of floating point numbers, so this         *
     *  function attempts to determine this. If your compiler does not        *
     *  support IEEE-754 format at all (most do in modern times), the         *
     *  endianness will be set to unknown and none of those tools will be     *
     *  used in libtmpl.                                                      */
#if defined(__STDC_IEC_559__)

    /*  The IEEE-754 format specifies that a 64-bit float is comprised of a   *
     *  sign bit (positive or negative), 11 bits for the exponent (the value  *
     *  b in the expression x = 1.m * 2^b), and 52 bits for the mantissa (the *
     *  value m in x = 1.m * 2^b). Big endian will have sign -> expo -> mant, *
     *  whereas little endian will have mant -> expo -> sign. Use a union     *
     *  with two structs and a double to determine which one, if either, is   *
     *  implemented.                                                          */
    union {

        /*  Store the bits in a bit-field. This allows us to store an exact   *
         *  number of bits (up to 16, per the standard) for a single variable *
         *  inside the struct. Use this to have 1 bit for the sign, 11 bits   *
         *  for the exponent, and 52 bits for the mantissa. Note, to avoid    *
         *  padding (adding extra redundant bits), Ensure that the 4-bit      *
         *  mantissa component is adjacent to the 11 bit exponent. This way   *
         *  the sign, exponent, and smallest mantissa component will occupy a *
         *  16 bit block and no padding will be needed.                       */
        struct _big_bits {
            unsigned int sign : 1;
            unsigned int expo : 11;
            unsigned int man0 : 4;
            unsigned int man1 : 16;
            unsigned int man2 : 16;
            unsigned int man3 : 16;
        } big_bits;

        /*  Little endianness is the reverse of big endianness.               */
        struct _little_bits {
            unsigned int man3 : 16;
            unsigned int man2 : 16;
            unsigned int man1 : 16;
            unsigned int man0 : 4;
            unsigned int expo : 11;
            unsigned int sign : 1;
        } little_bits;

        /*  And lastly, a double that the above structs are representing.     */
        double r;
    } d;

    /*  Same this for single precision.                                       */
    union {
        struct _big_bitsf {
            unsigned int sign : 1;
            unsigned int expo : 8;
            unsigned int man0 : 7;
            unsigned int man1 : 16;
        } big_bits;
        struct _little_bitsf {
            unsigned int man1 : 16;
            unsigned int man0 : 7;
            unsigned int expo : 8;
            unsigned int sign : 1;
        } little_bits;
        float r;
    } f;
#endif
/*  End of #if defined(__STDC_IEC_559__).                                     */

    /*  n is for indexing and power keeps track of the power of an integer.   */
    unsigned long int n, power;

    /*  And lastly, open the file include/tmpl_endianness.h using fopen and   *
     *  give the file write permissions.                                      */
    FILE *fp = fopen("./include/tmpl_endianness.h", "w");

    /*  If fopen fails, it returns NULL. Check that it did not.               */
    if (fp == NULL)
    {
        puts("Error Encountered: libtmpl\n"
             "    det_end.c\n"
             "fopen returned NULL for FILE *fp. Aborting.\n");
        return -1;
    }

    /*  The idea is as follows. Create the integer 76543210, store this in the*
     *  unsigned long int part of our union, and then check the array part to *
     *  see which element is 0. This would work if computers are base 10, but *
     *  they usually use base 2, base 8, or base 16. Letting N be the base,   *
     *  we'll store the number 7*N^7 + 6*N^6 + ... + 2*N^2 + 1*N + 0. The     *
     *  array will then be:                                                   *
     *      ---------------------------------                                 *
     *      | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |                                 *
     *      ---------------------------------                                 *
     *  This is assuming sizeof(unsigned long int) = 8. If it is some other   *
     *  value, the array will be 0 up to that number. We'll start by          *
     *  initializing the unsigned long int part of the union to 0.            */
    e.n = 0UL;

    /*  We need to set power to 2^(number of bits in a byte). This number is  *
     *  found in limits.h as CHAR_BIT. We're going to write out the number as *
     *  7 * power^7 + 6 * power^6 + ... + 2 * power^2 + power + 0. If we      *
     *  somehow had a base-10 computer, this would be                         *
     *  7*10^7 + 6*10^6 + ... + 2*10^2 + 1*10 + 0 = 76543210.                 *
     *  We want this in base 2^CHAR_BIT. We can compute 2^CHAR_BIT quickly    *
     *  using bitwise operators. 1 << N is the number 1000...000 in binary    *
     *  with N 0's. This would be the number 2^N in decimal, which is what    *
     *  we want. We compute 2^CHAR_BIT via 1UL << CHAR_BIT. UL means unsigned *
     *  long, which is the data type of power.                                */
    power = 1UL << CHAR_BIT;

    /*  Write out 76543210 in base 2^CHAR_BIT by adding.                      */
    for (n = 1UL; n < sizeof(unsigned long int); ++n)
    {
        e.n += n * power;

        /*  From power^k we can get power^(k+1) by shifting the "decimal"     *
         *  CHAR_BIT to the right. In decimal, if we had 100 and want 1000,   *
         *  we'd write 100.00, shift the decimal to the right, and get 1000.0.*
         *  Writing pow = pow << CHAR_BIT is the base 2^CHAR_BIT equivalent.  */
        power = power << CHAR_BIT;
    }

    /*  Create the file include/tmpl_endianness.h and return.                 */
    fprintf(fp, "/******************************************************************************\n");
    fprintf(fp, " *                                 LICENSE                                    *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  This file is part of libtmpl.                                             *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  libtmpl is free software: you can redistribute it and/or modify           *\n");
    fprintf(fp, " *  it under the terms of the GNU General Public License as published by      *\n");
    fprintf(fp, " *  the Free Software Foundation, either version 3 of the License, or         *\n");
    fprintf(fp, " *  (at your option) any later version.                                       *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  libtmpl is distributed in the hope that it will be useful,                *\n");
    fprintf(fp, " *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *\n");
    fprintf(fp, " *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *\n");
    fprintf(fp, " *  GNU General Public License for more details.                              *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  You should have received a copy of the GNU General Public License         *\n");
    fprintf(fp, " *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *                              tmpl_endianness                               *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  Purpose:                                                                  *\n");
    fprintf(fp, " *      This file is created by the det_enc.c file. It provides the macros    *\n");
    fprintf(fp, " *      TMPL_ENDIANNESS, TMPL_FLOAT_ENDIANNESS, and TMPL_DOUBLE_ENDIANNESS    *\n");
    fprintf(fp, " *      which are used functions where the code is endian specific.           *\n");
    fprintf(fp, " ******************************************************************************/\n");
    fprintf(fp, "#ifndef TMPL_ENDIANNESS_H\n");
    fprintf(fp, "#define TMPL_ENDIANNESS_H\n\n");
    fprintf(fp, "#define TMPL_BIG_ENDIAN 0\n");
    fprintf(fp, "#define TMPL_LITTLE_ENDIAN 1\n");
    fprintf(fp, "#define TMPL_MIXED_ENDIAN 2\n");
    fprintf(fp, "#define TMPL_UNKNOWN_ENDIAN 3\n\n");

    /*  We now have 76543210 in the array part of the union (or n-1...210 if  *
     *  sizeof(unsigned long int) = n). If the zeroth entry of the array is   *
     *  0, we have little endian. If it is n-1, we have big endian. Anything  *
     *  between 0 and n-1 is mixed endian, and any other result is unknown.   *
     *  There is one, extremely rare, exceptional case that needs to be       *
     *  handled separately. If sizeof(unsigned long int) = 1, then the char   *
     *  array will have one element, which is the same number as the unsigned *
     *  long int value. Because of this we would be unable to determine the   *
     *  endianness. If this is true, return unknown endian. I know of no      *
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

        /*  Omitting comments since this is the exact same as before.         */
        union {
            unsigned long long int x;
            unsigned char arr[sizeof(unsigned long long int)];
        } ell;

        unsigned long long int powerll, kll;

        /*  The ULL suffix means unsigned long long.                          */
        ell.x = 0ULL;
        powerll = 1ULL << CHAR_BIT;

        for (kll = 1ULL; kll < sizeof(unsigned long long int); ++kll)
        {
            ell.x += kll * powerll;
            powerll = powerll << CHAR_BIT;
        }

        if (sizeof(unsigned long long int) == 1)
            fprintf(fp, "#define TMPL_ENDIANNESS TMPL_UNKNOWN_ENDIAN\n");
        else if (ell.arr[0] == 0U)
            fprintf(fp, "#define TMPL_ENDIANNESS TMPL_LITTLE_ENDIAN\n");
        else if (ell.arr[0] == sizeof(unsigned long long int) - 1U)
            fprintf(fp, "#define TMPL_ENDIANNESS TMPL_BIG_ENDIAN\n");
        else if (ell.arr[0] < sizeof(unsigned long long int) - 1U)
            fprintf(fp, "#define TMPL_ENDIANNESS TMPL_MIXED_ENDIAN\n");
        else
            fprintf(fp, "#define TMPL_ENDIANNESS TMPL_UNKNOWN_ENDIAN\n");

#else
/*  Else for #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.    */

        /*  If we get here, sizeof(unsigned long int) = 1 and your compiler   *
         *  does not support the C99, or higher, standard so unsigned long    *
         *  long int may not be defined. Return unknown.                      */
        fprintf(fp, "#define TMPL_ENDIANNESS TMPL_UNKNOWN_ENDIAN\n");
#endif
/*  End of #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.      */

    }
    /* End of if (sizeof(unsigned long int) == 1).                            */

    else if (e.arr[0] == 0)
        fprintf(fp, "#define TMPL_ENDIANNESS TMPL_LITTLE_ENDIAN\n");
    else if (e.arr[0] == (sizeof(unsigned long int) - 1))
        fprintf(fp, "#define TMPL_ENDIANNESS TMPL_BIG_ENDIAN\n");
    else if ((0 < e.arr[0]) && (e.arr[0] < (sizeof(unsigned long int) - 1)))
        fprintf(fp, "#define TMPL_ENDIANNESS TMPL_MIXED_ENDIAN\n");
    else
        fprintf(fp, "#define TMPL_ENDIANNESS TMPL_UNKNOWN_ENDIAN\n");

    /*  Now that integer endianness has been determined, try floating point.  *
     *  It is almost always the same as integer, but on certain ARM           *
     *  processors it is different.                                           */
#if defined(__STDC_IEC_559__)

    /*  Set the bits in the struct to represent the number 1.0 using the      *
     *  IEEE-754 format. If the endianness is flipped, we should get          *
     *  gibberish, whereas if its correct we should get 1.0.                  */
    f.little_bits.sign = 0x0U;
    f.little_bits.expo = 0x7FU;
    f.little_bits.man0 = 0x0U;
    f.little_bits.man1 = 0x0U;

    /*  If the float in the union is actual 1, we have IEEE-754 support and   *
     *  we have little endianness for float.                                  */
    if (f.r == 1.0F)
        fprintf(fp, "#define TMPL_FLOAT_ENDIANNESS TMPL_LITTLE_ENDIAN\n");

    /*  Otherwise, try big endianness.                                        */
    else
    {
        f.big_bits.sign = 0x0U;
        f.big_bits.expo = 0x7FU;
        f.big_bits.man0 = 0x0U;
        f.big_bits.man1 = 0x0U;

        if (f.r == 1.0F)
            fprintf(fp, "#define TMPL_FLOAT_ENDIANNESS TMPL_BIG_ENDIAN\n");
        else
            fprintf(fp, "#define TMPL_FLOAT_ENDIANNESS TMPL_UNKNOWN_ENDIAN\n");
    }

    /*  Do the same with with double.                                         */
    d.little_bits.sign = 0x0U;
    d.little_bits.expo = 0x3FFU;
    d.little_bits.man0 = 0x0U;
    d.little_bits.man1 = 0x0U;
    d.little_bits.man2 = 0x0U;
    d.little_bits.man3 = 0x0U;

    /*  If the double in the union is actual 1, we have IEEE-754 support and  *
     *  we have big endianness for double.                                    */
    if (d.r == 1.0)
        fprintf(fp, "#define TMPL_DOUBLE_ENDIANNESS TMPL_LITTLE_ENDIAN\n");

    /*  Otherwise, try big endian.                                            */
    else
    {
        d.big_bits.sign = 0x0U;
        d.big_bits.expo = 0x3FFU;
        d.big_bits.man0 = 0x0U;
        d.big_bits.man1 = 0x0U;
        d.big_bits.man2 = 0x0U;
        d.big_bits.man3 = 0x0U;

        if (d.r == 1.0)
            fprintf(fp, "#define TMPL_DOUBLE_ENDIANNESS TMPL_BIG_ENDIAN\n");
        else
            fprintf(fp, "#define TMPL_DOUBLE_ENDIANNESS TMPL_UNKNOWN_ENDIAN\n");
    }
#else

    /*  Define the floating-point endianness macro.                           */
    fprintf(fp, "#define TMPL_FLOAT_ENDIANNESS TMPL_UNKNOWN_ENDIAN\n");
    fprintf(fp, "#define TMPL_DOUBLE_ENDIANNESS TMPL_UNKNOWN_ENDIAN\n");

#endif

    /*  Print the end of the include guard.                                   */
    fprintf(fp, "\n#endif\n");
    return 0;
}
/*  End of main.                                                              */

