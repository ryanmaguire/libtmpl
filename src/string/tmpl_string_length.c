#include <stddef.h>
#include <libtmpl/include/tmpl_string.h>

size_t tmpl_String_Length(const char *str)
{
    size_t string_length = (size_t)0;

    if (!str)
        return string_length;

    while (str[string_length])
    {
        string_length++;
    }

    return string_length;
}
