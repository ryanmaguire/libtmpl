#include <libtmpl/include/tmpl_string.h>

void tmpl_Remove_Spaces(char* s)
{
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while ((*s++ = *d++));
}

