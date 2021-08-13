#include <libtmpl/include/tmpl_string.h>

void tmpl_Remove_Spaces(char* s)
{
    const char* d = s;

    /*  If the input is NULL, the following will cause a segfault. Check.     */
    if (!s)
        return;

    do {
        while (*d == ' ') {
            ++d;
        }
    } while ((*s++ = *d++));
}

