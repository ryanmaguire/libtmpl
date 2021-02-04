
#include <libtmpl/include/tmpl_bytes.h>

void tmpl_Swap_Bytes(char *ptr1, char *ptr2)
{
    char tmp;

    tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
    return;
}
