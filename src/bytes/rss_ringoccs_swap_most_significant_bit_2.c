
#include <libtmpl/include/tmpl_bytes.h>

void tmpl_Swap_Most_Significant_Bit_2(char *ptr)
{
    char tmp;

    tmp = ptr[0];
    ptr[0] = ptr[1];
    ptr[1] = tmp;
    return;
}
