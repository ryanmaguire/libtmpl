#include <stdio.h>
#include <libtmpl/include/tmpl_bytes.h>

int main(void)
{
    tmpl_Endian e = tmpl_Determine_Endianness();

    if (e == tmpl_LittleEndian)
        printf("__TMPL_LITTLE_ENDIAN__");
    else if (e == tmpl_BigEndian)
        printf("__TMPL_BIG_ENDIAN__");
    else if (e == tmpl_MixedEndian)
        printf("__TMPL_MIXED_ENDIAN__");
    else
        printf("__TMPL_UNKNOWN_ENDIAN__");
    return 0;
}

