
#include <libtmpl/include/tmpl_bytes.h>

void tmpl_Swap_Most_Significant_Bit_4(char *ptr)
{
    tmpl_Swap_Bytes(&(ptr[0]), &(ptr[3]));
    tmpl_Swap_Bytes(&(ptr[1]), &(ptr[2]));
}
