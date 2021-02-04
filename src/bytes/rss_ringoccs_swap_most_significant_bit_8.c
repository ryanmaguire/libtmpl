
#include <libtmpl/include/tmpl_bytes.h>

void tmpl_Swap_Most_Significant_Bit_8(char *ptr)
{
    tmpl_Swap_Bytes(&(ptr[0]), &(ptr[7]));
    tmpl_Swap_Bytes(&(ptr[1]), &(ptr[6]));
    tmpl_Swap_Bytes(&(ptr[2]), &(ptr[5]));
    tmpl_Swap_Bytes(&(ptr[3]), &(ptr[4]));
}
