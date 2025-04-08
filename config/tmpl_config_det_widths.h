/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_DET_WIDTHS_H
#define TMPL_CONFIG_DET_WIDTHS_H

/*  Number of bits in char. char is not allowed to have padding, so all bits  *
 *  are used. This fact can be used to determine this value.                  */
static unsigned int TMPL_CHAR_BIT;

/*  The other integer data types are allowed to have padding. These numbers   *
 *  represent the number of unpadded bits.                                    */
static unsigned int TMPL_SHORT_BIT;
static unsigned int TMPL_INT_BIT;
static unsigned int TMPL_LONG_BIT;
#ifdef TMPL_LONG_LONG_IS_AVAILABLE
static unsigned int TMPL_LLONG_BIT;
#endif
static int TMPL_BITS_HAVE_BEEN_SET = 0;
static int TMPL_HAS_64_BIT_INT;
static int TMPL_HAS_32_BIT_INT;

/*  Function for determining the number of bits in char, and others.          */
static void tmpl_det_widths(void)
{
    unsigned char c = 0x01U;
    unsigned short int s = 1U;
    unsigned int i = 1U;
    unsigned long int l = 1UL;
#ifdef TMPL_LONG_LONG_IS_AVAILABLE
    unsigned long long int ll = 1ULL;
    TMPL_LLONG_BIT = 0U;
#endif
    TMPL_CHAR_BIT = 0U;
    TMPL_SHORT_BIT = 0U;
    TMPL_INT_BIT = 0U;
    TMPL_LONG_BIT = 0U;

    /*  Unsigned integer types can not overflow since the result is computed  *
     *  mod 2^N where N is the number of bits. By started with 1 and          *
     *  repeatedly multiplying by 2 we will eventually get 2^N, which will    *
     *  be computed as 0 mod 2^N. By counting the number of times we need to  *
     *  to multiply by 2 in order to get zero we can compute the number of    *
     *  bits in a char.                                                       */
    while (c != 0x00U)
    {
        c = c * 0x02U;
        TMPL_CHAR_BIT++;
    }

    /*  Similar idea for short, int, and long. These integer data types can   *
     *  have padding. The number computed is not necessarily the number of    *
     *  bits in a short, int, or long, just the number of used, or unpadded,  *
     *  bits. For most compilers this is the same as the size of the type and *
     *  no padding is actually used.                                          */
    while (s != 0U)
    {
        s = s * 2U;
        TMPL_SHORT_BIT++;
    }

    while (i != 0U)
    {
        i = i * 2U;
        TMPL_INT_BIT++;
    }

    while (l != 0UL)
    {
        l = l * 2UL;
        TMPL_LONG_BIT++;
    }

#ifdef TMPL_LONG_LONG_IS_AVAILABLE
    while (ll != 0ULL)
    {
        ll = ll * 2ULL;
        TMPL_LLONG_BIT++;
    }
#endif

    TMPL_BITS_HAVE_BEEN_SET = 1;

    if (TMPL_CHAR_BIT == 32)
        TMPL_HAS_32_BIT_INT = 1;
    else if (TMPL_SHORT_BIT == 32 && (TMPL_CHAR_BIT * sizeof(unsigned short int)) == 32)
        TMPL_HAS_32_BIT_INT = 1;
    else if (TMPL_INT_BIT == 32 && (TMPL_CHAR_BIT * sizeof(unsigned int)) == 32)
        TMPL_HAS_32_BIT_INT = 1;
    else if (TMPL_LONG_BIT == 32 && (TMPL_CHAR_BIT * sizeof(unsigned long int)) == 32)
        TMPL_HAS_32_BIT_INT = 1;
#ifdef TMPL_LONG_LONG_IS_AVAILABLE
    else if (TMPL_LLONG_BIT == 32 && (TMPL_CHAR_BIT * sizeof(unsigned long long int)) == 32)
        TMPL_HAS_32_BIT_INT = 1;
#endif
    else
        TMPL_HAS_32_BIT_INT = 0;

    if (TMPL_CHAR_BIT == 64)
        TMPL_HAS_64_BIT_INT = 1;
    else if (TMPL_SHORT_BIT == 64 && (TMPL_CHAR_BIT * sizeof(unsigned short int)) == 64)
        TMPL_HAS_64_BIT_INT = 1;
    else if (TMPL_INT_BIT == 64 && (TMPL_CHAR_BIT * sizeof(unsigned int)) == 64)
        TMPL_HAS_64_BIT_INT = 1;
    else if (TMPL_LONG_BIT == 64 && (TMPL_CHAR_BIT * sizeof(unsigned long int)) == 64)
        TMPL_HAS_64_BIT_INT = 1;
#ifdef TMPL_LONG_LONG_IS_AVAILABLE
    else if (TMPL_LLONG_BIT == 64 && (TMPL_CHAR_BIT * sizeof(unsigned long long int)) == 64)
        TMPL_HAS_64_BIT_INT = 1;
#endif
    else
        TMPL_HAS_64_BIT_INT = 0;
}
/*  End of tmpl_det_widths.                                                   */


#endif
/*  End of include guard.                                                     */
